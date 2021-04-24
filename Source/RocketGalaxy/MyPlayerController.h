// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "NetworkBasedCode/Projectiles/NVShootProjectile.h"

#include "MyPlayerController.generated.h"

class ANWPlayerPawn;

/**
 *
 */
UCLASS()
class STREAMARCADE_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);
    void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
    void OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location);

    UFUNCTION(BlueprintCallable)
        void SetPlayerID(int playerID);

    UFUNCTION(BlueprintCallable)
        int GetPlayerID();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        ANWPlayerPawn* possessedPawn;

    UPROPERTY(BlueprintReadWrite)
    bool canReceiveInputs = false;

protected:
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
 
private:
    UPROPERTY(Replicated)
    int playerID;
};
