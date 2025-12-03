

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetSwitches);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleCompleted);

class AGroundSwitch;

UCLASS()
class THEGAUNTLETEX_API AGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGate();

	//Event to reset switches
	UPROPERTY(BlueprintAssignable)
	FOnResetSwitches OnResetSwitches;

	FOnPuzzleCompleted OnPuzzleCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gate")
	TArray<TObjectPtr<AGroundSwitch>> LinkedSwitches;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gate")
	TArray<int> CorrectOrderIDs;

	// Gate movement
	UPROPERTY(EditAnywhere, Category ="Gate")
	float MoveDuration = 2.f;

	UPROPERTY(EditAnywhere, Category ="Gate")
	float MoveHeight = 500.f;

	FTimerHandle GateTimerHandle;
	float ElapsedTime = 0.f;
	FVector StartLocation;
	FVector EndLocation;
	//------------------------------------
	TArray<int> ActivatedSwitchesIDs;

	int CurrentSwitchIndex = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateGateMovement();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,Category ="Switch")
	void CheckSwitches(int ActivatedSwitchID);

	void Open();

};
