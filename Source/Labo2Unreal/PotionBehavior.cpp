// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionBehavior.h"
#include "Avatar.h"
#include "ItemData.h"

void UPotionBehavior::Use(AAvatar* avatar, UItemData* itemData)
{
	avatar->AddPermanentStat(&itemData->Stat);
	avatar->PopItem();
}