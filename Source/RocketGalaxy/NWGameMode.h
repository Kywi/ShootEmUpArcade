// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSessionInterface.h"
#include "GameFramework/GameMode.h"
#include "NetworkBasedCode/NWComponents/NWEnemiesSpawnController.h"
#include "NWGameMode.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerConnnected);

UCLASS()
class STREAMARCADE_API ANWGameMode : public AGameMode
{
    GENERATED_BODY()

    ANWGameMode();
    
public:
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FPlayerConnnected playerConnnected;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
    UNWEnemiesSpawnController* EnemySpawnController;

    UFUNCTION(BlueprintCallable)
    void TravelToAnotherMap(FString mapName);

    UFUNCTION(BlueprintCallable)
    int GeneratePLayerID();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void IncreaseDifficulty();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
    float IncreaseDifficultyPeriod;

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void StartSpawnEnemies();

private:

    int32 loginedUsers = -1;
    FTimerHandle IncreaseDifficultyTimer;
};
