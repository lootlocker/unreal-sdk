// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerPersistentStorageRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerPlayerPersistentStorageKeyValueSet
{
	GENERATED_BODY()
		FLootLockerPlayerPersistentStorageKeyValueSet() {}

	FLootLockerPlayerPersistentStorageKeyValueSet(const FString& InKey, const FString& InValue, bool InIsPublic)
		: Key(InKey), Value(InValue), Is_public(InIsPublic)
	{
	}
	/*
	 The key for this set, used to access the value
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Key = "";
	/*
	 The Value of this set, this is the data you want to store
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Value = "";
	/*
	 Whether this key is public or not. If it is public, other players can read this storage.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool Is_public = false;
};

/*
 Describes a set of key-value pairs that are stored for a player
 */
USTRUCT(BlueprintType)
struct FLootLockerPlayerPersistentStorageEntry
{
	GENERATED_BODY()
	/*
	 The player ID for which these items are being stored
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int Player_id = 0;
	/*
	 A list of key value pairs that are stored for the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerPersistentStorageKeyValueSet> Items;
};

USTRUCT(BlueprintType)
struct FLootLockerPersistentStorageItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool is_public = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int order = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerPersistentStorageItems {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerPersistentStorageItem> payload;
};


USTRUCT(BlueprintType)
struct FLootLockerGetPublicPersistentStorageForPlayersAndKeysRequest {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> keys;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> player_ids;
};

//==================================================
// Response Definitions
//==================================================

USTRUCT(BlueprintType)
struct FLootLockerPersistentStorageItemsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerPersistentStorageItem> payload;
    TMap<FString, FString> Map;
    FLootLockerPersistentStorageItemsResponse()
    {
        for (auto Item : payload)
            Map.Add(Item.key, Item.value);
    }
};

USTRUCT(BlueprintType)
struct FLootLockerPersistentStorageItemResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerPersistentStorageItem payload;
};

USTRUCT(BlueprintType)
struct FLootLockerGetPublicPersistentStorageForPlayersAndKeysResponse : public FLootLockerResponse
{
	GENERATED_BODY()

	/*
	 The persistent publicly available storage retrieved for the requested player ids and keys
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerPersistentStorageEntry> Storages;
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FPersistentStorageItemsResponseDelegateBP, FLootLockerPersistentStorageItemsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPersistentStorageItemResponseDelegateBP, FLootLockerPersistentStorageItemResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetPublicPersistentStorageForPlayersAndKeysResponseBP, FLootLockerGetPublicPersistentStorageForPlayersAndKeysResponse, Response);
DECLARE_DELEGATE_OneParam(FPersistentStorageItemsResponseDelegate, FLootLockerPersistentStorageItemsResponse);
DECLARE_DELEGATE_OneParam(FPersistentStorageItemResponseDelegate, FLootLockerPersistentStorageItemResponse);
DECLARE_DELEGATE_OneParam(FLootLockerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate, FLootLockerGetPublicPersistentStorageForPlayersAndKeysResponse);
/**
 * 
 */
UCLASS()
class LOOTLOCKERSDK_API ULootLockerPersistentStorageRequestHandler : public UObject
{
public:
	GENERATED_BODY()
    
public:
    ULootLockerPersistentStorageRequestHandler();
    
	static void GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP = FPersistentStorageItemsResponseDelegateBP(), const FPersistentStorageItemsResponseDelegate& OnCompletedRequest = FPersistentStorageItemsResponseDelegate());
    
    static void GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnCompletedRequestBP = FPersistentStorageItemResponseDelegateBP(), const FPersistentStorageItemResponseDelegate& OnCompletedRequest = FPersistentStorageItemResponseDelegate());
    
    static void AddItemsToPersistentStorage(const FLootLockerPersistentStorageItems Items, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP =
                                                FPersistentStorageItemsResponseDelegateBP(), const FPersistentStorageItemsResponseDelegate& OnCompletedRequest =
                                                FPersistentStorageItemsResponseDelegate());
    static void AddItemToPersistentStorage(const FLootLockerPersistentStorageItem Item, const FPersistentStorageItemResponseDelegateBP& OnCompletedRequestBP =
        FPersistentStorageItemResponseDelegateBP(), const FPersistentStorageItemResponseDelegate& OnCompletedRequest =
        FPersistentStorageItemResponseDelegate());
    
    static void DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP = FPersistentStorageItemsResponseDelegateBP(), const FPersistentStorageItemsResponseDelegate& OnCompletedRequest = FPersistentStorageItemsResponseDelegate());
    
    static void GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP = FPersistentStorageItemsResponseDelegateBP(), const FPersistentStorageItemsResponseDelegate& OnCompletedRequest = FPersistentStorageItemsResponseDelegate());

	static void GetPublicPersistentStorageForPlayersAndKeys(TArray<FString> PlayerIDs, TArray<FString> Keys, const FLootLockerGetPublicPersistentStorageForPlayersAndKeysResponseBP& OnCompleteRequestBP = FLootLockerGetPublicPersistentStorageForPlayersAndKeysResponseBP(), const FLootLockerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate& OnCompleteResponse = FLootLockerGetPublicPersistentStorageForPlayersAndKeysResponseDelegate());


    static ULootLockerHttpClient* HttpClient;
};
