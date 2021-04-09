// Fill out your copyright notice in the Description page of Project Settings.


#include "NWGameMode.h"

#include "Engine/Engine.h"


ANWGameMode::ANWGameMode()
{

}

void ANWGameMode::TravelToAnotherMap()
{
    GetWorld()->ServerTravel("M_MainMenu", true);
}

void ANWGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    //FTransform transform;
    //transform.SetLocation(FVector(100, 100, 0));
    if(HasAuthority())
    {
       // auto actor =  GetWorld()->SpawnActor<APawn>(ActorToPosses, transform);
       // NewPlayer->Possess(actor);
        //actor->SetOwner(NewPlayer);
        
    }
   // NewPlayer->ReceivedPlayer();
    
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Connected users , %d"), ++loginedUsers));
    if (loginedUsers == 2) playerConnnected.Broadcast();
}



