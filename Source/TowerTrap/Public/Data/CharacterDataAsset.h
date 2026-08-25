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
	UPROPERTY(EditAnywhere)
	float MaxHealth;
	UPROPERTY(EditAnywhere)
	TMap<EDamageType,float> DamageResistances; //multiplies taken damaged base on type
	UPROPERTY(EditAnywhere)
	TMap<EDamageType,float> DamageMultipliers; //multiplies base damage
	UPROPERTY(EditAnywhere)
	bool bFlies;
	UPROPERTY(EditAnywhere)
	float BaseDamage;
	UPROPERTY(EditAnywhere)
	float Range;
	UPROPERTY(EditAnywhere)
	float MovementSpeed;
	UPROPERTY(EditAnywhere)
	float DodgeChance;
};
