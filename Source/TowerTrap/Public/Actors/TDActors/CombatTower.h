// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatUnit.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "CombatTower.generated.h"

UCLASS()
class TOWERTRAP_API ACombatTower : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACombatTower();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TObjectPtr<UCombatComponent> CombatComponent;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TObjectPtr<USphereComponent> DetectionRange;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta=(ExposeOnSpawn))
	TObjectPtr<UGroundUnitData> GroundUnitData;
	
	//Handling range upgrade
	void OnAttackRangeChanged(const FOnAttributeChangeData& Data);
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<TObjectPtr<ACombatUnit>> Targets;
	UPROPERTY()
	TObjectPtr<ACombatUnit> CurrentTarget;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int32 UpgradeLevel = 0;
	
	UFUNCTION(BlueprintCallable)
	bool ApplyUpgrade();
};
