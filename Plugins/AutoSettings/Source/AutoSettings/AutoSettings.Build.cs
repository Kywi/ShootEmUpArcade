// Copyright 2017-2018 Sam Bonifacio. All Rights Reserved.

using UnrealBuildTool;

public class AutoSettings : ModuleRules
{
	public AutoSettings(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore", "GameplayTags" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
