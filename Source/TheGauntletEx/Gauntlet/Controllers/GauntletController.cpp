// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Controllers/GauntletController.h"
#include "EnhancedInputSubsystems.h"
#include  "Engine/LocalPlayer.h"


void AGauntletController::BeginPlay()
{
	Super::BeginPlay();

	//aggiungere widget quando servirá
}

void AGauntletController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (IsLocalPlayerController())
	{
		// add the input mapping context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}


