// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerHealthComponent.h"

// Sets default values for this component's properties
UMainPlayerHealthComponent::UMainPlayerHealthComponent() :
    Healths(3)
{}

// Called when the game starts
void UMainPlayerHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    bReplicates = true;
    if (GetOwner())
        UE_LOG(LogTemp, Error, TEXT("No playerPawn!!!"));
}


void UMainPlayerHealthComponent::ChangeHealths(int ByValue)
{
    Healths += ByValue;
    if (Healths <= 0)
        HealthsEnded.Broadcast();
    UE_LOG(LogTemp, Log, TEXT("Health changed: %i"), Healths);
}

int UMainPlayerHealthComponent::GetHealths() const
{
    return Healths;
}



