// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/EDamageType.h"
#include "CharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UCharacterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	float MaxHealth;
	TMap<EDamageType,float> DamageResistances; //multiplies taken damaged base on type
	TMap<EDamageType,float> DamageMultipliers; //multiplies base damage
	bool bFlies;
	float BaseDamage;
	float Range;
	float MovementSpeed;
	float DodgeChance;
};
