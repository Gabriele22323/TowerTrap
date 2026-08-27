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
		ReadyToSpawn.Broadcast(this);
		this->SetActorTickEnabled(false); //basically sets it to sleep until anything else needs to be spawned and monitored
	}
}
		

void AWaveSpawner::SpawnPawn(TSubclassOf<ATTCharacter> Character)
{
	const FVector* Location = new FVector(GetActorLocation() + FVector(0,0,100));
	const FRotator* Rotation = new FRotator(GetActorRotation());
	const FActorSpawnParameters& SpawnParams = FActorSpawnParameters();
	LastSpawnedPawn = GetWorld()->SpawnActor(Character,Location,Rotation,SpawnParams);
	this->SetActorTickEnabled(true);
}

