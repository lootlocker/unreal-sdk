// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
#include "LootLockerMiscellaneousRequestHandler.generated.h"

//==================================================
// Data Definitions
//==================================================

/*
*/
USTRUCT(BlueprintType)
struct FLootLockerGameInfo
{
    GENERATED_BODY()
    // The title ID of the game (uniquely identifies the game in LootLocker)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Title_id = "";
    // The environment ID of the game (identifies which environment instance of the title this game refers to in LootLocker)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Environment_id = "";
    // The id of the game (uniquely identifies the game in LootLocker)
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 Game_id = 0;
    // The name of the game as configured in LootLocker
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name = "";
};

//==================================================
// Request Definitions
//==================================================
/*
*/
USTRUCT(BlueprintType)
struct FLootLockerGameInfoRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString api_key = "";
};

//==================================================
// Response Definitions
//==================================================
/*
*/
USTRUCT(BlueprintType)
struct FLootLockerTimeResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString date = "";
};

/*
*/
USTRUCT(BlueprintType)
struct FLootLockerGameInfoResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    // Information about the game
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerGameInfo Info;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================
/**
 * Blueprint response delegate for fetching server time
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FTimeResponseDelegateBP, FLootLockerTimeResponse, Response);
/**
 * Blueprint response delegate for fetching game info
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FGameInfoResponseDelegateBP, FLootLockerGameInfoResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================
/**
 * C++ response delegate for fetching server time
 */
DECLARE_DELEGATE_OneParam(FTimeResponseDelegate, FLootLockerTimeResponse);
/**
 * C++ response delegate for fetching game info
 */
DECLARE_DELEGATE_OneParam(FGameInfoResponseDelegate, FLootLockerGameInfoResponse);

//==================================================
// API Class Definition
//==================================================
UCLASS()
class LOOTLOCKERSDK_API ULootLockerMiscellaneousRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerMiscellaneousRequestHandler();
    
	static void GetServerTime(const FLootLockerPlayerData& PlayerData, const FTimeResponseDelegate& OnCompletedRequest = FTimeResponseDelegate());
	static FString GetLastActivePlatform(const FLootLockerPlayerData& PlayerData);
    static void GetGameInfo(const FGameInfoResponseDelegate& OnCompletedRequest = FGameInfoResponseDelegate());
public:
	static ULootLockerHttpClient* HttpClient;
};