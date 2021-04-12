// Fill out your copyright notice in the Description page of Project Settings.


#include "CreaturesHealthComponent.h"

// Sets default values for this component's properties
UCreaturesHealthComponent::UCreaturesHealthComponent()
{
}



void UCreaturesHealthComponent::OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* Instigator, AActor* DamageCauser)
{
    ChangeHealth(-Damage);
}

void UCreaturesHealthComponent::ChangeHealth(float value)
{
    Health += value;

    if (Health <= 0.f) {
        GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UCreaturesHealthComponent::OnOwnerDamaged);
        OnHealthEnded.Broadcast();
    }
}

float UCreaturesHealthComponent::GetHealth() const
{
    return Health;
}

void UCreaturesHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCreaturesHealthComponent::OnOwnerDamaged);
}


