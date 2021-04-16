// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"

#include "NVShootProjectile.generated.h"

UCLASS()
class STREAMARCADE_API ANVShootProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ANVShootProjectile();
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
        USphereComponent* Collision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
        UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
        UParticleSystemComponent* Particle;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
        float ProjectileSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
        float Damage;

protected:
    virtual void BeginPlay() override;

    int playerID;
    UFUNCTION()
        void OnProjectileOverlap(UPrimitiveComponent* OpelappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
            int32 BodyIndex, bool Sweep, const FHitResult& Hit);

};
