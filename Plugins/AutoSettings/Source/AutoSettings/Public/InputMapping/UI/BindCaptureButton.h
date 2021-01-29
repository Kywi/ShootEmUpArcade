// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "KeyLabel.h"
#include "BindCapturePrompt.h"
#include "BindCaptureButton.generated.h"

/**
 * Button that, when clicked, prompts the user and listens for an input chord
 */
UCLASS(abstract)
class AUTOSETTINGS_API UBindCaptureButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Tag of key group to use - useful for separating groups of keys from each other such as gamepad from keyboard
	// Key groups can be defined in project settings (AutoSettings page)
	UPROPERTY()
	FGameplayTag KeyGroup;

	// Fired when an input chord is captured using this button
	FChordCapturedEvent OnChordCaptured;

	// BindCapturePrompt class to create when button is clicked
	UPROPERTY(EditAnywhere, Category = "Bind Capture Button")
	TSubclassOf<UBindCapturePrompt> BindCapturePromptClass;

	// Create prompt and start listening for input chord
	// Returns the newly created prompt
	UFUNCTION(BlueprintCallable, Category = "Bind Capture Button")
	UBindCapturePrompt* StartCapture();

protected:

	// Called to initialize a new prompt widget to listen for input capture
	// Override this to change how the prompt is set up, or add it to another widget instead of the viewport
	UFUNCTION(BlueprintNativeEvent, Category = "Bind Capture Button")
	void InitializePrompt(UBindCapturePrompt* PromptWidget);
	
private:
	UPROPERTY()
	UBindCapturePrompt* Prompt;

	UFUNCTION()
	void ChordCaptured(FInputChord Chord);
	
};
