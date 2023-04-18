// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UItemData;

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
public:
	bool PlayerDataInit;

	float Health;

	UItemData* DataItemEquip;
	int NbItemEquip;
};

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FPlayerData PlayerData;
};
