// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SettingContainerUtils.generated.h"

/**
 * Static helper functions for operating on multiple settings at the same time
 */
UCLASS()
class AUTOSETTINGS_API USettingContainerUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	// Gets all Setting widgets which are descendant of the given Parent widget
	// @param UserWidget UserWidget which contains settings
	UFUNCTION(BlueprintPure, Category = "Settings", meta = (DefaultToSelf = "UserWidget"))
	static TArray<UAutoSettingWidget*> GetChildSettings(UUserWidget* UserWidget, UWidget* Parent = nullptr);

	// True if any descendant Settings of Parent have unapplied changes
	// @param UserWidget UserWidget which contains settings
	UFUNCTION(BlueprintPure, Category = "Settings", meta = (DefaultToSelf = "UserWidget"))
	static bool DoesAnyChildSettingHaveUnappliedChange(UUserWidget* UserWidget, UWidget* Parent = nullptr);

	// True if any descendant Settings of Parent have unsaved changes
	// @param UserWidget UserWidget which contains settings
	UFUNCTION(BlueprintPure, Category = "Settings", meta = (DefaultToSelf = "UserWidget"))
	static bool DoesAnyChildSettingHaveUnsavedChange(UUserWidget* UserWidget, UWidget* Parent = nullptr);

	// Applies all changes in descendant Settings of Parent
	// @param UserWidget UserWidget which contains settings
	UFUNCTION(BlueprintCallable, Category = "Settings", meta = (DefaultToSelf = "UserWidget"))
	static void ApplyChildSettings(UUserWidget* UserWidget, UWidget* Parent = nullptr);

	// Saves all changes in descendant Settings of Parent
	// @param UserWidget UserWidget which contains settings
	UFUNCTION(BlueprintCallable, Category = "Settings", meta = (DefaultToSelf = "UserWidget"))
	static void SaveChildSettings(UUserWidget* UserWidget, UWidget* Parent = nullptr);

	// Cancels all changes in descendant Settings of Parent
	// @param UserWidget UserWidget which contains settings
	UFUNCTION(BlueprintCallable, Category = "Settings", meta = (DefaultToSelf = "UserWidget"))
	static void CancelChildSettings(UUserWidget* UserWidget, UWidget* Parent = nullptr);
	
	
};
