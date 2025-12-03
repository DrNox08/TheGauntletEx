// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GauntletController.generated.h"

/**
 * 
 */

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
UCLASS()
class THEGAUNTLETEX_API AGauntletController : public APlayerController
{
	GENERATED_BODY()

	protected:
	
	/** Input mapping context for this player */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void RemoveInputs();
	
	
};
