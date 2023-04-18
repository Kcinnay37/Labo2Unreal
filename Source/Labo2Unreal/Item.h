// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Item.generated.h"

class UBoxComponent;
class AAvatar;
class UItemData;

/**
 * 
 */
UCLASS()
class LABO2UNREAL_API AItem : public AStaticMeshActor
{
	GENERATED_BODY()
private:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollider;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AItem();

	bool Pickup(AAvatar* avatar);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemData* ItemData;
};

