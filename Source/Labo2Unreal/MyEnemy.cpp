// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include"DrawDebugHelpers.h"
#include "AIController.h"
#include"MyPlayer.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MeleeWeapon.h"

AMyEnemy::AMyEnemy()
{
	
}

void AMyEnemy::OnDead()
{
	isDead = true;

	UnShowSlider();

	MeleeWeapon->SetLifeSpan(5);

	SetLifeSpan(5);
}

void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	isDead = false;

	startPoint = GetActorLocation();

	UnShowSlider();
}

void AMyEnemy::LoadData()
{
	Super::LoadData();

	CurrentHealth = GetMaxHealth();
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//brain
	if (!GetIsDead())
	{
		if (HasTarget())
		{
			bool canSeeTarget = CanSeeTarget();
			if (canSeeTarget || currTime > 0)
			{
				ShowSlider();
				RotateSlider();

				isRetourning = false;

				if (canSeeTarget)
				{
					currTime = timeAfterCantSee;
				}
				else
				{
					currTime -= DeltaTime;
				}

				AAIController* AI = Cast<AAIController>(GetController());
				if (CanAttackTarget())
				{
					if (AI)
					{
						AI->StopMovement();
						AI->SetFocus(CurrTarget);
						AI->SetFocalPoint(CurrTarget->GetActorLocation());
					}
					Attack();
				}
				else
				{
					if (AI)
					{
						AI->ClearFocus(EAIFocusPriority::Gameplay);
					}

					if (!GetIsAttacking())
					{
						ChaseTarget();
					}
				}
			}
			else
			{
				ReturnAtStartPoint();
			}
		}
		else
		{
			ReturnAtStartPoint();
		}
	}
	else if (!isDead)
	{
		OnDead();
	}
}

void AMyEnemy::OnPerception(AActor* Other)
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

void AMyEnemy::OnPerceptionEnd()
{
	CurrTarget = nullptr;
}

bool AMyEnemy::HasTarget()
{
	return CurrTarget != nullptr;
}

bool AMyEnemy::CanSeeTarget()
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector Start = GetActorLocation();
	FVector End = CurrTarget->GetActorLocation();

	UWorld* World = GetWorld();

	if (World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		if (Hit.Actor != nullptr)
		{
			//bool IsPlayer = Cast<AMyPlayer>(Hit.Actor) != nullptr;
			bool IsPlayer = Hit.Actor == CurrTarget;
			if (IsPlayer)
			{
				return true;
			}
		}
	}

	return false;
}

bool AMyEnemy::CanAttackTarget()
{
	FVector Me = GetActorLocation();
	FVector Target = CurrTarget->GetActorLocation();
	float Distance = FVector::Distance(Me, Target);
	if (Distance <= AttackRange)
	{
		return true;
	}

	return false;
}


void AMyEnemy::ChaseTarget()
{
	AAIController* AI = Cast<AAIController>(GetController());
	if (AI)
	{
		AI->MoveToLocation(CurrTarget->GetActorLocation());
	}
}

void AMyEnemy::ReturnAtStartPoint()
{
	if (!isRetourning)
	{
		UnShowSlider();

		AAIController* AI = Cast<AAIController>(GetController());
		if (AI)
		{
			AI->ClearFocus(EAIFocusPriority::Gameplay);

			AI->MoveToLocation(startPoint);
		}

		isRetourning = true;
	}
}