// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/DamageExecutionCalculation.h"

#include "Data/AttributeSets/CharacterAttributes.h"
#include "Data/AttributeSets/CombatAttributeSet.h"

FGameplayEffectAttributeCaptureDefinition
UDamageExecutionCalculation::BaseDamageDef;

FGameplayEffectAttributeCaptureDefinition
UDamageExecutionCalculation::PhysicalDamageDef;

FGameplayEffectAttributeCaptureDefinition
UDamageExecutionCalculation::MagicalDamageDef;

FGameplayEffectAttributeCaptureDefinition
UDamageExecutionCalculation::PhysicalDefenseDef;

FGameplayEffectAttributeCaptureDefinition
UDamageExecutionCalculation::MagicalDefenseDef;

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	BaseDamageDef = FGameplayEffectAttributeCaptureDefinition(UCombatAttributeSet::GetBaseDamageAttribute(),EGameplayEffectAttributeCaptureSource::Source,false);
	PhysicalDamageDef = FGameplayEffectAttributeCaptureDefinition(UCombatAttributeSet::GetPhysicalDamageAttribute(),EGameplayEffectAttributeCaptureSource::Source,false);
	MagicalDamageDef = FGameplayEffectAttributeCaptureDefinition(UCombatAttributeSet::GetMagicDamageAttribute(),EGameplayEffectAttributeCaptureSource::Source,false);
	PhysicalDefenseDef = FGameplayEffectAttributeCaptureDefinition(UCharacterAttributes::GetPhysicalResistanceAttribute(),EGameplayEffectAttributeCaptureSource::Target,false);
	MagicalDefenseDef = FGameplayEffectAttributeCaptureDefinition(UCharacterAttributes::GetMagicalResistanceAttribute(),EGameplayEffectAttributeCaptureSource::Target,false);
}

void UDamageExecutionCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	FAggregatorEvaluateParameters EvaluationParameters;
	float BaseDamage = 0.0f;
	float PhysicalDamage = 0.0f;
	float MagicalDamage = 0.0f;
	float PhysicalDefense = 0.0f;
	float MagicalDefense = 0.0f;
	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(BaseDamageDef,EvaluationParameters,BaseDamage);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalDamageDef,EvaluationParameters,PhysicalDamage);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicalDamageDef,EvaluationParameters,MagicalDamage);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalDefenseDef,EvaluationParameters,PhysicalDefense);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicalDefenseDef,EvaluationParameters,MagicalDefense);
	//Clamp defenses
	PhysicalDefense = FMath::Clamp(PhysicalDefense, 0.0f, 1.0f);
	MagicalDefense = FMath::Clamp(MagicalDefense, 0.0f, 1.0f);
	//calculate damage
	const float Physical =BaseDamage * PhysicalDamage * (1.0f - PhysicalDefense);
	const float Magical =BaseDamage * MagicalDamage * (1.0f - MagicalDefense);
	const float FinalDamage = Physical + Magical;
	//output
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UCharacterAttributes::GetHealthAttribute(),EGameplayModOp::Additive,-FinalDamage));
}
