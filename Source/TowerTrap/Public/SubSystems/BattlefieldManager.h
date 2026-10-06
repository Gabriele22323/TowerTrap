// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/WaveSpawner.h"
#include "Data/TD_DataAssets/GroundUnitDefinition.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BattlefieldManager.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoParamDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FoneParamDelegate,float,NewValue);

USTRUCT(BlueprintType, Blueprintable)
struct FEnemyWave
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<TObjectPtr<UGroundUnitDefinition>,int32> Wave;
	
	FEnemyWave()
	{
	}
	
	FEnemyWave(const TMap<TObjectPtr<UGroundUnitDefinition>, int32>& NewWave)
	{
		Wave = NewWave;
	}
};

UCLASS()

class TOWERTRAP_API UBattlefieldManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	UPROPERTY(BlueprintGetter = GetEndPoints)
	TArray<FVector> EndPoints;
	UPROPERTY(BlueprintGetter = GetSpawners)
	TArray<AWaveSpawner*> Spawners;
	UPROPERTY()
	FTimerHandle NextWaveTimer;
	UPROPERTY()
	TArray<TObjectPtr<UGroundUnitDefinition>> ReferenceMap;
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FEnemyWave> Waves;
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentWave;
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentEnemy;
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> EndPointsActor;
	UPROPERTY(BlueprintReadWrite)
	int32 EnemyCounter;
	UPROPERTY(BlueprintReadWrite)
	bool bNoMoreEnemyInQueue;
	UPROPERTY(BlueprintReadWrite)
	float NextWaveTime; //time amount before a new wave starts
	
	
	//EndPoints functions
	UFUNCTION(BlueprintGetter)
	const TArray<FVector>& GetEndPoints() const;
	UFUNCTION(BlueprintCallable)
	void AddEndPoints(FVector NewPoint);
	UFUNCTION(BlueprintCallable)
	void ClearEndPoints();
	
	//Spawner functions
	UFUNCTION(BlueprintGetter)
	const TArray<AWaveSpawner*>& GetSpawners() const;
	UFUNCTION(BlueprintCallable)
	void AddSpawner(AWaveSpawner* NewSpawner);
	UFUNCTION(BlueprintCallable)
	void ClearSpawners();
	
	//Battlefield Essentials
	UFUNCTION(BlueprintCallable)
	void InitializeBattlefield(); //sets value for first wave
	UFUNCTION(BlueprintCallable)
	UGroundUnitDefinition* GetNextGroundUnit();
	
	//Enemy Handling
	UFUNCTION(BlueprintCallable)
	void DecreaseEnemyCounter();
	
	//Wave functions
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FNoParamDelegate OnWaveDefeated;
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FNoParamDelegate OnWaveStarted;
	UFUNCTION(BlueprintCallable)
	void StartNextWave(); //re-enables all spawner and increases currentWave counter
	UFUNCTION(BlueprintCallable)
	void EnterPrepPhase(); //starts timer for next phase
	UFUNCTION(BlueprintCallable)
	void ForceStartNextWave(); //clears timer and starts new wave
	
	//Timer Functions
	UFUNCTION(BlueprintCallable)
	float GetNextWaveElapsedTime() const;
	UFUNCTION(BlueprintCallable)
	float GetNextWaveRemainingTime() const;
	UFUNCTION(BlueprintCallable)
	void PauseTimer() const;
	UFUNCTION(BlueprintCallable)
	void ResumeTimer() const;
	
	//Player Health
	UPROPERTY(BlueprintReadWrite)
	float StartingHealth = 20;
	UPROPERTY(BlueprintReadWrite)
	float Health;
	UPROPERTY(BlueprintAssignable)
	FoneParamDelegate OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FNoParamDelegate OnHealthDepleted;
	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth,bool Broadcast);
	UFUNCTION(BlueprintCallable)
	void ApplyDamageToPlayer(float DamageAmount);
};
