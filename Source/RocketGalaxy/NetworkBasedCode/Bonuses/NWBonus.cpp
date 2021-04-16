// Fill out your copyright notice in the Description page of Project Settings.


#include "NWBonus.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NetworkBasedCode/NWPawn/NWPlayerPawn.h"

// Sets default values
ANWBonus::ANWBonus()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
    RootComponent = Collision;

    Collision->SetCollisionObjectType(ECC_WorldDynamic);
    Collision->SetSphereRadius(50);
}

// Called when the game starts or when spawned
void ANWBonus::BeginPlay()
{
    Super::BeginPlay();
}

void ANWBonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    UE_LOG(LogTemp, Log, TEXT("Bonus overlap"));
    if (!OtherActor) return;
    if (!Cast<ANWPlayerPawn>(OtherActor)) return;

    UE_LOG(LogTemp, Log, TEXT("Bonus CHAR overlap"));
    auto actorColBonus = Cast<ANWPlayerPawn>(OtherActor);
    BonusCollected(actorColBonus);
}

// Called every frame
void ANWBonus::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const float WorldMoveOffset = -200.f * DeltaTime;
    AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));
}

void ANWBonus::BonusCollected_Implementation(ANWPlayerPawn* ActorThatCollectBonus)
{
    if (CollectParticle)
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);
    Destroy();
}
