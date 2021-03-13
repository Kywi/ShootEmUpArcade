// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "PawnShield.generated.h"

class APlayerPawn;

UCLASS()
class STREAMARCADE_API APawnShield : public AActor
{
    GENERATED_BODY()
public:
    APawnShield();

    UFUNCTION(BlueprintCallable, Category = "Shield")
    void ActivateShield(APlayerPawn* PlayerPawn);

    UFUNCTION(BlueprintCallable, Category = "Shield")
    void DeactivateShield();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shield")
    float ShieldTime;

protected:
    FTimerHandle ShieldTimer;
    class APlayerPawn* ShildForPawn;
};
