// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/BattlefieldManager.h"

const TArray<FVector>& UBattlefieldManager::GetEndPoints() const
{
	return EndPoints;
}

void UBattlefieldManager::AddEndPoints(FVector NewPoint)
{
	EndPoints.Add(NewPoint);
}

void UBattlefieldManager::ClearEndPoints()
{
	EndPoints.Empty();
}

const TArray<AWaveSpawner*>& UBattlefieldManager::GetSpawners() const
{
	return Spawners;
}

void UBattlefieldManager::AddSpawner(AWaveSpawner* NewSpawner)
{
	Spawners.Add(NewSpawner);
}

void UBattlefieldManager::ClearSpawners()
{
	Spawners.Empty();
}

void UBattlefieldManager::InitializeBattlefield()
{
	CurrentWave = 0;
	CurrentEnemy = 0;
	bNoMoreEnemyInQueue = false;
	checkf(!Waves[0].Wave.IsEmpty(),TEXT("BattlefieldManager | InitializeBattlefield() : Wave is empty!"));
	Waves[CurrentWave].Wave.GenerateKeyArray(ReferenceMap);
	
	UE_LOG(LogTemp,Error,TEXT("Waves class number : %d"), Waves[CurrentWave].Wave.GetMaxIndex());
}

UCharacterDataAsset* UBattlefieldManager::GetNextUnit()
{
	if (!Waves[CurrentWave].Wave.IsEmpty())
	{
		if (*Waves[CurrentWave].Wave.Find(ReferenceMap[CurrentEnemy]) > 0) //if there are still enemies of this type
		{
			Waves[CurrentWave].Wave.Add(ReferenceMap[CurrentEnemy],*Waves[CurrentWave].Wave.Find(ReferenceMap[CurrentEnemy])-1); //reduce enemy counter by 1
			return ReferenceMap[CurrentEnemy];
		}
		else
		{
			if (Waves[CurrentWave].Wave.GetMaxIndex()-3 >= CurrentEnemy) //if there are more enemy types
			{
				UE_LOG(LogTemp,Log,TEXT("Loading next enemy type..."));
				if (*Waves[CurrentWave].Wave.Find(ReferenceMap[CurrentEnemy+1]) > 0) //if there are still enemies of this type
				{
					CurrentEnemy++;
					Waves[CurrentWave].Wave.Add(ReferenceMap[CurrentEnemy],*Waves[CurrentWave].Wave.Find(ReferenceMap[CurrentEnemy])-1); //reduce enemy counter by 1
					return ReferenceMap[CurrentEnemy];
				}
			}
			else
			{
				if (!bNoMoreEnemyInQueue)
				{
					bNoMoreEnemyInQueue = true;
					UE_LOG(LogTemp,Log,TEXT("No more enemy types found..."));
				}
			}
		}
		return nullptr; //no enemy :(
	}
	return nullptr;
}

void UBattlefieldManager::DecreaseEnemyCounter()
{
	EnemyCounter--;
	if (EnemyCounter == 0)
	{
		EnterPrepPhase();
	}
}

void UBattlefieldManager::StartNextWave()
{
	CurrentWave++;
	OnWaveStarted.Broadcast();
	for (AWaveSpawner* Spawner : Spawners)
	{
		Spawner->SetActorTickEnabled(true);
	}
}

void UBattlefieldManager::EnterPrepPhase()
{
	UE_LOG(LogTemp,Log,TEXT("EnemyCounter : %d	NoMoreEnemyInQueue : %hhd"),EnemyCounter,bNoMoreEnemyInQueue);
	if (EnemyCounter == 0 && bNoMoreEnemyInQueue)
	{
		OnWaveDefeated.Broadcast();
		GetWorld()->GetTimerManager().SetTimer(NextWaveTimer,this,&UBattlefieldManager::StartNextWave,120);
	}
}

void UBattlefieldManager::ForceStartNextWave()
{
	GetWorld()->GetTimerManager().ClearTimer(NextWaveTimer);
	StartNextWave();
}

float UBattlefieldManager::GetNextWaveElapsedTime() const
{
	return GetWorld()->GetTimerManager().GetTimerElapsed(NextWaveTimer);
}

float UBattlefieldManager::GetNextWaveRemainingTime() const
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(NextWaveTimer);
}

void UBattlefieldManager::PauseTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(NextWaveTimer);
}

void UBattlefieldManager::ResumeTimer()
{
	GetWorld()->GetTimerManager().UnPauseTimer(NextWaveTimer);
}
		
