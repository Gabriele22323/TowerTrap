// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/ESolveState.h"
#include "PuzzleDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API UPuzzleDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	ESolveState State; //whether it starts impossible or not
	UPROPERTY(EditAnywhere)
	FString InitialInput; //the starting state the puzzle is in
	UPROPERTY(EditAnywhere)
	FString Solution; //the final state the puzzle will be in
};
