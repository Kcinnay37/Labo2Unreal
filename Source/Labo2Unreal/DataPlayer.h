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
	bool DataIsInit;

	float Health;

	UPROPERTY()
	TArray<FInventorySlot> Inventory;
	int IndexEquip;
	int InventorySize = 2;

	UPROPERTY()
	TMap<FString, FVector> DictPos;
	UPROPERTY()
	TMap<FString, FRotator> DictRotation;

	void InitData(AMyPlayer* Player);

public:
	UDataPlayer();

	void LoadData(AMyPlayer* Player);
	void SaveData(AMyPlayer* Player);
	void ResetData();

	bool CollectItem(UItemData* item);
	void PopItemEquip();
	FInventorySlot GetInventorySlotEquip();
	FInventorySlot GetInventorySlotAt(int index);

	void SetIndexEquip(int index);
	int GetInventorySize();
	int GetIndexEquip();

	bool Contain(UItemData* item);

	UFUNCTION(BlueprintCallable)
	void SetSpawn(FString levelName, FVector location, FRotator rotation);
	FVector GetSpawnLocation(FString levelName);
	FRotator GetSpawnRotation(FString levelName);
};
