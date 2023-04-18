// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheBossController.generated.h"


/**
 *
 */
UCLASS()
class LABO2UNREAL_API ATheBossController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	bool GetIsCrouch() const;
	bool GetIsDancing() const;
	float GetRotationSpeed() const;

private:
	UPROPERTY(EditAnywhere)
	float walkRatio;

	UPROPERTY(EditAnywhere)
	float rotationSpeed;

	bool isCrouch = false;
	bool isRun = false;
	float currentRatioWalkSpeed;
	float currentRotationSpeed = 0;

	bool isDancing = false;
	bool isDead = false;

	void MoveForward(float axisValue);
	void MoveRight(float axisValue);

	void BeginRun();
	void EndRun();

	void SetCurrentRatioWalkSpeed();

	void BeginCrouch();
	void EndCrouch();

	void ChangeDanseState();

	void LookUp(float axisValue);
	void LookRight(float axisValue);

	void UseItem();

	UFUNCTION()
	void PlayerDead();
protected:
	virtual void BeginPlay() override;
};
