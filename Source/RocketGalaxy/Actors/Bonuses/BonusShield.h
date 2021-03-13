#pragma once

#include "CoreMinimal.h"

#include "Actors/Bonuses/Bonus.h"

#include "BonusShield.generated.h"

class APawnShield;

UCLASS()
class STREAMARCADE_API ABonusShield : public ABonus
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield")
    TSubclassOf<APawnShield> ShieldClass;

protected:
    virtual void BonusCollected_Implementation() override;
};
