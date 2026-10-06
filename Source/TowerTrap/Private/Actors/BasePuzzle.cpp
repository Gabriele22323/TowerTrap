// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePuzzle.h"


void ABasePuzzle::BeginPlay()
{
	Super::BeginPlay();
	if (PuzzleData)
	{
		State = PuzzleData->State;
		CurrentInput = PuzzleData->InitialInput;
	}
}
void ABasePuzzle::SetState(ESolveState NewState)
{
	State = NewState;
}

void ABasePuzzle::ShowWidget_Implementation()
{
}

bool ABasePuzzle::CheckIfSolved()
{
	if (CurrentInput == PuzzleData->Solution)
	{
		SetState(ESolveState::Done);
		SendInfoToGI();
		return true;
	}
	return false;
}

void ABasePuzzle::SendInfoToGI_Implementation()
{
}

//void ABasePuzzle::Execute_Interact()
