#include "NWPlayerPawn.h"

#include "AnimationCompression.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "EngineMinimal.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

#include "MyPlayerController.h"

#pragma region EngineEvents

ANWPlayerPawn::ANWPlayerPawn()
{
    pawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
    RootComponent = pawnCollision;
    pawnCollision->SetCollisionProfileName("Pawn");
    pawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

    pawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
    pawnMesh->SetupAttachment(pawnCollision, NAME_None);

    pawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));

    shootComponent = CreateDefaultSubobject<UNVShootComponent>(TEXT("shootComponent"));

    healtComponent = CreateDefaultSubobject<UMainPlayerHealthComponent>(TEXT("HealtComponent"));
}

void ANWPlayerPawn::BeginPlay()
{
    Super::BeginPlay();
  //  if (HasAuthority())
   //     SetReplicates(true);
    PawnMaterial = pawnMesh->GetMaterial(0);
}

void ANWPlayerPawn::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    playerController = Cast<AMyPlayerController>(NewController);
    playerController->possessedPawn = this;
    healtComponent->HealthsEnded.AddDynamic(this, &ANWPlayerPawn::DestroyPlayer);
}

float ANWPlayerPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if (!(GetNetMode() == ENetMode::NM_ListenServer && CanBeDamaged()))
        return 0.f;

    Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    healtComponent->ChangeHealths(DamageAmount);

    ExplodePawn();
    GetWorld()->GetTimerManager().SetTimer(recoverTimer, this, &ANWPlayerPawn::RecoverPawn, pawnRecoverTime, false);
    return DamageAmount;
}

#pragma endregion overriding engine events

#pragma region MovePawn

void ANWPlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
    GetWorld()->GetTimerManager().ClearTimer(rotateAnimTimer);
    FVector2D TouchDeltaMove = FVector2D(touchLocation.X - Location.X, touchLocation.Y - Location.Y);

    TouchDeltaMove = TouchDeltaMove * TouchMoveSensivity;

    FVector NewLocation = GetActorLocation();
    NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);
    NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, -MoveLimit.X, MoveLimit.X);

    if (IsValid(InputComponent))
    {
        RotationAnimation(NewLocation);
        MoveOnline(NewLocation);
    }

    SetActorLocation(NewLocation);
    touchLocation = FVector2D(Location.X, Location.Y);
}

void ANWPlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
    touchLocation = FVector2D(Location.X, Location.Y);
}

void ANWPlayerPawn::OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location)
{
    fromInterp = currentRotation;
    GetWorld()->GetTimerManager().SetTimer(rotateAnimTimer, this, &ANWPlayerPawn::RotateBack, delayTimerInterp, true, 0);
}

#pragma endregion Moving pawn methods

#pragma region RotationPawn

void ANWPlayerPawn::RotationAnimation(const FVector& NewLocation)
{
    const auto forwardVector = UKismetMathLibrary::GetDirectionUnitVector(NewLocation, GetActorLocation());
    const auto forwardY = (forwardVector.Y < 0) ? 1 : (forwardVector.Y == 0) ? 0 : -1;

    currentRotation = pawnMesh->GetComponentRotation().Roll + 1.01 * forwardY;
    if (UKismetMathLibrary::Abs(currentRotation) <= maxRotationAngle)
    {
        const FRotator rotator(0, 0, currentRotation);
        if (!HasAuthority())
            pawnMesh->SetWorldRotation(rotator);
        RotateMeshOnline(rotator);
    }
}

void ANWPlayerPawn::RotateBack()
{
    fromInterp = FMath::FInterpTo(fromInterp, targetInterp, 3, stepInterp);

    const FRotator rotator(0, 0, fromInterp);
    pawnMesh->SetWorldRotation(rotator);
    RotateMeshOnline(rotator);

    if (fromInterp == targetInterp)
        GetWorld()->GetTimerManager().ClearTimer(rotateAnimTimer);
}


#pragma endregion Rotation pawn animation implementation

#pragma region RPC

void ANWPlayerPawn::RotateMeshOnline_Implementation(FRotator Rotation)
{
    pawnMesh->SetWorldRotation(Rotation);
}

void ANWPlayerPawn::MoveOnline_Implementation(FVector Location)
{
    SetActorLocation(Location);
}

#pragma endregion RPC methods

bool ANWPlayerPawn::CanBeDamaged_Implementation()
{
    return bCanBeDamaged;
}

void ANWPlayerPawn::RecoverPawn_Implementation()
{
    SetActorEnableCollision(true);

    shootComponent->StartShooting();

    pawnMesh->SetMaterial(0, PawnMaterial);

    //  for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
     // {
      //    Component->Activate(true);
     // }
}

void ANWPlayerPawn::ExplodePawn_Implementation()
{
    SetActorEnableCollision(false);

    shootComponent->StopShooting();

    pawnMesh->SetMaterial(0, RecoverMaterial);

    if (DestroyParticle)
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

    // for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
    // {
     //    Component->Deactivate();
    // }
}

void ANWPlayerPawn::DestroyPlayer()
{
    if (DestroyParticle)
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
    Destroy();
}
