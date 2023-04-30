// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataPlayer.generated.h"

class AMyPlayer;
class UItemData;
class UItemBehavior;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UItemData* DataItem = nullptr;
	UPROPERTY()
	UItemBehavior* ItemBehavior = nullptr;
	UPROPERTY()
	int Nb = 0;
};

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API UDataPlayer : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	bool DataIsInit;

	UPROPERTY()
	float Health;

	UPROPERTY()
	TArray<FInventorySlot> Inventory;
	UPROPERTY()
	int IndexEquip;

	void InitData(AMyPlayer* Player);

public:
	UDataPlayer();

	void LoadData(AMyPlayer* Player);
	void SaveData(AMyPlayer* Player);
	void ResetData(AMyPlayer* Player);

	bool CollectItem(UItemData* item);
	void PopItemEquip();
	FInventorySlot GetInventorySlotEquip();
};
