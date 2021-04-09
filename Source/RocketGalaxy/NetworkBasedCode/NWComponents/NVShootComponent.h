// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "../Projectiles/NVShootProjectile.h"
#include "NVShootComponent.generated.h"

USTRUCT(BlueprintType)
struct FNVShootInfo
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    TSubclassOf<ANVShootProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    FVector Offset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
    float Angle;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STREAMARCADE_API UNVShootComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UNVShootComponent();

    UFUNCTION(BlueprintCallable, Category = "Shooting")
    void StartShooting();

    UFUNCTION(BlueprintCallable, Category = "Shooting")
    void StopShooting();

    UFUNCTION(BlueprintCallable, Category = "Shooting")
    void RestartShooting();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
    float ShootPeriod;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
    TArray<FNVShootInfo> ShootInfos;

protected:
    virtual void BeginPlay() override;
    void Shoot();
    FTimerHandle ShootingTimer;
};
