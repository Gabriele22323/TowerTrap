// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "TurretData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FUpgrade
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 UpgradePrice; //simple price
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float UpgradePriceIncrement = 1; //price increase in multiplication at every upgrade
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> UpgradeEffect; //GAS effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 UpgradeAmountLimit; //amount of times it can be bought
};

UCLASS()
class TOWERTRAP_API UTurretData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUpgrade Upgrade; //defines the upgrade used in the turret
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> Mesh; //simple mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price; //price used to place the turret
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AAIController> TowerController; //Used to add custom behavior to towers (I.E. for the garrison to keep track of deployed units)
};
