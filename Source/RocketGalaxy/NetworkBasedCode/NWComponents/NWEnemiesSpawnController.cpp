
#include "NWEnemiesSpawnController.h"

#include "Engine/World.h"
#include "TimerManager.h"


void UNWEnemiesSpawnController::BeginPlay()
{
    Super::BeginPlay();

    Random.GenerateNewSeed();
    // StartSpawnStage();
}

void UNWEnemiesSpawnController::Deactivate()
{
    Super::Deactivate();

    GetWorld()->GetTimerManager().ClearTimer(ChangeStageTimer);
    GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimer);
}

void UNWEnemiesSpawnController::SpawnEnemy()
{
    const FActorSpawnParameters SpawnParameters;
    GetWorld()->SpawnActor<ANWEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform, SpawnParameters);

    EnemiesSpawned++;
    if (EnemiesSpawned < SpawnStage.NumOfEnemies)
    {
        GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimer, this, &UNWEnemiesSpawnController::SpawnEnemy,
            SpawnStage.SpawnDelay, false);
    }
}

void UNWEnemiesSpawnController::StartSpawnStage()
{
    SpawnStage = SpawnStages[Random.RandRange(0, SpawnStages.Num() - 1)];

    EnemiesSpawned = 0;
    SpawnEnemy();

    const float ChangeStageTime = Random.RandRange(StageMinDelay, StageMaxDelay) * ChangeStageTimeMultiplier;
    GetWorld()->GetTimerManager().SetTimer(ChangeStageTimer, this, &UNWEnemiesSpawnController::StartSpawnStage,
        ChangeStageTime, false);
}


