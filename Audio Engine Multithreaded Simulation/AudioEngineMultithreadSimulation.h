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
	bool bStop;

public:
	AudioEngineMultithreadSimulation()
		: bStop(false) {}

	FORCEINLINE void Play(int SoundID)
	{
		Message msg;
		msg.type = MessageType::Play;
		msg.id = SoundID;
		messageQueue.Enqueue(msg);
	}

	FORCEINLINE void Stop(int InSoundID)
	{
		Message msg;
		msg.type = MessageType::Stop;
		msg.id = InSoundID;
		messageQueue.Enqueue(msg);
	}

	FORCEINLINE void Update()
	{
		FrameMessages.IncrementExchange();
	}

	void ProcessMessages();

	FORCEINLINE void StopEngine()
	{
		bStop = true;
	}
};