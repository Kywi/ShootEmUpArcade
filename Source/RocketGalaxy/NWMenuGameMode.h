// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NWMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STREAMARCADE_API ANWMenuGameMode : public AGameMode
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
     void TravelToAnotherMap(FString mapName);
};
