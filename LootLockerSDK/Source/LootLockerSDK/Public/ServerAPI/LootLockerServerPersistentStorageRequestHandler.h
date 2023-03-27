// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"

#include "LootLockerServerPersistentStorageRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerPlayerPersistentStorageItems
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPersistentStorageItem> items;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerPersistentStorageSets
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPersistentStorageItem> sets;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPersistentStorageItemsRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerPersistentStorageSets> payload;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPersistentStorageItemsResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerPersistentStorageItems> items;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FServerPersistentStorageItemsResponseDelegateBP, FLootLockerServerPersistentStorageItemsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FServerPersistentStorageDeleteItemResponseDelegateBP, FLootLockerResponse, Response);
DECLARE_DELEGATE_OneParam(FServerPersistentStorageItemsResponseDelegate, FLootLockerServerPersistentStorageItemsResponse);
DECLARE_DELEGATE_OneParam(FServerPersistentStorageDeleteItemResponseDelegate, FLootLockerResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSDK_API ULootLockerServerPersistentStorageRequestHandler : public UObject
{
public:
	GENERATED_BODY()
    
public:
	ULootLockerServerPersistentStorageRequestHandler();
    
	static void AddItemsToPersistentStorage(const FString& PlayerId, const TArray<FLootLockerPersistentStorageItem>& Items, const FServerPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP = FServerPersistentStorageItemsResponseDelegateBP(), const FServerPersistentStorageItemsResponseDelegate& OnCompletedRequest = FServerPersistentStorageItemsResponseDelegate());
	static void DeleteItemFromPersistentStorage(const FString& PlayerId, const FString& Key, const FServerPersistentStorageDeleteItemResponseDelegateBP& OnCompletedRequestBP = FServerPersistentStorageDeleteItemResponseDelegateBP(), const FServerPersistentStorageDeleteItemResponseDelegate& OnCompletedRequest = FServerPersistentStorageDeleteItemResponseDelegate()); 
	static void GetPlayerPersistentStorage(const FString& PlayerId, const FServerPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP = FServerPersistentStorageItemsResponseDelegateBP(), const FServerPersistentStorageItemsResponseDelegate& OnCompletedRequest = FServerPersistentStorageItemsResponseDelegate());

    static ULootLockerHttpClient* HttpClient;
};
