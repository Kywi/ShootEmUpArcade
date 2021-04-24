// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"


#include "UnrealNetwork.h"
#include "NetworkBasedCode/NWPawn/NWPlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"


void AMyPlayerController::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (possessedPawn && canReceiveInputs)
    {
        possessedPawn->OnTouchMove(FingerIndex, Location);
    }
    else
        possessedPawn = Cast<ANWPlayerPawn>(GetPawn());
}


void AMyPlayerController::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (possessedPawn)
    {
        possessedPawn->OnTouchPress(FingerIndex, Location);
    }
    else
        possessedPawn = Cast<ANWPlayerPawn>(GetPawn());
}

void AMyPlayerController::OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (possessedPawn && canReceiveInputs)
        possessedPawn->OnTouchReleased(FingerIndex, Location);
    else
        possessedPawn = Cast<ANWPlayerPawn>(GetPawn());
}

void AMyPlayerController::SetPlayerID(int playerId)
{
    this->playerID = playerId;
}

int AMyPlayerController::GetPlayerID()
{
    return playerID;
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindTouch(IE_Pressed, this, &AMyPlayerController::OnTouchPress);
    InputComponent->BindTouch(IE_Released, this, &AMyPlayerController::OnTouchReleased);
    InputComponent->BindTouch(IE_Repeat, this, &AMyPlayerController::OnTouchMove);
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMyPlayerController, playerID);
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}
