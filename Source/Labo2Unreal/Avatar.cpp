// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "CharacterAttribute.h"
#include "Components/Image.h"
#include "ItemBehavior.h"
#include "ItemData.h"
#include "MyGameInstance.h"

// Sets default values
AAvatar::AAvatar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();

	LoadPlayerData();
}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AAvatar::GetHealth()
{
	return CurrentHealth;
}

float AAvatar::GetMaxHealth()
{
	if (IsValid(Attributes))
	{
		return Attributes->MaxHealth;
	}

	return 0.0f;
}

float AAvatar::GetPercentHealth()
{
	if (IsValid(Attributes))
	{
		if (Attributes->MaxHealth > 0)
		{
			return CurrentHealth / Attributes->MaxHealth;
		}
	}

	return 0.0f;
}

UTexture2D* AAvatar::GetPortrait()
{
	if (IsValid(Attributes))
	{
		return Attributes->Portrait;
	}

	return nullptr;
}

float AAvatar::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float MaxHealth = GetMaxHealth();
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	OnHealthChanged();

	if (GetIsDead())
	{
		ResetPlayerData();
		PlayerDeadDelegate.Broadcast();
	}

	SavePlayerData();

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

bool AAvatar::GetIsDead() const
{
	return CurrentHealth <= 0;
}

void AAvatar::AddOnDelegate(FScriptDelegate DelagateToAdd)
{
	if (DelagateToAdd.IsBound())
	{
		PlayerDeadDelegate.AddUnique(DelagateToAdd);
	}
}

bool AAvatar::CollectItem(UItemData* item)
{
	if (DataItemEquip == nullptr || NbItemEquip == 0)
	{
		NbItemEquip = 0;

		if (NbItemEquip < item->MaxStack)
		{
			NbItemEquip++;
			DataItemEquip = item;
			if (IsValid(item->ItemBehavior))
			{
				ItemBehavior = NewObject<UItemBehavior>(this, item->ItemBehavior.Get());
			}
			OnNbItemEquipChanged(NbItemEquip, DataItemEquip->Image);
			SavePlayerData();
			return true;
		}
	}
	else if (item == DataItemEquip)
	{
		if (NbItemEquip < item->MaxStack)
		{
			NbItemEquip++;
			OnNbItemEquipChanged(NbItemEquip, DataItemEquip->Image);
			SavePlayerData();
			return true;
		}
	}

	return false;
}

void AAvatar::PopItem()
{
	if (DataItemEquip == nullptr || NbItemEquip == 0) return;
	NbItemEquip--;
	if (NbItemEquip == 0)
	{
		DataItemEquip = nullptr;
		OnNbItemEquipChanged(NbItemEquip, nullptr);
	}
	else
	{
		OnNbItemEquipChanged(NbItemEquip, DataItemEquip->Image);
	}
	SavePlayerData();
}

void AAvatar::UseItem()
{
	if (DataItemEquip == nullptr || NbItemEquip == 0) return;

	ItemBehavior->Use(this, DataItemEquip);
}

void AAvatar::AddPermanentStat(FBonusesStat* bonusStat)
{
	CurrentHealth += bonusStat->Health;
	if (CurrentHealth > GetMaxHealth())
	{
		CurrentHealth = GetMaxHealth();
	}
	OnHealthChanged();
	SavePlayerData();
}

void AAvatar::SavePlayerData()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance))
	{
		GameInstance->PlayerData.PlayerDataInit = true;

		GameInstance->PlayerData.Health = CurrentHealth;

		GameInstance->PlayerData.DataItemEquip = DataItemEquip;
		GameInstance->PlayerData.NbItemEquip = NbItemEquip;
	}
}

void AAvatar::LoadPlayerData()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance))
	{
		if (GameInstance->PlayerData.PlayerDataInit)
		{
			CurrentHealth = GameInstance->PlayerData.Health;

			DataItemEquip = GameInstance->PlayerData.DataItemEquip;
			NbItemEquip = GameInstance->PlayerData.NbItemEquip;
			if (IsValid(DataItemEquip) && IsValid(DataItemEquip->ItemBehavior))
			{
				ItemBehavior = NewObject<UItemBehavior>(this, DataItemEquip->ItemBehavior.Get());
			}
		}
		else
		{
			if (IsValid(Attributes))
			{
				CurrentHealth = Attributes->MaxHealth;
			}
			SavePlayerData();
		}
	}
	OnHealthChanged();
	if (IsValid(DataItemEquip) && IsValid(DataItemEquip->Image))
	{
		OnNbItemEquipChanged(NbItemEquip, DataItemEquip->Image);
	}
	else
	{
		OnNbItemEquipChanged(NbItemEquip, nullptr);
	}
}

void AAvatar::ResetPlayerData()
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance))
	{
		GameInstance->PlayerData.PlayerDataInit = false;
	}
}