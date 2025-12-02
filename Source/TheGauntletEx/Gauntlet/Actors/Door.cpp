// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Actors/Door.h"

#include "Components/BoxComponent.h"
#include "Gauntlet/Character/MainCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup
	//Root
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);


	//Door Collision
	DoorCollision = CreateDefaultSubobject<UBoxComponent>("Door Collision");
	DoorCollision->SetupAttachment(Root);

	//Door Frame Mesh
	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door Frame Mesh");
	DoorFrameMesh->SetupAttachment(Root);

	//Door Mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door Mesh");
	DoorMesh->SetupAttachment(Root);

	SecondDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door Mesh 2");
	SecondDoorMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	InitialPivotalRotation = DoorMesh->GetRelativeRotation();
	TargetPivotalRotation = FRotator(0.f, -90.f, 0.f);

	InitialPositionSlidingDoor1 = DoorMesh->GetRelativeLocation();
	InitialPositionSlidingDoor2 = SecondDoorMesh->GetRelativeLocation();

	//Bind to switch event
	if (DoorSwitchActor)
	{
		DoorSwitchActor->OnSwitchInteracted.BindUObject(this, &ADoor::Interact);
		DoorSwitchActor->OnSwitchClosingBack.BindUObject(this, &ADoor::CloseBack);
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOpen)
	{
		if (!isSlidingDoor)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("APERTURA PIVOTAL"), true);
			FRotator CurrentRot = DoorMesh->GetRelativeRotation();
			FRotator NewRot = FMath::RInterpTo(DoorMesh->GetRelativeRotation(), TargetPivotalRotation, DeltaTime,
			                                   speed);
			DoorMesh->SetRelativeRotation(NewRot);
			if (CurrentRot.Equals(TargetPivotalRotation, 0.1f))
			{
				bIsOpen = false;
			}
		}
		else
		{
			UKismetSystemLibrary::PrintString(GetWorld(), TEXT("APERTURA SLIDING"), true);
			FVector CurrentPos1 = DoorMesh->GetRelativeLocation();
			FVector NewPos1 = FMath::VInterpTo(DoorMesh->GetRelativeLocation(), TargetPositionSlidingDoor1, DeltaTime,
			                                   speed);
			DoorMesh->SetRelativeLocation(NewPos1);

			FVector CurrentPos2 = SecondDoorMesh->GetRelativeLocation();
			FVector NewPos2 = FMath::VInterpTo(SecondDoorMesh->GetRelativeLocation(), TargetPositionSlidingDoor2,
			                                   DeltaTime,
			                                   speed);
			SecondDoorMesh->SetRelativeLocation(NewPos2);

			if (CurrentPos1.Equals(TargetPositionSlidingDoor1, 0.1f) &&
				CurrentPos2.Equals(TargetPositionSlidingDoor2, 0.1f))
			{
				bIsOpen = false;
			}
		}
	}

	if (bIsClosingBack)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("CHIUSURA SLIDING"), true);

		FVector CurrentPos1 = DoorMesh->GetRelativeLocation();
		FVector NewPos1 = FMath::VInterpTo(CurrentPos1, InitialPositionSlidingDoor1, DeltaTime, speed);
		DoorMesh->SetRelativeLocation(NewPos1);

		FVector CurrentPos2 = SecondDoorMesh->GetRelativeLocation();
		FVector NewPos2 = FMath::VInterpTo(CurrentPos2, InitialPositionSlidingDoor2, DeltaTime, speed);
		SecondDoorMesh->SetRelativeLocation(NewPos2);

		if (NewPos1.Equals(InitialPositionSlidingDoor1, 0.1f) &&
			NewPos2.Equals(InitialPositionSlidingDoor2, 0.1f))
		{
			bIsClosingBack = false;
		}
	}
}

void ADoor::Interact(AActor* Interactor)
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("APERTURA PORTA"), true);
	if (isSlidingDoor)
	{
		bIsOpen = true;
	}
	else
	{
		auto Character = Cast<AMainCharacter>(Interactor);
		if (!Character) return;

		for (auto item : Character->Inventory)
		{
			if (item->ActorHasTag(FName(KeyTagRequired)))
			{
				UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Porta sbloccata con la chiave!"), true);
				Character->Inventory.Remove(item);
				bIsOpen = true;
				break;
			}
		}
	}
}

void ADoor::CloseBack()
{
	bIsClosingBack = true;
}
