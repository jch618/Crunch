// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_SendGameplayEvent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagsManager.h"

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (!MeshComp->GetOwner())
	{
		return;
	}
	
	FGameplayEventData Spec;
	Spec.EventTag = EventTag;
	Spec.Instigator = MeshComp->GetOwner();
	Spec.Target = MeshComp->GetOwner();
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, Spec);
}

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	if (EventTag.IsValid())
	{
		TArray<FName> TagNames;
		UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
		if (TagNames.Num() > 0)
		{
			return TagNames.Last().ToString();
		}
	}
	return TEXT("None");
}
