// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar.h"
#include "MyPlayer.generated.h"

class UItemData;
class UItemBehavior;

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API AMyPlayer : public AAvatar
{
	GENERATED_BODY()
public:
	bool CollectItem(UItemData* item);
	void PopItem();
	void UseItem();

	virtual void SaveData() override;
	virtual void LoadData() override;
	virtual void ResetData() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnItemEquipChanged(int currNb, UTexture2D* currTexture);
};
