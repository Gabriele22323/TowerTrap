// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePuzzle.h"

bool ABasePuzzle::CheckIfIsSolved_Implementation()
{
	return bIsSolved;
}

void ABasePuzzle::BeginPlay()
{
	Super::BeginPlay();
	if (PuzzleData)
	{
		State = PuzzleData->State;
		CurrentInput = PuzzleData->InitialInput;
	}
}
