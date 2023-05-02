// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMeleeWeapon::WeaponHit(AActor* Other, AController* Controller)
{
	if (IsSwinging && !IgnoredActors.Contains(Other))
	{
		if (Controller)
		{
			UGameplayStatics::ApplyDamage(Other, 10.0f, Controller, this, UDamageType::StaticClass());
			IgnoredActors.AddUnique(Other);
		}
	}
}

void AMeleeWeapon::BeginSwing(AActor* Holder)
{
	TheHolder = Holder;

	IgnoredActors.Empty();
	IgnoredActors.AddUnique(Holder);
	IsSwinging = true;
}

void AMeleeWeapon::ResetSwing()
{
	IgnoredActors.Empty();
	IsSwinging = false;
}