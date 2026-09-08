// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/EnemyController.h"

#include "SubSystems/BattlefieldManager.h"


// Sets default values
AEnemyController::AEnemyController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Log,TEXT("EnemyController initialized"));
}
		

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedCharacter = Cast<ATTCharacter>(InPawn);
	if (!PossessedCharacter)
	{
		UE_LOG(LogTemp,Warning,TEXT("EnemyController : cast failed"));
	}
}

