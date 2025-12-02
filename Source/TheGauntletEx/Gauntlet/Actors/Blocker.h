// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gauntlet/Core/Interactable.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blocker.generated.h"

class UStaticMeshComponent;
class UGeometryCollection;
class UMaterialInstanceDynamic;
struct FTimerHandle;

UCLASS()

class THEGAUNTLETEX_API ABlocker : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlocker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Mesh")
	TObjectPtr<UStaticMeshComponent> BlockerMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blocker")
	float BlockerHealth = 100.f;

	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blocker")
	float DamagePerHit = 20.f;

	//Visual
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blocker")
	float FlashDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blocker")
	FLinearColor HitColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blocker")
	FName ColorParameterName = "BaseColor";

	// Geometry
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Blocker")
	TObjectPtr<UGeometryCollection> DismantleGeometry;

private:

	UMaterialInstanceDynamic* DynamicMaterial;
	FLinearColor OriginalColor;
	
	FTimerHandle FlashTimerHandle;

	void GetDamage(float DamageAmount);
	void PlayHitEffect();
	void ResetColor();
	void HandleDeath();

	void Interact(AActor* Interactor) override;

};
