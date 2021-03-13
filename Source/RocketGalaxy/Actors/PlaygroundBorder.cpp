// Fill out your copyright notice in the Description page of Project Settings.

#include "PlaygroundBorder.h"
#include "Pawns/PlayerPawn.h"

#include "Components/BoxComponent.h"

// Sets default values
APlaygroundBorder::APlaygroundBorder()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);

	Trigger->SetCollisionProfileName("OverlapAll");
}

void APlaygroundBorder::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (!OtherActor) return;
	if (Cast<APlayerPawn>(OtherActor)) return;

	OtherActor->Destroy();
}
