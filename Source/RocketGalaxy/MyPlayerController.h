// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "NetworkBasedCode/Projectiles/NVShootProjectile.h"

#include "MyPlayerController.generated.h"

class ANWPlayerPawn;

/**
 *
 */
UCLASS()
class STREAMARCADE_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);
    void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
    void OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location);

    UFUNCTION(Server, Reliable)
    void SpawnProjectile(TSubclassOf<ANVShootProjectile> actorToSpawn, FVector location, FRotator rotation,
                         AActor* Towner,
                         float damage);

    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    ANWPlayerPawn* possessedPawn;

    virtual void SetupInputComponent() override;
protected:
    virtual void OnPossess(APawn* InPawn) override;
};
