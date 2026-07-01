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
	int32 CurrentComboCount = 1;
	
	UPROPERTY(EditAnywhere, Category = "Crunch|Targeting")
	float TargetSweepSphereRadius = 30.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crunch|Montage")
	TObjectPtr<UAnimMontage> ComboMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crunch|Gameplay Effects")
	TSubclassOf<UGameplayEffect> DefaultDamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crunch|Gameplay Effects")
	TMap<int32, TSubclassOf<UGameplayEffect>> DamageEffectMap;
	
	TSubclassOf<UGameplayEffect> GetDamageEffectForCurrentCombo() const;
	
	void SetupWaitComboInputPress();
	void OnMontageCompleted();
	void TryCommitCombo();
	
	UFUNCTION()
	void OnInputPressed(float TimeWaited);
	
	UFUNCTION()
	void OnComboChangedEventReceived(FGameplayEventData Data);
	
	UFUNCTION()
	void ApplyDamage(FGameplayEventData Data);
};
