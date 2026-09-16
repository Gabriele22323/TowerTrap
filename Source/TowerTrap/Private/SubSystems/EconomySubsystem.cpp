// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystems/EconomySubsystem.h"
void UEconomySubsystem::SetCurrency(const int32 NewValue)
{
	Currency = NewValue;
	OnCurrencyChanged.Broadcast(Currency);
}

int32 UEconomySubsystem::GetCurrency() const
{
	return Currency;
}

void UEconomySubsystem::AddCurrency(const int32 Value)
{
	Currency += Value;
}

bool UEconomySubsystem::SubtractCurrency(int32 Value)
{
	if (Currency - Value >= 0)
	{
		Currency -= Value;
		return true;
	}
	return false;
}