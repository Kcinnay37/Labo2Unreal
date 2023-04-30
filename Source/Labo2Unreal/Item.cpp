// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "MyPlayer.h"
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
	AMyPlayer* player = Cast<AMyPlayer>(OtherActor);
	if (IsValid(player))
	{
		if (Pickup(player))
		{
			Destroy();
		}
	}
}

bool AItem::Pickup(AMyPlayer* player)
{
	return player->CollectItem(ItemData);
}