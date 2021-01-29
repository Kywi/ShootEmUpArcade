// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "UI/SettingControls/ToggleSetting.h"

void UToggleSetting::UpdateSelection_Implementation(const FString& Value)
{
	Super::UpdateSelection_Implementation(Value);

	int32 IntValue = FCString::Atoi(*Value);

	UpdateToggleState(IntValue > 0);
}

void UToggleSetting::UpdateToggleState_Implementation(bool State)
{
}

void UToggleSetting::ToggleStateUpdated(bool State)
{
	int32 IntValue = State ? 1 : 0;

	ApplySettingValue(FString::FromInt(IntValue));
}
