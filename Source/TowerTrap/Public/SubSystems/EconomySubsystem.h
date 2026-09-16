// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EconomySubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIntParamDelegate,int32,Value);

UCLASS()
class TOWERTRAP_API UEconomySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	//Economy System
	UPROPERTY(BlueprintSetter = SetCurrency, BlueprintGetter = GetCurrency)
	int32 Currency;
	UPROPERTY(BlueprintAssignable)
	FIntParamDelegate OnCurrencyChanged;
	UFUNCTION(BlueprintCallable)
	void SetCurrency(int32 NewValue);
	UFUNCTION(BlueprintCallable)
	int32 GetCurrency() const;
	UFUNCTION(BlueprintCallable)
	void AddCurrency(int32 Value);
	UFUNCTION(BlueprintCallable)
	bool SubtractCurrency(int32 Value);
};
