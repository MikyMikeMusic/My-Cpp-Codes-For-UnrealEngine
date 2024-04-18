// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AudioDeviceForTest
{
public:

    typedef void(*AudioCallback)(float*, int, int, void*);

    AudioDeviceForTest(int SampleRate, int Channels, int Frames, AudioCallback, void* InCookie);
    ~AudioDeviceForTest();

private:
    int SampleRate;
    int Channels;
    int Frames;
    AudioCallback Callback;
    void* Cookie;

protected:
    void MyAudioCallback(float* InBuffer, int NumFrames, int NumChannels, void* InCookie);
};



