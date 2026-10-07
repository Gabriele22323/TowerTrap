// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TDActors/CombatTower.h"

#include "AbilitySystemComponent.h"
#include "Data/AttributeSets/CombatAttributeSet.h"
#include "Engine/OverlapResult.h"
#include "Misc/MapErrors.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Turret_Attack, "Tower.Attack.Primary");

// Sets default values
ACombatTower::ACombatTower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CombatComponent = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	DetectionRange = CreateDefaultSubobject<USphereComponent>("DetectionRange");
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	DetectionRange->OnComponentBeginOverlap.AddDynamic(this,&ACombatTower::OnOverlapBegin);
	CombatComponent->FOnInitialize.AddDynamic(this, &ACombatTower::BindDelegates);
}

// Called when the game starts or when spawned
void ACombatTower::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACombatTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsTargetAvailable)
	{
		if (!CurrentTarget)
		{
			if (Targets.IsEmpty())
			{
				bIsTargetAvailable = false;
				return;
			}
			else
			{
				CurrentTarget = Targets[0];
			}
			if (CurrentTarget->bIsDead)
			{
				Targets.Remove(CurrentTarget);
				CurrentTarget = nullptr;
			}
		}
		if (CurrentTarget && CurrentTarget->bIsDead)
		{
			CurrentTarget = nullptr;
			Targets.Remove(CurrentTarget);
		}
		if (CurrentTarget && !CurrentTarget->bIsDead)
		{
			GetAbilitySystemComponent()->TryActivateAbilitiesByTag(FGameplayTagContainer(TAG_Turret_Attack),false);
		}
	}
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
	if (TowerData)
	{
		if (UpgradeLevel < TowerData->Upgrade.UpgradeAmountLimit)
		{
			FGameplayEffectContextHandle ContextHandle = CombatComponent->AbilitySystemComponent->MakeEffectContext();
			ContextHandle.AddSourceObject(this);
			FGameplayEffectSpecHandle SpecHandle = CombatComponent->AbilitySystemComponent->MakeOutgoingSpec(TowerData->Upgrade.UpgradeEffect,1.0f, ContextHandle);
			if (SpecHandle.IsValid())
			{
				CombatComponent->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
	return false;
}

void ACombatTower::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OverlappedActor, UPrimitiveComponent* PrimitiveComponent, int Index, bool Sweep, const FHitResult& SweepResult)
{
	if (OverlappedActor->ActorHasTag("Enemy"))
	{
		ACombatUnit* Target = Cast<ACombatUnit>(OverlappedActor);
		Targets.Add(Target);
		bIsTargetAvailable = true;
		if (!CurrentTarget)
		{
			CurrentTarget = Target;
		}
	}
}

void ACombatTower::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OverlappedActor,UPrimitiveComponent* PrimitiveComponent, int Index, bool Sweep, const FHitResult& SweepResult)
{
	if (OverlappedActor->ActorHasTag("Enemy"))
	{
		ACombatUnit* Target = Cast<ACombatUnit>(OverlappedActor);
		Targets.Remove(Target);
	}
	if (Targets.IsEmpty())
	{
		bIsTargetAvailable = false;
		CurrentTarget = nullptr;
	}
}

void ACombatTower::BindDelegates()
{
	CombatComponent->AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCombatAttributeSet::GetAttackRangeAttribute()).AddUObject(this,&ACombatTower::OnAttackRangeChanged);
	DetectionRange->SetSphereRadius(CombatComponent->AbilitySystemComponent->GetNumericAttribute(UCombatAttributeSet::GetAttackRangeAttribute()));
}

void ACombatTower::ForceCheckDetection()
{
	Targets.Empty();
	const float Detection = GetAbilitySystemComponent()->GetNumericAttribute(UCombatAttributeSet::GetAttackRangeAttribute());
	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	const bool bHasOverlaps = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		GetOwner()->GetActorLocation(),
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(Detection),
		QueryParams
	);
	if (!bHasOverlaps)
	{
		return;
	}
	for (const FOverlapResult& Result : Overlaps)
	{
		ACombatUnit* CombatUnit = Cast<ACombatUnit>(Result.GetActor());
		if (IsValid(CombatUnit) && !CombatUnit->bIsDead)
		{
			Targets.AddUnique(CombatUnit);
		}
	}
	if (!Targets.IsEmpty())
	{
		CurrentTarget = Targets[0];
		bIsTargetAvailable = true;
	}
}

void ACombatTower::InitializeTower(UTurretDefinition* Def)
{
	TowerData = Def->TowerData;
	CombatComponent->AssignDataAndInitialize(Def->CombatData);
	if (TowerData)
	{
		StaticMesh->SetStaticMesh(TowerData->Mesh);
	}
}

void ACombatTower::SetOwningSlot(ATurretSlot* Slot)
{
	if (Slot)
	{
		OwningSlot = Slot;
	}
}

void ACombatTower::UnHovered_Implementation_Implementation()
{
	if (OwningSlot)
	{
		IInteractable::Execute_UnHovered(OwningSlot);
	}
}

void ACombatTower::Hovered_Implementation_Implementation()
{
	if (OwningSlot)
	{
		IInteractable::Execute_Hovered(OwningSlot);
	}
}

void ACombatTower::Interact_Implementation_Implementation()
{
	if (OwningSlot)
	{
		IInteractable::Execute_Interact(OwningSlot);
	}
}

