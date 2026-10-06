// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:

	UDamageExecutionCalculation();
	static FGameplayEffectAttributeCaptureDefinition BaseDamageDef;
	static FGameplayEffectAttributeCaptureDefinition PhysicalDamageDef;
	static FGameplayEffectAttributeCaptureDefinition MagicalDamageDef;

	static FGameplayEffectAttributeCaptureDefinition PhysicalDefenseDef;
	static FGameplayEffectAttributeCaptureDefinition MagicalDefenseDef;
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
