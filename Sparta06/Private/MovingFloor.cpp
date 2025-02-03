// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingFloor.h"

// Sets default values
AMovingFloor::AMovingFloor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
}

void AMovingFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovingFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + FVector(0, Speed * DeltaTime, 0));
}

