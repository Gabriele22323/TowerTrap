// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatData.h"
#include "GroundUnitData.h"
#include "Engine/DataAsset.h"
#include "GroundUnitDefinition.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UGroundUnitDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Definition")
	TObjectPtr<UGroundUnitData> UnitData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Definition")
	TObjectPtr<UCombatData> CombatData;
};
