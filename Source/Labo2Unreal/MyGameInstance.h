// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UDataPlayer;

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	void ResetAllData();

	UPROPERTY(BlueprintReadOnly)
	UDataPlayer* PlayerData;
};
