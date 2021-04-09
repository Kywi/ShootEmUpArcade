// Fill out your copyright notice in the Description page of Project Settings.


#include "NVShootProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ANVShootProjectile::ANVShootProjectile():
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

// Called when the game starts or when spawned
void ANVShootProjectile::BeginPlay()
{
    Super::BeginPlay();
    Super::BeginPlay();

    if (GetOwner())
    {
        UBoxComponent* OwnerCollision = GetOwner()->FindComponentByClass<UBoxComponent>();
        Collision->IgnoreComponentWhenMoving(OwnerCollision, true);
        OwnerCollision->IgnoreComponentWhenMoving(Collision, true);

        Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
    //  Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);
}

// Called every frame
void ANVShootProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AddActorLocalOffset(FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f));
}
