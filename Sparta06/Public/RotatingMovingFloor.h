// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovingFloor.h"
#include "RotatingMovingFloor.generated.h"

/**
 * 
 */
UCLASS()
class TASK_6_API ARotatingMovingFloor : public AMovingFloor
{
	GENERATED_BODY()

public:
	ARotatingMovingFloor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Rotating")
	float RotationSpeed = 10.0f;
};
