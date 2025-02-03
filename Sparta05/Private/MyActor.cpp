// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	start = FVector2D(0, 0);
	UE_LOG(LogTemp, Warning, TEXT("시작 위치 x : %f, y : %f"), start.X, start.Y);
	move();
}

void AMyActor::move()
{
	for (int i = 0; i < 10; i++)
	{
		start.X += step();
		start.Y += step();
		UE_LOG(LogTemp, Warning, TEXT("현재 위치 x : %f, y : %f"), start.X, start.Y);
	}
}

int32 AMyActor::step()
{
	return FMath::RandRange(-1, 1);
}


