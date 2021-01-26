// Fill out your copyright notice in the Description page of Project Settings.

#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "StreamArcadeGameModeBase.h"

void ABonusPoints::BonusCollected_Implementation()
{
	AStreamArcadeGameModeBase* Gamemode = Cast<AStreamArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode) Gamemode->AddPoints(Points);

	Super::BonusCollected_Implementation();
}
