// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "StreamArcadeGameModeBase.h"
#include "Engine/World.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;
	PawnCollision->SetCollisionProfileName("Pawn");

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(PawnCollision, NAME_None);
	
	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::KillPawn);
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);
}

void AEnemyPawn::KillPawn()
{
	AStreamArcadeGameModeBase* Gamemode = Cast<AStreamArcadeGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode) Gamemode->AddPoints(DestroyPoints);

	SpawnBonuses();

	DestroyPawn();
}

void AEnemyPawn::DestroyPawn()
{
	if (DestroyParticle)
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
	UGameplayStatics::SpawnSound2D(GetWorld(),DestroySound);

	Destroy();
}

void AEnemyPawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) return;

	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());

	if(AppliedDamage > 0.f) DestroyPawn();
}

void AEnemyPawn::SpawnBonuses()
{
	FRandomStream Random;
	Random.GenerateNewSeed();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (FBonusChance Bonus : PossibleBonuses) {
		float RandChance = Random.RandRange(0.f, 100.f);
		UE_LOG(LogTemp, Log, TEXT("Bonus: %s, Chance needed: %f, Chance random: %f"), *Bonus.BonusClass->GetName(), Bonus.Chance, RandChance);
		if (RandChance < Bonus.Chance) {
			UE_LOG(LogTemp, Log, TEXT("Bonus spawned"));
			GetWorld()->SpawnActor<ABonus>(Bonus.BonusClass, GetActorLocation(), FRotator(0.f), SpawnParameters);
		}
	}
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorldMoveOffset = -200.f * DeltaTime;
	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));

}