// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gauntlet/Core/Interactable.h"
#include "DoorSwitch.generated.h"

DECLARE_DELEGATE_OneParam(FOnSwitchInteracted, AActor* /*Interactor*/);
DECLARE_DELEGATE(FOnSwitchClosingBack);

UCLASS()
class THEGAUNTLETEX_API ADoorSwitch : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorSwitch();

	FOnSwitchInteracted OnSwitchInteracted;
	FOnSwitchClosingBack OnSwitchClosingBack;

	FRotator InitialRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Switch")
	float SwitchResetDelay = 3.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsInteracted;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact(AActor* Interactor) override;

	void ResetSwitch();

	void SafeResetSwitch(); // Non avevo voglia di rifattorizzare con un enum

};
