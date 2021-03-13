// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "PlaygroundBorder.generated.h"

UCLASS()
class STREAMARCADE_API APlaygroundBorder : public AActor
{
    GENERATED_BODY()

public:
    APlaygroundBorder();

    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UBoxComponent* Trigger;
};
