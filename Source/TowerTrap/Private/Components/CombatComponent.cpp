// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CombatComponent.h"

#include "AbilitySystemComponent.h"


// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UAbilitySystemComponent* UCombatComponent::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCombatData* UCombatComponent::GetCombatUnitData() const
{
	return CombatUnitData;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent = NewObject<UAbilitySystemComponent>(GetOwner(),TEXT("AbilitySystemComponent"));
	GetOwner()->AddInstanceComponent(AbilitySystemComponent);
	AbilitySystemComponent->RegisterComponent();
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::AssignDataAndInitialize(UCombatData* Data)
{
	CombatUnitData = Data;
	InitializeCombat();
	FOnInitialize.Broadcast();
}

void UCombatComponent::InitializeCombat()
{
	if (bCombatInitialized)
	{
		return;
	}
	if (!AbilitySystemComponent || !CombatUnitData)
	{
		return;
	}
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}
	InitializeAttributeSets();
	AbilitySystemComponent->InitAbilityActorInfo(Owner,Owner);
	InitializeStartupEffects();
	InitializeAbilities();
	bCombatInitialized = true;
}

void UCombatComponent::InitializeAttributeSets()
{
	if (!CombatUnitData)
	{
		return;
	}

	for (const TSubclassOf<UAttributeSet>& AttributeSetClass : CombatUnitData->AttributeSet)
	{
		if (!AttributeSetClass)
		{
			continue;
		}
		UAttributeSet* NewAttributeSet = NewObject<UAttributeSet>(this, AttributeSetClass); //instantiate attribute set
		if (!NewAttributeSet)
		{
			continue;
		}
		AbilitySystemComponent->AddAttributeSetSubobject(NewAttributeSet);
		AttributeSets.Add(NewAttributeSet);
		UE_LOG(LogTemp,Log,TEXT("Added attribute set %s"),*AttributeSetClass->GetName());
	}
}

void UCombatComponent::InitializeStartupEffects()
{
	if (!CombatUnitData)
	{
		return;
	}
	for (const TSubclassOf<UGameplayEffect>& EffectClass : CombatUnitData->StartUpEffects)
	{
		if (!EffectClass)
		{
			continue;
		}
		FGameplayEffectContextHandle EffectContext =AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(GetOwner());
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass,1.0f,EffectContext);
		if (!SpecHandle.IsValid())
		{
			continue;
		}
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		UE_LOG(LogTemp,Log,TEXT("Applied startup effect %s"),*EffectClass->GetName());
	}
}

void UCombatComponent::InitializeAbilities()
{
	if (!CombatUnitData)
	{
		return;
	}
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : CombatUnitData->Abilities)
	{
		if (!AbilityClass)
		{
			continue;
		}
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass));
		UE_LOG(LogTemp,Log,TEXT("Added ability %s"),*AbilityClass->GetName());
	}
}

