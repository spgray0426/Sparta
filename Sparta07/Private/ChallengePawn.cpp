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
	

	MoveSpeed = 600.0f;
}

void AChallengePawn::BeginPlay()
{
	Super::BeginPlay();
}

void AChallengePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

