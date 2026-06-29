// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/CGameplayAbility.h"

UAnimInstance* UCGameplayAbility::GetOwnerAnimInstance() const
{
	if (USkeletalMeshComponent* OwnerMesh = GetOwningComponentFromActorInfo())
	{
		return OwnerMesh->GetAnimInstance();
	}
	return nullptr;
}
