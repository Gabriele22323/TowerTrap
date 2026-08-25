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
	UPROPERTY(EditAnywhere,meta=(UIMin = 0, ClampMin = 0))
	float MaxHealth;
	UPROPERTY(EditAnywhere)
	TMap<EDamageType,float> DamageResistances; //multiplies taken damaged base on type
	UPROPERTY(EditAnywhere)
	TMap<EDamageType,float> DamageMultipliers; //multiplies base damage
	UPROPERTY(EditAnywhere)
	bool bFlies;
	UPROPERTY(EditAnywhere,meta=(UIMin = 0, ClampMin = 0))
	float BaseDamage;
	UPROPERTY(EditAnywhere,meta=(UIMin = 0, ClampMin = 0))
	float Range;
	UPROPERTY(EditAnywhere,meta=(UIMin = 100, ClampMin = 100))
	float MovementSpeed;
	UPROPERTY(EditAnywhere,meta=(UIMin = 0, ClampMin = 0,UIMax = 1, ClampMax = 1))
	float DodgeChance;
};
