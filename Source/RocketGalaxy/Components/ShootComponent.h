// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "StructsCollection/StructsCollection.h"
#include "Actors/Projectiles/ShootProjectile.h"

#include "Components/ActorComponent.h"

#include "ShootComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STREAMARCADE_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UShootComponent();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
    void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
    void StopShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
    void RestartShooting();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	float ShootPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	TArray<FShootInfo> ShootInfos;
	
protected:
	virtual void BeginPlay() override;
	void Shoot();

	FTimerHandle ShootingTimer;
};
