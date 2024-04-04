// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "AudioSorter.generated.h"

UCLASS()
class TESTINGSOUNDS_API AAudioSorter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAudioSorter();

private:
	//The sounds to be sorted
	UPROPERTY()
	TArray<USoundBase*> Sounds;

	//Memoization array, memo[i] stores the length of Sounds[i]
	UPROPERTY()
	TArray<float> memo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Set the sounds to be sorted
	UFUNCTION(BlueprintCallable, Category = "AudioSort")
	FORCEINLINE void SetSounds(TArray<USoundBase*> newSounds)
	{
		Sounds = newSounds;
		memo.Init(-1, Sounds.Num());
	}

	//Sort the sounds by length
	UFUNCTION(BlueprintCallable, Category = "AudioSort")
	TArray<USoundBase*> SortAudioComponents();

	//Sort the sounds by name, with quicksort algorithm
	UFUNCTION(BlueprintCallable, Category = "AudioSort")
	TArray<USoundBase*> SortByName();

private: 
	//Bubble sort algorithm
	void BubbleSort();

	//Get the length of the sound at index
	float GetAudioLength(int index);
};
