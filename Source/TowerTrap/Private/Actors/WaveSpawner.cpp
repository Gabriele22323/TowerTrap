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
	GetGameInstance()->GetSubsystem<UBattlefieldManager>()->AddSpawner(this);
}

// Called every frame
void AWaveSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetDistanceTo(LastSpawnedPawn) > SafeRange)
	{
		SpawnNextUnit();
	}
}

bool AWaveSpawner::SpawnNextUnit()
{
	UE_LOG(LogTemp,Log,TEXT("Spawning next unit..."));
	TObjectPtr<UGroundUnitDefinition> CharacterData =  GetGameInstance()->GetSubsystem<UBattlefieldManager>()->GetNextGroundUnit();
	if (CharacterData != nullptr)
	{
		const FTransform Transform = GetActorTransform();
		AActor* Actor = GetWorld()->SpawnActorDeferred<ACombatUnit>(PawnClass,Transform,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn); //spawn without initialization
		LastSpawnedPawn = Cast<ACombatUnit>(Actor);
		LastSpawnedPawn->Tags.Add("Enemy");
		LastSpawnedPawn->CombatUnitData = CharacterData->UnitData;
		LastSpawnedPawn->FinishSpawning(Transform); //initialize actor
		LastSpawnedPawn->CombatComponent->AssignDataAndInitialize(CharacterData->CombatData);
		GetGameInstance()->GetSubsystem<UBattlefieldManager>()->EnemyCounter++;
		return true;
	}
	else
	{
		this->SetActorTickEnabled(false);
		return false;
	}
}

