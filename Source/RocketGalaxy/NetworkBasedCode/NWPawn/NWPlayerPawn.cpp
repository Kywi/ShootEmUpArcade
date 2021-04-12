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
    PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
    RootComponent = PawnCollision;
    PawnCollision->SetCollisionProfileName("Pawn");
    PawnCollision->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

    PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
    PawnMesh->SetupAttachment(PawnCollision, NAME_None);

    PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));

    ShootComponent = CreateDefaultSubobject<UNVShootComponent>(TEXT("shootComponent"));
}

void ANWPlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    MoveLimit.X = 1000;
    MoveLimit.Y = 1000;
    if (HasAuthority())
        SetReplicates(true);
}

void ANWPlayerPawn::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    PlayerController = Cast<AMyPlayerController>(NewController);
    PlayerController->possessedPawn = this;
}

#pragma endregion overriding engine events

#pragma region MovePawn

void ANWPlayerPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
    GetWorld()->GetTimerManager().ClearTimer(rotateAnimTimer);
    FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);

    TouchDeltaMove = TouchDeltaMove * TouchMoveSensivity;

    FVector NewLocation = GetActorLocation();
    NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);
    NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, -MoveLimit.X, MoveLimit.X);

    if (IsValid(InputComponent))
    {
        RotationAnimation(NewLocation);
        moveOnlineRPC(NewLocation);
    }

    SetActorLocation(NewLocation);
    TouchLocation = FVector2D(Location.X, Location.Y);
}

void ANWPlayerPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
    TouchLocation = FVector2D(Location.X, Location.Y);
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

    currentRotation = PawnMesh->GetComponentRotation().Roll + 1.01 * forwardY;
    if (UKismetMathLibrary::Abs(currentRotation) <= maxRotationAngle)
    {
        const FRotator rotator(0, 0, currentRotation);
        if (!HasAuthority())
            PawnMesh->SetWorldRotation(rotator);
        RotateMesh(rotator);
    }
}

void ANWPlayerPawn::RotateBack()
{
    fromInterp = FMath::FInterpTo(fromInterp, targetInterp, 3, stepInterp);

    const FRotator rotator(0, 0, fromInterp);
    PawnMesh->SetWorldRotation(rotator);
    RotateMesh(rotator);

    if (fromInterp == targetInterp)
        GetWorld()->GetTimerManager().ClearTimer(rotateAnimTimer);
}

#pragma endregion Rotation pawn animation implementation

#pragma region RPC

void ANWPlayerPawn::RotateMesh_Implementation(FRotator Rotation)
{
    PawnMesh->SetWorldRotation(Rotation);
}

void ANWPlayerPawn::moveOnlineRPC_Implementation(FVector Location)
{
    SetActorLocation(Location);
}

#pragma endregion RPC methods