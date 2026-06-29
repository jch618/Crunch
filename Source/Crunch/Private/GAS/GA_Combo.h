// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/CGameplayAbility.h"
#include "GA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class UGA_Combo : public UCGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Combo();
	
protected:
	//~ Begin UGameplayAbility Interfaces Begin
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interfaces Begin
	
private:
	int32 ComboCount = 1;
	
	void SetupWaitComboInputPress();
	void OnMontageCompleted();
	
	UPROPERTY(EditDefaultsOnly, Category = "Crunch|Montage")
	TObjectPtr<UAnimMontage> ComboMontage;
	
	void TryCommitCombo();
	
	UFUNCTION()
	void OnInputPressed(float TimeWaited);
	
	UFUNCTION()
	void OnComboChangedEventReceived(FGameplayEventData Data);
};
