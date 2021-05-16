// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NetworkBasedCode/Bonuses/NWBonus.h"
#include "MyNWBonusPoints.generated.h"

/**
 * 
 */
UCLASS()
class STREAMARCADE_API AMyNWBonusPoints : public ANWBonus
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
	int Points;
	
protected:
	virtual void BonusCollected_Implementation(ANWPlayerPawn* ActorThatCollectBonus) override;
};
