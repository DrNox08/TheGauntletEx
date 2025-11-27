// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEGAUNTLETEX_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	float InteractionDistance = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	float Radius = 300.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	bool bDrawBdebug = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	AActor* CurrentInteractable = nullptr;

	TArray<AActor*> ActorsFound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceChannels;
	

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void TryInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ScanInteractable();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
