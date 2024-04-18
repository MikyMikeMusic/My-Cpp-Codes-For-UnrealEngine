// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class TripleBuffer_
{
public:
	TripleBuffer_(int32 InSamples)
		: Samples(InSamples), ReadIndex(Samples), WriteIndex(0)
	{
			Buffer.SetNum(Samples * 3);
	}
	~TripleBuffer_();

	float* GetWriteBuffer()
	{
		return Buffer.GetData() + WriteIndex;
	}
	void FinishWrite()
	{
		WriteIndex = (WriteIndex + Samples) % Buffer.Num();
	}

	float* GetReadBuffer()
	{
		return Buffer.GetData() + ReadIndex;
	}
	void FinishRead()
	{
		ReadIndex = (ReadIndex + Samples) % Buffer.Num();
	}

private: 
	TArray<float> Buffer;
	int32 Samples;
	int32 ReadIndex;
	int32 WriteIndex;
};
