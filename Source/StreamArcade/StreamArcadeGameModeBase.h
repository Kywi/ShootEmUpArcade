#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Components/EnemySpawnController.h"
#include "Components/GameHealthComponent.h"
#include "Components/ShootComponent.h"
#include "StreamArcadeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

UCLASS()
class STREAMARCADE_API AStreamArcadeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AStreamArcadeGameModeBase();

	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void RecoverPawn();
	void RecoverPawn_Implementation();

	FTimerHandle RecoverTimer;
	FTimerHandle IncreaseDifficultyTimer;

	bool IsGameOver;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	UEnemySpawnController* EnemySpawnController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")
	UGameHealthComponent* HealthsComponent;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void IncreaseDifficulty();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddPoints(int Points);

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool ChangeShootLevel(bool Up);

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	float PlayerRecoverTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float IncreaseDifficultyPeriod;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class APlayerPawn* PlayerPawn;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int GamePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TArray<FShootInfoLevel> ShootInfoLevels;

	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
	int CurrentShootLevel;

};
