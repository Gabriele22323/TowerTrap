// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseInteractable.h"
#include "Enums/ESolveState.h"
#include "Data/PuzzleDataAsset.h"
#include "BasePuzzle.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API ABasePuzzle : public ABaseInteractable
{
	GENERATED_BODY()
private:

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPuzzleDataAsset* PuzzleData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ESolveState State;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CurrentInput; //the solution that has been inputted last
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSolved;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CheckIfIsSolved();
	virtual void BeginPlay() override;
};
