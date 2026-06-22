// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ValueGauge.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Debug/CDebugHelper.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	ProgressBar->SetFillColorAndOpacity(BarColor);
}

void UValueGauge::SetAndBoundToGameplayAttribute(UAbilitySystemComponent* ASC, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
{
	if (ASC)
	{
		bool bFound = false;
		float Value = ASC->GetGameplayAttributeValue(Attribute, bFound);
		if (!bFound)
		{
			return;
		}
		float MaxValue = ASC->GetGameplayAttributeValue(MaxAttribute, bFound);
		if (!bFound)
		{
			return;
		}
		
		SetValue(Value, MaxValue);
		ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &ThisClass::OnValueChanged);
		ASC->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &ThisClass::OnMaxValueChanged);
	}
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{
	CachedValue = NewValue;
	CachedMaxValue = NewMaxValue;
	
	if (NewValue == 0)
	{
		C_LOG("Value Gauge: %s, NewMaxValue can't be 0", *GetName());
		return;
	}
	
	float NewPercent = NewValue / NewMaxValue;
	ProgressBar->SetPercent(NewPercent);
	
	FNumberFormattingOptions FormatOptions = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	
	ValueText->SetText(
		FText::Format(
			FTextFormat::FromString("{0}/{1}"),
			FText::AsNumber(NewValue, &FormatOptions),
			FText::AsNumber(NewMaxValue, &FormatOptions)
	));
}

void UValueGauge::OnValueChanged(const FOnAttributeChangeData& ChangeData)
{
	SetValue(ChangeData.NewValue, CachedMaxValue);
}

void UValueGauge::OnMaxValueChanged(const FOnAttributeChangeData& ChangeData)
{
	SetValue(CachedValue, ChangeData.NewValue);
}
