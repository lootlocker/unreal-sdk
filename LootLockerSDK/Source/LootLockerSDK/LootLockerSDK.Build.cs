// Copyright (c) 2021 LootLocker

using System.IO;
using UnrealBuildTool;

public class LootLockerSDK : ModuleRules
{
    public LootLockerSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableExceptions = true;

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Public")
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "Private")
            }
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
			}
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "HTTP",
                "Json",
                "JsonUtilities"
            }
        );
        if (Target.Type == TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "Slate",
                    "SlateCore",
                    "EditorStyle"
                }
            );
        }
    }
}
