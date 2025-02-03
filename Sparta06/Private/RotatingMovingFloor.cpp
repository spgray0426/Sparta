// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingMovingFloor.h"

ARotatingMovingFloor::ARotatingMovingFloor()
{
}

void ARotatingMovingFloor::BeginPlay()
{
	Super::BeginPlay();
}

void ARotatingMovingFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
}
