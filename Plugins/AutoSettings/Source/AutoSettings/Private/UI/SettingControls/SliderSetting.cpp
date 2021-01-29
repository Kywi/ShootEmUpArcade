// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "UI/SettingControls/SliderSetting.h"

USliderSetting::USliderSetting(const FObjectInitializer& ObjectInitializer) : UAutoSettingWidget(ObjectInitializer), RightValue(1.0f)
{
}

void USliderSetting::UpdateSelection_Implementation(const FString& Value)
{
	Super::UpdateSelection_Implementation(Value);

	float RawValue = FCString::Atof(*Value);

	float NormalizedValue = FMath::GetMappedRangeValueUnclamped(FVector2D(LeftValue, RightValue), FVector2D(0.0f, 1.0f), RawValue);

	UpdateSliderValue(NormalizedValue, RawValue);

	OnSliderValueUpdated(NormalizedValue, RawValue);

}

void USliderSetting::UpdateSliderValue_Implementation(float NormalizedValue, float RawValue)
{
}

void USliderSetting::SliderValueUpdated(float NormalizedValue)
{
	float RawValue = FMath::GetMappedRangeValueUnclamped(FVector2D(0.0f, 1.0f), FVector2D(LeftValue, RightValue), NormalizedValue);

	ApplySettingValue(FString::SanitizeFloat(RawValue), ShouldSaveCurrentValue());

	OnSliderValueUpdated(NormalizedValue, RawValue);
}

bool USliderSetting::ShouldSaveCurrentValue_Implementation() const
{
	return true;
}
