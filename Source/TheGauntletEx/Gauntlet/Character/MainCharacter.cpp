// Fill out your copyright notice in the Description page of Project Settings.


#include "Gauntlet/Character/MainCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gauntlet/Core/InteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractionComponent = FindComponentByClass<UInteractionComponent>();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Setw up action bindings

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMainCharacter::TryInteract);
		
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("SetupInput: EnhancedInput OK"));
		UE_LOG(LogTemp, Warning, TEXT("MoveAction      = %s"), *GetNameSafe(MoveAction));
		UE_LOG(LogTemp, Warning, TEXT("LookAction      = %s"), *GetNameSafe(LookAction));
		UE_LOG(LogTemp, Warning, TEXT("MouseLookAction = %s"), *GetNameSafe(MouseLookAction));
		UE_LOG(LogTemp, Warning, TEXT("JumpAction      = %s"), *GetNameSafe(JumpAction));
		UE_LOG(LogTemp, Warning, TEXT("InteractAction  = %s"), *GetNameSafe(InteractAction));
	}

}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector Right   = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(Forward, MovementVector.Y);
	AddMovementInput(Right, MovementVector.X);
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	// route the input
	
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AMainCharacter::TryInteract()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("PREMUTO E"), true);
	if (InteractionComponent)
	{
		InteractionComponent->TryInteract();
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("No Interaction Component found"), true);
	}
}

void AMainCharacter::CollectItem(AActor* ItemActor)
{
	Inventory.AddUnique(ItemActor);
}




