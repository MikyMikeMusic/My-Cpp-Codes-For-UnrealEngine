// Fill out your copyright notice in the Description page of Project Settings.
#include "AudioDeviceForTest.h"


AudioDeviceForTest::AudioDeviceForTest(int InSampleRate, int InChannels, int InFrames, AudioCallback InCallback, void* InCookie)
	: SampleRate(InSampleRate), Channels(InChannels), Frames(InFrames), Callback(InCallback), Cookie(InCookie)
{
}

AudioDeviceForTest::~AudioDeviceForTest()
{
}

void AudioDeviceForTest::MyAudioCallback(float* InBuffer, int NumFrames, int NumChannels, void* Cookies)
{

	for (int i = 0; i < NumChannels * NumFrames; i++)
	{
		InBuffer[i] = 0.0f;
	}
}
