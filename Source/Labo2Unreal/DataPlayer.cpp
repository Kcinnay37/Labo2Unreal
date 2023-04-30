// Fill out your copyright notice in the Description page of Project Settings.

#include "DataPlayer.h"
#include "MyPlayer.h"
#include "ItemData.h"
#include "ItemBehavior.h"

UDataPlayer::UDataPlayer()
{
	DataIsInit = false;
	Health = 0;
	IndexEquip = -1;
}

void UDataPlayer::InitData(AMyPlayer* Player)
{
	DataIsInit = true;

	Health = Player->GetMaxHealth();
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

void UDataPlayer::ResetData(AMyPlayer* Player)
{
	DataIsInit = false;
}

bool UDataPlayer::CollectItem(UItemData* item)
{
	if (Inventory.Num() == 1)
	{
		if (Inventory[0].DataItem == item && Inventory[0].Nb < item->MaxStack)
		{
			Inventory[0].Nb += 1;
			return true;
		}
	}
	else
	{
		FInventorySlot InventorySlot;
		InventorySlot.DataItem = item;
		InventorySlot.Nb = 1;
		InventorySlot.ItemBehavior = NewObject<UItemBehavior>(this, item->ItemBehavior.Get());
		Inventory.Add(InventorySlot);
		IndexEquip = 0;
		return true;
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
			Inventory[IndexEquip].ItemBehavior = nullptr;
			Inventory.RemoveAt(IndexEquip);

			IndexEquip = -1;
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