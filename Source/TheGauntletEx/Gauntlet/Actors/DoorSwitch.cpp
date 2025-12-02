// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Actors/DoorSwitch.h"

// Sets default values
ADoorSwitch::ADoorSwitch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADoorSwitch::BeginPlay()
{
	Super::BeginPlay();

	bIsInteracted = false;

	InitialRotation = GetActorRotation();
}

// Called every frame
void ADoorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoorSwitch::Interact(AActor* Interactor)
{
	if (bIsInteracted) return;
	if (OnSwitchInteracted.IsBound())
	{
		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Pitch = -180.f;
		SetActorRotation(CurrentRotation);
		OnSwitchInteracted.Execute(Interactor);
		bIsInteracted = true;

		//Set timer to reset switch
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ADoorSwitch::ResetSwitch, SwitchResetDelay, false);
	}
}

void ADoorSwitch::ResetSwitch()
{
	if (OnSwitchClosingBack.IsBound()) OnSwitchClosingBack.Execute();
	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ADoorSwitch::SafeResetSwitch, 3.f, false);
}

void ADoorSwitch::SafeResetSwitch() // Visto che non ho rifattorizzato questa é un antispam del tasto E
{
	bIsInteracted = false;
	SetActorRotation(InitialRotation);
}
