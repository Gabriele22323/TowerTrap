// Fill out your copyright notice in the Description page of Project Settings.

#include "Turrets/BaseTurret.h"
#include "VectorTypes.h"
#include "GameFramework/Character.h"

// Sets default values
ABaseTurret::ABaseTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Detection_Radius"));
}
// Called when the game starts or when spawned
void ABaseTurret::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->SetSphereRadius(Radius);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseTurret::EnterDetectionRadius);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseTurret::ExitDetectionRadius);
	ShootingDelay = 60.0f / RPM;
}

// Called every frame
void ABaseTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float ClosestDistance = Radius + 1;
	ClosestTarget = nullptr;
	for (auto Target : Targets)
	{
		float distance = UE::Geometry::Distance(GetActorLocation(), Target->GetActorLocation());
		if (distance < ClosestDistance)
		{
			ClosestDistance = distance;
			ClosestTarget = Target;
		}
	}
	if (ShootingTimer <= 0.0f)
	{
		ShootingTimer = ShootingDelay;
		//shooting logic
		if (ClosestTarget != nullptr) //if target exists
			DrawDebugLine(GetWorld(),GetActorLocation(),ClosestTarget->GetActorLocation(),FColor::Blue,false,3,0,1);
	}
	else
	{
		ShootingTimer -= DeltaTime;
	}
}
// Called to bind functionality to input
void ABaseTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseTurret::UseAbility_Implementation()
{
}

void ABaseTurret::EnterDetectionRadius(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int Index, bool bSweep, const FHitResult& Hit)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		Targets.Add(Character);
	}
}

void ABaseTurret::ExitDetectionRadius(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int Index)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		Targets.RemoveSwap(Character);
	}
}



