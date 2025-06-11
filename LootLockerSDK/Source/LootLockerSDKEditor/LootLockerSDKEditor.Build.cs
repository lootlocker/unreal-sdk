// Copyright (c) LootLocker. All Rights Reserved.
using UnrealBuildTool;

public class LootLockerSDKEditor : ModuleRules
{
    public LootLockerSDKEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "Slate", "SlateCore", "UnrealEd", "ToolMenus", "LootLockerSDK", "InputCore", "WebBrowser"
        });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "Slate", "SlateCore", "InputCore", "UnrealEd", "Projects", "HTTP", "WebBrowser"
        });

        PublicIncludePaths.AddRange(new string[] {
            // Add public include paths required here
        });

        PrivateIncludePaths.AddRange(new string[] {
            // Add private include paths required here
        });
    }
}
