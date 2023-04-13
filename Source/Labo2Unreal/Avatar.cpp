// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "CharacterAttribute.h"

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

	if (IsValid(Attributes))
	{
		CurrentHealth = Attributes->MaxHealth;
	}
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

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

