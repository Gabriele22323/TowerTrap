// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerCameraBoundsManager.generated.h"

UCLASS()
class TOWERTRAP_API APlayerCameraBoundsManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerCameraBoundsManager();
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoundsBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	FBox GetBounds() const;
};
