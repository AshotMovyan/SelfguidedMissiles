// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SelfguidedMissiles : ModuleRules
{
	public SelfguidedMissiles(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
