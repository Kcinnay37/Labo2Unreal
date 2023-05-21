// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAvatarDeadDelegate);

struct FBonusesStat;
class AMeleeWeapon;

UCLASS()
class LABO2UNREAL_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCharacterAttribute* Attributes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	float CurrentHealth = 1;
	AMeleeWeapon* MeleeWeapon;
public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	float GetHealth();
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable)
	float GetPercentHealth();
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetPortrait();
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (BlueprintThreadSafe))
	bool GetIsDead() const;

	void SetHealth(float Healt);

	void AddOnDelegate(FScriptDelegate DelagateToAdd);
	void AddPermanentStat(FBonusesStat* bonusStat);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void Dead();

	virtual void SaveData();
	virtual void LoadData();
	virtual void ResetData();

	UFUNCTION(BlueprintCallable)
	void BeginAttack();
	UFUNCTION(BlueprintCallable)
	void EndAttack();
	UFUNCTION(BlueprintCallable)
	void BeginAttackAnim();
	UFUNCTION(BlueprintCallable)
	void EndAttackAnim();

	void Attack();

	bool GetIsAttacking();

private:
	UPROPERTY()
	FAvatarDeadDelegate AvatarDeadDelegate;

	float AttackTimer = 0.0f;

	bool bAnimAttackPlaying;
};
