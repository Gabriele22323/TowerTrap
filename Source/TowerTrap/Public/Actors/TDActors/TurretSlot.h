// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatTower.h"
#include "Data/TD_DataAssets/TurretDefinition.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "TurretSlot.generated.h"

UCLASS()
class TOWERTRAP_API ATurretSlot : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurretSlot();
	
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	TObjectPtr<USceneComponent> TowerSpawnPoint;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<ACombatTower> OwnedTower;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<ACombatTower> TowerClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void SpawnTower(UTurretDefinition* TowerDefinition);
	UFUNCTION(BlueprintCallable)
	void DestroyTower();
	
	UFUNCTION(BlueprintNativeEvent)
	void Interact_Implementation() override;
};
