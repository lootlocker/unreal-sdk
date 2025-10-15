// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerBroadcastRequestHandler.generated.h"

//==================================================
// Data Definitions
//==================================================

/**
 * Indicates which games are allowed to see this broadcast.
 * This may be useful if you want to know what other games might be seeing this broadcast at the point of display.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerBroadcastGame
{
    GENERATED_BODY()
    
    /**
     * The id of the game
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id = 0;
    
    /**
     * The name of the game
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
};

/**
 * Represents a publication setting for a broadcast message
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerBroadcastPublicationSetting
{
    GENERATED_BODY()
    
    /**
     * The id of the publication setting
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 id = 0;
    
    /**
     * The time of publication
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime start;
    
    /**
     * The optional time of when the broadcast will no longer be returned
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FDateTime end;
    
    /**
     * The IANA timezone that the start and end times are specified in, eg. UTC, Asia/Tokyo, or America/Washington
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString tz = "";
};


/**
 * Internal localization entry as received from API
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerInternalBroadcastLocalizationEntry
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key = "";
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value = "";
};

/**
 * Internal language structure as received from API
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerInternalBroadcastLanguage
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString language_code = "";
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerInternalBroadcastLocalizationEntry> localizations;
};

/**
 * Internal broadcast structure as received from API
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerInternalBroadcast
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id = "";
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString game_name = "";
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerBroadcastGame> games;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerBroadcastPublicationSetting> publication_settings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerInternalBroadcastLanguage> languages;
};

/**
 * Represents a localised version of a broadcast message
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerBroadcastLanguage
{
    GENERATED_BODY()
    
    /**
     * The language code for this localised version of the broadcast message, eg. en-GB
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString language_code = "";
    
    /**
     * The headline for this broadcast message
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString headline = "";
    
    /**
     * The body for this broadcast message
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString body = "";
    
    /**
     * The image URL for this broadcast message
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString image_url = "";
    
    /**
     * The action for this broadcast message
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString action = "";
    
    /**
     * List of the keys available in the localizations dictionary
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> localization_keys;
    
    /**
     * Localized entries for this broadcast message
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FString> localizations;

public:
    FLootLockerBroadcastLanguage() {};
    FLootLockerBroadcastLanguage(const FLootLockerInternalBroadcastLanguage& OtherLanguage);
};

/**
 * Represents a broadcast message
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerBroadcast
{
    GENERATED_BODY()
    
    /**
     * The unique identifier (ULID) for this broadcast message
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString id = "";
    
    /**
     * The name of this broadcast message
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name = "";
    
    /**
     * Name of the current game you're seeing this broadcast on.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString game_name = "";
    
    /**
     * Indicates which games are allowed to see this broadcast.
     * This may be useful if you want to know what other games might be seeing this broadcast at the point of display.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerBroadcastGame> games;
    
    /**
     * A list of publication settings for this broadcast message
     * This list will always contain at least the publication time in UTC, but may also contain additional publication settings for different timezones
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerBroadcastPublicationSetting> publication_settings;
    
    /**
     * The language codes available for this broadcast message
     * eg. ["en", "en-US", "zh"]
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> language_codes;
    
    /**
     * Localised versions of this broadcast message
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FLootLockerBroadcastLanguage> languages;

public:
    FLootLockerBroadcast() {};
    FLootLockerBroadcast(const FLootLockerInternalBroadcast& OtherBroadcast);
};

//==================================================
// Response Definitions
//==================================================

/**
 * Internal response structure as received from API
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerInternalListBroadcastsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerInternalBroadcast> broadcasts;
};

/**
 * Response for listing broadcasts
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListBroadcastsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    
    /**
     * A list of chronologically ordered broadcasts
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerBroadcast> broadcasts;

public:
    FLootLockerListBroadcastsResponse() {};
    FLootLockerListBroadcastsResponse(const FLootLockerInternalListBroadcastsResponse& OtherResponse);
};

//==================================================
// Blueprint Delegate Definitions
//==================================================
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListBroadcastsResponseBP, FLootLockerListBroadcastsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerInternalListBroadcastsResponseBP, FLootLockerInternalListBroadcastsResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================
DECLARE_DELEGATE_OneParam(FLootLockerListBroadcastsResponseDelegate, FLootLockerListBroadcastsResponse);
DECLARE_DELEGATE_OneParam(FLootLockerInternalListBroadcastsResponseDelegate, FLootLockerInternalListBroadcastsResponse);

//==================================================
// Request Handler
//==================================================
UCLASS()
class LOOTLOCKERSDK_API ULootLockerBroadcastRequestHandler : public UObject
{
    GENERATED_BODY()

public:
	ULootLockerBroadcastRequestHandler();
    static void ListBroadcasts(const FLootLockerPlayerData& PlayerData, const TArray<FString>& Languages, int32 Limit, const FLootLockerListBroadcastsResponseBP& OnCompleteBP = FLootLockerListBroadcastsResponseBP(), const FLootLockerListBroadcastsResponseDelegate& OnComplete = FLootLockerListBroadcastsResponseDelegate());
public:
	static ULootLockerHttpClient* HttpClient;
};