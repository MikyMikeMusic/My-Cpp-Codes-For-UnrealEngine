// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "SoundLocalization.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGSTUFFSOUNDS_API USoundLocalization : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USoundLocalization();

private:
	//Right and left ear audio components for simulating sound localization
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound Localization", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* RightEar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound Localization", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* LeftEar;
	//Other useful attributes for sound localization
	AActor* Owner;
	UWorld* World;
	APlayerController* PlayerController;
	FVector ActorLocation;
	FVector CameraLocation;

protected:
	float FadeInTime = 0.1f;
	float PreviousDistance;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Function to get the right and left ear audio components
	FORCEINLINE UAudioComponent* GetRightEar() const { return RightEar; }
	FORCEINLINE UAudioComponent* GetLeftEar() const { return LeftEar; }

	//Function to set the sound to play
	UFUNCTION(BlueprintCallable , Category = "Sound Localization")
	void StartPlayingSound();
};
