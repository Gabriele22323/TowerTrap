// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/TDCameraController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ToolContextInterfaces.h"
#include "Interfaces/Interactable.h"

void ATDCameraController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSubsystem->AddMappingContext(MappingContext,0);
		}
	}
}

void ATDCameraController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ATDCameraController::CameraMove);
	EnhancedInput->BindAction(ZoomAction,ETriggerEvent::Triggered,this,&ATDCameraController::CameraZoom);
	EnhancedInput->BindAction(Interact,ETriggerEvent::Started,this,&ATDCameraController::CameraInteract);
}

void ATDCameraController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledPawn = Cast<ATDPlayerPawn>(InPawn);
}

void ATDCameraController::OnUnPossess()
{
	Super::OnUnPossess();
	ControlledPawn = nullptr;
}

void ATDCameraController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult HitResult;
	if (!GetHitResultUnderCursor(ECC_Visibility,false,HitResult))
	{
		return;
	}
	if (HitResult.GetActor() != HoveredActor) //hit actor is different from previous one
	{
		if (HoveredActor != nullptr && HoveredActor->Implements<UInteractable>()) 
		{
			IInteractable::Execute_UnHovered(HoveredActor);
			HoveredActor = nullptr;
		}
		if (HitResult.GetActor()->Implements<UInteractable>())
		{
			HoveredActor = HitResult.GetActor();
			IInteractable::Execute_Hovered(HoveredActor);
		}
	}
}

void ATDCameraController::CameraMove(const struct FInputActionValue& Value)
{
	const FVector2D Movement = Value.Get<FVector2D>();
	ControlledPawn->MoveCamera(Movement);
}

void ATDCameraController::CameraZoom(const struct FInputActionValue& Value)
{
	const float Zoom = Value.Get<float>();
	ControlledPawn->ZoomCamera(Zoom);
}

void ATDCameraController::CameraInteract(const struct FInputActionValue& Value)
{
	FHitResult HitResult;
	if (!GetHitResultUnderCursor(ECC_Visibility,false,HitResult))
	{
		return;
	}
	AActor* HitActor = HitResult.GetActor();
	if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_Interact(HitActor);
	}
}
