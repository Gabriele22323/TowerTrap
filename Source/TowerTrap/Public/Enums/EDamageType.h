// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "EDamageType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDamageType : uint8 {
	Physical UMETA(DisplayName = "Physical"),
	Magical UMETA(DisplayName = "Magical"),
};
