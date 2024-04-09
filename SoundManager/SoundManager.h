#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "SoundManager.generated.h"

USTRUCT(BlueprintType)
struct FSoundResult
{
	GENERATED_BODY()

public:
	USoundBase* Sound;
	FString FormattedString;
};

UCLASS()
class UMySoundNode : public UObject
{
	GENERATED_BODY()

public:
	//Member variables of the sound node
	UMySoundNode* parent;
	TArray<UMySoundNode*> children;
	int priority;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), BlueprintType)
class TESTINGSOUNDS_API USoundManager : public UActorComponent
{
	GENERATED_BODY()

public:
	//Constructor and destructor
	USoundManager();
	virtual ~USoundManager();

	//Member variables of the sound manager
	UPROPERTY()
	TMap<USoundBase*, UMySoundNode*> soundTree; // Changed key and value types
	UPROPERTY()
	UMySoundNode* rootNode;
	UPROPERTY()
	USoundBase* CurrentSound;

	//Member functions of the sound manager
	UFUNCTION(BlueprintCallable, Category = "Sound Manager")
	void AddSoundEffect(USoundBase* sound, int priority);
	UFUNCTION(BlueprintCallable, Category = "Sound Manager")
	void RemoveSoundEffect(USoundBase* sound);

	UFUNCTION(BlueprintCallable, Category = "Sound Manager")
	USoundBase* PlayHighestPrioritySoundEffect(bool playAllInOrder);

	UFUNCTION(BlueprintCallable, Category = "Sound Manager")
	void SetSoundPriority(USoundBase* sound, int priority);
	UFUNCTION(BlueprintCallable, Category = "Sound Manager")
	int GetSoundPriority(USoundBase* sound);
	UFUNCTION()
	UMySoundNode* GetHighestPriorityNode();
	UFUNCTION()
	UMySoundNode* GetParentNode(USoundBase* sound);
	UFUNCTION(BlueprintCallable, Category = "Sound Manager")
	FSoundResult GetHighestPrioritySound();
	UFUNCTION()
	UMySoundNode* GetNewNode();
	UFUNCTION()
	FORCEINLINE void ReleaseNode(UMySoundNode* node)
	{
		// Clean up the node data
		node->parent = nullptr;
		node->children.Empty();
		node->priority = 0;

		// Push the node back into the pool
		nodePool.Push(node);
	}

private:
	UFUNCTION()
	FORCEINLINE void OnAudioFinishedHandler()
	{
		// When a sound finishes, play the next sound in the queue
		USoundBase* sound;
		if (soundQueue.Dequeue(sound))
		{
			CurrentSound = sound;
			AudioComponent->SetSound(CurrentSound);
			AudioComponent->Play();
		}
	}

private:
	TQueue<USoundBase*> soundQueue;
	TArray<UMySoundNode*> nodePool;
	UAudioComponent* AudioComponent;
};


