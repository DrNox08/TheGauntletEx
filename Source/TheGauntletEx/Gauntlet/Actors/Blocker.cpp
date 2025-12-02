// Fill out your copyright notice in the Description page of Project Settings.

#include "Gauntlet/Actors/Blocker.h"
#include "Components/StaticMeshComponent.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

// Sets default values
ABlocker::ABlocker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlockerMesh = CreateDefaultSubobject<UStaticMeshComponent>("BlockerMesh");
	SetRootComponent(BlockerMesh);
}

// Called when the game starts or when spawned
void ABlocker::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = BlockerHealth;

	if (BlockerMesh)
	{
		DynamicMaterial = BlockerMesh->CreateAndSetMaterialInstanceDynamic(0);

		FLinearColor TmpColor;

		if (DynamicMaterial->GetVectorParameterValue(ColorParameterName, TmpColor))
		{
			OriginalColor = TmpColor;
		}
	}
}

// Called every frame
void ABlocker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlocker::GetDamage(float DamageAmount)
{
	if (CurrentHealth <= 0.f)
	{
		HandleDeath();
	}

	CurrentHealth -= DamageAmount;
	PlayHitEffect();
}

void ABlocker::PlayHitEffect()
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue(ColorParameterName, HitColor);

		//Set timer to reset color
		GetWorldTimerManager().ClearTimer(FlashTimerHandle);
		GetWorldTimerManager().SetTimer(FlashTimerHandle, this, &ABlocker::ResetColor, FlashDuration, false);
	}
}

void ABlocker::ResetColor()
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue(ColorParameterName, OriginalColor);
	}
}

void ABlocker::HandleDeath()
{
	if (DismantleGeometry)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Spawna un GeometryCollectionActor
		AGeometryCollectionActor* GCActor = GetWorld()->SpawnActor<AGeometryCollectionActor>(
			GetActorLocation(),
			GetActorRotation(),
			SpawnParams
		);

		FVector CubeScale = GetActorScale3D();
		GCActor->SetActorScale3D(CubeScale);


		if (GCActor)
		{
			UGeometryCollectionComponent* GCC = GCActor->GetGeometryCollectionComponent();
			if (GCC)
			{
				GCC->SetRestCollection(DismantleGeometry);

				GCC->SetSimulatePhysics(true);

				GCC->AddRadialImpulse(GetActorLocation() + FVector(0.f, 0.f, 5.f), 500.f, 1000.f,
				                      ERadialImpulseFalloff::RIF_Linear, true);
				
			}
		}

		GCActor->SetLifeSpan(3.f);
	}

	

	Destroy();
}

void ABlocker::Interact(AActor* Interactor)
{
	GetDamage(DamagePerHit);
}
