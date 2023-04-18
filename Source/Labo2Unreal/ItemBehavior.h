// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBehavior.generated.h"

class AAvatar;
class UItemData;

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API UItemBehavior : public UObject
{
	GENERATED_BODY()

public:
	virtual void Use(AAvatar* avatar, UItemData* itemData);
};
