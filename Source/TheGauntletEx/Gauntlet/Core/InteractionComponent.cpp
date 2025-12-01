// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Core/InteractionComponent.h"

#include "Interactable.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UInteractionComponent::TryInteract()
{
	if (CurrentInteractable)
	{
		IInteractable* Interactable = Cast<IInteractable>(CurrentInteractable);
		
		if (Interactable) 
		{
			Interactable->Interact(GetOwner());
		}
	}
	
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Tracing Interactables
	ScanInteractable();
}

void UInteractionComponent::ScanInteractable()
{
	AActor* Owner = GetOwner();
	if(!Owner) return;
	
	const FVector Start = Owner->GetActorLocation();
	const FVector ForwardVector = Owner->GetActorForwardVector();
	const FVector End = ((ForwardVector * InteractionDistance) + Start);

	TArray<FHitResult> Hits;
	TArray<AActor*> ActorsToIgnore;

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		this->GetOwner()->GetWorld(),
		Start,
		End,
		Radius,
		TraceChannels,
		false,
		ActorsToIgnore,
		bDrawBdebug ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		Hits,
		true
		);

	for (FHitResult Results : Hits)
	{
		ActorsFound.AddUnique(Results.GetActor());
	}

	float minDistance = FLT_MAX;

	for (AActor* Actor : ActorsFound)
	{
		float distance = FVector::Dist(Actor->GetActorLocation(), Owner->GetActorLocation());
		if (distance < minDistance)
		{
			minDistance = distance;
			CurrentInteractable = Actor;
		}
	}

	if (CurrentInteractable)
	{
		//UKismetSystemLibrary::PrintString(this->GetOwner()->GetWorld(), CurrentInteractable->GetName(), true);
	}

	

	
	
	
}
