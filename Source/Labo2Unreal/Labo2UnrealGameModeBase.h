// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Labo2UnrealGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API ALabo2UnrealGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnWinGame();

	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;

	virtual bool SpawnDefaultPawnFor_Validate(AController* NewPlayer, AActor* StartSpot);
};
