// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Actors/MovingPlatform.h"

#include "Components/BoxComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Root generico
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Collision
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(Root);
	Collision->SetBoxExtent(FVector(100.f, 100.f, 20.f)); 
	Collision->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	// Mesh
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMesh->SetupAttachment(Root);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	distanceToCover -= GetActorLocation();
	PointB = GetActorLocation() + distanceToCover;
	PointA = GetActorLocation();
	
}

void AMovingPlatform::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (Collision && PlatformMesh)
	{
		// Extent della box (metà dimensione)
		const FVector BoxExtent = Collision->GetUnscaledBoxExtent();

		// Se usi il Cube di default di UE (100 unit per lato)
		const float BaseHalfSize = 50.f; // 100 / 2

		FVector NewScale(
			BoxExtent.X / BaseHalfSize,
			BoxExtent.Y / BaseHalfSize,
			BoxExtent.Z / BaseHalfSize
		);

		PlatformMesh->SetRelativeScale3D(NewScale);

		// Allinea la mesh alla box (se non lo è già)
		PlatformMesh->SetRelativeLocation(Collision->GetRelativeLocation());
		PlatformMesh->SetRelativeRotation(Collision->GetRelativeRotation());
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = bMovingToB ? PointB : PointA;

	// --- Pausa agli estremi ---
	if (CurrentWaitTime > 0.f)
	{
		CurrentWaitTime -= DeltaTime;
		return;
	}

	// --- Movimento ---
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * Speed * DeltaTime;

	SetActorLocation(NewLocation);

	// --- Controllo arrivo al punto ---
	const float Distance = FVector::Dist(NewLocation, TargetLocation);
	if (Distance <= 5.f)
	{
		bMovingToB = !bMovingToB; // inverti direzione
		CurrentWaitTime = WaitTimeAtPoints; // reset della pausa
	}

}

