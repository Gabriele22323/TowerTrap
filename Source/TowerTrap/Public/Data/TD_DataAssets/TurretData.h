// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UpgradePrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> UpgradeEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UpgradeAmountLimit;
};

UCLASS()
class TOWERTRAP_API UTurretData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUpgrade Upgrade;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;
};
