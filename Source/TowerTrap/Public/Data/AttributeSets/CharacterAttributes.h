// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CharacterAttributes.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UCharacterAttributes : public UAttributeSet
{
	GENERATED_BODY()
public:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGameplayAttributeData PhysicalResistance;
		ATTRIBUTE_ACCESSORS_BASIC(UCharacterAttributes,PhysicalResistance);
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FGameplayAttributeData MagicalResistance;
		ATTRIBUTE_ACCESSORS_BASIC(UCharacterAttributes,MagicalResistance);
		UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FGameplayAttributeData MaxHealth;
		ATTRIBUTE_ACCESSORS_BASIC(UCharacterAttributes,MaxHealth);
		UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FGameplayAttributeData Health;
		ATTRIBUTE_ACCESSORS_BASIC(UCharacterAttributes,Health);
		UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FGameplayAttributeData MovementSpeed;
		ATTRIBUTE_ACCESSORS_BASIC(UCharacterAttributes,MovementSpeed);
		UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FGameplayAttributeData DamageToTower;
		ATTRIBUTE_ACCESSORS_BASIC(UCharacterAttributes,DamageToTower);
		UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FGameplayAttributeData CurrencyAcquiredOnKill;
		ATTRIBUTE_ACCESSORS_BASIC(UCharacterAttributes,CurrencyAcquiredOnKill);
};
