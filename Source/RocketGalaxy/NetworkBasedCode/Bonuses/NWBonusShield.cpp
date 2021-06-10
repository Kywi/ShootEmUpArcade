// Fill out your copyright notice in the Description page of Project Settings.


#include "NWBonusShield.h"
#include "NetworkBasedCode/NWPawn/NWPlayerPawn.h"

void ANWBonusShield::BonusCollected_Implementation(ANWPlayerPawn* ActorThatCollectBonus)
{
	if (!ActorThatCollectBonus->bCanBeDamaged) return;

	if (GetNetMode() == ENetMode::NM_ListenServer)
	{

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = ActorThatCollectBonus;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ANWShield* Shield = GetWorld()->SpawnActor<ANWShield>(ShieldClass, SpawnParams);

		if(Shield) Shield->ActivateShield(ActorThatCollectBonus);
	}
	Super::BonusCollected_Implementation(ActorThatCollectBonus);
}
