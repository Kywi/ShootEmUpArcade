// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusShootLevelUp.h"

#include "Kismet/GameplayStatics.h"

#include "StreamArcadeGameModeBase.h"

void ABonusShootLevelUp::BonusCollected_Implementation()
{
	AStreamArcadeGameModeBase* Gamemode = Cast<AStreamArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!Gamemode) return;
	Gamemode->ChangeShootLevel(true);
	Super::BonusCollected_Implementation();
}
