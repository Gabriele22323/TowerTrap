// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Actors/TTCharacter.h"
#include "EnemyController.generated.h"

UCLASS()
class TOWERTRAP_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyController();
	UPROPERTY(BlueprintReadOnly)
	ATTCharacter* PossessedCharacter = nullptr;
	UPROPERTY(BlueprintReadWrite)
	FVector Destination;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* Pawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
