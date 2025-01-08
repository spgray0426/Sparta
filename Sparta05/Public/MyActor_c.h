// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor_c.generated.h"

UCLASS()
class SPARTA4_API AMyActor_c : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor_c();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	FVector2D start;

	UPROPERTY(EditAnywhere)
	int32 evCnt;

	UPROPERTY(EditAnywhere)
	float totDist;
	
	void move();
	int32 step();
	float distance(FVector2D start, FVector2D end);
	bool createEvent();

};


