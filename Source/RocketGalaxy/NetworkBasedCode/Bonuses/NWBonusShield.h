// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkBasedCode/Bonuses/NWBonus.h"
#include "../NWActors/NWShield.h"
#include "NWBonusShield.generated.h"

/**
 * 
 */
UCLASS()
class STREAMARCADE_API ANWBonusShield : public ANWBonus
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
	TSubclassOf<ANWShield> ShieldClass;

protected:
	virtual void BonusCollected_Implementation(ANWPlayerPawn* ActorThatCollectBonus) override;
};
