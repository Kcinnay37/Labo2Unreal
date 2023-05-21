// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avatar.h"
#include "MyEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API AMyEnemy : public AAvatar
{
	GENERATED_BODY()
private:
	FVector startPoint;

	bool isDead;

	float timeAfterCantSee = 3.0f;
	float currTime = 0.0f;

	bool isRetourning = false;

	void OnDead();

protected:
	virtual void BeginPlay() override;
	virtual void LoadData() override;

public:
	AMyEnemy();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowSlider();
	UFUNCTION(BlueprintImplementableEvent)
	void UnShowSlider();
	UFUNCTION(BlueprintImplementableEvent)
	void RotateSlider();

	UFUNCTION(BlueprintCallable)
	void OnPerception(AActor* Other);

	UFUNCTION(BlueprintCallable)
	void OnPerceptionEnd();

	AAvatar* CurrTarget = nullptr;
	UPROPERTY(EditAnywhere)
	float AttackRange = 200.0f;

	//brain function
	bool HasTarget();
	bool CanSeeTarget();
	bool CanAttackTarget();
	void ChaseTarget();
	void ReturnAtStartPoint();
};
