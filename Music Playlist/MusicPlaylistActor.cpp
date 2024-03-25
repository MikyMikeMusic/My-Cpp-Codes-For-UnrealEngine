#include "MusicPlaylistActor.h"
#include "Engine/Engine.h"

AMusicPlaylistActor::AMusicPlaylistActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsPlaying = false;
	bIsShuffling = false;

	CurrentTrackIndex = 0;
}

void AMusicPlaylistActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMusicPlaylistActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMusicPlaylistActor::Play()
{
	if (CurrentTrackIndex < Tracks.Num())
	{
		UAudioComponent* CurrentTrack = Tracks[CurrentTrackIndex];
		if (CurrentTrack && !CurrentTrack->IsPlaying())
		{
			CurrentTrack->Play();
			bIsPlaying = true;
			FString Message = FString::Printf(TEXT("Playback started: %s"), *TrackNames[CurrentTrack]);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
		}
	}
}

void AMusicPlaylistActor::Stop()
{
	if (CurrentTrackIndex < Tracks.Num())
	{
		UAudioComponent* CurrentTrack = Tracks[CurrentTrackIndex];
		if (CurrentTrack && CurrentTrack->IsPlaying())
		{
			CurrentTrack->Stop();
			bIsPlaying = false;
			UE_LOG(LogTemp, Warning, TEXT("Playback stopped."));
		}
	}
}

void AMusicPlaylistActor::Next()
{
	Stop();
	CurrentTrackIndex = (CurrentTrackIndex + 1) % Tracks.Num();
	Play();
}

void AMusicPlaylistActor::Previous()
{
	Stop();
	CurrentTrackIndex = (CurrentTrackIndex - 1 + Tracks.Num()) % Tracks.Num();
	Play();
}

void AMusicPlaylistActor::Shuffle()
{
	if (Tracks.Num() > 1)
	{
		for (int32 i = Tracks.Num() - 1; i > 0; --i)
		{
			int32 j = FMath::RandRange(0, i);
			Tracks.Swap(i, j);
		}
		CurrentTrackIndex = 0;
	}
}

void AMusicPlaylistActor::AddTrack(FString TrackName, USoundBase* Track)
{
	if (Track)
	{
		UAudioComponent* AudioComponent = NewObject<UAudioComponent>(this);
		AudioComponent->SetSound(Track);
		Tracks.Add(AudioComponent);
		TrackMap.Add(TrackName, AudioComponent);
		TrackNames.Add(AudioComponent, TrackName);
	}
}

void AMusicPlaylistActor::GetTrackByName(FString TrackName)
{
	if (UAudioComponent** TrackPtr = TrackMap.Find(TrackName))
	{
		UAudioComponent* Track = *TrackPtr;
		Track->Play();
	}
}









