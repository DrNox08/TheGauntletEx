// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Gauntlet/Core/Interactable.h"
#include "Door.generated.h"

UCLASS()
class THEGAUNTLETEX_API ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Fields
	
	UPROPERTY(visibleAnywhere,BlueprintReadOnly, Category = "Door")
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(visibleAnywhere,BlueprintReadOnly, Category = "Door")
	TObjectPtr<UStaticMeshComponent> DoorFrameMesh;

	UPROPERTY(visibleAnywhere,BlueprintReadOnly, Category = "Door")
	TObjectPtr<UBoxComponent> DoorCollision;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor) override;

	UPROPERTY(blueprintreadwrite, EditAnywhere, Category="Door")
	bool isSlidingDoor = false;

};
