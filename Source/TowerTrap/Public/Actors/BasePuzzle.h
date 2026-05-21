// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseInteractable.h"
#include "BasePuzzle.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API ABasePuzzle : public ABaseInteractable
{
	GENERATED_BODY()
private:
	UPROPERTY()
	bool bIsSolved;
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CheckIfIsSolved();
};
