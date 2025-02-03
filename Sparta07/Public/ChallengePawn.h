// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ChallengePawn.generated.h"

struct FInputActionValue;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TASK_7_API AChallengePawn : public APawn
{
	GENERATED_BODY()

public:

	AChallengePawn();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, category = "Component")
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, category = "Component")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, category = "Component")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, category = "Component")
	UCameraComponent* Camera;

	//Space/Shift
	UFUNCTION()
	void MoveUpDown(const FInputActionValue& value);
	//W/S
	UFUNCTION()
	void MoveForwardBack(const FInputActionValue& value);
	//A/D
	UFUNCTION()
	void MoveLeftRight(const FInputActionValue& value);
	//마우스 X
	UFUNCTION()
	void Turn(const FInputActionValue& value);
	//마우스 Y
	UFUNCTION()
	void LookUpDown(const FInputActionValue& value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed;
};
