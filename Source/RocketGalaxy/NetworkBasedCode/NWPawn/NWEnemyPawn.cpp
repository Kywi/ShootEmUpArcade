#include "NWEnemyPawn.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "NWGameMode.h"
#include "NWGameState.h"
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

    OnActorBeginOverlap.AddDynamic(this, &ANWEnemyPawn::OnEnemyOverlap);
    healthComponent->OnHealthEnded.AddDynamic(this, &ANWEnemyPawn::KillPawn);
}

void ANWEnemyPawn::KillPawn(int playerID)
{
    if (GetNetMode() == NM_ListenServer)
    {
        auto gameState = GetWorld()->GetGameState<ANWGameState>();
        //  gameState->gamePoints[playerID] += DestroyPoints;
        UE_LOG(LogTemp, Log, TEXT("Player ID: %i"), playerID);
        gameState->gamePoints[playerID] += DestroyPoints;
        gameState->OnRep_gamePoints();
        //if (Gamemode) Gamemode->AddPoints(DestroyPoints);

        //SpawnBonuses();

        DestroyPawn();
    }
}

void ANWEnemyPawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
    // UE_LOG(LogTemp, Error, TEXT("Overlap cast result: %p"), OtherActor->GetClass());
    if (!Cast<ANWPlayerPawn>(OtherActor))
        return;

    const float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, -1.f, GetController(), this,
                                                              UDamageType::StaticClass());
    if (AppliedDamage != 0.f)
        DestroyPawn();
}

void ANWEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const float WorldMoveOffset = -200.f * DeltaTime;
    AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));
}

void ANWEnemyPawn::DestroyPawn_Implementation()
{
    if (DestroyParticle)
    {
        auto transform = GetActorTransform();
        transform.SetScale3D(ScaleDestroyParticle);
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, transform, true);
    }
    //UGameplayStatics::SpawnSound2D(GetWorld(), DestroySound);

    Destroy();
}
