// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TDActors/TDPlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "ToolContextInterfaces.h"
#include "Actors/TDActors/PlayerCameraBoundsManager.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/Interactable.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATDPlayerPawn::ATDPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PawnCamera ->SetupAttachment(Root);
	PawnCamera->ProjectionMode = ECameraProjectionMode::Perspective;
	PawnCamera->FieldOfView = 75.0f;
	AutoPossessPlayer = EAutoReceiveInput::Disabled;
}

void ATDPlayerPawn::MoveCamera(const FInputActionValue& Value)
{
	const FVector Movement = Value.Get<FVector>();
	if (Movement.IsNearlyZero())
	{
		return;
	}
	FVector Forward = PawnCamera->GetForwardVector();
	FVector Right   = PawnCamera->GetRightVector();
	Forward.Z = 0.0f;
	Right.Z = 0.0f;
	Forward.Normalize();
	Right.Normalize();
	FVector MovementDirection = Forward * Movement.Y + Right * Movement.X;
	MovementDirection.Normalize();
	const FVector CurrentLocation = GetActorLocation();
	FVector DesiredLocation = CurrentLocation + MovementDirection * MoveSpeed * GetWorld()->GetDeltaSeconds();
	DesiredLocation.X =FMath::Clamp(DesiredLocation.X,ValidPawnMin.X,ValidPawnMax.X);
	DesiredLocation.Y =FMath::Clamp(DesiredLocation.Y,ValidPawnMin.Y,ValidPawnMax.Y);
	DesiredLocation.Z = CurrentLocation.Z;
	SetActorLocation(DesiredLocation);

}

void ATDPlayerPawn::ZoomCamera(const FInputActionValue& Value)
{
	const float ZoomAmount= Value.Get<float>();
	if (FMath::IsNearlyZero(ZoomAmount))
	{
		return;
	}
	const float NewFov = PawnCamera->FieldOfView - (ZoomAmount * ZoomSpeed);
	PawnCamera->SetFieldOfView(FMath::Clamp(NewFov,MinFOV,MaxFOV));
	CalculateCameraBounds();
	FVector Location = GetActorLocation();
	Location.X =FMath::Clamp(Location.X,ValidPawnMin.X,ValidPawnMax.X);
	Location.Y =FMath::Clamp(Location.Y,ValidPawnMin.Y,ValidPawnMax.Y);
	SetActorLocation(Location);
}

// Called when the game starts or when spawned
void ATDPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	CurrentController = GetLocalViewingPlayerController();
	FVector Location = GetActorLocation();
	Location.Z = CameraHeight;
	SetActorLocation(Location);
	//gets the actor responsible for the bounds
	CameraBoundsManager = Cast<APlayerCameraBoundsManager>(UGameplayStatics::GetActorOfClass(GetWorld(),APlayerCameraBoundsManager::StaticClass()));
	checkf(CameraBoundsManager,TEXT("Error : Missing camera bounds manager"));
	UE_LOG(LogTemp,Log,TEXT("TDPlayerPawn initialized!"));
}

void ATDPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult HitResult;
	if (CurrentController) //check if controller is valid
	{
		if (!CurrentController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult))
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
	else
	{
		CurrentController = GetLocalViewingPlayerController();
	}
}

void ATDPlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	CalculateCameraBounds();
}

// Called to bind functionality to input
void ATDPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(CameraMoveAction,ETriggerEvent::Triggered,this,&ATDPlayerPawn::MoveCamera);
		EnhancedInput->BindAction(CameraZoomAction,ETriggerEvent::Triggered,this,&ATDPlayerPawn::ZoomCamera);
		EnhancedInput->BindAction(PrimaryAction,ETriggerEvent::Started,this,&ATDPlayerPawn::PrimaryPlayerAction);
	}
}

bool ATDPlayerPawn::GetCameraGroundPoint(const FVector2D& ScreenCorner,FVector& OutGroundPoint) const
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC)
	{
		return false;
	}
	int32 ViewportX;
	int32 ViewportY;
	PC->GetViewportSize(ViewportX, ViewportY);
	if (ViewportX <= 0 || ViewportY <= 0)
	{
		return false;
	}
	//really fucking complicated maths because fuck you
	const float AspectRatio = static_cast<float>(ViewportX) /static_cast<float>(ViewportY);
	const float HorizontalFOV = FMath::DegreesToRadians(PawnCamera->FieldOfView);
	const float VerticalFOV =2.0f * FMath::Atan(FMath::Tan(HorizontalFOV * 0.5f) / AspectRatio);
	const float ScreenX =ScreenCorner.X * 2.0f - 1.0f;
	const float ScreenY =1.0f - ScreenCorner.Y * 2.0f;
	FVector LocalDirection;
	LocalDirection.X = 1.0f;
	LocalDirection.Y =ScreenX * FMath::Tan(HorizontalFOV / 2);
	LocalDirection.Z =ScreenY * FMath::Tan(VerticalFOV / 2);
	LocalDirection.Normalize();
	const FTransform CameraTransform =PawnCamera->GetComponentTransform();
	const FVector WorldDirection =CameraTransform.TransformVectorNoScale(LocalDirection).GetSafeNormal();
	const FVector CameraLocation =PawnCamera->GetComponentLocation();
	if (FMath::IsNearlyZero(WorldDirection.Z))
	{
		return false;
	}
	const float T =(BattlefieldZ - CameraLocation.Z) / WorldDirection.Z;
	if (T <= 0.0f)
	{
		return false;
	}
	OutGroundPoint = CameraLocation + WorldDirection * T;
	return true;
}

void ATDPlayerPawn::CalculateCameraBounds()
{
	const FVector2D ScreenCorners[] =
	{
		FVector2D(0.0f, 0.0f), // Top left
		FVector2D(1.0f, 0.0f), // Top right
		FVector2D(0.0f, 1.0f), // Bottom left
		FVector2D(1.0f, 1.0f)  // Bottom right
	};
	FVector2D MinOffset(BIG_NUMBER,BIG_NUMBER);
	FVector2D MaxOffset(-BIG_NUMBER,-BIG_NUMBER);
	const FVector PawnLocation =GetActorLocation();
	for (const FVector2D& ScreenCorner : ScreenCorners) //calculate each corner
	{
		FVector GroundPoint;
		if (!GetCameraGroundPoint(ScreenCorner,GroundPoint))
		{
			return;
		}
		const FVector2D Offset(GroundPoint.X - PawnLocation.X,GroundPoint.Y - PawnLocation.Y);
		MinOffset.X =FMath::Min(MinOffset.X, Offset.X);
		MinOffset.Y =FMath::Min(MinOffset.Y, Offset.Y);
		MaxOffset.X =FMath::Max(MaxOffset.X, Offset.X);
		MaxOffset.Y =FMath::Max(MaxOffset.Y, Offset.Y);
		ValidPawnMin.X =CameraBoundsManager->GetBounds().Min.X - MinOffset.X;
		ValidPawnMax.X =CameraBoundsManager->GetBounds().Max.X - MaxOffset.X;
		ValidPawnMin.Y =CameraBoundsManager->GetBounds().Min.Y - MinOffset.Y;
		ValidPawnMax.Y =CameraBoundsManager->GetBounds().Max.Y - MaxOffset.Y;
	}
}

void ATDPlayerPawn::PrimaryPlayerAction(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Log,TEXT("PrimaryAction fired"));
	if (HoveredActor!=nullptr)
	{
		if (HoveredActor->Implements<UInteractable>())
		{
			IInteractable::Execute_Interact(HoveredActor);
		}
	}
}
