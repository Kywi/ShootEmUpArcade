// Fill out your copyright notice in the Description page of Project Settings.


#include "NVShootComponent.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "../NWPawn/NWPlayerPawn.h"
#include "../../MyPlayerController.h"

// Sets default values for this component's properties
UNVShootComponent::UNVShootComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void UNVShootComponent::BeginPlay()
{
    Super::BeginPlay();

    StartShooting();
}

void UNVShootComponent::Shoot()
{
    for (auto ShootInfo : ShootInfos)
    {
      //  FActorSpawnParameters SpawnParameters;
      //  SpawnParameters.Owner = GetOwner();
      //  SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        FVector SpawnLocation =
            GetOwner()->GetActorLocation()
            +
            GetOwner()->GetActorRotation().RotateVector(ShootInfo.Offset);

        FRotator SpawnRotation = GetOwner()->GetActorRotation();
        SpawnRotation.Add(0.f, ShootInfo.Angle, 0.f);

        AMyPlayerController* playerController = (Cast<AMyPlayerController>(
            Cast<ANWPlayerPawn>(GetOwner())->GetController()));
        playerController->SpawnProjectile(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, GetOwner(),
                                          ShootInfo.Damage);
    }
}

void UNVShootComponent::StartShooting()
{
    GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UNVShootComponent::Shoot, ShootPeriod, true,
                                           ShootPeriod);
}

void UNVShootComponent::StopShooting()
{
    GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}

void UNVShootComponent::RestartShooting()
{
    StopShooting();
    StartShooting();
}
