// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gate.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GroundSwitch.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTouch, int32, SwitchID);


class UMaterialInstanceDynamic;

UCLASS()
class THEGAUNTLETEX_API AGroundSwitch : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGroundSwitch();
	
	//Event called by this class when switch is touched by player
	UPROPERTY(BlueprintAssignable, Category="Switch")
	FOnTouch OnSwitchTouched;
	
	//Internal
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Switch")
	TObjectPtr<UStaticMeshComponent> SwitchMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Switch")
	TObjectPtr<UBoxComponent> BoxCollision;
	//-----------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Switch")
	int SwitchID;

	UPROPERTY(editAnywhere, BlueprintReadWrite, Category="Switch")
	AGate* GateActor;

	UMaterialInstanceDynamic* DynamicMaterialInstance;

	FColor ActiveColor = FColor::Green;
	FColor InactiveColor = FColor::Red;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category ="Switch")
	int TouchTriggered();

	UFUNCTION(blueprintCallable, Category ="Switch")
	void ResetSwitch();
};
