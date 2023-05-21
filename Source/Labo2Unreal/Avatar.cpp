// Fill out your copyright notice in the Description page of Project Settings.


#include "Avatar.h"
#include "CharacterAttribute.h"
#include "ItemData.h"
#include "MyGameInstance.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MeleeWeapon.h"

// Sets default values
AAvatar::AAvatar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();

	LoadData();

	bAnimAttackPlaying = false;

	if (Attributes && Attributes->MeleeWeaponClass)
	{
		UWorld* World = GetWorld();
		MeleeWeapon = World->SpawnActor<AMeleeWeapon>(Attributes->MeleeWeaponClass, FVector(), FRotator());

		const USkeletalMeshSocket* Socket = GetMesh()->GetSocketByName(FName("RightHandSocket"));
		if (Socket)
		{
			Socket->AttachActor(MeleeWeapon, GetMesh());
		}
	}
}

void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackTimer -= DeltaTime;
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
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && Attributes && Attributes->AttackMontage)
		{
			AnimInstance->Montage_Stop(0.10f, Attributes->AttackMontage);
			if (MeleeWeapon)
			{
				MeleeWeapon->ResetSwing();
			}
		}

		ResetData();
		Dead();
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

void AAvatar::BeginAttack()
{
	if (MeleeWeapon)
	{
		MeleeWeapon->BeginSwing(this);
	}
}

void AAvatar::EndAttack()
{
	if (MeleeWeapon)
	{
		MeleeWeapon->ResetSwing();
	}
}

void AAvatar::BeginAttackAnim()
{
	bAnimAttackPlaying = true;
}

void AAvatar::EndAttackAnim()
{
	bAnimAttackPlaying = false;
}

void AAvatar::Attack()
{
	if (AttackTimer <= 0.0f && Attributes)
	{
		if (Attributes->AttackMontage)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				AnimInstance->Montage_JumpToSection(FName("Slash"), Attributes->AttackMontage);
				AnimInstance->Montage_Play(Attributes->AttackMontage);
			}
		}

		AttackTimer = Attributes->AttackRate;
	}
}

bool AAvatar::GetIsAttacking()
{
	return bAnimAttackPlaying;
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