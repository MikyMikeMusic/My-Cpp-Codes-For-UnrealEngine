// SoundSource.h
#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "SoundSource.generated.h"

UCLASS(Blueprintable)
class MODULETEST_API ASoundSource : public AActor
{
	GENERATED_BODY()

public:
	ASoundSource();

	// Initializes an array of SoundSources with the given sounds, positions them, and connects them all together.
	UFUNCTION(BlueprintCallable, Category = "Sound Source")
	TArray<ASoundSource*> InitializeAndPositionSoundSources(TArray<USoundBase*> SoundsArray);

	// Returns the sound associated with this sound source. Returns nullptr if no sound is set.
	UFUNCTION()
	FORCEINLINE USoundBase* GetAssociatedSound() const { return Sound; }

	// Sets the sound to be associated with this sound source.
	UFUNCTION()
	FORCEINLINE void SetAssociatedSound(USoundBase* NewSound) { Sound = NewSound; }

	// Performs a depth-first search (DFS) starting from the given sound source.
	UFUNCTION(BlueprintCallable, Category = "Sound Source")
	void PerformDFS(ASoundSource* StartSource, TMap<ASoundSource*, bool>& VisitedNodes, int MaxDepth, int CurrentDepth);

private:

	//Sound associated with this sound source
	UPROPERTY()
	USoundBase* Sound;

	//Audio component for this sound source
	UPROPERTY()
	UAudioComponent* AudioComponent;

	//Connections to other sound sources
	UPROPERTY()
	TArray<ASoundSource*> Connections;

	// Marks the given node as visited.
	FORCEINLINE void MarkNodeAsVisited(ASoundSource* Node, TMap<ASoundSource*, bool>& VisitedNodes) { VisitedNodes.Add(Node, true); }

	// Plays the sound at the given node.
	void PlaySoundAtNode(ASoundSource* Node);

	// Prints the position of the given node.
	void PrintNodePosition(ASoundSource* Node);
};