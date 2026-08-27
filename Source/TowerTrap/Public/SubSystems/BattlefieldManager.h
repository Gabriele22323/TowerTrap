// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/WaveSpawner.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BattlefieldManager.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UBattlefieldManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	UPROPERTY(BlueprintGetter = GetEndPoints)
	TArray<FVector> EndPoints;
	UPROPERTY(BlueprintGetter = GetSpawners)
	TArray<AWaveSpawner*> Spawners;
public:
	UFUNCTION(BlueprintGetter)
	const TArray<FVector>& GetEndPoints() const;
	UFUNCTION(BlueprintCallable)
	void AddEndPoints(FVector NewPoint);
	UFUNCTION(BlueprintCallable)
	void ClearEndPoints();
	UFUNCTION(BlueprintGetter)
	const TArray<AWaveSpawner*>& GetSpawners() const;
	UFUNCTION(BlueprintCallable)
	void AddSpawner(AWaveSpawner* NewSpawner);
	UFUNCTION(BlueprintCallable)
	void ClearSpawners();
	UFUNCTION(BlueprintCallable)
	void SpawnNextUnit();
};
