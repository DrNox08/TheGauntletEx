// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class THEGAUNTLETEX_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platform")
	FVector distanceToCover;

private:

	UPROPERTY(VisibleAnywhere, Category="Platform")
	TObjectPtr<UBoxComponent> Collision;
	
	UPROPERTY(VisibleAnywhere, Category="Platform")
	TObjectPtr<UStaticMeshComponent> PlatformMesh;

	// Punto A
	UPROPERTY(EditAnywhere, Category="Platform")
	FVector PointA;

	// Punto B
	UPROPERTY(EditAnywhere, Category="Platform")
	FVector PointB;

	// Velocità di movimento
	UPROPERTY(EditAnywhere, Category="Platform")
	float Speed = 200.f;

	// Opzionale: pausa agli estremi
	UPROPERTY(EditAnywhere, Category="Platform")
	float WaitTimeAtPoints = 0.5f;

	// interno
	bool bMovingToB = true; 
	float CurrentWaitTime = 0.f;

};
