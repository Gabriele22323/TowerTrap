// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/TowerHandlingSubsystem.h"

TArray<UTurretDefinition*> UTowerHandlingSubsystem::GetAvailableTowers() const
{
	return AvailableTowers->AvailableTurrets;
}

void UTowerHandlingSubsystem::SetAvailableTurrets(UTowerList* Towers)
{
	if (Towers)
	{
		AvailableTowers = Towers;
	}
}
	
