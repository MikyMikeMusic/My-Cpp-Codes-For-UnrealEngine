// Fill out your copyright notice in the Description page of Project Settings.

#include "Dijkstra.h"

// Sets default values for this component's properties
UDijkstra::UDijkstra()
	: actorToMove(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ChooseTheNumberOfNode = 3;

	currentNodeIndex = 0;
	speed = 0.01f;
}

void UDijkstra::BeginPlay()
{
	Super::BeginPlay();

	if (ChooseTheNumberOfNode > 0)
	{
		AddNode(ChooseTheNumberOfNode);
		//print the number of nodes
		UE_LOG(LogTemp, Warning, TEXT("Number of nodes: %d"), Nodes.Num());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Use SetChooseTheNumberOfNode function for set the nodes"));
		return;
	}

	startNodeIndex = FindClosestNode(GetOwner()->GetActorLocation());
	if (startNodeIndex < 0 || startNodeIndex >= Nodes.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid start node index"));
		return;
	}

	if (Nodes.Contains(startNodeIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Start node index: %d"), startNodeIndex);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid start node index"));
		return;
	};

	TArray<int32> pathResult = DijkstraAlgorithm(startNodeIndex);
	Algo::Reverse(pathResult);

	MoveActorAlongPath(GetOwner(), pathResult, 0.01f);
}

void UDijkstra::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Se c'è un attore da muovere
	if (actorToMove != nullptr)
	{
		// Se l'attore ha raggiunto il nodo corrente, passa al nodo successivo
		if (FVector::Dist(actorToMove->GetActorLocation(), Nodes[path[currentNodeIndex]].Position) < speed * DeltaTime)
		{
			++currentNodeIndex;

			// Se l'attore ha raggiunto l'ultimo nodo, smetti di muoverlo
			if (currentNodeIndex >= path.Num())
			{
				actorToMove = nullptr;
			}
		}
		else
		{
			// Muovi l'attore verso il nodo corrente
			FVector direction = (Nodes[path[currentNodeIndex]].Position - actorToMove->GetActorLocation()).GetSafeNormal();
			actorToMove->SetActorLocation(actorToMove->GetActorLocation() + direction * speed * DeltaTime);
		}
	}
}


void UDijkstra::AddNode(int numberOfNode)
{
	TArray<FVector> positions = GenerateRandomPositions(numberOfNode);

	for (FVector position : positions)
	{
		FDijkstraNode newNode(position);
		int32 newNodeIndex = Nodes.Add(newNode);

		for (int32 existingNodeIndex = 0; existingNodeIndex < Nodes.Num(); ++existingNodeIndex)
		{
			if (existingNodeIndex != newNodeIndex)
			{
				float weight = FVector::Dist(Nodes[existingNodeIndex].Position, newNode.Position);
				AddEdge(existingNodeIndex, newNodeIndex, weight);
			}
		}
	}
}

int32 UDijkstra::FindClosestNode(FVector actorPosition)
{
	int32 closestNodeIndex = -1;
	float closestDistance = FLT_MAX;

	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		float distance = FVector::Dist(actorPosition, Nodes[i].Position);
		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestNodeIndex = i;
		}
	}
	return closestNodeIndex;
}

void UDijkstra::MoveActorAlongPath(AActor* actor, TArray<int32> newPath, float newSpeed)
{
	// Salva il percorso e l'attore da muovere
	path = newPath;
	actorToMove = actor;
	speed = newSpeed;

	// Inizia dal primo nodo del percorso
	currentNodeIndex = 0;

	// Inizia dal primo nodo del percorso
	currentNodeIndex = 0;

	for (int32 i = 0; i < path.Num() - 1; ++i)
	{
		FVector start = Nodes[path[i]].Position;
		FVector end = Nodes[path[i + 1]].Position;

		for (float t = 0.0f; t < 1.0f; t += speed)
		{
			FVector interpolatedPosition = FMath::Lerp(start, end, t);
			actor->SetActorLocation(interpolatedPosition);
			FPlatformProcess::Sleep(0.01); // Sleep for a short time to simulate movement
		}
	}
}


//Helper Function
TArray<FVector> UDijkstra::GenerateRandomPositions(int numberOfNode)
{
	TArray<FVector> positions;

	for (int i = 0; i < numberOfNode; i++)
	{
		float radius = 100.0f;
		float theta = FMath::RandRange(0.0f, 360.0f);
		float phi = FMath::RandRange(0.0f, 180.0f);
		float x = radius * FMath::Sin(FMath::DegreesToRadians(theta)) * FMath::Cos(FMath::DegreesToRadians(phi));
		float y = radius * FMath::Sin(FMath::DegreesToRadians(theta)) * FMath::Sin(FMath::DegreesToRadians(phi));
		float z = radius * FMath::Cos(FMath::DegreesToRadians(theta));

		positions.Add(FVector(x, y, z));
	}

	return positions;
}
//Main Function
TArray<int32> UDijkstra::DijkstraAlgorithm(int32 startNodeIndexParam)
{
	TMap<int32, float> shortestDistances;
	TMap<int32, int32> previousNodes;
	TSet<int32> unvisitedNodes;

	for (int32 nodeIndex = 0; nodeIndex < Nodes.Num(); ++nodeIndex)
	{
		shortestDistances[nodeIndex] = FLT_MAX;
		unvisitedNodes.Add(nodeIndex);
	}

	shortestDistances[startNodeIndexParam] = 0;

	while (unvisitedNodes.Num() > 0)
	{
		int32 currentNodeIndexLocal = -1;
		for (int32 potentialNodeIndex : unvisitedNodes)
		{
			if (currentNodeIndexLocal == -1 || shortestDistances[potentialNodeIndex] < shortestDistances[currentNodeIndexLocal])
			{
				currentNodeIndexLocal = potentialNodeIndex;
			}
		}

		if (shortestDistances[currentNodeIndexLocal] == FLT_MAX)
		{
			break;
		}

		unvisitedNodes.Remove(currentNodeIndexLocal);

		for (auto& neighborPair : Nodes[currentNodeIndexLocal].Neighbors)
		{
			int32 neighborNodeIndex = neighborPair.Key;
			float edgeWeight = neighborPair.Value;

			float alternativePathDistance = shortestDistances[currentNodeIndexLocal] + edgeWeight;
			if (alternativePathDistance < shortestDistances[neighborNodeIndex])
			{
				shortestDistances[neighborNodeIndex] = alternativePathDistance;
				previousNodes[neighborNodeIndex] = currentNodeIndexLocal;
			}
		}
	}

	TArray<int32> result;
	for (auto& pair : previousNodes)
	{
		result.Add(pair.Value);
	}

	return result;
}