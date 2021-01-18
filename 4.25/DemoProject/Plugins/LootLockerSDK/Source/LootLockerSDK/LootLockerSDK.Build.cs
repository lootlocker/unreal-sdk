// Copyright (c) 2020 LootLocker

using UnrealBuildTool;

public class LootLockerSDK : ModuleRules
{
    public LootLockerSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

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
                "Slate",
                "SlateCore",
                "Http",
                "Json",
                "JsonUtilities"
				//,
    //            "UnrealEd",
    //            "Blutility",
    //            "UMG",
    //            "UMGEditor",
    //            "InputCore",
    //            "Projects",
    //            "HeadMountedDisplay",
    //            "DesktopPlatform"
				// ... add private dependencies that you statically link with here ...
			}
            );

#if WITH_EDITOR
		PrivateDependencyModuleNames.AddRange(
	new string[]
	{
		            "UnrealEd",
                    "Blutility",
                    "UMG",
                    "UMGEditor",
                    "InputCore",
                    "Projects",
                    "HeadMountedDisplay",
                    "DesktopPlatform"
		// ... add private dependencies that you statically link with here ...
	}

    );
#endif
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }
}
