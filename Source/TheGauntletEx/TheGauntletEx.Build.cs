// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheGauntletEx : ModuleRules
{
	public TheGauntletEx(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TheGauntletEx",
			"TheGauntletEx/Variant_Platforming",
			"TheGauntletEx/Variant_Platforming/Animation",
			"TheGauntletEx/Variant_Combat",
			"TheGauntletEx/Variant_Combat/AI",
			"TheGauntletEx/Variant_Combat/Animation",
			"TheGauntletEx/Variant_Combat/Gameplay",
			"TheGauntletEx/Variant_Combat/Interfaces",
			"TheGauntletEx/Variant_Combat/UI",
			"TheGauntletEx/Variant_SideScrolling",
			"TheGauntletEx/Variant_SideScrolling/AI",
			"TheGauntletEx/Variant_SideScrolling/Gameplay",
			"TheGauntletEx/Variant_SideScrolling/Interfaces",
			"TheGauntletEx/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
