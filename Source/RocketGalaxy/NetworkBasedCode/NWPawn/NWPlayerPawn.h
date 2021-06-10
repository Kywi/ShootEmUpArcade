// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "../NWComponents/NVShootComponent.h"
#include "../NWComponents/MainPlayerHealthComponent.h"

#include "NWPlayerPawn.generated.h"

USTRUCT(BlueprintType)
struct FNWShootInfoLevel
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TArray<FNVShootInfo> ShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ShootPeriod;
};


class AMyPlayerController;

UCLASS()
class STREAMARCADE_API ANWPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ANWPlayerPawn();

	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location);
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Server, Reliable)
	void MoveOnline(FVector Location);

	UFUNCTION(Server, Reliable)
	void SetInterpToLocation(FVector Location);

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void RotateMeshOnline(FRotator Rotation);

	UFUNCTION(NetMulticast, Reliable)
	void ExplodePawn();

	UFUNCTION(NetMulticast, Reliable)
	void RecoverPawn();

	UFUNCTION(NetMulticast, Reliable)
	void ChangeEvolutionLvl(bool up);

	UFUNCTION(Client, Reliable)
	void InitTouchLocation();

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Healths")
	bool CanBeDamaged();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UBoxComponent* pawnCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UStaticMeshComponent* pawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UCameraComponent* pawnCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
	UNVShootComponent* shootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UMainPlayerHealthComponent* healtComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UMaterialInterface* RecoverMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	UParticleSystem* DestroyParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TArray<FNWShootInfoLevel> ShootEvolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	float TouchMoveSensivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	FVector2D MoveLimit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RotationAnimation")
	float maxRotationAngle = 40;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RotationAnimation")
	float targetInterp = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RotationAnimation")
	float delayTimerInterp = 0.05;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RotationAnimation")
	float stepInterp = 0.05;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float pawnRecoverTime = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Controls")
	float interpSpeedSmoothMoving = 3;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	void RotationAnimation(const FVector& NewLocation);
	void RotateBack();
	UFUNCTION()
	void DestroyPlayer();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	AMyPlayerController* playerController;
	FTimerHandle rotateAnimTimer;
	FTimerHandle recoverTimer;

private:
	UFUNCTION()
	void OnHealthChanged(int byValue);

	UPROPERTY(Replicated)
	FVector interpToLocation;

	FVector currentLocation;


	FVector2D touchLocation;
	bool doOnce = true;
	int currentShootLevel = 0;
	float fromInterp;
	double currentRotation = 0;
	UMaterialInterface* PawnMaterial;
};
