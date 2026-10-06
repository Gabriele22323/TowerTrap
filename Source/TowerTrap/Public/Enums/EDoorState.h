// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "EDoorState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDoorState : uint8 {
	Locked UMETA(DisplayName = "Locked"),
	Unlocked UMETA(DisplayName = "Unlocked"),
};
