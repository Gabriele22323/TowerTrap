// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Actors/TDActors/TDPlayerPawn.h"
#include "GameFramework/PlayerController.h"
#include "TDCameraController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERTRAP_API ATDCameraController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Interact;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Pawn")
	TObjectPtr<ATDPlayerPawn> ControlledPawn;
	
	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<AActor> HoveredActor;
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void Tick(float DeltaTime) override;
	
private:

	void CameraMove(const struct FInputActionValue& Value);
	void CameraZoom(const struct FInputActionValue& Value);	
	
	void CameraInteract(const struct FInputActionValue& Value);
};
