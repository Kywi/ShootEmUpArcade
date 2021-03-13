// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Pawns/EnemyPawn.h"
#include "StructsCollection/StructsCollection.h"

#include "EnemySpawnController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STREAMARCADE_API UEnemySpawnController : public UActorComponent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	TArray<FEnemySpawnInfo> SpawnStages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMinDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float StageMaxDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemies")
	float ChangeStageTimeMultiplier;
	
protected:
	virtual void BeginPlay() override;
	virtual void Deactivate() override;
	void StartSpawnStage();
	void SpawnEnemy();

	FEnemySpawnInfo SpawnStage;
	int EnemiesSpawned;
	FTimerHandle ChangeStageTimer;
	FTimerHandle EnemySpawnTimer;
	FRandomStream Random;
};
