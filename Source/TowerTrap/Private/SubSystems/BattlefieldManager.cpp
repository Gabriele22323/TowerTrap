// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/BattlefieldManager.h"

const TArray<FVector>& UBattlefieldManager::GetEndPoints() const
{
	return EndPoints;
}

void UBattlefieldManager::AddEndPoints(FVector NewPoint)
{
	EndPoints.Add(NewPoint);
}

void UBattlefieldManager::ClearEndPoints()
{
	EndPoints.Empty();
}
