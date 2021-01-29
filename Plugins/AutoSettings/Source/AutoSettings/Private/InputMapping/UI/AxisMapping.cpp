// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "InputMapping/UI/AxisMapping.h"
#include "InputMapping/InputMappingManager.h"

void UAxisMapping::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAxisMapping::UpdateLabel_Implementation()
{
	GetAxisLabel()->AxisName = AxisName;
	GetAxisLabel()->Scale = Scale;
	GetAxisLabel()->MappingGroup = MappingGroup;
	GetAxisLabel()->KeyGroup = KeyGroup;
	GetAxisLabel()->bUsePlayerKeyGroup = false;
	GetAxisLabel()->IconTags = IconTags;
	GetAxisLabel()->InitializeLabel();
}

void UAxisMapping::BindChord(FInputChord InChord)
{
	FKey Key = InChord.Key;

	FKeyScale AnalogKeyScale = GetDefault<UAutoSettingsConfig>()->GetAnalogKey(Key);
	bool UseAnalogKey = AnalogKeyScale.Key.IsValid();

	FKey FinalKey = UseAnalogKey ? AnalogKeyScale.Key : Key;
	float FinalScale = UseAnalogKey ? AnalogKeyScale.Scale * Scale : Scale;

	FInputAxisKeyMapping NewMapping = FInputAxisKeyMapping(AxisName, FinalKey, FinalScale);

	// Override all key groups if none is specified
	bool bAnyKeyGroup = !KeyGroup.IsValid();

	UInputMappingManager::Get()->AddPlayerAxisOverride(GetOwningPlayer(), NewMapping, MappingGroup, bAnyKeyGroup);
}
