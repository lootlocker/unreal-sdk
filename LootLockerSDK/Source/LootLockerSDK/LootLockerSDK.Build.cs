// Copyright (c) 2021 LootLocker

using UnrealBuildTool;

public class LootLockerSDK : ModuleRules
{
    public static bool bEnableGoogleSubsystemHelper = false;
    public LootLockerSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableExceptions = true;

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
				// ... add other public dependencies that you statically link with here ...
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
                "JsonUtilities",
                "Projects"
			}
            );
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );

        if(bEnableGoogleSubsystemHelper)
        {
            PublicDefinitions.Add("LOOTLOCKER_ENABLE_GOOGLESUBSYSTEMHELPER");
            PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });
        }
    }
}
