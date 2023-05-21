// Fill out your copyright notice in the Description page of Project Settings.

#include "DataPlayer.h"
#include "MyPlayer.h"
#include "ItemData.h"
#include "ItemBehavior.h"

UDataPlayer::UDataPlayer()
{
	DataIsInit = false;
	Health = 0;
	IndexEquip = 0;
}

void UDataPlayer::InitData(AMyPlayer* Player)
{
	DataIsInit = true;

	Health = Player->GetMaxHealth();
	Inventory.Empty();
	for (int i = 0; i < InventorySize; i++)
	{
		Inventory.Add(FInventorySlot());
	}

	IndexEquip = 0;
}

void UDataPlayer::LoadData(AMyPlayer* Player)
{
	if (!DataIsInit)
	{
		InitData(Player);
	}

	Player->SetHealth(Health);
}

void UDataPlayer::SaveData(AMyPlayer* Player)
{
	Health = Player->GetHealth();
}

void UDataPlayer::ResetData()
{
	DataIsInit = false;

	DictPos.Empty();
	DictRotation.Empty();
}

bool UDataPlayer::CollectItem(UItemData* item)
{
	for(FInventorySlot& slot : Inventory)
	{
		if (slot.DataItem == item && slot.Nb < item->MaxStack)
		{
			slot.Nb += 1;
			return true;
		}
	}

	for (FInventorySlot& slot : Inventory)
	{
		if (slot.DataItem == nullptr)
		{
			slot.DataItem = item;
			slot.Nb = 1;
			if (item->ItemBehavior != nullptr)
			{
				slot.ItemBehavior = NewObject<UItemBehavior>(this, item->ItemBehavior.Get());
			}
			return true;
		}
	}

	return false;
}

void UDataPlayer::PopItemEquip()
{
	if (IndexEquip != -1)
	{
		Inventory[IndexEquip].Nb -= 1;
		if (Inventory[IndexEquip].Nb <= 0)
		{
			Inventory[IndexEquip].DataItem = nullptr;
			Inventory[IndexEquip].ItemBehavior = nullptr;
			Inventory[IndexEquip].Nb = 0;
		}
	}
}

FInventorySlot UDataPlayer::GetInventorySlotEquip()
{
	if (IndexEquip != -1)
	{
		return Inventory[IndexEquip];
	}
	return FInventorySlot();
}

FInventorySlot UDataPlayer::GetInventorySlotAt(int index)
{
	return Inventory[index];
}

void UDataPlayer::SetIndexEquip(int index)
{
	if (index < 0)
	{
		IndexEquip = 0;
	}
	else if (IndexEquip >= InventorySize)
	{
		IndexEquip = InventorySize - 1;
	}
	else
	{
		IndexEquip = index;
	}
}

int UDataPlayer::GetInventorySize()
{
	return InventorySize;
}

int UDataPlayer::GetIndexEquip()
{
	return IndexEquip;
}

bool UDataPlayer::Contain(UItemData* item)
{
	for (FInventorySlot& slot : Inventory)
	{
		if (slot.DataItem == item && slot.Nb > 0)
		{
			return true;
		}
	}
	return false;
}

void UDataPlayer::SetSpawn(FString levelName, FVector location, FRotator rotation)
{
	if (DictPos.Contains(levelName))
	{
		DictPos[levelName] = location;
	}
	else
	{
		DictPos.Add(levelName, location);
	}

	if (DictRotation.Contains(levelName))
	{
		DictRotation[levelName] = rotation;
	}
	else
	{
		DictRotation.Add(levelName, rotation);
	}
}

FVector UDataPlayer::GetSpawnLocation(FString levelName)
{
	if (DictPos.Contains(levelName))
	{
		return DictPos[levelName];
	}
	return FVector::ZeroVector;
}

FRotator UDataPlayer::GetSpawnRotation(FString levelName)
{
	if (DictRotation.Contains(levelName))
	{
		return DictRotation[levelName];
	}
	return FRotator::ZeroRotator;
}
