// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GroundUnitData.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UGroundUnitData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> Mesh;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UAnimInstance> AnimationBlueprint;
};
