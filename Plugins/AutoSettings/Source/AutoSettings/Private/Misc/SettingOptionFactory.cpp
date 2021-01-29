// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "Misc/SettingOptionFactory.h"
#include "AutoSettings.h"

TArray<FSettingOption> USettingOptionFactory::ConstructOptions_Implementation() const
{
	UE_LOG(LogAutoSettings, Error, TEXT("Default ConstructOptions called, no options constructed"));
	return TArray<FSettingOption>();
}