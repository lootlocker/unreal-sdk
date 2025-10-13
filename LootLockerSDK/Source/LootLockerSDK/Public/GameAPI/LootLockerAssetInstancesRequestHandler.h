// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerAssetInstancesRequestHandler.generated.h"



USTRUCT(BlueprintType)
struct FLootLockerAssetInstanceStorageItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key = "";
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value = "";
};

USTRUCT(BlueprintType)
struct FLootLockerAssetInstanceStorageResponseItem : public FLootLockerAssetInstanceStorageItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetInstanceStorageItems {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetInstanceStorageItem> storage;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetInstanceStorageItemsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerAssetInstanceStorageResponseItem> storage;
};

USTRUCT(BlueprintType)
struct FLootLockerAssetInstanceStorageItemResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAssetInstanceStorageResponseItem storage;
};

USTRUCT(BlueprintType)
struct FLootLockerLootBoxItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_rental_option_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int weight = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerLootBoxContentResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerLootBoxItem> contents;
};

USTRUCT(BlueprintType)
struct FLootLockerOpenLootBoxResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool check_grant_notifications = false;
};

USTRUCT(BlueprintType)
struct FLootLockerDeleteAssetInstanceResponse : public FLootLockerResponse
{
    GENERATED_BODY()
};

DECLARE_DELEGATE_OneParam(FAssetInstanceStorageItemsResponseDelegate, FLootLockerAssetInstanceStorageItemsResponse);
DECLARE_DELEGATE_OneParam(FAssetInstanceStorageItemResponseDelegate, FLootLockerAssetInstanceStorageItemResponse);
DECLARE_DELEGATE_OneParam(FLootBoxContentResponseDelegate, FLootLockerLootBoxContentResponse);
DECLARE_DELEGATE_OneParam(FOpenLootBoxResponseDelegate, FLootLockerOpenLootBoxResponse);
DECLARE_DELEGATE_OneParam(FDeleteAssetInstanceResponseDelegate, FLootLockerDeleteAssetInstanceResponse);


UCLASS()
class LOOTLOCKERSDK_API ULootLockerAssetInstancesRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    static void GetAllKeyValuePairsForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());

    static void GetAllKeyValuePairsToAnInstanceForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void GetAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemResponseDelegate());
    
    static void CreateAKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootLockerAssetInstanceStorageItems Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void UpdateAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemResponseDelegate());
    
    static void DeleteAKeyValuePairByIdForAssetInstance(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void InspectLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest = FLootBoxContentResponseDelegate());

    static void OpenLootBox(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest = FOpenLootBoxResponseDelegate());

    static void DeleteAssetInstanceFromPlayerInventory(const FLootLockerPlayerData& PlayerData, int AssetInstanceID, const FDeleteAssetInstanceResponseDelegate& OnCompletedRequest = FDeleteAssetInstanceResponseDelegate());

public:
    ULootLockerAssetInstancesRequestHandler();

    static ULootLockerHttpClient* HttpClient;
};
