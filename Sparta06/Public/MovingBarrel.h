// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingFloor.h"
#include "MovingBarrel.generated.h"

/**
 * 
 */
UCLASS()
class TASK_6_API AMovingBarrel : public AMovingFloor
{
	GENERATED_BODY()

public:
	AMovingBarrel();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// 위아래 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float OscillationFrequency;

	// 움직임 진폭
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MovementAmplitude;

private:
	FVector StartLocation;

	float RunningTime;
};
