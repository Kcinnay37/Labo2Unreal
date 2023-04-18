// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Avatar.h"
#include "Components/BoxComponent.h"
#include "ItemData.h"

AItem::AItem()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnComponentBeginOverlap);
}

void AItem::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAvatar* avatar = Cast<AAvatar>(OtherActor);
	if (IsValid(avatar))
	{
		if (Pickup(avatar))
		{
			Destroy();
		}
	}
}

bool AItem::Pickup(AAvatar* avatar)
{
	return avatar->CollectItem(ItemData);
}