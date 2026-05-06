// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "JsonUtils/RapidJsonUtils.h"
#include "BaseTurret.generated.h"

UCLASS()
class TOWERTRAP_API ABaseTurret : public APawn
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess))
	float Radius;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess))
	TArray<AActor*> Targets;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess))
	float Damage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess))
	float RPM;
	UPROPERTY()
	AActor* ClosestTarget;
	UPROPERTY()
	float ShootingDelay;
	UPROPERTY()
	float ShootingTimer;
	
public:
	// Sets default values for this pawn's properties
	ABaseTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
