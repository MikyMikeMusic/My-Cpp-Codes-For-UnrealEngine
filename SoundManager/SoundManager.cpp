#include "SoundManager.h"

USoundManager::USoundManager() : soundQueue()
{
	//initialize the sound tree
	soundTree = TMap<USoundBase*, UMySoundNode*>(); // Changed key and value types

	//Initialize the root node
	rootNode = NewObject<UMySoundNode>();
	rootNode->parent = nullptr;
	rootNode->priority = 0;

	//Add the root node to the sound tree
	soundTree.Add(nullptr, rootNode); // Changed order of arguments

	//Initialize the current sound
	CurrentSound = nullptr;

	//Initialize the audio component
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	/*AudioComponent->OnAudioFinished.RemoveDynamic(this, &USoundManager::OnAudioFinishedHandler);*/
	if (AudioComponent == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AudioComponent is null"));
	}
}

USoundManager::~USoundManager()
{
	for (UMySoundNode* node : nodePool)
	{
		node->ConditionalBeginDestroy();
	}
}

void USoundManager::SetSoundPriority(USoundBase* sound, int priority)
{
	UMySoundNode** nodePtr = soundTree.Find(sound); // Use Find for efficiency
	if (nodePtr == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sound not found"));
		return;
	}

	(*nodePtr)->priority = priority;
}

int USoundManager::GetSoundPriority(USoundBase* sound)
{
	UMySoundNode** nodePtr = soundTree.Find(sound); // Use Find for efficiency
	if (nodePtr == nullptr)
	{
		//If the sound is not in the sound tree, return a default priority
		return 0;
	}

	return (*nodePtr)->priority;
}

UMySoundNode* USoundManager::GetHighestPriorityNode()
{
	UMySoundNode* highestPriorityNode = nullptr;
	int highestPriority = INT_MIN;//Negative infinity

	//Iterate through the sound tree
	for (auto& pair : soundTree)
	{
		UMySoundNode* node = pair.Value; // Changed to Value

		if (node->priority > highestPriority)
		{
			highestPriority = node->priority;
			highestPriorityNode = node;
		}
	}

	return highestPriorityNode;
}

FSoundResult USoundManager::GetHighestPrioritySound()
{
	// Initialize the highest priority to the lowest possible value
	int highestPriority = INT_MIN;
	// Initialize the highest priority sound to nullptr
	USoundBase* highestPrioritySound = nullptr;

	// Iterate through the sound tree
	for (auto& pair : soundTree)
	{
		// If the current node's priority is higher than the highest priority found so far
		if (pair.Value->priority > highestPriority)
		{
			// Update the highest priority and the highest priority sound
			highestPriority = pair.Value->priority;
			highestPrioritySound = pair.Key;
		}
	}

	// Create a result
	FSoundResult result;
	result.Sound = highestPrioritySound;
	if (highestPrioritySound != nullptr)
	{
		result.FormattedString = FString::Printf(TEXT("Sound: %s, Priority: %d"), *highestPrioritySound->GetName(), highestPriority);
	}
	else
	{
		result.FormattedString = "No sound found";
	}

	// Return the result
	return result;
}

UMySoundNode* USoundManager::GetNewNode()
{
	if (nodePool.Num() > 0)
	{
		//if there are nodes in the pool, pop one
		UMySoundNode* node = nodePool.Pop();
		return node;
	}
	else
	{
		// Otherwise, create a new node
		UMySoundNode* node = NewObject<UMySoundNode>();
		if (node == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Node is null"));
			return nullptr;
		}
		return node;
	}
}

UMySoundNode* USoundManager::GetParentNode(USoundBase* sound)
{
	UMySoundNode** nodePtr = soundTree.Find(sound); // Use Find for efficiency
	if (nodePtr == nullptr)
	{
		//If the sound is not in the sound tree, return null
		return nullptr;
	}

	return (*nodePtr)->parent;
}

void USoundManager::AddSoundEffect(USoundBase* sound, int priority)
{
	if (soundTree.Contains(sound))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sound already exists"));
		return;
	}

	// Create a new sound node
	UMySoundNode* child = GetNewNode();
	// Set the parent, priority of the child to the root node
	child->parent = rootNode; // Assuming the root node is the one with a null sound
	child->priority = priority;

	// Add the child to the root node's children
	child->parent->children.Add(child);
	// Add the sound and child to the sound tree
	soundTree.Add(sound, child); // Changed order of arguments
}

void USoundManager::RemoveSoundEffect(USoundBase* sound)
{
	UMySoundNode** nodeToRemovePtr = soundTree.Find(sound); // Use Find for efficiency
	if (nodeToRemovePtr == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Sound not found"));
		return;
	}

	UMySoundNode* nodeToRemove = *nodeToRemovePtr;
	// Remove the node from the parent's children array
	if (nodeToRemove->parent != nullptr)
	{
		nodeToRemove->parent->children.Remove(nodeToRemove);
	}
	// Remove the sound from the sound tree
	soundTree.Remove(sound);

	// Release the node using ReleaseNode()
	ReleaseNode(nodeToRemove);
}

USoundBase* USoundManager::PlayHighestPrioritySoundEffect(bool playAllInOrder)
{
	if (AudioComponent == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AudioComponent is null"));
		return nullptr;
	}

	// Create a sorted array of the nodes
	TArray<UMySoundNode*> sortedNodes;
	for (auto& pair : soundTree)
	{
		sortedNodes.Add(pair.Value);
	}

	// Sort the array based on priority
	sortedNodes.Sort([](const UMySoundNode& a, const UMySoundNode& b) {
		return a.priority > b.priority;
		});

	// Clear the sound queue
	soundQueue.Empty();

	// Add all the sounds to the queue in order
	for (UMySoundNode* node : sortedNodes)
	{
		USoundBase* sound = nullptr;
		for (auto& pair : soundTree)
		{
			if (pair.Value == node)
			{
				sound = pair.Key;
				break;
			}
		}

		if (sound != nullptr)
		{
			soundQueue.Enqueue(sound);
		}
	}

	if (playAllInOrder)
	{
		// Play the first sound in the queue
		USoundBase* sound;
		if (soundQueue.Dequeue(sound))
		{
			CurrentSound = sound;
			AudioComponent->SetSound(CurrentSound);
			AudioComponent->Play();
			AudioComponent->OnAudioFinished.AddDynamic(this, &USoundManager::OnAudioFinishedHandler);
		}
	}
	else
	{
		// Play the highest priority sound
		USoundBase* highestPrioritySound;
		if (soundQueue.Peek(highestPrioritySound) && highestPrioritySound != nullptr)
		{
			AudioComponent->SetSound(highestPrioritySound);
			AudioComponent->Play();
		}
	}

	return nullptr;
}













