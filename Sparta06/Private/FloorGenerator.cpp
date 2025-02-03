// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorGenerator.h"

#include "MovingFloor.h"

AFloorGenerator::AFloorGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFloorGenerator::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AFloorGenerator::BeginPlay 실행됨"));
	for (FSpawnLocationData& Data : SpawnLocationDataArray)
	{
		// 유효한 클래스와 스폰 주기인지 확인
		if (Data.MovingFloorClass != nullptr && Data.SpawnInterval > 0.0f)
		{
			GetWorld()->GetTimerManager().SetTimer(
			Data.SpawnTimerHandle, 
				FTimerDelegate::CreateLambda([this, Data]()-> void
				{
					SpawnMovingFloorAtLocation(Data);
				}), 
				Data.SpawnInterval, 
				true
			);	
		}
	}

}

void AFloorGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorGenerator::SpawnMovingFloorAtLocation(const FSpawnLocationData& SpawnLocationData)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	FVector WorldLocation = GetActorTransform().TransformPosition(SpawnLocationData.Location);
	
	// 위치의 트랜스폼에 MovingFloor 스폰
	UWorld* world= GetWorld();
	if (world)
	{
		world->SpawnActor<AMovingFloor>(
			SpawnLocationData.MovingFloorClass,
			WorldLocation,
			FRotator::ZeroRotator,
			SpawnParams
		);
	}
		
}



