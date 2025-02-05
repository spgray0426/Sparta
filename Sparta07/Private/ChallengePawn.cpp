// Fill out your copyright notice in the Description page of Project Settings.

#include "ChallengePawn.h"

#include "ChallengePlayerController.h"
#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

AChallengePawn::AChallengePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
	
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bIsFalling = false;
	bIsMoving = false;
	CurrentVelocity = FVector::ZeroVector;
	MoveSpeed = 600.0f;
}

void AChallengePawn::BeginPlay()
{
	Super::BeginPlay();
}

void AChallengePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFalling && !bIsMoving)
	{
		CurrentVelocity.Z += Gracity * DeltaTime;
	}

	if (!CheckGroundCollision(DeltaTime))
	{
		// 이동 처리 (충돌이 없는 경우)
		FVector GracityLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(GracityLocation, true);
	}
}

bool AChallengePawn::CheckGroundCollision(float DeltaTime)
{
	// 충돌 결과를 저장할 변수
	FHitResult HitResult;
	
	//현재 위치에서 다음 중력의 위치까지
	const FVector Start = GetActorLocation();
	const FVector End = Start + FVector(0, 0, CurrentVelocity.Z * DeltaTime);

	// Sphere 콜리전을 사용하여 충돌 감지
	const float SphereRadius = Sphere->GetScaledSphereRadius(); // Sphere의 스케일 반지름 가져오기
	const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SphereRadius); // 구 형태의 충돌 객체 생성

	// 충돌 감지 시 자신을 무시하도록 설정
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// SweepSingleByChannel을 사용하여 충돌 감지
	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult,							   // 충돌 결과 데이터
		Start,								   // 시작 위치
		End,									 // 끝 위치
		FQuat::Identity,						// 회전 설정
		ECollisionChannel::ECC_Visibility,	  // 충돌 채널
		CollisionShape,						 // 충돌 형태
		CollisionParams						 // 충돌 관련 매개변수
	);

	if (bHit)
	{
		// 충돌이 발생한 경우 착지 처리
		SetActorLocation(HitResult.Location); // 캐릭터 위치를 충돌 지점으로 설정
		CurrentVelocity.Z = 0.0f;			 // Z축 속도를 0으로 초기화
		bIsFalling = false;				   // 낙하 상태를 착지 상태로 전환
		return true;
	}

	// 충돌이 없으면 낙하 상태 유지
	bIsFalling = true; 
	return false;
}


void AChallengePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AChallengePlayerController* PlayerController = Cast<AChallengePlayerController>(GetController()))
		{
			if (PlayerController->IA_MoveUpDown)
			{
				EnhancedInputComponent->BindAction(
				PlayerController->IA_MoveUpDown,
				ETriggerEvent::Triggered,
				this,
				&AChallengePawn::MoveUpDown
				);
				
				EnhancedInputComponent->BindAction(
				PlayerController->IA_MoveUpDown,
				ETriggerEvent::Completed,
				this,
				&AChallengePawn::MoveUpDownEnd
				);
			}

			if (PlayerController->IA_MoveForwardBack)
			{
				EnhancedInputComponent->BindAction(
				PlayerController->IA_MoveForwardBack,
				ETriggerEvent::Triggered,
				this,
				&AChallengePawn::MoveForwardBack
				);
			}

			if (PlayerController->IA_MoveLeftRight)
			{
				EnhancedInputComponent->BindAction(
				PlayerController->IA_MoveLeftRight,
				ETriggerEvent::Triggered,
				this,
				&AChallengePawn::MoveLeftRight
				);
			}

			if (PlayerController->IA_Turn)
			{
				EnhancedInputComponent->BindAction(
				PlayerController->IA_Turn,
				ETriggerEvent::Triggered,
				this,
				&AChallengePawn::Turn
				);
			}

			if (PlayerController->IA_LookUpDown)
			{
				EnhancedInputComponent->BindAction(
				PlayerController->IA_LookUpDown,
				ETriggerEvent::Triggered,
				this,
				&AChallengePawn::LookUpDown
				);
			}
		}
		
	}

}

void AChallengePawn::MoveUpDown(const FInputActionValue& value)
{
	bIsMoving = true;
	CurrentVelocity.Z = 0.0f;
	const float Scale = value.Get<float>();
	if (Scale != 0.0f)
	{
		if (GetWorld())
		{
			FVector Movement = FVector::UpVector * Scale * MoveSpeed * GetWorld()->DeltaTimeSeconds;
			AddActorWorldOffset(Movement, false);	
		}
	}
}

void AChallengePawn::MoveUpDownEnd(const FInputActionValue& value)
{
	bIsMoving = false;
}

void AChallengePawn::MoveForwardBack(const FInputActionValue& value)
{
	const float Scale = value.Get<float>();
	if (Scale != 0.0f)
	{
		if (GetWorld())
		{
			FVector Movement = GetActorForwardVector() * Scale * MoveSpeed * GetWorld()->DeltaTimeSeconds;
			AddActorWorldOffset(Movement, false);
			
		}
	}
}

void AChallengePawn::MoveLeftRight(const FInputActionValue& value)
{
	const float Scale = value.Get<float>();
	if (Scale != 0.0f)
	{
		if (GetWorld())
		{
			FVector Movement = GetActorRightVector() * Scale * MoveSpeed * GetWorld()->DeltaTimeSeconds;
			AddActorWorldOffset(Movement, false);
			
		}
	}
}

void AChallengePawn::Turn(const FInputActionValue& value)
{
	const float TurnValue = value.Get<float>();
	if (Controller && TurnValue != 0.0f)
	{
		AddControllerYawInput(TurnValue);
	}
}

void AChallengePawn::LookUpDown(const FInputActionValue& value)
{
	const float LookUpValue = value.Get<float>();
	if (Controller && LookUpValue != 0.0f)
	{
		AddControllerPitchInput(LookUpValue);
	}
}

