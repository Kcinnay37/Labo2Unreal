// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "CharacterAttribute.h"
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

	LoadData();
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
	SaveData();

	if (GetIsDead())
	{
		ResetData();
		AvatarDeadDelegate.Broadcast();
	}

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void AAvatar::SaveData()
{
}

void AAvatar::LoadData()
{
}

void AAvatar::ResetData()
{
}

void AAvatar::SetHealth(float Healt)
{
	if (Healt < 0)
	{
		CurrentHealth = 0;
	}
	else if (Healt > GetMaxHealth())
	{
		CurrentHealth = GetMaxHealth();
	}
	else
	{
		CurrentHealth = Healt;
	}

	OnHealthChanged();
}

bool AAvatar::GetIsDead() const
{
	return CurrentHealth <= 0;
}

void AAvatar::AddOnDelegate(FScriptDelegate DelagateToAdd)
{
	if (DelagateToAdd.IsBound())
	{
		AvatarDeadDelegate.AddUnique(DelagateToAdd);
	}
}

void AAvatar::AddPermanentStat(FBonusesStat* bonusStat)
{
	CurrentHealth += bonusStat->Health;
	if (CurrentHealth > GetMaxHealth())
	{
		CurrentHealth = GetMaxHealth();
	}

	OnHealthChanged();
	SaveData();
}