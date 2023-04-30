// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionBehavior.h"
#include "MyPlayer.h"
#include "ItemData.h"

void UPotionBehavior::Use(AMyPlayer* player, UItemData* itemData)
{
	player->AddPermanentStat(&itemData->Stat);

	if (itemData->PopOnUse)
	{
		player->PopItem();
	}
}