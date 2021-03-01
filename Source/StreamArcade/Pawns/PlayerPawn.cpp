#include "PlayerPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "EngineMinimal.h"
#include "Engine/Engine.h"

APlayerPawn::APlayerPawn() :  TouchMoveSensivity(1.f)
{
    //  MoveLimit(FVector2D(500.f, 600.f))
    PrimaryActorTick.bCanEverTick = true;

    PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
    RootComponent = PawnCollision;
    PawnCollision->SetCollisionProfileName("Pawn");
    PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

    PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
    PawnMesh->SetupAttachment(PawnCollision, NAME_None);

    PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));

    ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
}

void APlayerPawn::PossessedBy(AController* NewController)
{
    PlayerController = Cast<APlayerController>(NewController);
}

bool APlayerPawn::CanBeDamaged_Implementation()
{
    return bCanBeDamaged;
}

void APlayerPawn::ExplodePawn_Implementation()
{
    SetActorEnableCollision(false);

    ShootComponent->StopShooting();

    PawnMesh->SetMaterial(0, RecoverMaterial);

    if (DestroyParticle)
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

    for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
    {
        Component->Deactivate();
    }
}

void APlayerPawn::RecoverPawn_Implementation()
{
    SetActorEnableCollision(true);

    ShootComponent->StartShooting();

    PawnMesh->SetMaterial(0, PawnMaterial);

    for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
    {
        Component->Activate(true);
    }
}
// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    ShootComponent->StartShooting();
    PawnMaterial = PawnMesh->GetMaterial(0);
    MoveLimit = GetGameViewportSize();
    //MoveLimit.X -= 300;
  //  MoveLimit.Y -= 300;
    UE_LOG(LogTemp, Log, TEXT("x:  %f, y:  %f"), MoveLimit.X, MoveLimit.Y);
}

float APlayerPawn::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy,
                              AActor* DamageCauser)
{
    if (!CanBeDamaged()) return 0.f;

    Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauser);
    PawnDamaged.Broadcast();
    return Damage;
}

FVector2D APlayerPawn::GetGameViewportSize()
{
    FVector2D Result = FVector2D(1, 1);

    if (GEngine && GEngine->GameViewport)
    {
        GEngine->GameViewport->GetViewportSize(/*out*/Result);
    }
    return Result;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    InputComponent->BindTouch(IE_Pressed, this, &APlayerPawn::OnTouchPress);
    //InputComponent->BindTouch(IE_Released, this, &APlayerPawn::OnTouchRelease);
    InputComponent->BindTouch(IE_Repeat, this, &APlayerPawn::OnTouchMove);
}

// Touch controls
void APlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
    FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);

    TouchDeltaMove = TouchDeltaMove * TouchMoveSensivity;

    FVector NewLocation = GetActorLocation();
    NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);
    NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, -MoveLimit.X, MoveLimit.X);

    SetActorLocation(NewLocation);

    TouchLocation = FVector2D(Location.X, Location.Y);
}

void APlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
    TouchLocation = FVector2D(Location.X, Location.Y);
}
