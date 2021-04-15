// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "../NWComponents/NVShootComponent.h"
#include "../NWComponents/MainPlayerHealthComponent.h"

#include "NWPlayerPawn.generated.h"

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

    UFUNCTION(Server, Reliable)
        void MoveOnline(FVector Location);

    UFUNCTION(Server, Reliable)
        void RotateMeshOnline(FRotator Rotation);

    UFUNCTION(NetMulticast, Reliable)
        void ExplodePawn();

    UFUNCTION(NetMulticast, Reliable)
        void RecoverPawn();

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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
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

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void PossessedBy(AController* NewController) override;
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    void RotationAnimation(const FVector& NewLocation);
    void RotateBack();
    UFUNCTION()
        void DestroyPlayer();

    AMyPlayerController* playerController;
    FTimerHandle rotateAnimTimer;
    FTimerHandle recoverTimer;

private:
    FVector2D touchLocation;
    float fromInterp;
    double currentRotation = 0;
    UMaterialInterface* PawnMaterial;
};
