// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCameraBoundsManager.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "TDPlayerPawn.generated.h"

UCLASS()
class TOWERTRAP_API ATDPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDPlayerPawn();
	
	void MoveCamera(const FVector2D& Movement);
	void ZoomCamera(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> PawnCamera;
	
	UPROPERTY(EditAnywhere, Category = "Camera|Movement")
	float CameraHeight = 5000.0f;
	
	UPROPERTY(EditAnywhere, Category = "Camera|Movement")
	float MoveSpeed = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MinFOV = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float MaxFOV = 75.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float ZoomSpeed = 5.0f;
	
	//bound calculation 
	UPROPERTY(EditAnywhere, Category = "Camera|Bounds")
	APlayerCameraBoundsManager* CameraBoundsManager;
	
	UPROPERTY(EditAnywhere, Category = "Camera|Bounds")
	FVector2D ValidPawnMin;
	
	UPROPERTY(EditAnywhere, Category = "Camera|Bounds")
	FVector2D ValidPawnMax;

	UPROPERTY(EditAnywhere, Category = "Camera|Bounds")
	float BattlefieldZ = 0.0f;
	
	bool GetCameraGroundPoint(const FVector2D& ScreenCorner,FVector& OutGroundPoint) const;
	void CalculateCameraBounds();
};
