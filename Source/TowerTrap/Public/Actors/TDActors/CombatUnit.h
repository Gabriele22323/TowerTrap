// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CombatComponent.h"
#include "Data/TD_DataAssets/GroundUnitData.h"
#include "GameFramework/Character.h"
#include "CombatUnit.generated.h"

UCLASS()
class TOWERTRAP_API ACombatUnit : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatUnit();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TObjectPtr<UCombatComponent> CombatComponent;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta=(ExposeOnSpawn))
	TObjectPtr<UGroundUnitData> CombatUnitData;
	
	UFUNCTION()
	void BindDelegates();
	
	void ChangeMovementSpeed(const FOnAttributeChangeData& Data);
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
