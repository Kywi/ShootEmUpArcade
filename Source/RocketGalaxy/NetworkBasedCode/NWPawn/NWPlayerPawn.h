// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "../NWComponents/NVShootComponent.h"

#include "NWPlayerPawn.generated.h"


class AMyPlayerController;
UCLASS()
class STREAMARCADE_API ANWPlayerPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ANWPlayerPawn();
    // Called every frame

    void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);

    void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
    void OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location);

    virtual void PossessedBy(AController* NewController) override;
    // Called to bind functionality to input
    void RotationAnimation(const FVector& NewLocation);
    void RotateBack();

    UFUNCTION(Server, Reliable)
    void moveOnlineRPC(FVector Location);

    UFUNCTION(Server, Reliable)
    void RotateMesh(FRotator Rotation);


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
    UBoxComponent* PawnCollision;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
    UStaticMeshComponent* PawnMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
    UCameraComponent* PawnCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
    float TouchMoveSensivity;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
    //UNVShootComponent* ShootComponent;

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

    AMyPlayerController* PlayerController;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;


    FTimerHandle rotateAnimTimer;

private:
    FVector2D TouchLocation;
    float fromInterp;
    double currentRotation = 0;
    UMaterialInterface* PawnMaterial;
};
