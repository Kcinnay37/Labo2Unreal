// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstancEnemy.h"
#include "Avatar.h"

bool UAnimInstancEnemy::GetIsDead()
{
	APawn* pawn = TryGetPawnOwner();
	if (!pawn) return false;

	AAvatar* avatar = Cast<AAvatar>(pawn);
	if (!avatar) return false;

	return avatar->GetIsDead();
}