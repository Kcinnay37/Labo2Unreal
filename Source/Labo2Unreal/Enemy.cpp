// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Avatar.h"
#include"DrawDebugHelpers.h"
#include "AIController.h"
#include "Animation/AnimInstance.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MeleeWeapon.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (MeleeWeaponClass)
	{
		UWorld* World = GetWorld();
		MeleeWeapon = World->SpawnActor<AMeleeWeapon>(MeleeWeaponClass, FVector(), FRotator());

		const USkeletalMeshSocket* Socket = GetMesh()->GetSocketByName(FName("RightHandSocket"));
		if (Socket)
		{
			Socket->AttachActor(MeleeWeapon, GetMesh());
		}
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//brain
	if (!IsDead())
	{
		if (HasTarget())
		{
			if (CanSeeTarget())
			{
				DrawDebugSphere(GetWorld(), GetActorLocation(), AttackRange, 12, FColor::Yellow, false);
				if (CanAttackTarget())
				{
					AAIController* AI = Cast<AAIController>(GetController());
					if (AI)
					{
						AI->StopMovement();
					}
					AttackTarget(DeltaTime);
				}
				else
				{
					ChaseTarget();
				}
			}
		}
	}
}

void AEnemy::OnPerception(AActor* Other)
{
	if (Other)
	{
		AAvatar* Target = Cast<AAvatar>(Other);
		if (Target)
		{
			CurrTarget = Target;
		}
	}
}

void AEnemy::BeginAttack()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "BEGIN");
	if (MeleeWeapon)
	{
		MeleeWeapon->BeginSwing(this);
	}
}

void AEnemy::EndAttack()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "END");
	if (MeleeWeapon)
	{
		MeleeWeapon->ResetSwing();
	}
}

bool AEnemy::IsDead()
{
	// if Health <= 0;
	return false;
}

bool AEnemy::HasTarget()
{
	return CurrTarget != nullptr;
}

bool AEnemy::CanSeeTarget()
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector Start = GetActorLocation();
	FVector End = CurrTarget->GetActorLocation();

	UWorld* World = GetWorld();

	if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		//DrawDebugLine(World, Start, End, FColor::Red, false, 2.0f);
		if (Hit.Actor != nullptr)
		{
			bool IsPlayer = Cast<AAvatar>(Hit.Actor) != nullptr;
			if (IsPlayer)
			{
				return true;
			}
		}
	}

	return false;
}

bool AEnemy::CanAttackTarget()
{
	FVector Me = GetActorLocation();
	FVector Target = CurrTarget->GetActorLocation();
	float Distance = FVector::Distance(Me, Target);
	if (Distance < AttackRange)
	{
		return true;
	}

	return false;
}

void AEnemy::AttackTarget(float DeltaTime)
{
	AttackTimer -= DeltaTime;
	if (AttackTimer <= 0.0f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "ATTACK");
		if (AttackMontage)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance)
			{
				AnimInstance->Montage_JumpToSection(FName("Slash"), AttackMontage);
				AnimInstance->Montage_Play(AttackMontage);
			}
		}

		AttackTimer = AttackRate;
	}
}

void AEnemy::ChaseTarget()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, "CHASE");

	AAIController* AI = Cast<AAIController>(GetController());
	if (AI)
	{
		AI->MoveToLocation(CurrTarget->GetActorLocation());
	}
}

