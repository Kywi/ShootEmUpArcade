// Fill out your copyright notice in the Description page of Project Settings.


#include "NWGameState.h"

#include "UnrealNetwork.h"

void ANWGameState::BeginPlay()
{
    Super::BeginPlay();
}

void ANWGameState::OnRep_gamePoints() const
{
    gameScoreChanged.Broadcast();
}

void ANWGameState::OnRep_playersHealth() const
{
    playersHealthChanged.Broadcast();
}

void ANWGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(ANWGameState, gamePoints);
    DOREPLIFETIME(ANWGameState, playersHealth);
}
