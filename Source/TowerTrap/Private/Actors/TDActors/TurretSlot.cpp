// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TDActors/TurretSlot.h"

#include "AbilitySystemComponent.h"


// Sets default values
ATurretSlot::ATurretSlot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TowerSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TowerSpawnPoint"));
}

// Called when the game starts or when spawned
void ATurretSlot::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATurretSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurretSlot::SpawnTower(UTurretDefinition* TowerDefinition)
{
	FTransform Transform = TowerSpawnPoint->GetComponentTransform();
	ACombatTower* Actor = GetWorld()->SpawnActorDeferred<ACombatTower>(TowerClass,Transform);
	if (!Actor)
	{
		UE_LOG(LogTemp,Log,TEXT("%s : Failed to spawn tower"),*GetName());
		return;
	}
	Actor->FinishSpawning(Transform);
	Actor->InitializeTower(TowerDefinition);	
	Actor->ForceCheckDetection();
	OwnedTower = Actor;
	OwnedTower->SetOwner(this);
	OwnedTower->SetOwningSlot(this);
}

void ATurretSlot::DestroyTower()
{
	OwnedTower->CombatComponent->AbilitySystemComponent->CancelAllAbilities();
	OwnedTower->Destroy();
	OwnedTower = nullptr;
}

void ATurretSlot::Interact_Implementation_Implementation()
{
	
}

