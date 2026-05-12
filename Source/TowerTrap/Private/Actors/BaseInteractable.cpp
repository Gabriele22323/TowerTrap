// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseInteractable.h"


// Sets default values
ABaseInteractable::ABaseInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseInteractable::Interact_Implementation_Implementation()
{
	UE_LOG(LogTemp,Error,TEXT("Missing interaction implementation"));
}

