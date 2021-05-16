// Fill out your copyright notice in the Description page of Project Settings.


#include "NWBonusLvlUp.h"
#include "../NWPawn/NWPlayerPawn.h"
// Sets default values

void ANWBonusLvlUp::BonusCollected_Implementation(ANWPlayerPawn* ActorThatCollectBonus)
{
    if (GetNetMode() == ENetMode::NM_ListenServer)
    {
        if (ActorThatCollectBonus)
            ActorThatCollectBonus->ChangeEvolutionLvl(true);
    }
    Super::BonusCollected_Implementation(ActorThatCollectBonus);
}
