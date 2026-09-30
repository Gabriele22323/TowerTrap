// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TDActors/PlayerCameraBoundsManager.h"

#include "Components/BoxComponent.h"


// Sets default values
APlayerCameraBoundsManager::APlayerCameraBoundsManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoundsBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundsBox"));
	RootComponent = BoundsBox;
	BoundsBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APlayerCameraBoundsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCameraBoundsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FBox APlayerCameraBoundsManager::GetBounds() const
{
	return BoundsBox->Bounds.GetBox();
}

