// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ValueGauge.generated.h"

struct FOnAttributeChangeData;
struct FGameplayAttribute;
class UAbilitySystemComponent;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class UValueGauge : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//~ Begin UUserWidget Interfaces
	virtual void NativePreConstruct() override;
	//~ End UUserWidget Interfaces
	
	void SetAndBoundToGameplayAttribute(UAbilitySystemComponent* ASC, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);
	void SetValue(float NewValue, float NewMaxValue);
	
private:
	float CachedValue;
	float CachedMaxValue;
	
	void OnValueChanged(const FOnAttributeChangeData& ChangeData);
	void OnMaxValueChanged(const FOnAttributeChangeData& ChangeData);
	
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColor;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ValueText;
};
