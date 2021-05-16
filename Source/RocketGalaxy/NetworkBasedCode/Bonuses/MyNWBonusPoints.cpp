// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNWBonusPoints.h"

#include "MyPlayerController.h"
#include "NWGameState.h"
#include "NetworkBasedCode/NWPawn/NWPlayerPawn.h"

void AMyNWBonusPoints::BonusCollected_Implementation(ANWPlayerPawn* ActorThatCollectBonus)
{
	if (GetNetMode() == ENetMode::NM_ListenServer)
	{
		auto gameState = GetWorld()->GetGameState<ANWGameState>();
		
		gameState->gamePoints[ActorThatCollectBonus->GetController<AMyPlayerController>()->GetPlayerID()] += Points;
		gameState->OnRep_gamePoints();
	}
	Super::BonusCollected_Implementation(ActorThatCollectBonus);
}
