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
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowWidget();
	UFUNCTION(BlueprintCallable)
	bool CheckIfSolved();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SendInfoToGI();
	virtual void BeginPlay() override;
	void SetState(ESolveState NewState);
};
