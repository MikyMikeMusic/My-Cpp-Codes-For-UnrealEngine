// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"
#include "DopplerEffect.generated.h"

UCLASS(Blueprintable)
class MYPROJECT_API ADopplerEffect : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* _AudioComponent;//Audio component

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* _RootSceneComponent;//Root component

	FVector PreviousLocation;//Previous location of the audio component

public:
	// Sets default values for this actor's properties
	ADopplerEffect();

	const float SpeedOfSound = 343.0f;//Speed of sound in air in meters per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DopplerEffect")
	float speed = 150.0f;//Speed of the source in meters per second
	FVector CurrentLocation;//Current location of the audio component

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UAudioComponent* GetAudioComponent() const { return _AudioComponent; }

	//create a function call DopplerEffect that will be called in the blueprint and will return an FVector
	UFUNCTION(BlueprintCallable, Category = "DopplerEffect", meta = (DisplayName = "DopplerEffect"))
	void DopplerEffect();

};
