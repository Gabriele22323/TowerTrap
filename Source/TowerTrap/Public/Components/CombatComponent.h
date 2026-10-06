// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "Components/ActorComponent.h"
#include "Data/TD_DataAssets/CombatData.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitialize);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERTRAP_API UCombatComponent : public UActorComponent , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCombatComponent();
	
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintGetter = GetAbilitySystemComponent, Category = "Combat")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UCombatData> CombatUnitData;
	
	UFUNCTION(BlueprintCallable)
	void AssignDataAndInitialize(UCombatData* Data);
	
	UPROPERTY(BlueprintAssignable)
	FOnInitialize FOnInitialize;
	
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> AttributeSets;
	
	void InitializeCombat();
	void InitializeAttributeSets();
	void InitializeStartupEffects();
	void InitializeAbilities();
	
	bool bCombatInitialized = false;
	
	UFUNCTION(BlueprintPure, Category = "Combat")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure, Category = "Combat")
	UCombatData* GetCombatUnitData() const;
};
