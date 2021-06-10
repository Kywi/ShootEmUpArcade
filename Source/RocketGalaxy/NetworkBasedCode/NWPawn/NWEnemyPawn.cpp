#include "NWEnemyPawn.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "NWGameMode.h"
#include "NWGameState.h"
#include "NWPlayerPawn.h"
#include "Engine/Engine.h"

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

void ANWEnemyPawn::SetPlayerID(int TplayerID)
{
    this->playerID = TplayerID;
}

int ANWEnemyPawn::GetPlayerID()
{
    return playerID;
}

void ANWEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    
	pawnCollision->OnComponentBeginOverlap.AddDynamic(this, &ANWEnemyPawn::OnEnemyOverlap);
   // OnActorBeginOverlap.AddDynamic(this, &ANWEnemyPawn::OnEnemyOverlap);
    healthComponent->OnHealthEnded.AddDynamic(this, &ANWEnemyPawn::KillPawn);
}

void ANWEnemyPawn::KillPawn(int TplayerID)
{
    if (GetNetMode() == NM_ListenServer)
    {
        auto gameState = GetWorld()->GetGameState<ANWGameState>();
        UE_LOG(LogTemp, Log, TEXT("Player ID: %i"), TplayerID);
        gameState->gamePoints[TplayerID] += DestroyPoints;
        gameState->OnRep_gamePoints();

        FRandomStream Random;
        Random.GenerateNewSeed();


        for (FNWBonusChance Bonus : possibleBonuses)
        {
            float RandChance = Random.RandRange(0.f, 100.f);
            UE_LOG(LogTemp, Log, TEXT("Bonus: %s, Chance needed: %f, Chance random: %f"), *Bonus.BonusClass->GetName(),
                   Bonus.Chance, RandChance);
            if (RandChance < Bonus.Chance)
            {
                SpawnBonuses(Bonus.BonusClass);

                UE_LOG(LogTemp, Log, TEXT("Bonus spawned"));
                break;
            }
        }

        DestroyPawn();
    }
}

void ANWEnemyPawn::OnEnemyOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

void ANWEnemyPawn::SpawnBonuses_Implementation(TSubclassOf<ANWBonus> BonusClass)
{
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    GetWorld()->SpawnActor<ANWBonus>(BonusClass, GetActorLocation(), FRotator(0.f), SpawnParameters);
}

void ANWEnemyPawn::DestroyPawn_Implementation()
{
    if (DestroyParticle)
    {
        auto transform = GetActorTransform();
        transform.SetScale3D(ScaleDestroyParticle);
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, transform, true);
    }
    if (DestroySound)
        UGameplayStatics::SpawnSound2D(GetWorld(), DestroySound);

    Destroy();
}

