// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/GameModeGauntlet.h"
#include "Character/MainCharacter.h"
#include "Controllers/GauntletController.h"


AGameModeGauntlet::AGameModeGauntlet()
{
	// Set default pawn class to our main
	DefaultPawnClass = AMainCharacter::StaticClass();
	
	// Set default player controller class to our controller
	PlayerControllerClass = AGauntletController::StaticClass();
}
