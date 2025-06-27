// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AFpsCharacter::AFpsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFpsCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hello world! AFpsProjectGameModeBase"));
}

void AFpsCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerController* PlayerController = Cast<APlayerController>(NewController);
	if (PlayerController)
	{
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (LocalPlayer)
		{
			UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			if (InputSubsystem)
			{
				InputSubsystem->AddMappingContext(InputMapping, 0);
			}
		}
	}
}

// Called every frame
void AFpsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFpsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInput)
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFpsCharacter::Move);
		}

		if (LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFpsCharacter::Look);
		}

		if (JumpAction)
		{
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &AFpsCharacter::StartJump);
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFpsCharacter::StopJump);
		}
	}
}

void AFpsCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputDirection = Value.Get<FVector2D>();
	FVector MoveDirection = GetActorForwardVector() * InputDirection.Y + GetActorRightVector() * InputDirection.X;
	AddMovementInput(MoveDirection);
}

void AFpsCharacter::Look(const FInputActionValue& Value)
{
	FVector2D InputDirection = Value.Get<FVector2D>();

	if (InputDirection.X != 0.f)
	{
		AddControllerYawInput(InputDirection.X);
	}

	if (InputDirection.Y != 0.f)
	{
		AddControllerPitchInput(-InputDirection.Y);
	}
}

void AFpsCharacter::StartJump()
{
	bPressedJump = true;
}

void AFpsCharacter::StopJump()
{
	bPressedJump = false;
}