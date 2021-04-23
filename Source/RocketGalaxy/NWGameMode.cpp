// Fill out your copyright notice in the Description page of Project Settings.


#include "NWGameMode.h"

#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "MyPlayerController.h"

ANWGameMode::ANWGameMode()
{
    EnemySpawnController = CreateDefaultSubobject<UNWEnemiesSpawnController>(TEXT("EnemySpawnController"));

    playerConnnected.AddDynamic(this, &ANWGameMode::StartSpawnEnemies);
}

void ANWGameMode::TravelToAnotherMap(FString mapName)
{
    GetWorld()->ServerTravel(mapName, true);
}

int ANWGameMode::GeneratePLayerID()
{
    return ++loginedUsers;
}

void ANWGameMode::IncreaseDifficulty()
{
    EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier * 0.95,
                                                                 0.4);
    UE_LOG(LogTemp, Log, TEXT("Difficulty increased: %f"), EnemySpawnController->ChangeStageTimeMultiplier);
}

void ANWGameMode::BeginPlay()
{
    Super::BeginPlay();
}


void ANWGameMode::StartSpawnEnemies()
{
    EnemySpawnController->StartSpawnStage();
    GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this,
                                           &ANWGameMode::IncreaseDifficulty, IncreaseDifficultyPeriod,
                                           true);
}
