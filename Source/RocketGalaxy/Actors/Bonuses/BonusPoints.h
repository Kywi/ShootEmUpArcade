#pragma once

#include "CoreMinimal.h"

#include "Actors/Bonuses/Bonus.h"

#include "BonusPoints.generated.h"


UCLASS()
class STREAMARCADE_API ABonusPoints : public ABonus
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bonus")
    int Points;

protected:
    virtual void BonusCollected_Implementation() override;
};
