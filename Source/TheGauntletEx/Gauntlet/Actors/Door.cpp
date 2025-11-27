// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Actors/Door.h"

#include "Components/BoxComponent.h"

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
	DoorCollision->SetupAttachment(RootComponent);

	//Door Frame Mesh
	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door Mesh");
	DoorFrameMesh->SetupAttachment(RootComponent);
	
	//Door Mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door Frame Mesh");
	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::Interact(AActor* Interactor)
{
	//TODO: Open Door
}

