// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Controller.h"
#include "Components/ActorComponent.h"

#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEndedEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STREAMARCADE_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthComponent();

    UFUNCTION(BlueprintCallable, Category = "Health")
        void ChangeHealth(float Value);

    UFUNCTION(BlueprintPure, Category = "Health")
        float GetHealth() const;

    UPROPERTY(BlueprintAssignable, Category = "Health")
    FHealthEndedEvent OnHealthEnded;
    
protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    float Health;

    UFUNCTION()
        void OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
};
