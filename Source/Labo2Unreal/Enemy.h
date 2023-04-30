// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AAvatar;

UCLASS()
class LABO2UNREAL_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnPerception(AActor* Other);

private:
	AAvatar* CurrTarget = nullptr;
	UPROPERTY(EditAnywhere)
	float AttackRange = 200.0f;

	//brain function
	bool IsDead();
	bool HasTarget();
	bool CanSeeTarget();
	bool CanAttackTarget();
	void AttackTarget();
	void ChaseTarget();

};
