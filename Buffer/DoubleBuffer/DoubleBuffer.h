// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class DoubleBuffer
{
public:

	DoubleBuffer(int32 samples) : buffer(), Read(nullptr), Write(nullptr)
	{
		buffer.Init(0.0f, samples * 2);
		Read = buffer.GetData();
		Write = buffer.GetData() + samples;
	}
	 ~DoubleBuffer();

	FORCEINLINE void Swap()
	{
		float* Oldread = Read;
		Read = Write;
		Write = Oldread;
	}

	float* GetReadBuffer() { return Read; }
	float* GetWriteBuffer() { return Write; }

private: 
	TArray<float> buffer;
	float* Read;
	float* Write;
};
