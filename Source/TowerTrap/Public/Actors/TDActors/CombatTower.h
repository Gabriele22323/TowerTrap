// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatUnit.h"
#include "Components/SphereComponent.h"
#include "Data/TD_DataAssets/TurretData.h"
#include "Data/TD_DataAssets/TurretDefinition.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/Interactable.h"
#include "CombatTower.generated.h"

class ATurretSlot;

UCLASS()
class TOWERTRAP_API ACombatTower : public APawn, public IAbilitySystemInterface, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACombatTower();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TObjectPtr<UCombatComponent> CombatComponent;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TObjectPtr<USphereComponent> DetectionRange;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta=(ExposeOnSpawn))
	TObjectPtr<UTurretData> TowerData;
	
	//Handling range upgrade
	void OnAttackRangeChanged(const FOnAttributeChangeData& Data);
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<TObjectPtr<ACombatUnit>> Targets;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	TObjectPtr<ACombatUnit> CurrentTarget;
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int32 UpgradeLevel = 0;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool bIsTargetAvailable;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	TObjectPtr<ATurretSlot> OwningSlot;
	
	UFUNCTION(BlueprintCallable)
	bool ApplyUpgrade();
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OverlappedActor, UPrimitiveComponent* PrimitiveComponent, int Index, bool Sweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,AActor* OverlappedActor, UPrimitiveComponent* PrimitiveComponent, int Index);
	
	UFUNCTION()
	void BindDelegates();
	UFUNCTION(BlueprintCallable,CallInEditor)
	void ForceCheckDetection();
	UFUNCTION(BlueprintCallable)
	void InitializeTower(UTurretDefinition* Def);
	UFUNCTION(BlueprintCallable)
	void SetOwningSlot(ATurretSlot* Slot);
	
	UFUNCTION(BlueprintNativeEvent)
	void Interact_Implementation() override;
	UFUNCTION(BlueprintNativeEvent)
	void Hovered_Implementation() override;
	UFUNCTION(BlueprintNativeEvent)
	void UnHovered_Implementation() override;
};
