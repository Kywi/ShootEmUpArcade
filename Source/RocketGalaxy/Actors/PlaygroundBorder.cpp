// Fill out your copyright notice in the Description page of Project Settings.

#include "PlaygroundBorder.h"
#include "Pawns/PlayerPawn.h"
#include "NetworkBasedCode/NWPawn/NWPlayerPawn.h"
#include "Components/BoxComponent.h"

// Sets default values
APlaygroundBorder::APlaygroundBorder()
{
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
    SetRootComponent(Trigger);
    Trigger->SetCollisionProfileName("OverlapAll");
}

void APlaygroundBorder::NotifyActorEndOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    if (!OtherActor || Cast<APlayerPawn>(OtherActor) || Cast<ANWPlayerPawn>(OtherActor))
        return;

    OtherActor->Destroy();
}
