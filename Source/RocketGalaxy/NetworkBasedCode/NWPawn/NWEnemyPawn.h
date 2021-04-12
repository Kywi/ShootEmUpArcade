// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "../NWComponents/NVShootComponent.h"
#include "Components/HealthComponent.h"
#include "Actors/Bonuses/Bonus.h"
#include "Components/ArrowComponent.h"
#include "Sound/SoundBase.h"
#include "../NWComponents/CreaturesHealthComponent.h"
#include "NWEnemyPawn.generated.h"

UCLASS()
class STREAMARCADE_API ANWEnemyPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ANWEnemyPawn();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Pawn")
        void DestroyPawn();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
        UBoxComponent* pawnCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
        UArrowComponent* arrowComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
        UStaticMeshComponent* pawnMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
        UNVShootComponent* shootComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
        UCreaturesHealthComponent* healthComponent;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

   // void SpawnBonuses();

    UFUNCTION()
        void KillPawn();

    UFUNCTION()
        void OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor);

};
