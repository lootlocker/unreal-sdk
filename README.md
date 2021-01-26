# LootLocker Unreal SDK Documentation
Full Documentation can be found on https://docs.lootlocker.io/

## Quick Start Guide for Installing from repository

 1. Download the latest Unreal Package release from the [Github](https://github.com/LootLocker/unreal-sdk/releases) repository.
 2. Download Repository as a Zip or Clone the project.
 3. Copy the LootLockerSDK folder from the plugins folder equivalent to the Unreal Version you intend to use. For example, if you are using Unreal Version 4.26, Navigate to 4.26/Plugins to find the appropriate LootLockerSDK folder.
 4. Create a plugins folder in your Unreal project root folder if it doesnt already exist.
 5. Paste the LootLockerSDK folder into the plugins folder created.
 6. Return to the root project folder.
 7. Right-click on the "Unreal Engine Project Launch" file and click on "Generate Visual Studio Project Files".
 8. Open the .sln file of your project.
 9. Open your project's Build.cs file.
10. Add {"LootLockerSDK"} to the PublicDependencyModuleNames list.

    Example: PublicDependencyModuleNames.AddRange(new string\[\] { "Core", "CoreUObject", "Engine", "InputCore", "LootLockerSDK" });
11. Add {"Http", "Json", "JsonUtilities"} to the PrivateDependencyModuleNames list.

    Example: PrivateDependencyModuleNames.AddRange(new string\[\] { "Http", "Json", "JsonUtilities" });
12. Open the LootLockerConfig.CPP file located in the plugins folder.

13. Modify the LootLockerGameKey, Platform, Game Version, Development mode and AllowTokenRefresh (Set to true if you want the LootLockerSDK to attempt to refresh the token if it expires).

14. You should now have access to the SDK in both your C++ and Blueprint projects.


## Connecting to the SDK
### Using C++

Every response inherits from the LootLockerResponse class.

``` cpp
    struct FLootLockerResponse
    {
        GENERATED_BODY()
        public:
        UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool success;
        UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool ServerCallHasError;
        UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int ServerCallStatusCode;
        UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FString FullTextFromServer;
        UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FString ServerError;
    };
```


In any response coming from the callbacks of all LootLocker methods, you get the response above. You can get the raw text from “FullTextFromServer”.

#### Example Response

We have a class for each response. The response class contains all the variables from the JSON response of the API request. You can see this when checking out the examples that come with the SDK and comparing them with the API JSON response expected.

```json
    // Example json
    {
        "success": true,
        "payload": [
            {
                "key": "user.answer",
                "value": "42"
            }
        ]
    }
```

```cpp
//Response Class

USTRUCT(BlueprintType)
struct FPersistentStorageItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString value;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool is_public;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int order;
};

USTRUCT(BlueprintType)
struct FPersistentStorageItemsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FPersistentStorageItem> items;
    public:
    FPersistentStorageItemsResponse()
    {}
};
```

#### SDK Configuration

If you want to modify the LootLockerConfig by code, you can do this by calling "ULootLockerConfig::SetLootLockerSettings". This method requires you to pass in your LootLockerGameKey, Platform, Game Version, Development mode and AllowTokenRefresh.
#### Authentication With Steam

API Reference: [https://docs.lootlocker.io/game-api/#player-verification](https://docs.lootlocker.io/game-api/#player-verification "https://docs.lootlocker.io/game-api/#player-verification")

Using LootLocker with Steam requires "ULootLockerSDKManager::VerifyPlayer" to be the very first call made. After a successful response from this call, you can follow up with the "ULootLockerSDKManager::StartSession" call.

One of the variables required by ULootLockerSDKManager::VerifyPlayer call is the "SteamIdentityToken". You can retrieve this using the sample code found below, but first you have to follow the instructions found [here](https://docs.unrealengine.com/en-US/ProgrammingAndScripting/Online/Steam/index.html). These instructions tell you how to enable the online subsystems of the Unreal Engine.

If you prefer videos, you can follow the guide found [here](https://www.youtube.com/watch?v=4CgeAxiS19s&ab_channel=VictorBurgosGames "here").


```cpp

FString IdentityToken = OnlineSub->GetIdentityInterface()->GetAuthToken(0);
ULootLockerSDKManager::VerifyPlayer(IdentityToken, FLootLockerDefaultAuthenticationResponse::CreateUObject(this, &ADemoAuthentication::OnVerifyPlayerCompleted));
   
   void ADemoAuthentication::OnVerifyPlayerCompleted(FAuthenticationDefaultResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnVerifyPlayer Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnVerifyPlayer Failed"));
    }
}
```

```cpp
void ADemoAuthentication::DemoVerifyPlayer()
{
    ULootLockerSDKManager::VerifyPlayer(IdentityToken, FLootLockerDefaultAuthenticationResponse::CreateUObject(this, &ADemoAuthentication::OnVerifyPlayerCompleted));
}

void ADemoAuthentication::OnVerifyPlayerCompleted(FAuthenticationDefaultResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnVerifyPlayer Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnVerifyPlayer Failed"));
    }
}
```


#### Session/Authentication Request

API Reference: [https://docs.lootlocker.io/game-api/#authentication-request](https://docs.lootlocker.io/game-api/#authentication-request "https://docs.lootlocker.io/game-api/#authentication-request")

For non-steam games, your first call should be "ULootLockerSDKManager::StartSession". This call only requires you to send a "PlayerId". This can be any string you use to identify your players. You should note that you are responsible for keeping this persistent since this is the only way LockerLocker can identify your players. 

```cpp
//Example Method
void ADemoAuthentication::DemoStartSession()
{
    ULootLockerSDKManager::StartSession(PlayerId, FLootLockerSessionResponse::CreateUObject(this, &ADemoAuthentication::OnStartSessionCompleted));
}

//Example callback method
void ADemoAuthentication::OnStartSessionCompleted(FAuthenticationResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnStartSession Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnStartSession Failed"));
    }
}
```

Remember you need to have your appropriate header files with the methods declared.

### Using Blueprint
#### Connecting to LootLocker
#### Setting Config

It is important that in your first ever Blueprint class you set the LootLocker configurations.

1. Right click within the Event Graph of your blueprint class and locate "LootLocker Settings" category.
2. Select "Set LootLocker Settings" in that category.
3. Fill in the info from the LootLocker dashboard (LootLockerGameKey, Platform, Game Version, Development mode and AllowTokenRefresh). You should already have an account from [https://my.lootlocker.io/login](https://my.lootlocker.io/login "https://my.lootlocker.io/login").
4. You can now continue with connecting with LootLocker APIs via blueprint.

#### Standard Calls

Every LootLocker Method is static, meaning that you can right click and search for any LootLocker method you wish to use in all Blueprint event graphs. These methods are also put into categories for you to easily access.

#### Session/Authentication Request

#### Subsequent Requests

Please download the Sample Project available [here](https://github.com/LootLocker/unreal-sdk/releases). There you can check out sample Blueprint examples
