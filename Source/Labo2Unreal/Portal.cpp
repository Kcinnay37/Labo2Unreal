// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include"MyPlayer.h"

APortal::APortal()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	Box->SetupAttachment(GetRootComponent());
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentHit.AddDynamic(this, &APortal::OnComponentHit);
}

void APortal::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyPlayer* player = Cast<AMyPlayer>(OtherActor);

	if (IsValid(player))
	{
		UGameplayStatics::OpenLevel(this, FName(*LevelName));
	}
}