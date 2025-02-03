// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorGenerator.generated.h"

class AMovingFloor;

USTRUCT(BlueprintType)
struct FSpawnLocationData
{
	GENERATED_BODY()

	//생성할 클래스
	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AMovingFloor> MovingFloorClass;

	//생성할 위치
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = "true"))
	FVector Location;

	//생성될 주기
	UPROPERTY(EditAnywhere)
	float SpawnInterval;

	//타이머
	FTimerHandle SpawnTimerHandle;
};

UCLASS()
class TASK_6_API AFloorGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloorGenerator();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	//모든 데이터를 구조체로 관리
	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<FSpawnLocationData> SpawnLocationDataArray;

	UFUNCTION()
	void SpawnMovingFloorAtLocation(const FSpawnLocationData& SpawnLocationData);
};
