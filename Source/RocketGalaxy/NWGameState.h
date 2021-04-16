// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameState.h"
#include "Delegates/Delegate.h"

#include "NWGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoreChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayersHealthChanged);

UCLASS()
class STREAMARCADE_API ANWGameState : public AGameState
{
    GENERATED_BODY()

public:
    UPROPERTY(Replicated, BlueprintReadWrite,ReplicatedUsing = OnRep_gamePoints)
    TArray<float> gamePoints;

    UPROPERTY(Replicated, BlueprintReadWrite,ReplicatedUsing = OnRep_playersHealth)
    TArray<float> playersHealth;
    
    UFUNCTION(BlueprintCallable)
    void OnRep_gamePoints() const;

    UFUNCTION(BlueprintCallable)
    void OnRep_playersHealth() const;
    
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FScoreChanged gameScoreChanged;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FPlayersHealthChanged playersHealthChanged;
    
protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
