// Fill out your copyright notice in the Description page of Project Settings.

#include "Dijkstra.h"

// Sets default values for this component's properties
UDijkstra::UDijkstra()
	: actorToMove(nullptr)//Actor to mova start with null
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Set the number of nodes of the graph
	ChooseTheNumberOfNode = 3;

	//Initialize the variables
	currentNodeIndex = 0;
	speed = 0.01f;
}

void UDijkstra::BeginPlay()
{
	Super::BeginPlay();

	//Check 
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

	//Use the DijkstraAlgorithm function to find the shortest path
	TArray<int32> pathResult = DijkstraAlgorithm(startNodeIndex);
	Algo::Reverse(pathResult);

	//Use the DijkstraAlgorithm function to find the shortest path
	MoveActorAlongPath(GetOwner(), pathResult, 0.01f);
}

void UDijkstra::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If there's an actor to move
	if (actorToMove != nullptr)
	{
		//If the actor move to the next node
		if (FVector::Dist(actorToMove->GetActorLocation(), Nodes[path[currentNodeIndex]].Position) < speed * DeltaTime)
		{
			++currentNodeIndex;

			//If the actor has reached the end of the path
			if (currentNodeIndex >= path.Num())
			{
				actorToMove = nullptr;
			}
		}
		else
		{
			//Move the actor towards the next node
			FVector direction = (Nodes[path[currentNodeIndex]].Position - actorToMove->GetActorLocation()).GetSafeNormal();
			actorToMove->SetActorLocation(actorToMove->GetActorLocation() + direction * speed * DeltaTime);
		}
	}
}


void UDijkstra::AddNode(int numberOfNode)
{
	//Generate random positions for the nodes
	TArray<FVector> positions = GenerateRandomPositions(numberOfNode);

	//Add the nodes and the edges
	for (FVector position : positions)
	{
		FDijkstraNode newNode(position);
		int32 newNodeIndex = Nodes.Add(newNode);

		//Add edges to the new node from all existing nodes
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
	//Find the closest node to the actor
	int32 closestNodeIndex = -1;
	float closestDistance = FLT_MAX;

	//Find the closest node to the actor
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
	//Save the path and the actor to move
	path = newPath;
	actorToMove = actor;
	speed = newSpeed;

	//Start to the first node in the path
	currentNodeIndex = 0;

	//Move the actor to the first node
	for (int32 i = 0; i < path.Num() - 1; ++i)
	{
		FVector start = Nodes[path[i]].Position;
		FVector end = Nodes[path[i + 1]].Position;

		//Move the actor from the start node to the end node
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
	//Generate random positions for the nodes
	TArray<FVector> positions;

	//Generate random positions for the nodes
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
	//Dijkstra's algorithm
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