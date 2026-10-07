// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TDActors/CombatUnit.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "NativeGameplayTags.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Data/AttributeSets/CharacterAttributes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GeometryCollection/GeometryCollectionSimulationTypes.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_CombatUnit_State_Dead, "CombatUnit.State.Dead");

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
	ASC->GetGameplayAttributeValueChangeDelegate(UCharacterAttributes::GetHealthAttribute()).AddUObject(this, &ACombatUnit::HealthChange);
}

void ACombatUnit::TimedDestroy()
{
	Destroy();
}

void ACombatUnit::HealthChange(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0 && !bIsDead)
	{
		Death(); //I wish I could too
	}
}

void ACombatUnit::ChangeMovementSpeed(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

UAbilitySystemComponent* ACombatUnit::GetAbilitySystemComponent() const
{
	return CombatComponent->AbilitySystemComponent;
}

void ACombatUnit::Death()
{
	AAIController* AIC = UAIBlueprintHelperLibrary::GetAIController(this);
	if (AIC)
	{
		if (AIC->GetBrainComponent())
		{
			AIC->GetBrainComponent()->StopLogic("Dead");
		}
	}
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatComponent->AbilitySystemComponent->AddLooseGameplayTag(TAG_CombatUnit_State_Dead);
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle,this,&ACombatUnit::TimedDestroy,3.0f,false);
	bIsDead = true;
}

