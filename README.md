<h1 align="center">LootLocker Unreal SDK</h1>

<h1 align="center">
  <a href="https://www.lootlocker.io/"><img src="https://s3.eu-west-1.amazonaws.com/cdn.lootlocker.io/public/lootlocker-github-bg.png" alt="LootLocker"></a>
</h1>

<p align="center">
  <a href="#about">About</a> •
  <a href="#Installation">Installation</a> •
  <a href="#configuration">Configuration</a> •
  <a href="#sample-app">Sample App</a> •
  <a href="#support">Support</a>
</p>

---

## About

LootLocker is a game backend-as-a-service that unlocks cross-platform systems so you can build, ship, and run your best games.

Full documentation is available [here](https://docs.lootlocker.com/)

## Installation

For a more detailed guide on installation, please see our [User Documentation](https://docs.lootlocker.com/getting-started/unreal-tutorials/getting-started-with-unreal)

1. Download the latest Unreal [Package release](https://github.com/LootLocker/unreal-sdk/releases)
2. Copy the LootLockerSDK folder from the plugins folder equivalent to the Unreal Version you intend to use. For example, if you are using Unreal Version 4.26, Navigate to `4.26/Plugins` to find the appropriate LootLockerSDK folder
3. Paste the LootLockerSDK folder into the plugins folder created in the root of your project (create if it doesn't exist)
4. Right-click on the "Unreal Engine Project Launch" file in the root of your project and click on "Generate Visual Studio Project Files"
5. Open the .sln file of your project
6. Open your project's Build.cs file
7. Add `LootLockerSDK` to the PublicDependencyModuleNames list

    Example: 
    ```cpp
    PublicDependencyModuleNames.AddRange(new string\[\] { "Core", "CoreUObject", "Engine", "InputCore", "LootLockerSDK" });
    ```
8. Add `{"Http", "Json", "JsonUtilities"}` to the PrivateDependencyModuleNames list

    Example: 
    ```cpp
    PrivateDependencyModuleNames.AddRange(new string\[\] { "Http", "Json", "JsonUtilities" });
    ```

## Configuration

### Using C++

1. Open the LootLockerConfig.CPP file located in the plugins folder
2. Navigate to Edit/Project Settings in the editor, Scroll down on the left panel until the plugins sections of the project settings, Click on LootLockerSDK
3. Modify the LootLockerGameKey, Platform, Game Version, Development mode and AllowTokenRefresh (Set to true if you want the LootLockerSDK to attempt to refresh the token if it expires)

### Using Blueprint

It is important that in your first ever Blueprint class you set the LootLocker configurations.

1. Right click within the Event Graph of your blueprint class and locate "LootLocker Settings" category.
2. Select "Set LootLocker Settings" in that category.
3. Fill in the info from the LootLocker dashboard (LootLockerGameKey, Platform, Game Version, Development mode and AllowTokenRefresh). You should already have an account from [https://my.lootlocker.com/login](https://my.lootlocker.com/login "https://my.lootlocker.com/login").

## Sample App

Please download the sample project available [here](https://github.com/LootLocker/unreal-sdk/releases). 

There you can check out our sample Blueprint examples.

## Support

If you have any issues or just wanna chat you can reach us on our [Discord Server](https://discord.lootlocker.com/)