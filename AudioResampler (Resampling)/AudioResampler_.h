// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/UnrealMathUtility.h"


class AudioResampler_
{
public:
	AudioResampler_();
	~AudioResampler_();

	void Resample(TArray<float>& input, TArray<float>& output, int inputFreq, int outputFreq);

private:

	FORCEINLINE float Lerp(float from, float to, float t)
	{
		return (1.0f - t) * from + t * to;
	}

	FORCEINLINE void SwitchResampleType(TArray<float>& input, TArray<float>& output, int inputFreq, int outputFreq)
	{
		if (inputFreq == outputFreq)
		{
			output = input;
			return;
		}

		if (inputFreq > outputFreq)
		{
			Downsample(input, output, inputFreq, outputFreq);
		}
		else
		{
			Upsample(input, output, inputFreq, outputFreq);
		}
	}

	void Upsample(TArray<float>& input, TArray<float>& output, int inputFreq, int outputFreq);

	void Downsample(TArray<float>& input, TArray<float>& output, int inputFreq, int outputFreq);



};
