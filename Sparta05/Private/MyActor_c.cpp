// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor_c.h"

// Sets default values
AMyActor_c::AMyActor_c()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMyActor_c::BeginPlay()
{
	Super::BeginPlay();
	//초기화
	start = FVector2D(0, 0);
	evCnt = 0;
	totDist = 0;
	
	UE_LOG(LogTemp, Warning, TEXT("시작 위치 x : %f, y : %f"), start.X, start.Y);

	UE_LOG(LogTemp, Warning, TEXT("======================================"));
	//실행
	move();
}

void AMyActor_c::move()
{
	for (int i = 0; i < 10; i++)
	{
		FVector2D tempVec = start;
		start.X += step();
		start.Y += step();
		float Dist = distance(tempVec, start);
		totDist += Dist;
		UE_LOG(LogTemp, Warning, TEXT("이동거리 : %f"), Dist);
		UE_LOG(LogTemp, Warning, TEXT("현재 위치 x : %f, y : %f"), start.X, start.Y);

		
		//이벤트 발생 여부
		if (createEvent())
		{
			UE_LOG(LogTemp, Warning, TEXT("이벤트 발생"));
			evCnt++;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("======================================"));
	}

	UE_LOG(LogTemp, Warning, TEXT("총 이동 거리 : %f"), totDist);
	UE_LOG(LogTemp, Warning, TEXT("총 이벤트 발생 횟수 : %d"), evCnt);
}

int32 AMyActor_c::step()
{
	return FMath::RandRange(-1, 1);
}

float AMyActor_c::distance(FVector2D first, FVector2D second)
{
	float dx = first.X - second.X;
	float dy = first.Y - second.Y;
	return FMath::Sqrt(dx*dx +  dy*dy);
}

bool AMyActor_c::createEvent()
{
	return FMath::RandRange(0, 1) == 1;
}
