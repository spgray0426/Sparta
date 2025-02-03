// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingBarrel.h"

AMovingBarrel::AMovingBarrel()
{
	PrimaryActorTick.bCanEverTick = true; 
	OscillationFrequency = 1.0f; 
	MovementAmplitude = 20.0f; 
	RunningTime = 0.0f;
}

void AMovingBarrel::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

void AMovingBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RunningTime += DeltaTime;
	
	float DeltaHeight = FMath::Sin(RunningTime * OscillationFrequency) * MovementAmplitude;

	float DeltaY = Speed * DeltaTime;
	
	FVector NewLocation = StartLocation;
	NewLocation.Z += DeltaHeight;
	NewLocation.Y += DeltaY;
	SetActorLocation(NewLocation);
	StartLocation.Y += DeltaY;
}
