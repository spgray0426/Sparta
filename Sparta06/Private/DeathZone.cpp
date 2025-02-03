// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathZone.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

ADeathZone::ADeathZone()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollistionBox"));
	SetRootComponent(CollisionBox);

	CollisionBox->SetCollisionProfileName(TEXT("Trigger"));    // 충돌 상태를 Trigger로 설정
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathZone::OnOverlapBegin);
}

void ADeathZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADeathZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (PlayerCharacter)
	{
		AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());
		if (PlayerStart)
		{
			// 플레이어를 스타터 위치로 이동
			FVector StartLocation = PlayerStart->GetActorLocation();
			FRotator StartRotation = PlayerStart->GetActorRotation();
			PlayerCharacter->SetActorLocation(StartLocation);
			PlayerCharacter->SetActorRotation(StartRotation);

		}
	}
}

