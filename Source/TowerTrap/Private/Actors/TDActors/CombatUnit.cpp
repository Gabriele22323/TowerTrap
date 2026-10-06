// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TDActors/CombatUnit.h"

#include "AbilitySystemComponent.h"
#include "Data/AttributeSets/CharacterAttributes.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ACombatUnit::ACombatUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CombatComponent = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	CombatComponent->FOnInitialize.AddDynamic(this, &ACombatUnit::BindDelegates);
}

// Called when the game starts or when spawned
void ACombatUnit::BeginPlay()
{
	Super::BeginPlay();
	if (CombatUnitData)
	{
		GetMesh()->SetSkeletalMesh(CombatUnitData->Mesh);
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(CombatUnitData->AnimationBlueprint);
	}
}

// Called every frame
void ACombatUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACombatUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACombatUnit::BindDelegates()
{
	UAbilitySystemComponent* ASC = CombatComponent->GetAbilitySystemComponent();
	ASC->GetGameplayAttributeValueChangeDelegate(UCharacterAttributes::GetMovementSpeedAttribute()).AddUObject(this, &ACombatUnit::ChangeMovementSpeed);
	GetCharacterMovement()->MaxWalkSpeed = ASC->GetNumericAttribute(UCharacterAttributes::GetMovementSpeedAttribute());
}

void ACombatUnit::ChangeMovementSpeed(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

UAbilitySystemComponent* ACombatUnit::GetAbilitySystemComponent() const
{
	return CombatComponent->AbilitySystemComponent;
}

