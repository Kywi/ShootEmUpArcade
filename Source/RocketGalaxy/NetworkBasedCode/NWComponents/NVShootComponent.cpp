#include "NVShootComponent.h"

#include "Engine/World.h"
#include "TimerManager.h"

#include "../NWPawn/NWPlayerPawn.h"
#include "../../MyPlayerController.h"
#include "../Projectiles/NVShootProjectile.h"

UNVShootComponent::UNVShootComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UNVShootComponent::BeginPlay()
{
    Super::BeginPlay();

    if (GetNetMode() == NM_ListenServer)
        StartShooting();
}

void UNVShootComponent::Shoot()
{
    for (auto ShootInfo : ShootInfos)
    {
        SpawnProjectile(ShootInfo);
    }
}

void UNVShootComponent::StartShooting()
{
    if (GetNetMode() == NM_ListenServer)
        GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UNVShootComponent::Shoot, ShootPeriod, true,
                                               ShootPeriod);
}

void UNVShootComponent::StopShooting()
{
    if (GetNetMode() == NM_ListenServer)
        GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}

void UNVShootComponent::RestartShooting()
{
    if (GetNetMode() == NM_ListenServer)
    {
        StopShooting();
        StartShooting();
    }
}

void UNVShootComponent::SpawnProjectile_Implementation(FNVShootInfo projectilesToShoot)
{
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.Owner = GetOwner();
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    const FVector SpawnLocation =
        GetOwner()->GetActorLocation()
        +
        GetOwner()->GetActorRotation().RotateVector(projectilesToShoot.Offset);

    FRotator SpawnRotation = GetOwner()->GetActorRotation();
    SpawnRotation.Add(0.f, projectilesToShoot.Angle, 0.f);

    ANVShootProjectile* Projectile = GetWorld()->SpawnActor<ANVShootProjectile>(
        projectilesToShoot.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParameters);

    if (Projectile) Projectile->Damage = projectilesToShoot.Damage;
}
