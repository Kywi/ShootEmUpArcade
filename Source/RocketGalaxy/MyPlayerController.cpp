// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "NetworkBasedCode/NWPawn/NWPlayerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"



void AMyPlayerController::SpawnProjectile_Implementation(TSubclassOf<ANVShootProjectile> actorToSpawn, FVector location,
    FRotator rotation, AActor* Towner, float damage)
{
    FActorSpawnParameters spawnParameters;
    spawnParameters.Owner = Towner;
    spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    auto projectile = GetWorld()->SpawnActor<ANVShootProjectile>(actorToSpawn, location, rotation, spawnParameters);
    projectile->Damage = damage;
    //GetWorld()->SpawnActor<AShootProjectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParameters);
}

void AMyPlayerController::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (possessedPawn)
        possessedPawn->OnTouchMove(FingerIndex, Location);
    else
        possessedPawn = Cast<ANWPlayerPawn>(GetPawn());

}

void AMyPlayerController::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
    if (possessedPawn)
        possessedPawn->OnTouchPress(FingerIndex, Location);
    else
        possessedPawn = Cast<ANWPlayerPawn>(GetPawn());
}

void AMyPlayerController::OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location)
{

    if (possessedPawn)
        possessedPawn->OnTouchReleased(FingerIndex, Location);
    else
        possessedPawn = Cast<ANWPlayerPawn>(GetPawn());
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindTouch(IE_Pressed, this, &AMyPlayerController::OnTouchPress);
    InputComponent->BindTouch(IE_Released, this, &AMyPlayerController::OnTouchReleased);
    InputComponent->BindTouch(IE_Repeat, this, &AMyPlayerController::OnTouchMove);
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    //  possessedPawn = Cast<ANWPlayerPawn>(InPawn);
     // possessedPawn->SetOwner(this);
      //possessedPawn->SetupPlayerInputComponent(InputComponent);
}

