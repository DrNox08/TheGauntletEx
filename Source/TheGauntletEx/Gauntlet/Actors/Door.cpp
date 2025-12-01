// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Actors/Door.h"

#include "Components/BoxComponent.h"
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
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsOpen)
	{
		FRotator CurrentRot = DoorMesh->GetRelativeRotation();
		FRotator NewRot = FMath::RInterpTo(DoorMesh->GetRelativeRotation(), TargetPivotalRotation, DeltaTime, speed);
		DoorMesh->SetRelativeRotation(NewRot);
		if(CurrentRot.Equals(TargetPivotalRotation, 0.1f))
		{
			bIsOpen = false;
		}
	}
}

void ADoor::Interact(AActor* Interactor)
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("APERTURA PORTA"), true);
	if (isSlidingDoor)
	{
		//Implement sliding door logic here
	}
	else
	{
		bIsOpen = true;
	}
		
}

