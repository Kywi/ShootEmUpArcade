// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#include "InputMapping/UI/BindCaptureButton.h"

UBindCapturePrompt* UBindCaptureButton::StartCapture()
{
	Prompt = CreateWidget<UBindCapturePrompt>(GetOwningPlayer(), BindCapturePromptClass);
	Prompt->OnChordCaptured.AddDynamic(this, &UBindCaptureButton::ChordCaptured);
	Prompt->KeyGroup = KeyGroup;
	InitializePrompt(Prompt);
	return Prompt;
}

void UBindCaptureButton::InitializePrompt_Implementation(UBindCapturePrompt * PromptWidget)
{
	// Add the prompt straight to the viewport
	PromptWidget->AddToViewport(1);
}

void UBindCaptureButton::ChordCaptured(FInputChord Chord)
{
	OnChordCaptured.Broadcast(Chord);
}
