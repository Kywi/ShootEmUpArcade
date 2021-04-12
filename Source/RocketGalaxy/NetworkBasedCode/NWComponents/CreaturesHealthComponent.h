#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Controller.h"
#include "Components/ActorComponent.h"
#include "Components/HealthComponent.h"

#include "CreaturesHealthComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNWHealthEndedEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STREAMARCADE_API UCreaturesHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCreaturesHealthComponent();

    UFUNCTION(BlueprintCallable, Category = "Health")
        void ChangeHealth(float value);

    UFUNCTION(BlueprintPure, Category = "Health")
        float GetHealth() const;

    UPROPERTY(BlueprintAssignable, Category = "Health")
        FHealthEndedEvent OnHealthEnded;

protected:

    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
        float Health;

    UFUNCTION()
        void OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
};
