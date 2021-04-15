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

void ANWGameMode::TravelToAnotherMap()
{
    GetWorld()->ServerTravel("M_MainMenu", true);
}

void ANWGameMode::IncreaseDifficulty()
{
    EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier * 0.95,
                                                                 0.4);
    UE_LOG(LogTemp, Log, TEXT("Difficulty increased: %f"), EnemySpawnController->ChangeStageTimeMultiplier);
}

void ANWGameMode::BeginPlay()
{
}

APawn* ANWGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
    const auto actor = GetWorld()->SpawnActor<APawn>(ActorToPosses, StartSpot->GetTransform());
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
                                     FString::Printf(TEXT("Connected users , %d"), ++loginedUsers));
    if (loginedUsers + 1 == 2)
        playerConnnected.Broadcast();
    Cast<AMyPlayerController>(NewPlayer)->SetPlayerID(loginedUsers);
    return actor;
}

void ANWGameMode::StartSpawnEnemies()
{
    EnemySpawnController->StartSpawnStage();
    GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this,
                                           &ANWGameMode::IncreaseDifficulty, IncreaseDifficultyPeriod,
                                           true);
}
