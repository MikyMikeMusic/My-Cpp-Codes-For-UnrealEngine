// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioResampler_.h"

AudioResampler_::AudioResampler_()
{
}

AudioResampler_::~AudioResampler_()
{
}

void AudioResampler_::Upsample(TArray<float>& input, TArray<float>& output, int inputFreq, int outputFreq)
{
	int inputSize = input.Num();
	int outputSize = inputSize * outputFreq / inputFreq;
	output.SetNum(outputSize);

	float step = (float)inputFreq / outputFreq;
	float pos = 0.0f;
	for (int i = 0; i < outputSize; i++)
	{
		int left = FMath::FloorToInt(pos);
		int right = FMath::CeilToInt(pos);
		if (right >= inputSize)
		{
			right = inputSize - 1;
		}
		float t = pos - left;
		output[i] = Lerp(input[left], input[right], t);
		pos += step;

	}
}

void AudioResampler_::Downsample(TArray<float>& input, TArray<float>& output, int inputFreq, int outputFreq)
{
	int inputSize = input.Num();
	int outputSize = inputSize * outputFreq / inputFreq;
	output.SetNum(outputSize);

	float step = (float)inputFreq / outputFreq;
	float pos = 0.0f;
	for (int i = 0; i < outputSize; i++)
	{
		int left = FMath::FloorToInt(pos);
		int right = FMath::CeilToInt(pos);
		if (right >= inputSize)
		{
			right = inputSize - 1;
		}
		float t = pos - left;
		output[i] = Lerp(input[left], input[right], t);
		pos += step;

	}
}

void AudioResampler_::Resample(TArray<float>& input, TArray<float>& output, int inputFreq, int outputFreq)
{
	float ratio = static_cast<float>(inputFreq) / outputFreq;
	float i = 0.0f;

	SwitchResampleType(input, output, inputFreq, outputFreq);

	for (int j = 0; j < output.Num(); j++)
	{
		int From = static_cast<int>(i);
		int To = From + 1;
		float t = i - From;

		// Check for edge case
		if (To >= output.Num())
		{
			To = output.Num() - 1;
		}

		output[j] = Lerp(output[From], output[To], t);
		i += ratio;
	}
}
