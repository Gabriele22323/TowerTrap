// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "ESolveState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESolveState : uint8 {
	Impossible UMETA(DisplayName = "Impossible"),
	Solving UMETA(DisplayName = "Solving"),
	Done UMETA(DisplayName = "Done"),
};