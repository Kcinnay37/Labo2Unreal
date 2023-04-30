// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "MyGameInstance.h"
#include "DataPlayer.h"
#include "ItemBehavior.h"
#include "ItemData.h"

bool AMyPlayer::CollectItem(UItemData* item)
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance) && IsValid(GameInstance->PlayerData))
	{
		if (GameInstance->PlayerData->CollectItem(item))
		{
			FInventorySlot InventorySlot = GameInstance->PlayerData->GetInventorySlotEquip();

			if (InventorySlot.DataItem != nullptr)
			{
				OnItemEquipChanged(InventorySlot.Nb, InventorySlot.DataItem->Image);
			}
			else
			{
				OnItemEquipChanged(0, nullptr);
			}
			return true;
		}
	}

	return false;
}

void AMyPlayer::PopItem()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance) && IsValid(GameInstance->PlayerData))
	{
		GameInstance->PlayerData->PopItemEquip();

		FInventorySlot InventorySlot = GameInstance->PlayerData->GetInventorySlotEquip();

		if (InventorySlot.DataItem != nullptr)
		{
			OnItemEquipChanged(InventorySlot.Nb, InventorySlot.DataItem->Image);
		}
		else
		{
			OnItemEquipChanged(0, nullptr);
		}
	}
}

void AMyPlayer::UseItem()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance) && IsValid(GameInstance->PlayerData))
	{
		FInventorySlot InventorySlot = GameInstance->PlayerData->GetInventorySlotEquip();

		if (InventorySlot.DataItem != nullptr && InventorySlot.ItemBehavior != nullptr)
		{
			InventorySlot.ItemBehavior->Use(this, InventorySlot.DataItem);
		}
	}
}

void AMyPlayer::SaveData()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance) && IsValid(GameInstance->PlayerData))
	{
		GameInstance->PlayerData->SaveData(this);
	}
}

void AMyPlayer::LoadData()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance) && IsValid(GameInstance->PlayerData))
	{
		GameInstance->PlayerData->LoadData(this);

		OnHealthChanged();

		FInventorySlot InventorySlot = GameInstance->PlayerData->GetInventorySlotEquip();
		if (InventorySlot.DataItem != nullptr)
		{
			OnItemEquipChanged(InventorySlot.Nb, InventorySlot.DataItem->Image);
		}
		else
		{
			OnItemEquipChanged(0, nullptr);
		}
	}
}

void AMyPlayer::ResetData()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance) && IsValid(GameInstance->PlayerData))
	{
		GameInstance->PlayerData->ResetData(this);
	}
}
