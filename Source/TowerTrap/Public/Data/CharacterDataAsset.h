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
	UPROPERTY(EditAnywhere,meta=(UIMin = 0, ClampMin = 0),BlueprintReadOnly)
	float MaxHealth;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TMap<EDamageType,float> DamageResistances; //multiplies taken damaged base on type
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TMap<EDamageType,float> DamageMultipliers; //multiplies base damage
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bFlies;
	UPROPERTY(EditAnywhere,meta=(UIMin = 0, ClampMin = 0),BlueprintReadOnly)
	float BaseDamage;
	UPROPERTY(EditAnywhere,meta=(UIMin = 0, ClampMin = 0),BlueprintReadOnly)
	float Range;
	UPROPERTY(EditAnywhere,meta=(UIMin = 100, ClampMin = 100),BlueprintReadOnly)
	float MovementSpeed;
	UPROPERTY(EditAnywhere,meta=(UIMin = 0, ClampMin = 0,UIMax = 1, ClampMax = 1),BlueprintReadOnly)
	float DodgeChance;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USkeletalMesh* Mesh;
};
