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
        void TravelToAnotherMap();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor to posses")
        TSubclassOf<APawn> ActorToPosses;

    UFUNCTION(BlueprintCallable, Category = "Game")
        void IncreaseDifficulty();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
        float IncreaseDifficultyPeriod;

protected:
    virtual void BeginPlay() override;
    virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;

private:
    UFUNCTION()
        void StartSpawnEnemies();

    int32 loginedUsers = -1;
    FTimerHandle RecoverTimer;
    FTimerHandle IncreaseDifficultyTimer;
};
