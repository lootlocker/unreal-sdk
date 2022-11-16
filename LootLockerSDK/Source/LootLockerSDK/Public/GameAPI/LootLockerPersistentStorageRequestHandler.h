// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"
#include "LootLockerPersistentStorageRequestHandler.generated.h"

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

DECLARE_DYNAMIC_DELEGATE_OneParam(FPersistentStorageItemsResponseDelegateBP, FLootLockerPersistentStorageItemsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPersistentStorageItemResponseDelegateBP, FLootLockerPersistentStorageItemResponse, Response);
DECLARE_DELEGATE_OneParam(FPersistentStorageItemsResponseDelegate, FLootLockerPersistentStorageItemsResponse);
DECLARE_DELEGATE_OneParam(FPersistentStorageItemResponseDelegate, FLootLockerPersistentStorageItemResponse);

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
    
    static ULootLockerHttpClient* HttpClient;
};
