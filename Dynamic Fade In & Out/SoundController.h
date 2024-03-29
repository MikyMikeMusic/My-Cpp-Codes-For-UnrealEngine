#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Components/TimelineComponent.h"
#include "SoundController.generated.h"

UCLASS()
class TESTINGSTUFFSOUNDS_API ASoundController : public AActor
{
	GENERATED_BODY()

public:
	ASoundController();

	//Play the sound
	UFUNCTION(BlueprintCallable, Category = "Sound Controller")
	void PlaySound();
	
	//Fade Out and In the sound
	UFUNCTION()
	void FadeInSound();
	
	UFUNCTION()
	void FadeOutSound();

	//Start the timer to play the sound for  certain amount of time with a Fade Out or Fade In
	UFUNCTION(BlueprintCallable, Category = "Sound Controller")
	void StartFadeInSoundTimer(float Delay);

	UFUNCTION(BlueprintCallable, Category = "Sound Controller")
	void StartFadeOutSoundTimer(float Delay);

	//Fade the volume of the sound, called by the timer
	UFUNCTION()
	FORCEINLINE void FadeVolumeIn(float Value)
	{
		if (CachedAudioComponent)
		{
			CachedAudioComponent->SetVolumeMultiplier(Value);
		}
	}

	UFUNCTION()
	FORCEINLINE void FadeVolumeOut(float Value)
	{
		if (CachedAudioComponent)
		{
			CachedAudioComponent->SetVolumeMultiplier(Value);
		}
	}

	//Getters and Setters
	UFUNCTION(BlueprintCallable, Category = "Sound Controller")
	FORCEINLINE USoundBase* GetSoundToPlay() const
	{
		return SoundToPlay;
	}

	UFUNCTION(BlueprintCallable, Category = "Sound Controller")
	FORCEINLINE void SetSoundToPlay(USoundBase* NewSound)
	{
		if (CachedAudioComponent)
		{
			CachedAudioComponent->OnAudioFinished.RemoveDynamic(this, &ASoundController::HandleSoundEnd);
		}

		SoundToPlay = NewSound;
	}

	UFUNCTION(BlueprintCallable, Category = "Sound Controller")
	FORCEINLINE void SetFadeOutCurve(UCurveFloat* NewCurve)
	{
		FadeOutCurve = NewCurve;
	}

	UFUNCTION(BlueprintCallable, Category = "Sound Controller")
	FORCEINLINE void SetFadeInCurve(UCurveFloat* NewCurve)
	{
		FadeInCurve = NewCurve;
	}
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void HandleSoundEnd();

private:
	UPROPERTY(EditAnywhere, Category = "Sound Controller")
	USoundBase* SoundToPlay;

	UPROPERTY(EditAnywhere, Category = "Sound Controller")
	UCurveFloat* FadeOutCurve;

	UPROPERTY(EditAnywhere, Category = "Sound Controller")
	UCurveFloat* FadeInCurve;

	UPROPERTY(EditAnywhere, Category = "Sound Controller")
	float FadeOutDelay;

	UPROPERTY(EditAnywhere, Category = "Sound Controller")
	float FadeInDelay;

	FOnTimelineFloat CachedFadeOutTimelineDelegate;
	FTimerHandle CachedPlaySoundTimerHandle;

	UPROPERTY()
	UTimelineComponent* CachedFadeOutTimeline;
	UPROPERTY()
	UTimelineComponent* CachedFadeInTimeline;

public:
	UPROPERTY()
	UAudioComponent* CachedAudioComponent;
};