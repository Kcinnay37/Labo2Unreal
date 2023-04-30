// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/ObjectMacros.h"
#include "ItemData.generated.h"

class UItemBehavior;

USTRUCT(BlueprintType)
struct FBonusesStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;
};

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API UItemData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBonusesStat Stat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxStack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool PopOnUse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UItemBehavior> ItemBehavior;
};
