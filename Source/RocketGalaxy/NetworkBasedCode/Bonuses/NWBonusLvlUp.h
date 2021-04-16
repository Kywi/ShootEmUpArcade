// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NWBonus.h"
#include "GameFramework/Actor.h"
#include "NWBonusLvlUp.generated.h"

UCLASS()
class STREAMARCADE_API ANWBonusLvlUp : public ANWBonus
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ANWBonusLvlUp();

protected:
    // Called when the game starts or when spawned
    virtual void BonusCollected_Implementation(ANWPlayerPawn* ActorThatCollectBonus) override;
};
