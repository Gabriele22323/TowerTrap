// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/BattlefieldManager.h"

#include "Actors/TDActors/CombatTower.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "WorldPartition/Cook/WorldPartitionCookPackage.h"

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
	CurrentWave = -1;
	CurrentEnemy = 0;
	bNoMoreEnemyInQueue = false;
	checkf(!Waves[0].Wave.IsEmpty(),TEXT("BattlefieldManager | InitializeBattlefield() : Wave is empty!"));
	WavesNum = Waves.Num();
	Health = StartingHealth; 
	BattlefieldState = EBattlefieldState::FirstPrepStage;
	GetWorld()->GetTimerManager().SetTimer(NextWaveTimer,this,&UBattlefieldManager::StartNextWave,NextWaveTime);
}

void UBattlefieldManager::InitializeBattlefieldWithParams(float FirstPrepTime, float PrepTime, float TowerHealth)
{
	CurrentWave = -1;
	CurrentEnemy = 0;
	bNoMoreEnemyInQueue = false;
	checkf(!Waves[0].Wave.IsEmpty(),TEXT("BattlefieldManager | InitializeBattlefield() : Wave is empty!"));
	WavesNum = Waves.Num();
	StartingHealth = TowerHealth;
	Health = StartingHealth;
	NextWaveTime = PrepTime;
	BattlefieldState = EBattlefieldState::FirstPrepStage;
	GetWorld()->GetTimerManager().SetTimer(NextWaveTimer,this,&UBattlefieldManager::StartNextWave,FirstPrepTime);
}

UGroundUnitDefinition* UBattlefieldManager::GetNextGroundUnit()
{
	if (!Waves[CurrentWave].Wave.IsEmpty())
	{
		if (*Waves[CurrentWave].Wave.Find(ReferenceMap[CurrentEnemy]) > 0) //if there are still enemies of this type
		{
			Waves[CurrentWave].Wave.Add(ReferenceMap[CurrentEnemy],*Waves[CurrentWave].Wave.Find(ReferenceMap[CurrentEnemy])-1); //reduce enemy counter by 1
			OnEnemySpawned.Broadcast();
			return ReferenceMap[CurrentEnemy];
		}
		else
		{
			if (CurrentEnemy < Waves[CurrentWave].Wave.Num() -1) //if there are more enemy types
			{
				UE_LOG(LogTemp,Log,TEXT("Loading next enemy type..."));
				if (*Waves[CurrentWave].Wave.Find(ReferenceMap[CurrentEnemy+1]) > 0) //if there are still enemies of this type
				{
					CurrentEnemy++;
					Waves[CurrentWave].Wave.Add(ReferenceMap[CurrentEnemy],*Waves[CurrentWave].Wave.Find(ReferenceMap[CurrentEnemy])-1); //reduce enemy counter by 1
					OnEnemySpawned.Broadcast();
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
		if (CurrentWave == WavesNum -1)
		{
			OnNoWavesRemaining.Broadcast();
			BattlefieldState = EBattlefieldState::EndStage;
		}
		else
		{
			EnterPrepPhase();
		}
	}
}

void UBattlefieldManager::StartNextWave()
{
	CurrentWave++;
	CurrentEnemy = 0;
	Waves[CurrentWave].Wave.GenerateKeyArray(ReferenceMap);
	UE_LOG(LogTemp,Log,TEXT("Started next wave"));
	OnWaveStarted.Broadcast();
	for (AWaveSpawner* Spawner : Spawners)
	{
		Spawner->SetActorTickEnabled(true);
		UE_LOG(LogTemp,Log,TEXT("%s : Tick status %hhd"),*Spawner->GetName(),Spawner->IsActorTickEnabled());
	}
	BattlefieldState = EBattlefieldState::WaveStage;
	GetWorld()->GetTimerManager().ClearTimer(NextWaveTimer);
}

void UBattlefieldManager::EnterPrepPhase()
{
	UE_LOG(LogTemp,Log,TEXT("EnemyCounter : %d	NoMoreEnemyInQueue : %hhd"),EnemyCounter,bNoMoreEnemyInQueue);
	if (EnemyCounter == 0 && bNoMoreEnemyInQueue)
	{
		GetWorld()->GetTimerManager().SetTimer(NextWaveTimer,this,&UBattlefieldManager::StartNextWave,NextWaveTime);
		BattlefieldState = EBattlefieldState::PrepStage;
		OnWaveDefeated.Broadcast();
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

void UBattlefieldManager::PauseTimer() const
{
	GetWorld()->GetTimerManager().PauseTimer(NextWaveTimer);
}

void UBattlefieldManager::ResumeTimer() const
{
	GetWorld()->GetTimerManager().UnPauseTimer(NextWaveTimer);
}

void UBattlefieldManager::SetHealth(const float NewHealth, const bool Broadcast)
{
	Health = NewHealth;
	if (Broadcast)
	{
		OnHealthChanged.Broadcast(Health);
	}
	if (Health <= 0)
	{
		OnHealthDepleted.Broadcast();
	}
}

void UBattlefieldManager::ApplyDamageToPlayer(const float DamageAmount)
{
	if (Health > 0)
	{
		Health -= DamageAmount;
		Health = FMath::Clamp<float>(Health,0,StartingHealth);
		OnHealthChanged.Broadcast(Health);
		if (Health <= 0)
			OnHealthDepleted.Broadcast();
	}
}

EBattlefieldState UBattlefieldManager::GetBattlefieldState() const
{
	return BattlefieldState;
}

void UBattlefieldManager::CacheLevelReference(ULevelStreamingDynamic* LevelReference)
{
	if (LevelReference != nullptr)
	{
		LoadedTDLevel = LevelReference;
	}
}

ULevelStreamingDynamic* UBattlefieldManager::GetCachedLevelReference()
{
	return LoadedTDLevel;
}

void UBattlefieldManager::UnloadCachedLevel()
{
	LoadedTDLevel->SetShouldBeLoaded(false);
	LoadedTDLevel->SetShouldBeVisible(false);
	GetWorld()->GetTimerManager().ClearTimer(NextWaveTimer);
}

void UBattlefieldManager::LoadCachedLevel()
{
	LoadedTDLevel->SetShouldBeLoaded(true);
	LoadedTDLevel->SetShouldBeVisible(true);
}

void UBattlefieldManager::EmptyCachedLevel()
{
	UnloadCachedLevel();
	LoadedTDLevel = nullptr;
}
		
		
		
