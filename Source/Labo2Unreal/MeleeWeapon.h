// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeleeWeapon.generated.h"

UCLASS()
class LABO2UNREAL_API AMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void WeaponHit(AActor* Other, AController* Controller);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* TheHolder;

public:	
	void BeginSwing(AActor* Holder);
	void ResetSwing();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHit(AActor* ActorHit);

private:
	TArray<AActor*> IgnoredActors;
	bool IsSwinging = false;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcces = true))
	float AttackDamage;
};
