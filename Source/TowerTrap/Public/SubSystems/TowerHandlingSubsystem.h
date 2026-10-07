// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/TD_DataAssets/TowerList.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TowerHandlingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UTowerHandlingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTowerList> AvailableTowers;
public:
	UFUNCTION(BlueprintCallable)
	TArray<UTurretDefinition*> GetAvailableTowers() const;
	UFUNCTION(BlueprintCallable)
	void SetAvailableTurrets(UTowerList* Towers);
};
