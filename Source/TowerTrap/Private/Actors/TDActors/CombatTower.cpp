// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TDActors/CombatTower.h"

#include "AbilitySystemComponent.h"
#include "Data/AttributeSets/CombatAttributeSet.h"


// Sets default values
ACombatTower::ACombatTower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CombatComponent = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	DetectionRange = CreateDefaultSubobject<USphereComponent>("DetectionRange");
}

// Called when the game starts or when spawned
void ACombatTower::BeginPlay()
{
	Super::BeginPlay();
	CombatComponent->AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCombatAttributeSet::GetAttackRangeAttribute()).AddUObject(this,&ACombatTower::OnAttackRangeChanged);
	DetectionRange->SetSphereRadius(CombatComponent->AbilitySystemComponent->GetNumericAttribute(UCombatAttributeSet::GetAttackRangeAttribute()));
}

// Called every frame
void ACombatTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACombatTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ACombatTower::GetAbilitySystemComponent() const
{
	return CombatComponent->AbilitySystemComponent;
}

void ACombatTower::OnAttackRangeChanged(const FOnAttributeChangeData& Data)
{
	if (DetectionRange)
	{
		DetectionRange->SetSphereRadius(Data.NewValue);
	}
}

bool ACombatTower::ApplyUpgrade()
{
	if (CombatComponent)
	{
		if (CombatComponent->CombatUnitData)
		{
			// if (UpgradeLevel < CombatComponent->CombatUnitData->Upgrade.UpgradeAmountLimit)
			// {
			// 	FGameplayEffectContextHandle Context = CombatComponent->AbilitySystemComponent->MakeEffectContext();
			// 	Context.AddSourceObject(GetOwner());
			// 	FGameplayEffectSpecHandle SpecHandle = CombatComponent->AbilitySystemComponent->MakeOutgoingSpec(CombatComponent->CombatUnitData->Upgrade.UpgradeEffect,1.0f,Context);
			// 	if (SpecHandle.IsValid())
			// 	{
			// 		CombatComponent->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			// 		return true;
			// 	}
			// }
		}
	}
	return false;
}

