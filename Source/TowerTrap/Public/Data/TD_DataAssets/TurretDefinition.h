// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatData.h"
#include "TurretData.h"
#include "Engine/DataAsset.h"
#include "TurretDefinition.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UTurretDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCombatData> CombatData;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UTurretData> TowerData;
};
