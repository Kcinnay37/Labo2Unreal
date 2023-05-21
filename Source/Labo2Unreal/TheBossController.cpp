// Fill out your copyright notice in the Description page of Project Settings.

#include "TheBossController.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include"MyPlayer.h"
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

		InputComponent->BindAction("UseItem", IE_Pressed, this, &ATheBossController::UseItem);

		InputComponent->BindAction("Attack", IE_Pressed, this, &ATheBossController::Attack);

		InputComponent->BindAction("Interact", IE_Pressed, this, &ATheBossController::Interact);

		InputComponent->BindAction("Equip0", IE_Pressed, this, &ATheBossController::Equip0);
		InputComponent->BindAction("Equip1", IE_Pressed, this, &ATheBossController::Equip1);
	}
}

void ATheBossController::BeginPlay()
{
	APawn* pawn = GetPawn();
	if (!pawn) return;

	AMyPlayer* player = Cast<AMyPlayer>(pawn);
	if (!player) return;
	
	FScriptDelegate delegate;
	delegate.BindUFunction(this, FName("PlayerDead"));

	player->AddOnDelegate(delegate);
}

void ATheBossController::MoveForward(float axisValue)
{
	if (axisValue == 0 || isDead) return;

	APawn* controlledPawn = GetPawn();
	if (!controlledPawn) return;

	AMyPlayer* player = Cast<AMyPlayer>(controlledPawn);
	if (player)
	{
		if (player->GetIsAttacking()) return;
	}

	FVector forward = controlledPawn->GetActorForwardVector();

	SetCurrentRatioWalkSpeed();

	controlledPawn->AddMovementInput(forward, axisValue * currentRatioWalkSpeed);
}

void ATheBossController::MoveRight(float axisValue)
{
	if (axisValue == 0 || isDead) return;

	APawn* controlledPawn = GetPawn();
	if (!controlledPawn) return;

	AMyPlayer* player = Cast<AMyPlayer>(controlledPawn);
	if (player)
	{
		if (player->GetIsAttacking()) return;
	}

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
	if (isDancing || isDead) return;

	APawn* controlledPawn = GetPawn();
	if (!controlledPawn) return;

	AMyPlayer* player = Cast<AMyPlayer>(controlledPawn);
	if (player)
	{
		if (player->GetIsAttacking()) return;
	}

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
	if (isDead) return;

	APawn* controlledPawn = GetPawn();
	if (!controlledPawn) return;

	AMyPlayer* player = Cast<AMyPlayer>(controlledPawn);
	if (player)
	{
		if (player->GetIsAttacking()) return;
	}

	isDancing = !isDancing;

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

void ATheBossController::PlayerDead()
{
	EndCrouch();
	if (isDancing)
	{
		ChangeDanseState();
	}

	APawn* pawn = GetPawn();
	if (!pawn) return;
	pawn->bUseControllerRotationYaw = false;


	isDead = true;
}

void ATheBossController::UseItem()
{
	if (isDead) return;

	APawn* pawn = GetPawn();
	if (!IsValid(pawn)) return;

	AMyPlayer* player = Cast<AMyPlayer>(pawn);
	if (!IsValid(player)) return;

	player->UseItem();
}

void ATheBossController::Attack()
{
	if (isDead) return;
	if (isDancing)
	{
		ChangeDanseState();
	}
	if (isCrouch)
	{
		EndCrouch();
	}

	APawn* pawn = GetPawn();
	if (!IsValid(pawn)) return;

	AMyPlayer* player = Cast<AMyPlayer>(pawn);
	if (!IsValid(player)) return;

	player->Attack();
}

void ATheBossController::Interact()
{
	if (isDead) return;

	interactKeyPress.Broadcast();
}

void ATheBossController::Equip0()
{
	if (isDead) return;

	APawn* pawn = GetPawn();
	if (!IsValid(pawn)) return;

	AMyPlayer* player = Cast<AMyPlayer>(pawn);
	if (!IsValid(player)) return;

	player->SetIndexEquip(0);
}

void ATheBossController::Equip1()
{
	if (isDead) return;

	APawn* pawn = GetPawn();
	if (!IsValid(pawn)) return;

	AMyPlayer* player = Cast<AMyPlayer>(pawn);
	if (!IsValid(player)) return;

	player->SetIndexEquip(1);
}
