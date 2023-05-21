// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Blueprint/UserWidget.h"
#include "CharacterAttribute.generated.h"

class AMeleeWeapon;
/**
 * 
 */
UCLASS()
class LABO2UNREAL_API UCharacterAttribute : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Portrait;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackRate;
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMeleeWeapon> MeleeWeaponClass;
};
