// Fill out your copyright notice in the Description page of Project Settings.


#include "NWMenuGameMode.h"
#include "Engine/World.h"

void ANWMenuGameMode::TravelToAnotherMap(FString mapName)
{
    GetWorld()->ServerTravel(mapName, true);
}
