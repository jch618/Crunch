// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UGameplayWidget;
class ACPlayerCharacter;
/**
 * 
 */
UCLASS()
class ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//~ Begin APlayerController Interfaces Begin
	// only called on the server
	virtual void OnPossess(APawn* NewPawn) override;
	
	// only called on the client, also on the listening server
	virtual void AcknowledgePossession(APawn* NewPawn) override;
	//~ End APlayerController Interfaces Begin
	
	void SpawnGameplayWidget();
	
private:
	UPROPERTY()
	TObjectPtr<ACPlayerCharacter> PlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGameplayWidget> GameplayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UGameplayWidget> GameplayWidget;
};
