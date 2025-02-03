// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StartaPawn.generated.h"

struct FInputActionValue;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TASK_7_API AStartaPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStartaPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, category = "Component")
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, category = "Component")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, category = "Component")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, category = "Component")
	UCameraComponent* Camera;

	UFUNCTION()
	void Move(const FInputActionValue& value);

	UFUNCTION()
	void Look(const FInputActionValue& value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;
};


