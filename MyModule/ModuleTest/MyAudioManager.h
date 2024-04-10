// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModuleTest.h"
#include "MyAudioManager.generated.h"

//Interface class with two pure virtual functions
class IMyAudioModule
{

public:
	virtual void Play() = 0;
	virtual void Stop() = 0;
};

//Class that inherits from the interface class
class MyAudioModuleInherits : public IMyAudioModule
{
public:
	virtual void Play() override;
	virtual void Stop() override;
};

//Class that inherits from AudioModule and create a new function itself
class MyAudioModuleInheritsWithNewFunction : public MyAudioModuleInherits
{
public:
	void Record();
};

UCLASS(BlueprintType)
class MODULETEST_API UMyAudioManager : public UObject
{
	GENERATED_BODY()
public:
	UMyAudioManager();
	virtual ~UMyAudioManager();

	//Composition principle with IMyAudioModule
	IMyAudioModule* IMyAudioModuleComposition;

	//Aggregation principle with IMyAudioModule
	TArray <IMyAudioModule*> IMyAudioModuleAggregation;
};
