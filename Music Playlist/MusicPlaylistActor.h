#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Components/TextRenderComponent.h"
#include "Containers/Map.h"
#include "Containers/Array.h"
#include "MusicPlaylistActor.generated.h"

UCLASS(Blueprintable)
class TESTINGSTUFFSOUNDS_API AMusicPlaylistActor : public AActor
{
	GENERATED_BODY()
private:
	TArray<UAudioComponent*> Tracks;
	TMap <FString, UAudioComponent*> TrackMap;
	TMap<UAudioComponent*, FString> TrackNames;
	TQueue<UAudioComponent*> TrackQueue;
	int32 CurrentTrackIndex; // Aggiungi questa linea

	bool bIsPlaying;
	bool bIsShuffling;

public:
	AMusicPlaylistActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE bool GetIsPlaying() const { return bIsPlaying; }
	FORCEINLINE bool GetIsShuffling() const { return bIsShuffling; }
	FORCEINLINE void SetIsPlaying(bool bPlaying) { bIsPlaying = bPlaying; }
	FORCEINLINE void SetIsShuffling(bool bShuffling) { bIsShuffling = bShuffling; }

	UFUNCTION(BlueprintCallable, Category = "Music Playlist")
	void Play();
	UFUNCTION(BlueprintCallable, Category = "Music Playlist")
	void Stop();
	UFUNCTION(BlueprintCallable, Category = "Music Playlist")
	void Next();
	UFUNCTION(BlueprintCallable, Category = "Music Playlist")
	void Previous();
	UFUNCTION(BlueprintCallable, Category = "Music Playlist")
	void Shuffle();
	UFUNCTION(BlueprintCallable, Category = "Music Playlist")
	void AddTrack(FString TrackName, USoundBase* Track);
	UFUNCTION(BlueprintCallable, Category = "Music Playlist")
	int32 GetTrackCount() const { return Tracks.Num(); }
	UFUNCTION(BlueprintCallable, Category = "Music Playlist")
	void GetTrackByName(FString TrackName);
};