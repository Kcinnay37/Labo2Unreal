// Copyright Epic Games, Inc. All Rights Reserved.


#include "Labo2UnrealGameModeBase.h"
#include "MyGameInstance.h"
#include "DataPlayer.h"

APawn* ALabo2UnrealGameModeBase::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance) && IsValid(GameInstance->PlayerData))
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FString levelName = world->GetMapName();

			FVector location = GameInstance->PlayerData->GetSpawnLocation(levelName);
			FRotator rotation = GameInstance->PlayerData->GetSpawnRotation(levelName);

			if (!location.IsZero())
			{
				StartSpot->GetRootComponent()->SetMobility(EComponentMobility::Movable);

				StartSpot->SetActorLocation(location);
				StartSpot->SetActorRotation(rotation);

				GameInstance->PlayerData->SetSpawn(levelName, FVector::ZeroVector, FRotator::ZeroRotator);
			}
		}
	}

    return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
}

bool ALabo2UnrealGameModeBase::SpawnDefaultPawnFor_Validate(AController* NewPlayer, AActor* StartSpot)
{
    return true;
}