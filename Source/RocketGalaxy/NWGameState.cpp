// Fill out your copyright notice in the Description page of Project Settings.


#include "NWGameState.h"

#include "UnrealNetwork.h"

ANWGameState::ANWGameState()
{
    
}

void ANWGameState::BeginPlay()
{
    Super::BeginPlay();
}

void ANWGameState::OnRep_gamePoints() const
{
    gameScoreChanged.Broadcast();
}

//
// void ANWGameState::OnRep_serverClientPoints() const
// {
//     clientScoreChanged.Broadcast();
// }
//
// void ANWGameState::OnRep_remoteClientPoints() const
// {
//     serverScoreChanged.Broadcast();
// }

void ANWGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    // DOREPLIFETIME(ANWGameState, serverClientPoints);
    // DOREPLIFETIME(ANWGameState, remoteClientPoints);
    DOREPLIFETIME(ANWGameState, gamePoints);
}
