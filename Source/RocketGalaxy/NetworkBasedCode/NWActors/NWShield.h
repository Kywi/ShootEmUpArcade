// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../NWPawn/NWPlayerPawn.h"
#include "NWShield.generated.h"

UCLASS()
class STREAMARCADE_API ANWShield : public AActor
{
	GENERATED_BODY()
	
	public:
	ANWShield();

	UFUNCTION(BlueprintCallable,Server, Reliable,Category = "Shield")
	void ActivateShield(ANWPlayerPawn* PlayerPawn);

	UFUNCTION(BlueprintCallable, Category = "Shield")
	void DeactivateShield();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shield")
	float ShieldTime;

	protected:
	FTimerHandle ShieldTimer;
	class ANWPlayerPawn* ShildForPawn;

};
