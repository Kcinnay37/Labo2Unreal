// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBehavior.h"
#include "PotionBehavior.generated.h"

class AMyPlayer;
class UItemData;

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API UPotionBehavior : public UItemBehavior
{
	GENERATED_BODY()
public:
	virtual void Use(AMyPlayer* player, UItemData* itemData) override;
};
