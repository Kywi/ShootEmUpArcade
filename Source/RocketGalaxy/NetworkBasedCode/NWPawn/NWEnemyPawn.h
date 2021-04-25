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
#include "NetworkBasedCode/Bonuses/NWBonus.h"

#include "NWEnemyPawn.generated.h"

USTRUCT(BlueprintType)
struct FNWBonusChance
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
    TSubclassOf<ANWBonus> BonusClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
    float Chance;
};

UCLASS()
class STREAMARCADE_API ANWEnemyPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ANWEnemyPawn();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(NetMulticast, Reliable)
    void DestroyPawn();

    UFUNCTION(NetMulticast, Reliable)
    void SpawnBonuses(TSubclassOf<ANWBonus> BonusClass);

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UParticleSystem* DestroyParticle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    FVector ScaleDestroyParticle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bonuses")
    TArray<FNWBonusChance> possibleBonuses;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    USoundBase* DestroySound;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
    int DestroyPoints;

    void SetPlayerID(int TplayerID);
    int GetPlayerID();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
    void KillPawn(int TplayerID);

    UFUNCTION()
    void OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor);

    int playerID;
};
