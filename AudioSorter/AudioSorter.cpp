// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioSorter.h"

// Sets default values
AAudioSorter::AAudioSorter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sounds = TArray<USoundBase*>();
	memo = TArray<float>();
}

// Called when the game starts or when spawned
void AAudioSorter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAudioSorter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AAudioSorter::GetAudioLength(int index)
{
	if (memo[index] != -1)
	{
		return memo[index];
	}
	else
	{
		float length = Sounds[index]->Duration;
		memo[index] = length;
		return length;
	}
}

TArray<USoundBase*> AAudioSorter::SortAudioComponents()
{
	BubbleSort();
	return Sounds;
}

TArray<USoundBase*> AAudioSorter::SortByName()
{
	Sounds.Sort([](const USoundBase& A, const USoundBase& B) {
		return A.GetName() > B.GetName();
	});
	return Sounds;
}

void AAudioSorter::BubbleSort()
{
	int i, j;
	for (i = 0; i < Sounds.Num() - 1; i++)
	{
		for (j = 0; j < Sounds.Num() - i - 1; j++)
		{
			if (GetAudioLength(j) > GetAudioLength(j + 1))
			{
				Sounds.Swap(j, j + 1);
			}
		}
	}
}

