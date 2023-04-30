// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Avatar.h"
#include"DrawDebugHelpers.h"
#include "AIController.h"

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
					AttackTarget();
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

void AEnemy::AttackTarget()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "ATTACK");
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

