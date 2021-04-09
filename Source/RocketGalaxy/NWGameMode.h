// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSessionInterface.h"
#include "GameFramework/GameMode.h"

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

    UFUNCTION(BlueprintCallable)
        void TravelToAnotherMap();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Actor to posses")
        TSubclassOf<APawn> ActorToPosses;

    virtual void PostLogin(APlayerController* NewPlayer);

    int loginedUsers = 0;

};
