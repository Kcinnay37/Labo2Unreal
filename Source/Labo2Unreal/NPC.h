// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

class ATheBossController;
class UItemData;

UCLASS()
class LABO2UNREAL_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString dialogueQuest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString dialogueWin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UItemData* questItem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void AddDelegateToPlayer(ATheBossController* playerController);
	UFUNCTION(BlueprintCallable)
	void RemoveDelegateToPlayer(ATheBossController* playerController);
	UFUNCTION(BlueprintCallable)
	bool GetPlayerHaveResource(ATheBossController* playerController);

	UFUNCTION(BlueprintImplementableEvent)
	void TalkToNPC();
	UFUNCTION(BlueprintImplementableEvent)
	void StopTalkingToNPC();
};
