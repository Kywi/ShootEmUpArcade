// Fill out your copyright notice in the Description page of Project Settings.

#include "StreamArcadeGameModeBase.h"
#include "Pawns/PlayerPawn.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


AStreamArcadeGameModeBase::AStreamArcadeGameModeBase():
    PlayerRecoverTime(3),
    IncreaseDifficultyPeriod(4.f),
    CurrentShootLevel(-1)
{
    EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
    HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AStreamArcadeGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    HealthsComponent->HealthsEnded.AddDynamic(this, &AStreamArcadeGameModeBase::EndGame);

    PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (!PlayerPawn) return;

    ChangeShootLevel(true);

    PlayerPawn->PawnDamaged.AddDynamic(this, &AStreamArcadeGameModeBase::ExplodePawn);

    GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this,
                                           &AStreamArcadeGameModeBase::IncreaseDifficulty, IncreaseDifficultyPeriod,
                                           true);
}

void AStreamArcadeGameModeBase::ExplodePawn_Implementation()
{
    PlayerPawn->ExplodePawn();

    HealthsComponent->ChangeHealths(-1);

    ChangeShootLevel(false);

    if (!IsGameOver)
        GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AStreamArcadeGameModeBase::RecoverPawn,
                                               PlayerRecoverTime, false);
}

void AStreamArcadeGameModeBase::RecoverPawn_Implementation()
{
    PlayerPawn->RecoverPawn();
}

void AStreamArcadeGameModeBase::EndGame()
{
    IsGameOver = true;

    EnemySpawnController->SetActive(false);

    GameOver.Broadcast();

    UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

    UE_LOG(LogTemp, Log, TEXT("GAME OVER!!!"));

    SetPause(UGameplayStatics::GetPlayerController(this, 0), nullptr);
}

void AStreamArcadeGameModeBase::IncreaseDifficulty()
{
    EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier * 0.95,
                                                                 0.4);
    UE_LOG(LogTemp, Log, TEXT("Difficulty increased: %f"), EnemySpawnController->ChangeStageTimeMultiplier);
}

void AStreamArcadeGameModeBase::AddPoints(int Points)
{
    GamePoints += Points;
}

bool AStreamArcadeGameModeBase::ChangeShootLevel(bool Up)
{
    PlayerPawn = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (!PlayerPawn) return false;

    int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, ShootInfoLevels.Num() - 1);

    if (NewLevel == CurrentShootLevel) return false;

    CurrentShootLevel = NewLevel;

    PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
    PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;
    UE_LOG(LogTemp, Log, TEXT("ChnagedShootPeriod: %f"), ShootInfoLevels[CurrentShootLevel].ShootPeriod);
    if (Up) PlayerPawn->ShootComponent->RestartShooting();

    return true;
}
