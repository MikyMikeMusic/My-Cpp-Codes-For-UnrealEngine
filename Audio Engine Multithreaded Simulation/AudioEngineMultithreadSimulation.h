#pragma once

#include "CoreMinimal.h"

enum class MessageType
{
	Play,
	Stop
};

struct Message
{
	MessageType type;//This can be Play or Stop
	int id;
};

class AudioEngineMultithreadSimulation
{

private:
	TQueue<Message> messageQueue;
	TAtomic<int32> FrameMessages;
	bool Stop;

public:
	AudioEngineMultithreadSimulation()
		: Stop(false) {}

	FORCEINLINE void Play(int SoundID)
	{
		Message msg;
		msg.type = MessageType::Play;
		msg.id = SoundID;
		messageQueue.Enqueue(msg);
	}

	FORCEINLINE void Stop(int SoundID)
	{
		Message msg;
		msg.type = MessageType::Stop;
		msg.id = SoundID;
		messageQueue.Enqueue(msg);
	}

	FORCEINLINE void Update()
	{
		FrameMessages.Increment();
	}

	void ProcessMessages();

	FORCEINLINE void StopEngine()
	{
		Stop = true;
	}
};