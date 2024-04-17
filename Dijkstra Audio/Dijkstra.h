#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Dijkstra.generated.h"

USTRUCT()
struct FDijkstraNode
{
	GENERATED_BODY()

public:
	FVector Position;
	TMap<int32, float> Neighbors;

	FDijkstraNode() {}

	FDijkstraNode(FVector Position) : Position(Position) {}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDijkstra : public UAudioComponent
{
	GENERATED_BODY()

public:
	UDijkstra();

	int ChooseTheNumberOfNode;
	int32 startNodeIndex;

private:
	AActor* actorToMove;
	TArray<int32> path;
	int32 currentNodeIndex;
	float speed;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Dijkstra")
	FORCEINLINE void SetChooseTheNumberOfNode(int numberOfNode) { ChooseTheNumberOfNode = numberOfNode; }

private:
	TArray<FVector> GenerateRandomPositions(int numberOfNode);
	void AddNode(int numberOfNode);
	void AddEdge(int32 NodeAIndex, int32 NodeBIndex, float Weight)
	{
		GetNode(NodeAIndex).Neighbors.Add(NodeBIndex, Weight);
		GetNode(NodeBIndex).Neighbors.Add(NodeAIndex, Weight);
	}
	int32 FindClosestNode(FVector actorPosition);
	TArray<int32> DijkstraAlgorithm(int32 startNodeIndex);

protected:
	UFUNCTION(BlueprintCallable, Category = "Dijkstra")
	virtual void MoveActorAlongPath(AActor* actor, TArray<int32> newPath, float newSpeed);

private:
	FORCEINLINE FDijkstraNode& GetNode(int32 index) { return Nodes[index]; }
	TArray<FDijkstraNode> Nodes;
};
