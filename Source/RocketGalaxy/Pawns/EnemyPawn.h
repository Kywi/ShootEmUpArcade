// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/ShootComponent.h"
#include "Components/HealthComponent.h"
#include "Actors/Bonuses/Bonus.h"
#include "Components/ArrowComponent.h"
#include "Sound/SoundBase.h"
#include "EnemyPawn.generated.h"


UCLASS()
class STREAMARCADE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Pawn")
	void DestroyPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UBoxComponent* PawnCollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
	UShootComponent* ShootComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	int DestroyPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bonus")
	TArray<FBonusChance> PossibleBonuses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	UParticleSystem* DestroyParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	FVector ScaleDestroyParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundBase* DestroySound;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnBonuses();

	UFUNCTION()
	void KillPawn();

	UFUNCTION()
	void OnEnemyOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
