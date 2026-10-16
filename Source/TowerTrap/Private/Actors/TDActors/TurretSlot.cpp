// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TDActors/TurretSlot.h"

#include "AbilitySystemComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"


// Sets default values
ATurretSlot::ATurretSlot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	TowerSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TowerSpawnPoint"));
	TowerSpawnPoint->SetupAttachment(RootComponent);
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
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.OverrideLevel = GetLevel();
	SpawnParameters.bDeferConstruction = true;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ACombatTower* Actor = GetWorld()->SpawnActor<ACombatTower>(TowerClass,Transform,SpawnParameters);
	if (!Actor)
	{
		UE_LOG(LogTemp,Log,TEXT("%s : Failed to spawn tower"),*GetName());
		return;
	}
	Actor->FinishSpawning(Transform);
	Actor->InitializeTower(TowerDefinition);	
	//Actor->ForceCheckDetection();
	OwnedTower = Actor;
	OwnedTower->SetOwner(this);
	OwnedTower->SetOwningSlot(this);
	OwnedTower->AttachToComponent(TowerSpawnPoint,FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("TowerSpawnPoint"));
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

