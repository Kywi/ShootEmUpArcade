// Fill out your copyright notice in the Description page of Project Settings.


#include "NWEnemyPawn.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "NWGameMode.h"
#include "NWPlayerPawn.h"

ANWEnemyPawn::ANWEnemyPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    pawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
    RootComponent = pawnCollision;
    pawnCollision->SetCollisionProfileName("Pawn");

    pawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
    pawnMesh->SetupAttachment(pawnCollision, NAME_None);
    pawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    arrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    arrowComponent->SetupAttachment(pawnCollision, NAME_None);

    shootComponent = CreateDefaultSubobject<UNVShootComponent>(TEXT("ShootComponent"));

    healthComponent = CreateDefaultSubobject<UCreaturesHealthComponent>(TEXT("HealthComponent"));
}

void ANWEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
        SetReplicates(true);

    OnActorBeginOverlap.AddDynamic(this, &ANWEnemyPawn::OnEnemyOverlap);
    healthComponent->OnHealthEnded.AddDynamic(this, &ANWEnemyPawn::KillPawn);
}

void ANWEnemyPawn::KillPawn()
{
    if (HasAuthority())
    {
        ANWGameMode* Gamemode = Cast<ANWGameMode>(UGameplayStatics::GetGameMode(this));
        //if (Gamemode) Gamemode->AddPoints(DestroyPoints);

        //SpawnBonuses();

        DestroyPawn();
    }

}

void ANWEnemyPawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
    if (!Cast<ANWPlayerPawn>(OtherActor))
        return;

    const float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());
    if (AppliedDamage > 0.f)
        DestroyPawn();
}

void ANWEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const float WorldMoveOffset = -200.f * DeltaTime;
    AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));
}

void ANWEnemyPawn::DestroyPawn()
{
    //  if (DestroyParticle)
     //     UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
      //UGameplayStatics::SpawnSound2D(GetWorld(), DestroySound);

    Destroy();
}



