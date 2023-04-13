// Fill out your copyright notice in the Description page of Project Settings.

#include "TheBossController.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include <cmath>

void ATheBossController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &ATheBossController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ATheBossController::MoveRight);
		InputComponent->BindAxis("LookRight", this, &ATheBossController::LookRight);
		InputComponent->BindAxis("LookUp", this, &ATheBossController::LookUp);

		InputComponent->BindAction("Crouch", IE_Pressed, this, &ATheBossController::BeginCrouch);
		InputComponent->BindAction("Crouch", IE_Released, this, &ATheBossController::EndCrouch);

		InputComponent->BindAction("Dance", IE_Pressed, this, &ATheBossController::ChangeDanseState);

		InputComponent->BindAction("Run", IE_Pressed, this, &ATheBossController::BeginRun);
		InputComponent->BindAction("Run", IE_Released, this, &ATheBossController::EndRun);
	}
}

void ATheBossController::MoveForward(float axisValue)
{
	if (axisValue == 0) return;

	APawn* controlledPawn = GetPawn();
	if (!controlledPawn) return;

	FVector forward = controlledPawn->GetActorForwardVector();

	SetCurrentRatioWalkSpeed();

	controlledPawn->AddMovementInput(forward, axisValue * currentRatioWalkSpeed);
}

void ATheBossController::MoveRight(float axisValue)
{
	if (axisValue == 0) return;

	APawn* controlledPawn = GetPawn();
	if (!controlledPawn) return;

	FVector right = controlledPawn->GetActorRightVector();

	SetCurrentRatioWalkSpeed();

	controlledPawn->AddMovementInput(right, axisValue * currentRatioWalkSpeed);
}

void ATheBossController::BeginRun()
{
	isRun = true;
}

void ATheBossController::EndRun()
{
	isRun = false;
}

void ATheBossController::SetCurrentRatioWalkSpeed()
{
	if (isDancing)
	{
		currentRatioWalkSpeed = 0.0f;
	}
	else if (isRun && !isCrouch)
	{
		currentRatioWalkSpeed = 1.0f;
	}
	else
	{
		currentRatioWalkSpeed = walkRatio;
	}
}

void ATheBossController::BeginCrouch()
{
	if (isDancing) return;

	APawn* controlledPawn = GetPawn();
	if (!controlledPawn) return;

	ACharacter* myCharacter = Cast<ACharacter>(controlledPawn);
	if (!myCharacter) return;

	myCharacter->Crouch();

	isCrouch = true;
}

void ATheBossController::EndCrouch()
{
	APawn* controlledPawn = GetPawn();
	if (!controlledPawn) return;

	ACharacter* myCharacter = Cast<ACharacter>(controlledPawn);
	if (!myCharacter) return;

	myCharacter->UnCrouch();

	isCrouch = false;
}

bool ATheBossController::GetIsCrouch() const
{
	return isCrouch;
}

void ATheBossController::ChangeDanseState()
{
	isDancing = !isDancing;

	APawn* controlledPawn = GetPawn();
	if (!controlledPawn) return;

	if (isDancing)
	{
		EndCrouch();
		controlledPawn->bUseControllerRotationYaw = false;
	}
	else
	{
		controlledPawn->bUseControllerRotationYaw = true;
	}
}

bool ATheBossController::GetIsDancing() const
{
	return isDancing;
}

void ATheBossController::LookUp(float axisValue)
{
	float dt = GetWorld()->GetDeltaSeconds();

	AddPitchInput(axisValue * rotationSpeed * dt);
}

void ATheBossController::LookRight(float axisValue)
{
	float dt = GetWorld()->GetDeltaSeconds();

	AddYawInput(axisValue * rotationSpeed * dt);

	//int axisValueInt = static_cast<int>(std::round(axisValue));

	currentRotationSpeed = axisValue * dt;
}

float ATheBossController::GetRotationSpeed() const
{
	return currentRotationSpeed;
}