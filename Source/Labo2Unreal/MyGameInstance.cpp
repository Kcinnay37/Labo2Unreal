// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "DataPlayer.h"

void UMyGameInstance::Init()
{
	PlayerData = NewObject<UDataPlayer>();
}

void UMyGameInstance::ResetAllData()
{
	PlayerData->ResetData();
}
