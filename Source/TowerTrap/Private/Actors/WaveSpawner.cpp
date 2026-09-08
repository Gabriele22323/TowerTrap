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
		

void AWaveSpawner::SpawnPawn(TSubclassOf<ATTCharacter> Character)
{
	const FVector* Location = new FVector(GetActorLocation());
	const FRotator* Rotation = new FRotator(GetActorRotation());
	const FActorSpawnParameters& SpawnParams = FActorSpawnParameters();
	LastSpawnedPawn = GetWorld()->SpawnActor(Character,Location,Rotation,SpawnParams);
	this->SetActorTickEnabled(true);
}

bool AWaveSpawner::SpawnNextUnit()
{
	UE_LOG(LogTemp,Log,TEXT("Spawning next unit..."));
	UCharacterDataAsset* CharacterData =  GetGameInstance()->GetSubsystem<UBattlefieldManager>()->GetNextUnit();
	if (CharacterData != nullptr)
	{
		const FTransform Transform = GetActorTransform();
		LastSpawnedPawn = GetWorld()->SpawnActorDeferred<ATTCharacter>(PawnClass,Transform,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn); //spawn without initialization
		ATTCharacter* Ch = Cast<ATTCharacter>(LastSpawnedPawn);
		Ch->CharacterData = CharacterData; //set data
		LastSpawnedPawn->FinishSpawning(Transform); //initialize actor
		GetGameInstance()->GetSubsystem<UBattlefieldManager>()->EnemyCounter++;
		return true;
	}
	else
	{
		this->SetActorTickEnabled(false);
		return false;
	}
}

