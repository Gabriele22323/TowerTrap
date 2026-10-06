// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet,PhysicalDamage);
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayAttributeData MagicDamage;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet,MagicDamage);
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayAttributeData AttackRate;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet,AttackRate);
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayAttributeData AttackRange;
	ATTRIBUTE_ACCESSORS_BASIC(UCombatAttributeSet,AttackRange);
};
