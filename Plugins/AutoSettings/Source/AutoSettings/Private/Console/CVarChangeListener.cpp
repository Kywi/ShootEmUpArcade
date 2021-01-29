// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "Console/CVarChangeListener.h"
#include "HAL/IConsoleManager.h"

void UCVarChangeListener::Init(IConsoleVariable* InCVar)
{
	CVar = InCVar;

	CurrentValue = CVar->GetString();

	// Register sink
	IConsoleManager::Get().RegisterConsoleVariableSink_Handle(FConsoleCommandDelegate::CreateUObject(this, &UCVarChangeListener::CVarSink));
}

void UCVarChangeListener::CVarSink()
{
	FString NewValue = CVar->GetString();

	// Check if value has updated since the last time we checked
	if (NewValue != CurrentValue)
	{
		CurrentValue = NewValue;

		OnStringCVarChanged.Broadcast(CurrentValue);
		OnIntCVarChanged.Broadcast(FCString::Atoi(*CurrentValue));
		OnFloatCVarChanged.Broadcast(FCString::Atof(*CurrentValue));

	}
}
