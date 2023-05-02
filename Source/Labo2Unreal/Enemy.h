// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AAvatar;
class AMeleeWeapon;

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

	UFUNCTION(BlueprintCallable)
	void BeginAttack();

	UFUNCTION(BlueprintCallable)
	void EndAttack();

private:
	AAvatar* CurrTarget = nullptr;
	UPROPERTY(EditAnywhere)
	float AttackRange = 200.0f;
	float AttackRate = 2.0f;
	float AttackTimer = 0.0f;
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMeleeWeapon> MeleeWeaponClass;
	AMeleeWeapon* MeleeWeapon;

	//brain function
	bool IsDead();
	bool HasTarget();
	bool CanSeeTarget();
	bool CanAttackTarget();
	void AttackTarget(float DeltaTime);
	void ChaseTarget();

};
