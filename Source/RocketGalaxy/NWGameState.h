// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Delegates/Delegate.h"
#include "NWGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreChanged);

UCLASS()
class STREAMARCADE_API ANWGameState : public AGameState
{
    GENERATED_BODY()

public:
    ANWGameState();

    virtual void BeginPlay() override;
    UPROPERTY(Replicated, BlueprintReadWrite,ReplicatedUsing = OnRep_gamePoints)
    TArray<float> gamePoints;

    UFUNCTION()
    void OnRep_gamePoints() const;

    // UFUNCTION()
    // void OnRep_serverClientPoints() const;
    //
    // UFUNCTION()
    // void OnRep_remoteClientPoints() const;


    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FScoreChanged gameScoreChanged;

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // UPROPERTY(BlueprintCallable, BlueprintAssignable)
    // FScoreChanged clientScoreChanged;
    //
    // UPROPERTY(BlueprintCallable, BlueprintAssignable)
    // FScoreChanged serverScoreChanged;
};
