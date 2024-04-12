// SoundSource.cpp
#include "SoundSource.h"

ASoundSource::ASoundSource()
	: Sound(nullptr)
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
}

TArray<ASoundSource*> ASoundSource::InitializeAndPositionSoundSources(TArray<USoundBase*> SoundsArray)
{
	TArray<ASoundSource*> SoundSources;

	// Define the bounds of your game environment
	FVector MinBounds(-5000.0f, -5000.0f, 0.0f);
	FVector MaxBounds(5000.0f, 5000.0f, 2000.0f);

	// Get the current game world
	UWorld* World = GetWorld();

	// Check if the world exists
	if (World)
	{
		// Create a new SoundSource for each sound
		for (USoundBase* SoundElement : SoundsArray)
		{
			// Spawn a new SoundSource and add it to the game world
			ASoundSource* NewSoundSource = World->SpawnActor<ASoundSource>();

			NewSoundSource->SetAssociatedSound(SoundElement);

			// Generate a random position within the bounds
			FVector NewLocation;
			NewLocation.X = FMath::RandRange(MinBounds.X, MaxBounds.X);
			NewLocation.Y = FMath::RandRange(MinBounds.Y, MaxBounds.Y);
			NewLocation.Z = FMath::RandRange(MinBounds.Z, MaxBounds.Z);

			// Set the sound source's position to the new location
			NewSoundSource->SetActorLocation(NewLocation);

			SoundSources.Add(NewSoundSource);
		}
	}

	// Connect all the SoundSources together
	for (ASoundSource* SoundSource : SoundSources)
	{
		for (ASoundSource* OtherSoundSource : SoundSources)
		{
			if (SoundSource != OtherSoundSource)
			{
				SoundSource->Connections.Add(OtherSoundSource);
			}
		}
	}

	// Return the array of SoundSources
	return SoundSources;
}

void ASoundSource::PerformDFS(ASoundSource* StartSource, TMap<ASoundSource*, bool>& VisitedNodes, int MaxDepth, int CurrentDepth)
{
	if (!StartSource || VisitedNodes.Contains(StartSource) || CurrentDepth > MaxDepth)
	{
		return;
	}

	// Mark the current node as visited
	MarkNodeAsVisited(StartSource, VisitedNodes);

	// Play the sound at the current node
	PlaySoundAtNode(StartSource);

	// Print the position of the current node
	PrintNodePosition(StartSource);

	// Recur for all the vertices adjacent to this vertex
	for (ASoundSource* AdjacentSource : StartSource->Connections)
	{
		PerformDFS(AdjacentSource, VisitedNodes, MaxDepth, CurrentDepth + 1);
	}
}

//Helper functions
void ASoundSource::PlaySoundAtNode(ASoundSource* Node)
{
	if (Node->GetAssociatedSound() && Node->AudioComponent)
	{
		Node->AudioComponent->SetSound(Node->GetAssociatedSound());
		Node->AudioComponent->Play();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Sound or AudioComponent is null"));
	}
}

void ASoundSource::PrintNodePosition(ASoundSource* Node)
{
	FVector Location = Node->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Node at position: %s"), *Location.ToString());
}