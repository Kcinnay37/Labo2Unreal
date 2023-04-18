// Fill out your copyright notice in the Description page of Project Settings.

#include "TheBossAnimInstance.h"
#include "TheBossController.h"
#include "Avatar.h"

float UTheBossAnimInstance::GetPawnCurrentSpeed()
{
	const APawn* pawn = TryGetPawnOwner();
	if (pawn)
	{
		const FVector velocity = pawn->GetVelocity();

		return velocity.Size();
	}

	return 0.f;
}

float UTheBossAnimInstance::GetPawnDirection()
{
	const APawn* pawn = TryGetPawnOwner();
	if (pawn)
	{
		if (GetPawnCurrentSpeed() == 0)
		{
			return 0;
		}
		const FVector forward = pawn->GetActorForwardVector();
		const FVector right = pawn->GetActorRightVector();

		const FVector velocity = pawn->GetVelocity().GetSafeNormal();

		float dir = FMath::Acos(FVector::DotProduct(forward, velocity));
		dir = FMath::RadiansToDegrees(dir);

		if (FVector::DotProduct(velocity, right) < 0)
		{
			dir = -dir;
		}

		return dir;
	}

	return 0.0f;
}

bool UTheBossAnimInstance::GetPlayerCrouch()
{
	const APawn* pawn = TryGetPawnOwner();
	if (pawn == nullptr) return false;

	const AController* controller = pawn->GetController();
	if (!controller) return false;

	const ATheBossController* character = Cast<ATheBossController>(controller);
	if (character == nullptr) return false;

	return character->GetIsCrouch();
}

bool UTheBossAnimInstance::GetPlayerDanse()
{
	const APawn* pawn = TryGetPawnOwner();
	if (pawn == nullptr) return false;

	const AController* controller = pawn->GetController();
	if (!controller) return false;

	const ATheBossController* character = Cast<ATheBossController>(controller);
	if (character == nullptr) return false;

	return character->GetIsDancing();
}

float UTheBossAnimInstance::GetPlayerTurn()
{
	if (GetPawnCurrentSpeed() != 0)
	{
		return 0.0f;
	}

	const APawn* pawn = TryGetPawnOwner();
	if (pawn == nullptr) return false;

	const AController* controller = pawn->GetController();
	if (!controller) return false;

	const ATheBossController* character = Cast<ATheBossController>(controller);
	if (character == nullptr) return false;

	float turnValue = character->GetRotationSpeed() * 180 * 180;

	return turnValue;
}

bool UTheBossAnimInstance::GetPlayerDead()
{
	const APawn* pawn = TryGetPawnOwner();
	if (!pawn) return false;

	const AAvatar* player = Cast<AAvatar>(pawn);
	if (!player) return false;
	
	return player->GetIsDead();
}