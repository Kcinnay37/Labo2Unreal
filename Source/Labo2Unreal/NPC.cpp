// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "TheBossController.h"
#include "MyGameInstance.h"
#include "DataPlayer.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::AddDelegateToPlayer(ATheBossController* playerController)
{
	playerController->interactKeyPress.AddDynamic(this, &ANPC::TalkToNPC);
}

void ANPC::RemoveDelegateToPlayer(ATheBossController* playerController)
{
	playerController->interactKeyPress.RemoveDynamic(this, &ANPC::TalkToNPC);
}

bool ANPC::GetPlayerHaveResource(ATheBossController* playerController)
{
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (IsValid(GameInstance) && IsValid(GameInstance->PlayerData))
	{
		return GameInstance->PlayerData->Contain(questItem);
	}
	return false;
}

