// Fill out your copyright notice in the Description page of Project Settings.


#include "DopplerEffect.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADopplerEffect::ADopplerEffect()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));//create an audio component
	SetRootComponent(_AudioComponent);//set the audio component as the root component
	_AudioComponent->bAutoActivate = false;

}

// Called when the game starts or when spawned
void ADopplerEffect::BeginPlay()
{
	Super::BeginPlay();
	_AudioComponent->Play(); // Play the audio component
	if (_AudioComponent->IsPlaying()) // If the audio component is playing
	{
		// Print on the screen that the audio component is playing
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Audio Component is playing"));
	}
	else // If the audio component is not playing
	{
		// Print on the screen that the audio component is not playing
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Audio Component is not playing"));
	}

	CurrentLocation = GetActorLocation(); // Get the location of this actor and store it in a variable
	//print on the screen the location of the sound source
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Sound Source Location: %s"), *CurrentLocation.ToString()));
}

// Called every frame
void ADopplerEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//set the location of this actor every time the tick function is called
	CurrentLocation.X += speed * DeltaTime;

	SetActorLocation(CurrentLocation); // Set the location of this actor to the new location

}

void ADopplerEffect::DopplerEffect()
{
	CurrentLocation = GetActorLocation();
	//Get the listener location
	FVector ListenerLocation = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraLocation();

	// Print on the screen the location of the sound source
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Sound Source Location: %s"), *CurrentLocation.ToString()));

	// Print on the screen the location of the listener
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Listener Location: %s"), *ListenerLocation.ToString()));

	FVector RelativeVelocity = ListenerLocation - CurrentLocation; // Calculate the relative velocity between the listener and the sound source

	// Calculate the Doppler effect and store it in a variable
	float DopplerEffect = (SpeedOfSound + RelativeVelocity.Size()) / (SpeedOfSound - RelativeVelocity.Size());

	if (_AudioComponent)
	{
		_AudioComponent->SetPitchMultiplier(DopplerEffect); // Set the pitch of the audio component to the calculated Doppler effect
		_AudioComponent->Play(); // Play the audio component
	}

	PreviousLocation = CurrentLocation; // Store the current location in the previous location variable
}














