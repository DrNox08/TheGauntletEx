// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Actors/GroundSwitch.h"

// Sets default values
AGroundSwitch::AGroundSwitch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	SwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>("Switch Mesh");
	SwitchMesh->SetupAttachment(Root);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxCollision->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGroundSwitch::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterialInstance = SwitchMesh->CreateAndSetMaterialInstanceDynamic(0);
	
}

void AGroundSwitch::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!SwitchMesh || !SwitchMesh->GetStaticMesh() || !BoxCollision)
	{
		return;
	}
	
	const FBoxSphereBounds MeshBounds = SwitchMesh->GetStaticMesh()->GetBounds();
	
	const FVector MeshScale = SwitchMesh->GetComponentScale();
	const FVector BoxExtent = MeshBounds.BoxExtent * MeshScale;

	BoxCollision->SetBoxExtent(BoxExtent, true);
	
	BoxCollision->SetRelativeLocation(MeshBounds.Origin);
}

// Called every frame
void AGroundSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int AGroundSwitch::TouchTriggered()
{
	OnSwitchTouched.Broadcast(SwitchID);

	return SwitchID;
}

void AGroundSwitch::ResetSwitch()
{
}
