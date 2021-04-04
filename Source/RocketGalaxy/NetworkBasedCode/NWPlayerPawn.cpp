// Fill out your copyright notice in the Description page of Project Settings.


#include "NWPlayerPawn.h"

// Sets default values
ANWPlayerPawn::ANWPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANWPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANWPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANWPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

