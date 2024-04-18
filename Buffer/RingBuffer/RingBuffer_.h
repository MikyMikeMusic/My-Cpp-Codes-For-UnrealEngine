// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class RingBuffer_
{
public:
	RingBuffer_(int32 Samples, int32 Frames)
		: Samples(Samples), MaxFrames(Frames), ReadIndex(0), WriteIndex(0), NumFrames(Frames)
	{
		Buffer.setNum(Samples * MaxFrames);
	}

	bool CanWrite() { return NumFrames != MaxFrames; }
	float* GetWriteBuffer() { return Buffer.GetData() + WriteIndex * Samples; }
	void FinishWrite() { WriteIndex = (WriteIndex + 1) % MaxFrames; NumFrames++; }

	bool CanRead() { return NumFrames != 0; }
	float* GetReadBuffer() { return Buffer.GetData() + ReadIndex * Samples; }
	void FinishRead() { ReadIndex = (ReadIndex + 1) % MaxFrames; NumFrames--; }

	~RingBuffer_();

private:
	TArray<float> Buffer;
	int32 Samples;
	int32 MaxFrames;
	int32 ReadIndex;
	int32 WriteIndex;
	int32 NumFrames;
};
