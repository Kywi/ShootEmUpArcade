// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "Console/CVarChangeListenerManager.h"
#include "Console/ConsoleUtils.h"
#include "AutoSettings.h"

UCVarChangeListenerManager* UCVarChangeListenerManager::Singleton = nullptr;

UCVarChangeListenerManager* UCVarChangeListenerManager::Get()
{
	if (!Singleton)
	{
		Singleton = NewObject<UCVarChangeListenerManager>();
		Singleton->AddToRoot();
	}

	return Singleton;
}

void UCVarChangeListenerManager::AddIntCVarCallbackStatic(FName Name, FIntCVarChangedSignature ChangedCallback, bool CallbackImmediately)
{
	Get()->AddIntCVarCallback(Name, ChangedCallback, CallbackImmediately);
}

void UCVarChangeListenerManager::AddFloatCVarCallbackStatic(FName Name, FFloatCVarChangedSignature ChangedCallback, bool CallbackImmediately)
{
	Get()->AddFloatCVarCallback(Name, ChangedCallback, CallbackImmediately);
}

void UCVarChangeListenerManager::AddStringCVarCallbackStatic(FName Name, FStringCVarChangedSignature ChangedCallback, bool CallbackImmediately)
{
	Get()->AddStringCVarCallback(Name, ChangedCallback, CallbackImmediately);
}

void UCVarChangeListenerManager::AddIntCVarCallback(FName Name, FIntCVarChangedSignature ChangedCallback, bool CallbackImmediately)
{
	UCVarChangeListener* Listener = FindOrCreateListener(Name);
	if (Listener->OnIntCVarChanged.Contains(ChangedCallback))
	{
		UE_LOG(LogAutoSettings, Warning, TEXT("Cannot add callback for %s because it is already registered"), *Name.ToString());
	}
	else
	{
		Listener->OnIntCVarChanged.Add(ChangedCallback);
	}
	if (CallbackImmediately)
		ChangedCallback.Execute(UConsoleUtils::GetCVar(Name)->GetInt());
}

void UCVarChangeListenerManager::AddFloatCVarCallback(FName Name, FFloatCVarChangedSignature ChangedCallback, bool CallbackImmediately)
{
	UCVarChangeListener* Listener = FindOrCreateListener(Name);
	if (Listener->OnFloatCVarChanged.Contains(ChangedCallback))
	{
		UE_LOG(LogAutoSettings, Warning, TEXT("Cannot add callback for %s because it is already registered"), *Name.ToString());
	}
	else
	{
		Listener->OnFloatCVarChanged.Add(ChangedCallback);
	}
	if (CallbackImmediately)
		ChangedCallback.Execute(UConsoleUtils::GetCVar(Name)->GetFloat());
}

void UCVarChangeListenerManager::AddStringCVarCallback(FName Name, FStringCVarChangedSignature ChangedCallback, bool CallbackImmediately)
{
	UCVarChangeListener* Listener = FindOrCreateListener(Name);
	if (Listener->OnStringCVarChanged.Contains(ChangedCallback))
	{
		UE_LOG(LogAutoSettings, Warning, TEXT("Cannot add callback for %s because it is already registered"), *Name.ToString());
	}
	else
	{
		Listener->OnStringCVarChanged.Add(ChangedCallback);
	}
	if (CallbackImmediately)
		ChangedCallback.Execute(UConsoleUtils::GetCVar(Name)->GetString());
}

UCVarChangeListener* UCVarChangeListenerManager::FindOrCreateListener(FName Name)
{
	IConsoleVariable* CVar = UConsoleUtils::GetCVar(Name);

	if (!ensureMsgf(CVar, TEXT("Failed to find CVar: %s"), *Name.ToString()))
	{
		return nullptr;
	}

	UCVarChangeListener** Pointer = Listeners.Find(Name);

	UCVarChangeListener* Listener = Pointer ? *Pointer : nullptr;

	// If it doesn't exist, create one
	if (!Listener)
	{
		Listener = NewObject<UCVarChangeListener>();
		Listener->Init(CVar);
		Listeners.Add(Name, Listener);
	}

	return Listener;

}