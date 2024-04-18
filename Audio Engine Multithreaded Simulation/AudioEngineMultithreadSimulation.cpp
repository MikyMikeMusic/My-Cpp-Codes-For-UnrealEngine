// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioEngineMultithreadSimulation.h"

void AudioEngineMultithreadSimulation::ProcessMessages()
{
	while (!Stop)
	{
		if (FrameMessages.Load() == 0)
		{
			break;
		}
	}

	Message m;
	if (messageQueue.Dequeue(m))
	{
		switch (m.type)
		{
			case MessageType::Play:
			{
				UE_LOG(LogTemp, Warning, TEXT("Play"), m.id);
				break;
			}
			case MessageType::Stop:
			{
				UE_LOG(LogTemp, Warning, TEXT("Stop"), m.id);
				break;
			}
		}
		FrameMessages.DecrementExchange();
	}
}