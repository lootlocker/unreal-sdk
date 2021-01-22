# LootLocker Unreal SDK Documentation
Full Documentation can be found on https://docs.lootlocker.io/

## Quick Start Guide for Installing from repository

1. Download Repository as Zip or Clone project
2. Copy the LootLockerSDK folder from the plugins folder for the Unreal Version you intend to use. For example, if you are using Unreal Version 4.26, Navigate to 4.26/Plugins to 
   find the LootLockerSDK folder.
3. Create a plugins folder on your Unreal project if it doesnt already exist.
4. Paste the folder in the plugins folder created.
5. Return to root project folder.
6. Right-Click the Unreal Engine Project Launch file and click generate Visual Studio project files or whatever code editor you use
7. Launch project with the Launch File.
8. Open Project Build.cs file.
9. Add "LootLockerSDK" to PublicDependencyModuleNames
   Example: PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "LootLockerSDK" });
10. Add "Http", "Json", "JsonUtilities" to the PrivateDependencyModuleNames
   Example: PrivateDependencyModuleNames.AddRange(new string[] { "Http", "Json", "JsonUtilities" });
11.You should now have access to the sdk in both your C++ and Blueprint projects.


## Connecting to the SDK
### Using C++

#### Standard Response

Every response inherits from the LootLockerResponse.

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



In any response coming from the callback of all LootLocker methods, you get the response above. You can get the raw text “FullTextFromServer” and deserialize into any JSON structure that you want.

#### Example GetPersistentStorageResponse Response

We also have a class for each response. The response class contains all the variables from any JSON response from all methods. You can see this when checking out the Sample App that comes with the SDK. You can also check the API responses for the JSON response expected.



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


From the example above you can get the data from the JSON without worrying about deserializing yourself.

#### Authentication With Steam

If you are working with steam, you need some extra setup to have access with steam.
Please follow the instructions found here 
https://docs.unrealengine.com/en-US/ProgrammingAndScripting/Online/Steam/index.html

Once you have completed this, you should be able to access the online subsystem to get access to SteamIdentityToken with the example code below

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

For non steam users, Making your first call should be the session call, You do not need to drag anything into the scene or init the sdk. It does this for you. In order for you to make your very first call.  You only need to send the device id. You can do the following:

1. Create a new C++ Class.
2. Copy the script below and paste it there.
3. The syntax is pretty basic
   1. ULootLockerSDKManager:  Our sdk manager class, you can view this yourself to see all the functions we support
   2. StartSession: Function in the sdk you need to call
   3. DeviceId:  data to send to the sdk to make a session call, this should be unique to the player. It allows for really fast authentication without the need for a username or password. You could generate a Unique ID for your players and save this somewhere on the device or you can decide to use a device identifier to make sure anytime the user downloads your app. They can easily retrieve their data.
   4. Response: This is a class with all the data from the json

```json
      {

          "success": true,

          "session_token": "e6fa44946f077dd9fe67311ab3f188c596df9969",

          "player_id": 3,

          "public_uid": "TSEYDXD8",

          "check_grant_notifications": true,

          "check_deactivation_notifications": false,

          "seen_before": true

      }
```

      This means you can easily do response.success to get the success value from the json response from the server
4. You need to pass a function that will be called when the response returns back from the server, You will find an example below also


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


Remember you need to have your appropriate header file with the method declared

### Using Blueprint
