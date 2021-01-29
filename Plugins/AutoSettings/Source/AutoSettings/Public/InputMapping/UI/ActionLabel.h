// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#pragma once

#include "InputLabel.h"
#include "Components/PanelWidget.h"
#include "ActionLabel.generated.h"

/**
 * Label for an input action
 * Shows the key the action is bound to, and also any modifier keys
 * Keys will use icons if available, or fall back to text label
 */
UCLASS(abstract)
class AUTOSETTINGS_API UActionLabel : public UInputLabel
{
	GENERATED_BODY()
	
public:

	// Name of the action to display
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Label")
	FName ActionName;

	// KeyLabel class to create for each key
	UPROPERTY(EditAnywhere, Category = "Action Label")
	TSubclassOf<UKeyLabel> KeyLabelWidgetClass;

	// Separator widget to place in between keys
	UPROPERTY(EditAnywhere, Category = "Action Label")
	TSubclassOf<UWidget> KeySeparatorWidgetClass;

	// Initialize this label
	void InitializeLabel();

	virtual void UpdateLabel_Implementation() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Action Label", meta = (BindWidget))
	UPanelWidget* KeyContainer;

	UPanelWidget* GetKeyContainer() const { return KeyContainer; }

	UKeyLabel* CreateLabel();

	UKeyLabel* CreateLabel(const FText& LabelOverride);

	virtual void NativePreConstruct() override;

	void UpdateKeyLabels(struct FInputActionKeyMapping Mapping);

private:

	UKeyLabel* PrimaryKeyLabel;
	UKeyLabel* ShiftLabel;
	UKeyLabel* CtrlLabel;
	UKeyLabel* AltLabel;
	UKeyLabel* CmdLabel;

	UWidget* ShiftSeparator;
	UWidget* CtrlSeparator;
	UWidget* AltSeparator;
	UWidget* CmdSeparator;

	void SetModifierKeyLabelVisibility(UKeyLabel* KeyLabel, UWidget* KeySeparator, bool Visiblity);

	UWidget* AddSeparatorIfValid();
};
