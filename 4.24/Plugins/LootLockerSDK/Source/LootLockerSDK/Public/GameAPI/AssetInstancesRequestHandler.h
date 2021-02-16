// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "AssetInstancesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAssetInstanceStorageItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString value;
};

USTRUCT(BlueprintType)
struct FAssetInstanceStorageResponseItem : public FAssetInstanceStorageItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int Id;
};

USTRUCT(BlueprintType)
struct FAssetInstanceStorageItems {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAssetInstanceStorageItem> storage;
};

USTRUCT(BlueprintType)
struct FAssetInstanceStorageItemsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FAssetInstanceStorageResponseItem> items;
};

USTRUCT(BlueprintType)
struct FLootBoxItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_rental_option_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int weight;
};

USTRUCT(BlueprintType)
struct FLootBoxContentResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootBoxItem> items;
};

USTRUCT(BlueprintType)
struct FOpenLootBoxResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool check_grant_notifications;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FAssetInstanceStorageItemsResponseDelegateBP, FAssetInstanceStorageItemsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootBoxContentResponseDelegateBP, FLootBoxContentResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOpenLootBoxResponseDelegateBP, FOpenLootBoxResponse, Response);
DECLARE_DELEGATE_OneParam(FAssetInstanceStorageItemsResponseDelegate, FAssetInstanceStorageItemsResponse);
DECLARE_DELEGATE_OneParam(FLootBoxContentResponseDelegate, FLootBoxContentResponse);
DECLARE_DELEGATE_OneParam(FOpenLootBoxResponseDelegate, FOpenLootBoxResponse);

UCLASS()
class LOOTLOCKERSDK_API UAssetInstancesRequestHandler : public UObject
{
public:
    GENERATED_BODY()
    
    static void GetAllKeyValuePairsForAssetInstance(const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());

    static void GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegateBP& OnCompletedRequestBP = FAssetInstanceStorageItemsResponseDelegateBP(), const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest = FAssetInstanceStorageItemsResponseDelegate());
    
    static void InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegateBP& OnCompletedRequestBP = FLootBoxContentResponseDelegateBP(), const FLootBoxContentResponseDelegate& OnCompletedRequest = FLootBoxContentResponseDelegate());
    
    static void OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegateBP& OnCompletedRequestBP = FOpenLootBoxResponseDelegateBP(), const FOpenLootBoxResponseDelegate& OnCompletedRequest = FOpenLootBoxResponseDelegate());
    
public:
    UAssetInstancesRequestHandler();

    static UHttpClient* HttpClient;
};
