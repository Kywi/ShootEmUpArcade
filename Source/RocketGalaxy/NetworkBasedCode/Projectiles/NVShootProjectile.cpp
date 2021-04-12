// Fill out your copyright notice in the Description page of Project Settings.


#include "NVShootProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NetworkBasedCode/NWPawn/NWPlayerPawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "NetworkBasedCode/NWPawn/NWEnemyPawn.h"
#include "TimerManager.h"

// Sets default values
ANVShootProjectile::ANVShootProjectile() :
    ProjectileSpeed(1000.f)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
    RootComponent = Collision;
    Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Collision);
    Mesh->SetCollisionProfileName("NoCollision");

    Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
    Particle->SetupAttachment(Collision);
}

void ANVShootProjectile::BeginPlay()
{
    Super::BeginPlay();

    if (GetOwner())
    {
        UBoxComponent* OwnerCollision = GetOwner()->FindComponentByClass<UBoxComponent>();
        Collision->IgnoreComponentWhenMoving(OwnerCollision, true);
        OwnerCollision->IgnoreComponentWhenMoving(Collision, true);

        Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ANVShootProjectile::OnProjectileOverlap);
}


void ANVShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OpelappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex,
    bool Sweep, const FHitResult& Hit)
{
    APawn* OtherPawn = Cast<APawn>(OtherActor);
    if (!OtherActor || !OtherPawn)
        return; // If no overlapped actor or it is not a pawn

//  if (!GetOwner())
 //       return;

    APawn* PawnOwner = Cast<APawn>(GetOwner());
    if (!PawnOwner)
        return;

    if (GetNetMode() == ENetMode::NM_Client && Cast<ANWEnemyPawn>(PawnOwner) && Cast<ANWPlayerPawn>(PawnOwner)) {
        Destroy();
        return;
    }

    if ((Cast<ANWEnemyPawn>(PawnOwner) && Cast<ANWEnemyPawn>(OtherPawn)) || (Cast<ANWPlayerPawn>(PawnOwner) && Cast<ANWPlayerPawn>(OtherPawn)))
        return;

    if (GetNetMode() == ENetMode::NM_ListenServer)
    {
        FTimerDelegate tempTimer;
        AController* DamageInstigator = PawnOwner->GetController();
        tempTimer.BindLambda([this, OtherActor, DamageInstigator]()
            {
                UGameplayStatics::ApplyDamage(OtherActor, Damage, DamageInstigator, this, UDamageType::StaticClass());
            });
        FTimerHandle handle;
        GetWorld()->GetTimerManager().SetTimer(handle, tempTimer, 0.2, false, 0.01);
    }
    Destroy();
}

void ANVShootProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AddActorLocalOffset(FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f));
}
