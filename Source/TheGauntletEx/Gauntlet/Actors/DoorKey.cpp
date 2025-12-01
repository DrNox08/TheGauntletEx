// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Actors/DoorKey.h"

#include "Gauntlet/Character/MainCharacter.h"

// Sets default values
ADoorKey::ADoorKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(KeyTag);
}

// Called every frame
void ADoorKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float IncrementRotation = 20.f * DeltaTime;
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Roll += IncrementRotation;
	SetActorRotation(CurrentRotation);

}

void ADoorKey::Interact(AActor* Interactor)
{
	auto Character = Cast<AMainCharacter>(Interactor);
	if (Character)
	{
		Character->CollectItem(this);
		Destroy();
	}
}

