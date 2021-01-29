// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "UI/GenericControls/RadioSelect/RadioSelect.h"
#include "Misc/SettingOption.h"

void URadioSelect::SetOptions(TArray<FSettingOption> InOptions)
{
	Options = InOptions;

	RadioButtons.Empty();

	if (IsValid(ButtonContainer))
	{
		ButtonContainer->ClearChildren();

		for (FSettingOption Option : Options)
		{
			URadioButton* NewButton = CreateWidget<URadioButton>(GetWorld(), RadioButtonClass);

			NewButton->SetLabel(Option.Label);
			NewButton->SetValue(Option.Value);

			RadioButtons.Add(NewButton);

			ButtonContainer->AddChild(NewButton);

			NewButton->OnSelected.AddDynamic(this, &URadioSelect::ButtonSelected);
		}

	}

}

void URadioSelect::Select(FString Value)
{
	SelectionChangedEvent.Broadcast(Value);

	for (URadioButton* RadioButton : RadioButtons)
	{
		RadioButton->SetSelected(RadioButton->GetValue() == Value);
	}

}

void URadioSelect::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetOptions(Options);
}

void URadioSelect::ButtonSelected(FString Value)
{
	Select(Value);
}

