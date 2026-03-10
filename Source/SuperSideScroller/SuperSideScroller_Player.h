// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "SuperSideScroller_Player.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Player : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()

	bool bIsSprinting;
	UPROPERTY(EditAnywhere) class UAnimMontage* ThrowMontage;
	UPROPERTY(EditAnywhere) TSubclassOf<class APlayerProjectile> PlayerProjectile;
	int32 NumberofCollectables;
	FTimerHandle PowerupHandle;
	bool bHasPowerupActive;
	void IncreseMovementPowerup();
	void EndPowerup();
public:
	ASuperSideScroller_Player();
	void SpawnProjectile();
	UFUNCTION(BlueprintPure)int32 GetCurrentNumberofCollectables() { return NumberofCollectables; };
	void IncrementNumberofCollectables(int32 Value);
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Sprint();
	void StopSprinting();
	void ThrowProjectile();
};
