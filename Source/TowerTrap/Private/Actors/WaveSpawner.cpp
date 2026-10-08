// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WaveSpawner.h"

#include "SubSystems/BattlefieldManager.h"


// Sets default values
AWaveSpawner::AWaveSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWaveSpawner::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorTickEnabled(false);
	GetGameInstance()->GetSubsystem<UBattlefieldManager>()->AddSpawner(this);
}

// Called every frame
void AWaveSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (LastSpawnedPawn)
	{
		if (GetDistanceTo(LastSpawnedPawn) > SafeRange || LastSpawnedPawn->bIsDead)
		{
			SpawnNextUnit();
		}
	}
	else
	{
		SpawnNextUnit();
	}
}

bool AWaveSpawner::SpawnNextUnit()
{
	UE_LOG(LogTemp,Log,TEXT("%s : Spawning next unit..."),*GetName());
	TObjectPtr<UGroundUnitDefinition> CharacterData =  GetGameInstance()->GetSubsystem<UBattlefieldManager>()->GetNextGroundUnit();
	if (CharacterData != nullptr)
	{
		const FTransform Transform = GetActorTransform();
		LastSpawnedPawn = GetWorld()->SpawnActorDeferred<ACombatUnit>(PawnClass,Transform,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn); //spawn without initialization
		LastSpawnedPawn->Tags.Add("Enemy");
		LastSpawnedPawn->CombatUnitData = CharacterData->UnitData;
		LastSpawnedPawn->FinishSpawning(Transform); //initialize actor
		LastSpawnedPawn->CombatComponent->AssignDataAndInitialize(CharacterData->CombatData);
		GetGameInstance()->GetSubsystem<UBattlefieldManager>()->EnemyCounter++;
		UE_LOG(LogTemp,Log,TEXT("%s : Finished spawning | %s"),*GetName(),*LastSpawnedPawn->GetName());
		return true;
	}
	else
	{
		this->SetActorTickEnabled(false);
		return false;
	}
}

