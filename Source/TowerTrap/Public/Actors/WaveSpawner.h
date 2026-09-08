// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTCharacter.h"
#include "GameFramework/Actor.h"
#include "WaveSpawner.generated.h"

UCLASS()
class TOWERTRAP_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReadyToSpawnSignature, AWaveSpawner*, Spawner);
public:
	// Sets default values for this actor's properties
	AWaveSpawner();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SafeRange = 150; //indicates the distance needed from the last spawned actor for another to spawn
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* LastSpawnedPawn;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FReadyToSpawnSignature ReadyToSpawn;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ATTCharacter> PawnClass = ATTCharacter::StaticClass();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void SpawnPawn(TSubclassOf<ATTCharacter> Character);
	UFUNCTION(BlueprintCallable)
	bool SpawnNextUnit();
};
