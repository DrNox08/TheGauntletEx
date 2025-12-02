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
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Activated Switches: %s"), *TotatlyActivated), true);

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
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GATE OPEN"), true);

	// Static = sopravvivono dopo l'uscita dalla funzione
	static float Time = 0.0f;
	static FTimerHandle TimerHandle;

	// Imposto i parametri del movimento
	const float MoveDuration = 10.0f;           // secondi
	const float TimerRate   = 0.01f;           // intervallo chiamata Timer

	// Prendo posizione iniziale ogni volta che chiamo Open (così se richiami, riparte da dove è)
	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation   = StartLocation + FVector(0.f, 0.f, 500.f);

	// Reset del tempo ogni volta che fai partire il movimento
	Time = 0.0f;

	// Se esiste un timer precedente su questa funzione, lo fermo prima di ripartire
	GetWorldTimerManager().ClearTimer(TimerHandle);

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, StartLocation, EndLocation, MoveDuration, TimerRate]()
	{
		// Incremento il tempo in base al rate del timer
		Time += TimerRate;

		float Alpha = FMath::Clamp(Time / MoveDuration, 0.0f, 1.0f);
		FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);
		SetActorLocation(NewLocation);

		if (Alpha >= 1.0f)
		{
			// Movimento completato: fermo il timer
			GetWorldTimerManager().ClearTimer(TimerHandle);
			Time = 0.0f; // opzionale: reset per riutilizzare Open()
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("GATE MOVEMENT DONE"), true);
		}
	});

	// Avvio del timer (looping = true, ma lo fermiamo noi quando Alpha >= 1)
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		TimerDelegate,
		TimerRate,
		true
	);

	//TODO: DISABLE COLLISION FOR EVERY SWITCH
	
	
	
}
