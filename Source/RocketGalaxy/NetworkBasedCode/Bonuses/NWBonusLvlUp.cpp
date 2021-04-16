// Fill out your copyright notice in the Description page of Project Settings.


#include "NWBonusLvlUp.h"
#include "../NWPawn/NWPlayerPawn.h"
// Sets default values
ANWBonusLvlUp::ANWBonusLvlUp()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void ANWBonusLvlUp::BonusCollected_Implementation(ANWPlayerPawn* ActorThatCollectBonus)
{
    if (GetNetMode() == ENetMode::NM_ListenServer)
    {
        if (ActorThatCollectBonus)
            ActorThatCollectBonus->ChangeEvolutionLvl(true);
    }
    Super::BonusCollected_Implementation(ActorThatCollectBonus);
}
