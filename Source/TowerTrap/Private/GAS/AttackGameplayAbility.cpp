// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttackGameplayAbility.h"

#include "Data/AttributeSets/CombatAttributeSet.h"

void UAttackGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		return;
	}
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	const float AttackRate = ASC->GetNumericAttribute(UCombatAttributeSet::GetAttackRateAttribute());
	if (AttackRate <= 0.0f)
	{
		return;
	}
	const float CooldownDuration = 60.0f / AttackRate;
	// Get the normal cooldown Gameplay Effect configured on the Blueprint ability.
	if (!CooldownGameplayEffectClass)
	{
		UE_LOG(LogTemp, Error, TEXT("CooldownGameplayEffectClass is NULL"));
		return;
	}
	FGameplayEffectSpecHandle SpecHandle =ASC->MakeOutgoingSpec(CooldownGameplayEffectClass,GetAbilityLevel(Handle, ActorInfo),ASC->MakeEffectContext());
	if (!SpecHandle.IsValid())
	{
		return;
	}
	SpecHandle.Data->SetDuration(CooldownDuration,true);
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
}
