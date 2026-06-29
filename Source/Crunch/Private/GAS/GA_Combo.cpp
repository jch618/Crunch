// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GA_Combo.h"

#include "CGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "Debug/CDebugHelper.h"

UGA_Combo::UGA_Combo()
{
	AbilityTags.AddTag(CGameplayTags::Ability_BasicAttack);
}

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			NAME_None,
			ComboMontage
		);
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &ThisClass::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();
		
		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this,
			CGameplayTags::Ability_Combo_Change_Next,
			nullptr,
			false,
			true
		);
		WaitComboChangeEventTask->EventReceived.AddDynamic(this, &ThisClass::OnComboChangedEventReceived);
		WaitComboChangeEventTask->ReadyForActivation();
		
		SetupWaitComboInputPress();
	}
}

void UGA_Combo::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	ComboCount = 1;
	C_LOG("End Ability");
}

void UGA_Combo::SetupWaitComboInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPress = UAbilityTask_WaitInputPress::WaitInputPress(
		this
	);
	WaitInputPress->OnPress.AddDynamic(this, &ThisClass::OnInputPressed);
	WaitInputPress->ReadyForActivation();
}

void UGA_Combo::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}


void UGA_Combo::TryCommitCombo()
{
	if (ComboCount == 1)
	{
		return;
	}
	
	UAnimInstance* OwnerAnimInst = GetOwnerAnimInstance();
	if (!OwnerAnimInst)
	{
		return;
	}
	
	FName NextSectionName = FName(FString::Printf(TEXT("combo_0%d"), ComboCount));
	OwnerAnimInst->Montage_SetNextSection(OwnerAnimInst->Montage_GetCurrentSection(ComboMontage), NextSectionName, ComboMontage);
}

void UGA_Combo::OnInputPressed(float TimeWaited)
{
	// SetupWaitComboInputPress();
	TryCommitCombo();
}

void UGA_Combo::OnComboChangedEventReceived(FGameplayEventData Data)
{
	FGameplayTag EventTag = Data.EventTag;
	
	if (EventTag == CGameplayTags::Ability_Combo_Change_End)
	{
		ComboCount = 1;
		C_LOG("Next combo is cleared");
		return;
	}
	
	++ComboCount;
	SetupWaitComboInputPress();
	
	C_LOG("next combo is now: %d", ComboCount);
}
