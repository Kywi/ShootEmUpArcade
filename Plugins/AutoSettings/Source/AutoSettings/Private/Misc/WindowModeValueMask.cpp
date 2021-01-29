// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "Misc/WindowModeValueMask.h"
#include "Misc/ResolutionStringUtils.h"

FString UWindowModeValueMask::MaskValue_Implementation(const FString& ConsoleValue) const
{
	return UResolutionStringUtils::GetMode(ConsoleValue);
}

FString UWindowModeValueMask::RecombineValues_Implementation(const FString& SettingValue, const FString& ConsoleValue) const
{
	return UResolutionStringUtils::GetPixelsString(ConsoleValue) + SettingValue;
}
