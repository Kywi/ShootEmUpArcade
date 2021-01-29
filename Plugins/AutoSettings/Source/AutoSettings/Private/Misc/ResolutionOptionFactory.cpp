// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "Misc/ResolutionOptionFactory.h"
#include "Misc/SettingOption.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<FSettingOption> UResolutionOptionFactory::ConstructOptions_Implementation() const
{
	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

	TArray<FSettingOption> Result;
	for (FIntPoint Resolution : Resolutions)
	{
		FText X = FText::FromString(FString::FromInt(Resolution.X));
		FText Y = FText::FromString(FString::FromInt(Resolution.Y));

		FText Label = FText::Format(FText::FromString("{0} X {1}"), X, Y);

		FString Value = FText::Format(FText::FromString("{0}x{1}"), X, Y).ToString();

		Result.Add(FSettingOption(Label, Value));
	}

	return Result;
}
