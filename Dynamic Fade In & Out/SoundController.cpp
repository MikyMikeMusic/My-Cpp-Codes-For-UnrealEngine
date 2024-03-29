// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundController.h"

ASoundController::ASoundController()
{
	PrimaryActorTick.bCanEverTick = true;

	CachedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = CachedAudioComponent;
	CachedAudioComponent->bAutoActivate = false;
	SoundToPlay = nullptr;

	CachedFadeOutTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FadeOutTimeline"));
	CachedFadeInTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("FadeInTimeline"));

}

void ASoundController::BeginPlay()
{
	Super::BeginPlay();
}

void ASoundController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (GEngine && CachedAudioComponent)
	{
		float CurrentVolume = CachedAudioComponent->VolumeMultiplier;
		/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Current Volume: %f"), CurrentVolume));*/
	}
}

//Play the sound
void ASoundController::PlaySound()
{
	if (SoundToPlay && CachedAudioComponent)
	{
		CachedAudioComponent->SetSound(SoundToPlay);
		CachedAudioComponent->OnAudioFinished.AddDynamic(this, &ASoundController::HandleSoundEnd);
		CachedAudioComponent->Play();
	}
}

//Fade Out and In the sound

void ASoundController::FadeInSound()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("FadeInSound called"));
	}

	if (!CachedAudioComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CachedAudioComponent is null"));
		return;
	}

	if (!CachedFadeInTimeline)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CachedFadeInTimeline is null"));
		return;
	}

	if (!FadeInCurve)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CachedFadeInCurve is null"));
		return;
	}

	FOnTimelineFloat onTimelineCallback;
	onTimelineCallback.BindUFunction(this, FName("FadeVolumeIn"));
	CachedFadeInTimeline->AddInterpFloat(FadeInCurve, onTimelineCallback);
	CachedFadeInTimeline->PlayFromStart();

	PlaySound();
}

void ASoundController::FadeOutSound()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("FadeOutSound called"));
	}

	if (!CachedAudioComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CachedAudioComponent is null"));
		return;
	}

	if (!CachedFadeOutTimeline)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CachedFadeOutTimeline is null"));
		return;
	}

	if (!FadeOutCurve)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CachedFadeOutCurve is null"));
		return;
	}

	FOnTimelineFloat onTimelineCallback;
	onTimelineCallback.BindUFunction(this, FName("FadeVolumeOut"));
	CachedFadeOutTimeline->AddInterpFloat(FadeOutCurve, onTimelineCallback);
	CachedFadeOutTimeline->PlayFromStart();
}

//Start the timer to play the sound for  certain amount of time with a Fade Out or Fade In

void ASoundController::StartFadeInSoundTimer(float Delay)
{
	if (GetWorld())
	{
		FadeInDelay = Delay;

		if (FadeOutDelay >= 0)
		{
			GetWorld()->GetTimerManager().SetTimer(CachedPlaySoundTimerHandle, this, &ASoundController::FadeInSound, FadeInDelay, false);
			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("StartFadeInSoundTimer called"));
			}*/
		}
	}
}

void ASoundController::StartFadeOutSoundTimer(float Delay)
{
	if (GetWorld())
	{
		FadeOutDelay = Delay;

		if (FadeOutDelay >= 0)
		{
			GetWorld()->GetTimerManager().SetTimer(CachedPlaySoundTimerHandle, this, &ASoundController::FadeOutSound, FadeOutDelay, false);
			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Timer set for FadeOutSound"));
			}*/
		}
	}
}

//Delegates

void ASoundController::HandleSoundEnd()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sound Ended"));
	}
}
