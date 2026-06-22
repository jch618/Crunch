// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "CCharacter.generated.h"

class UWidgetComponent;
class UCAttributeSet;
class UCAbilitySystemComponent;

UCLASS()
class ACCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacter();
	void ServerInit();
	void ClientInit();
	bool IsLocallyControlledByPlayer() const;
	
	//~ Begin ACharacter Interfaces
	// only called on the server
	virtual void PossessedBy(AController* NewController) override;
	//~ End ACharacter Interfaces
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ------------------------------------------------------------------------
	//								Ability System
	// ------------------------------------------------------------------------
public:
	//~ Begin IAbilitySystemInterface Interfaces
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interfaces
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	TObjectPtr<UCAbilitySystemComponent> CAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UCAttributeSet> CAttributeSet;
	
	// ------------------------------------------------------------------------
	//									UI
	// ------------------------------------------------------------------------
	
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> OverHeadWidgetComponent;
	
	void ConfigureOverHeadStatusWidget();
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityCheckInterval = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityRangeSquared = 1000000.f;
	
	FTimerHandle HeadStatGaugeVisibilityUpdateTimerHandle;
	
	void UpdateHeadGaugeVisibility();
};
