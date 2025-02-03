// Fill out your copyright notice in the Description page of Project Settings.


#include "ChallengePlayerController.h"

#include "EnhancedInputSubsystems.h"

void AChallengePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (InputMappingContext)
	{
		if(ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			if(UEnhancedInputLocalPlayerSubsystem* Subsystem =	LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}
