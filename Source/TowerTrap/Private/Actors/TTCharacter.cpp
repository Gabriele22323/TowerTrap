// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TTCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Splines/SplineMath.h"
#include "SubSystems/BattlefieldManager.h"


// Sets default values
ATTCharacter::ATTCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATTCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = CharacterData->MaxHealth;
	GetComponentByClass<USkeletalMeshComponent>()->SetSkeletalMesh(CharacterData->Mesh);
	GetCharacterMovement()->MaxWalkSpeed = CharacterData->MovementSpeed;
}

void ATTCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void ATTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATTCharacter::ApplyDamage_Implementation_Implementation(float Damage, EDamageType DamageType)
{
	if (CharacterData)
	{
		if (CharacterData->DamageResistances.Find(DamageType) != nullptr)
		{
			Health = Health - Damage * *CharacterData->DamageResistances.Find(DamageType);
		}
		else
		{
			Health -= Damage;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATTCharacter : CharacterData is null"));
		Health = Health - Damage;
	}
	if (Health <= 0)
	{
		Health = 0;
		Death();
	}
}
	

void ATTCharacter::Death_Implementation()
{
	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Ignore);
	GetGameInstance()->GetSubsystem<UBattlefieldManager>()->DecreaseEnemyCounter();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ATTCharacter::CharacterDestroy,5,false);
}

void ATTCharacter::CharacterDestroy()
{
	this->Destroy();
}
