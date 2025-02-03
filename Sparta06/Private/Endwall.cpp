// Fill out your copyright notice in the Description page of Project Settings.


#include "Endwall.h"

#include "MovingFloor.h"
#include "Components/BoxComponent.h"

// Sets default values
AEndwall::AEndwall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollistionBox"));
	SetRootComponent(CollisionBox);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AEndwall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndwall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndwall::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AMovingFloor* MovingActor = Cast<AMovingFloor>(OtherActor);

	if (MovingActor)
	{
		MovingActor->Destroy();
	}
}

