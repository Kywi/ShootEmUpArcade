// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent():
	Health(100)
{
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerDamaged);
}

void UHealthComponent::OnOwnerDamaged(AActor * DamagedActor, float Damage, const UDamageType* DamageType, AController * Instigator, AActor * DamageCauser)
{
	ChangeHealth(-Damage);
}

void UHealthComponent::ChangeHealth(float Value)
{
	Health += Value;
	
	if (Health <= 0.f) {
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::OnOwnerDamaged);
		OnHealthEnded.Broadcast();
	}
}

float UHealthComponent::GetHealth() const
{
	return Health;
}
