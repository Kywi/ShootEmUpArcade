// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Actors/Bonuses/Bonus.h"

#include "BonusShootLevelUp.generated.h"


UCLASS()
class STREAMARCADE_API ABonusShootLevelUp : public ABonus
{
	GENERATED_BODY()
	
protected:

	virtual void BonusCollected_Implementation() override;	
};
