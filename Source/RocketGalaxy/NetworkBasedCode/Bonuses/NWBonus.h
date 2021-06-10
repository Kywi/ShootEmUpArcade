// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NWBonus.generated.h"

class ANWPlayerPawn;
UCLASS()
class STREAMARCADE_API ANWBonus : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ANWBonus();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
    class USphereComponent* Collision;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UParticleSystem* CollectParticle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    USoundBase* CollectSound;
protected:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintNativeEvent)
    void BonusCollected(ANWPlayerPawn* ActorThatCollectBonus);
    virtual void BonusCollected_Implementation(ANWPlayerPawn* ActorThatCollectBonus);
    private:
    UFUNCTION(NetMulticast , Reliable)
    void SpawnBonusCollectedEffects();

};
