// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretDefinition.h"
#include "Engine/DataAsset.h"
#include "TowerList.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UTowerList : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	TArray<TObjectPtr<UTurretDefinition>> AvailableTurrets;
};
