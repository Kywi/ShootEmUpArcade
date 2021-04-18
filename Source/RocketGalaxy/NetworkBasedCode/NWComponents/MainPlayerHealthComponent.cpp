// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerHealthComponent.h"

#include "MyPlayerController.h"

// Sets default values for this component's properties
UMainPlayerHealthComponent::UMainPlayerHealthComponent() :
    Healths(3)
{
}

// Called when the game starts
void UMainPlayerHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    bReplicates = true;
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UMainPlayerHealthComponent::OnOwnerDamaged);
}

void UMainPlayerHealthComponent::OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                                AController* Instigator, AActor* DamageCauser)
{
    if (GetOwner()->bCanBeDamaged)
        ChangeHealths(Damage);
}


void UMainPlayerHealthComponent::ChangeHealths(int ByValue)
{
    Healths += ByValue;
    if (Healths <= 0)
    {
        Healths = 0;
        HealthsChanged.Broadcast(ByValue);
        HealthsEnded.Broadcast();
        return;
    }
    HealthsChanged.Broadcast(ByValue);
    UE_LOG(LogTemp, Log, TEXT("Health changed: %i"), Healths);
}

int UMainPlayerHealthComponent::GetHealths() const
{
    return Healths;
}
