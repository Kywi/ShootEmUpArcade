// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NetworkBasedCode/NWPawn/NWEnemyPawn.h"
#include "Components/ActorComponent.h"

#include "NWEnemiesSpawnController.generated.h"

USTRUCT(BlueprintType)
struct FNWEnemySpawnInfo
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
        TSubclassOf<ANWEnemyPawn> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
        FTransform SpawnTransform {
        FRotator(0, 180, 0)
    };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
        int NumOfEnemies;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
        float SpawnDelay;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STREAMARCADE_API UNWEnemiesSpawnController : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
        TArray<FNWEnemySpawnInfo> SpawnStages;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
        float StageMinDelay;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
        float StageMaxDelay;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
        float ChangeStageTimeMultiplier;

    UFUNCTION(BlueprintCallable)
        void StartSpawnStage();

protected:
    virtual void BeginPlay() override;
    virtual void Deactivate() override;
    UFUNCTION(Server, Reliable)
        void SpawnEnemy();

    FNWEnemySpawnInfo SpawnStage;
    int EnemiesSpawned;
    FTimerHandle ChangeStageTimer;
    FTimerHandle EnemySpawnTimer;
    FRandomStream Random;
};
