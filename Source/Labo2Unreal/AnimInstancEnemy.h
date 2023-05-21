// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstancEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API UAnimInstancEnemy : public UAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetIsDead();
};
