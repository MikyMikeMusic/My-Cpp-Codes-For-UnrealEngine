// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundLocalization.h"

// Sets default values for this component's properties
USoundLocalization::USoundLocalization()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RightEar = CreateDefaultSubobject<UAudioComponent>(TEXT("RightEar"));
	LeftEar = CreateDefaultSubobject<UAudioComponent>(TEXT("LeftEar"));

	// Ensure the audio components are properly initialized
	if (RightEar)
	{
		RightEar->bAutoActivate = false;//attiva il suono
		RightEar->bEnableLowPassFilter = true;//attiva il filtro
	}
	if (LeftEar)
	{
		LeftEar->bAutoActivate = false;//attiva il suono
		LeftEar->bEnableLowPassFilter = true;//attiva il filtro
	}
}

// Called when the game starts
void USoundLocalization::BeginPlay()
{
	Super::BeginPlay();
	
	//Set PreviousDistance to the initial distance between the actor and the camera 
	PreviousDistance = FVector::Dist(ActorLocation, CameraLocation);

	//Store the owner, world and player controller
	Owner = GetOwner();
	World = GetWorld();
	PlayerController = World->GetFirstPlayerController();

	// Attach the audio components to the actor
	RightEar->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);//attacca il suono all'attore
	LeftEar->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);//attacca il suono all'attore
}

void USoundLocalization::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Debug messages	
	float newVolumeMultiplierR = RightEar->VolumeMultiplier;
	float newVolumeMultiplierL = LeftEar->VolumeMultiplier;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("VolumeMultiplierR: %f"), newVolumeMultiplierR));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("VolumeMultiplierL: %f"), newVolumeMultiplierL));

	// Update frequently used values
	if (Owner)
	{
		ActorLocation = Owner->GetActorLocation();
	}
	// Get the camera location
	if (PlayerController && PlayerController->PlayerCameraManager)
	{
		CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
	}
	// Move the actor to the right
	if (Owner)
	{
		FVector NewLocation = ActorLocation + FVector(1, 0, 0);
		Owner->SetActorLocation(NewLocation);
	}

	// Calculate the distance between the actor and the camera, this istance is differente because is used to calculate the attenuation
	float Distance = FVector::Dist(ActorLocation, CameraLocation);

	// Calculate the distance in motion between the actor and the camera
	float DistanceInMotion = Distance - PreviousDistance;

	// Update the previous distance with the current distance
	PreviousDistance = Distance;

	//MaxDistance is the maximum distance that the sound can reach
	float MaxDistance = 10000.0f;

	//Attenuation is the value that will be used to decrease the volume of the sound
	float Attenuation = FMath::Clamp(1.0f - Distance / MaxDistance, 0.05f, 1.0f);

	//DirectionToCamera is the vector that goes from the actor to the camera before normalization 
	FVector DirectionToCamera = CameraLocation - ActorLocation;
	DirectionToCamera.Normalize();

	// Draw a debug line from the actor to the camera
	if (GEngine)
	{
		DrawDebugLine(
			GetWorld(),
			ActorLocation,
			ActorLocation + DirectionToCamera * 100.0f, 
			FColor::Red,
			false, 0.0f, 0,
			10.0f 
		);
	}

	//
	FVector ActorForward;
	if (Owner)
	{
		ActorForward = Owner->GetActorForwardVector();
		ActorForward.Normalize();
	}

	//Get the camera rotation
	FRotator CameraRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

	//Attributes to store the yaw and pitch of the camera
	float CameraYaw = CameraRotation.Yaw;
	float CameraPitch = CameraRotation.Pitch;
	//Calculate the angle between the actor and the camera using CameraYaw 
	float Angle = FMath::Fmod(CameraYaw, 360.0f);
	//Normalize the angle between -1 and 1 to use it as a stereo pan value -1 is left, 1 is right
	float NormalizedAngle = (Angle - 180.0f) / 180.0f;

	//If statement to set the stereo pan value of the audio components with SetFloatParameter
	if (RightEar)
	{
		float ClampedAngle = FMath::Clamp(-NormalizedAngle, 0.0f, 1.0f);
		RightEar->SetFloatParameter(FName("StereoPan"), ClampedAngle);
	}
	if (LeftEar)
	{
		float ClampedAngle = FMath::Clamp(-NormalizedAngle, -1.0f, 0.0f);
		LeftEar->SetFloatParameter(FName("StereoPan"), ClampedAngle);
	}

	//Set the volume with the Attenuation value
	RightEar->SetVolumeMultiplier(Attenuation);
	LeftEar->SetVolumeMultiplier(Attenuation);
}

//Function to start playing the sound
void USoundLocalization::StartPlayingSound()
{
	if (RightEar)
	{

		RightEar->Play();
	}
	if (LeftEar)
	{
		LeftEar->Play();
	}
}
