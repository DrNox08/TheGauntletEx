// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Actors/Gate.h"

#include "GroundSwitch.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AGate::AGate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void AGate::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// This function is called in Blueprint
void AGate::CheckSwitches(int ActivatedSwitchID)
{
	ActivatedSwitchesIDs.Add(ActivatedSwitchID);
	FString TotatlyActivated = FString::FromInt(ActivatedSwitchesIDs.Num());
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Activated Switches: %s"), *TotatlyActivated),
	                                  true);

	if (ActivatedSwitchesIDs[CurrentSwitchIndex] == CorrectOrderIDs[CurrentSwitchIndex])
	{
		CurrentSwitchIndex++;
		if (CurrentSwitchIndex >= CorrectOrderIDs.Num()) Open();
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("WRONG SWITCH ORDER! RESETTING..."), true);
		ActivatedSwitchesIDs.Empty();
		CurrentSwitchIndex = 0;
		OnResetSwitches.Broadcast();
	}
}


void AGate::Open()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GATE OPENED!"), true);

	if (OnPuzzleCompleted.IsBound())
	{
		OnPuzzleCompleted.Broadcast();
	}

	// Save initial pos and target pos
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + FVector(0.f, 0.f, MoveHeight);

	//Reset timer
	ElapsedTime = 0.f;

	//Clear any timer
	GetWorldTimerManager().ClearTimer(GateTimerHandle);

	const float TimeRate = 0.02f;

	//Start time that calls a function to update gate movement
	GetWorldTimerManager().SetTimer(GateTimerHandle, this, &AGate::UpdateGateMovement, TimeRate, true);
}

void AGate::UpdateGateMovement()
{
	if (!GetWorld()) return;

	const float TimeRate = 0.02f;
	ElapsedTime += TimeRate;

	float Alpha = FMath::Clamp(ElapsedTime/MoveDuration, 0.f, 1.f);
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);
	SetActorLocation(NewLocation);

	if (Alpha>=1.f)
	{
		GetWorldTimerManager().ClearTimer(GateTimerHandle);
		ElapsedTime = 0.f;

		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GATE FINISHED!"), true);
	}
}
