// Fill out your copyright notice in the Description page of Project Settings.


#include "CAbilitySystemStatics.h"

#include "CGameplayTags.h"

FGameplayTag UCAbilitySystemStatics::GetBasicAttackAbilityTag()
{
	return CGameplayTags::Ability_BasicAttack;
}
