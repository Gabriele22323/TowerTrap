// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterDataAsset.h"
#include "GameFramework/Character.h"
#include "Interfaces/Damageable.h"
#include "TTCharacter.generated.h"

UCLASS()
class TOWERTRAP_API ATTCharacter : public ACharacter , public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATTCharacter();
	UPROPERTY(EditAnywhere)
	UCharacterDataAsset* CharacterData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
