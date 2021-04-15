// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "Components/GameHealthComponent.h"

#include "MainPlayerHealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STREAMARCADE_API UMainPlayerHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UMainPlayerHealthComponent();


    UFUNCTION(BlueprintCallable, Category = "Game Health")
        void ChangeHealths(int ByValue);

    UFUNCTION(BlueprintPure, Category = "Game Health")
        int GetHealths() const;

    UPROPERTY(BlueprintAssignable, Category = "Game Health")
        FHealthsEndedEvent HealthsEnded;

    UPROPERTY(BlueprintAssignable, Category = "Game Health")
        FHealthsChangedEvent HealthsChanged;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "Game Health")
        int Healths;

};
