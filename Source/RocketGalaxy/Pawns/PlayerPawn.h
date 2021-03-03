// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ShootComponent.h"

#include "PlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamagedEvent);

UCLASS()
class STREAMARCADE_API APlayerPawn : public APawn
{
    GENERATED_BODY()

public:

    APlayerPawn();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Healths")
    bool CanBeDamaged();
    bool CanBeDamaged_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
    void ExplodePawn();
    void ExplodePawn_Implementation();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
    void RecoverPawn();
    void RecoverPawn_Implementation();

    UFUNCTION(BlueprintCallable, Category = "ScreeenRes")
    static FVector2D GetGameViewportSize();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
    UBoxComponent* PawnCollision;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Pawn")
    UStaticMeshComponent* PawnMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
    UCameraComponent* PawnCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
    UShootComponent* ShootComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
    float TouchMoveSensivity;

    UPROPERTY(BlueprintAssignable, Category = "Healths")
    FPawnDamagedEvent PawnDamaged;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
    UMaterialInterface* RecoverMaterial;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
    UParticleSystem* DestroyParticle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RotationAnimation")
    float maxRotationAngle = 40;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RotationAnimation")
    float targetInterp = 0;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RotationAnimation")
    float delayTimerInterp = 0.05;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RotationAnimation")
    float stepInterp = 0.05;
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy,
                             AActor* DamageCauser) override;
    void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);
    void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
    void OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location);
    virtual void PossessedBy(AController* NewController) override;
    void RotationAnimation(const FVector& NewLocation);
    void RotateBack();
    APlayerController* PlayerController;
    FVector2D MoveLimit;
    FTimerHandle rotateAnimTimer;
    
private:
    FVector2D TouchLocation;
    float fromInterp;
    double currentRotation = 0;
    UMaterialInterface* PawnMaterial;
};


