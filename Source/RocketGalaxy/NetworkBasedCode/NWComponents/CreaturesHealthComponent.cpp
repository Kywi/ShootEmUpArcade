// Fill out your copyright notice in the Description page of Project Settings.


#include "CreaturesHealthComponent.h"

#include "MyPlayerController.h"
#include "NetworkBasedCode/NWPawn/NWEnemyPawn.h"

// Sets default values for this component's properties
UCreaturesHealthComponent::UCreaturesHealthComponent()
{
}

void UCreaturesHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UCreaturesHealthComponent::OnOwnerDamaged);
}

void UCreaturesHealthComponent::OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                               AController* Instigator, AActor* DamageCauser)
{
    ChangeHealth(-Damage, Instigator);
}

void UCreaturesHealthComponent::ChangeHealth(float value, AController* Instigator)
{
    Health += value;

    if (Health <= 0.f)
    {
        GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UCreaturesHealthComponent::OnOwnerDamaged);
      //  UE_LOG(LogTemp, Log, TEXT("PlayerID : %s"), *Cast<AMyPlayerController>(Instigator)->GetPlayerID());
        OnHealthEnded.Broadcast(Cast<ANWEnemyPawn>(GetOwner())->GetPlayerID());
    }
}

float UCreaturesHealthComponent::GetHealth() const
{
    return Health;
}

