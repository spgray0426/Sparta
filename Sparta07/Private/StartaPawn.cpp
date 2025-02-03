// Fill out your copyright notice in the Description page of Project Settings.


#include "StartaPawn.h"

#include "EnhancedInputComponent.h"
#include "SpartaPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AStartaPawn::AStartaPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
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

// Called when the game starts or when spawned
void AStartaPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AStartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	//인풋 컴포넌트를 향상된 입력 컴포넌트로 캐스트
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInputComponent->BindAction(
				PlayerController->MoveAction,
				ETriggerEvent::Triggered,
				this,
				&AStartaPawn::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInputComponent->BindAction(
				PlayerController->LookAction,
				ETriggerEvent::Triggered,
				this,
				&AStartaPawn::Look
				);
			}
		}
	}
}

void AStartaPawn::Move(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!MoveInput.IsNearlyZero())
	{
		if (Controller)
		{
			FVector CurrentLocation = GetActorLocation();
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			//이동방향
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			FVector ForwardMovement = ForwardDirection * MoveInput.Y;
			FVector RightMovement = RightDirection * MoveInput.X;
			FVector InputDirection = ForwardMovement + RightMovement;
			if (GetWorld())
			{
				FVector NewLocation = CurrentLocation + InputDirection * MoveSpeed * GetWorld()->GetDeltaSeconds();
				SetActorLocation(NewLocation);
			}
			if (!InputDirection.IsNearlyZero())
			{
				FRotator TargetRotation = InputDirection.Rotation();
				FRotator CurrentRotation = GetActorRotation();		
				FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
				
				SetActorRotation(SmoothRotation); 
			}
		
			
		}
	}
}

void AStartaPawn::Look(const FInputActionValue& value)
{
	const FVector2D LookInput = value.Get<FVector2D>();

	if (!LookInput.IsNearlyZero())
	{
		AddControllerYawInput(LookInput.X);
		AddControllerPitchInput(LookInput.Y);
	}
}
