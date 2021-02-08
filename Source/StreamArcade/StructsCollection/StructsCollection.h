#pragma once

#include "CoreMinimal.h"

#include "Actors/Bonuses/Bonus.h"
#include "Actors/Projectiles/ShootProjectile.h"

#include "StructsCollection.generated.h"


class AEnemyPawn;

USTRUCT(BlueprintType)
struct FShootInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float Angle;
};


USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TSubclassOf<AEnemyPawn> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	int NumOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float SpawnDelay;
};


USTRUCT(BlueprintType)
struct FBonusChance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
	TSubclassOf<ABonus> BonusClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
	float Chance;

};


USTRUCT(BlueprintType)
struct FShootInfoLevel
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TArray<FShootInfo> ShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ShootPeriod;
};
