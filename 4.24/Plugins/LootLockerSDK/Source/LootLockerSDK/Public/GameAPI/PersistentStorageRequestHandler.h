// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "HttpClient.h"
#include "JsonObjectConverter.h"
#include "PersistentStorageRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FPersistentStorageItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString key;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString value;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool is_public;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int order;
};

USTRUCT(BlueprintType)
struct FPersistentStorageItemsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FPersistentStorageItem> items;
};

USTRUCT(BlueprintType)
struct FPersistentStorageItemResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FPersistentStorageItem item;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FPersistentStorageItemsResponseDelegateBP, FPersistentStorageItemsResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPersistentStorageItemResponseDelegateBP, FPersistentStorageItemResponse, Response);
DECLARE_DELEGATE_OneParam(FPersistentStorageItemsResponseDelegate, FPersistentStorageItemsResponse);
DECLARE_DELEGATE_OneParam(FPersistentStorageItemResponseDelegate, FPersistentStorageItemResponse);

/**
 * 
 */
UCLASS()
class LOOTLOCKERSDK_API UPersistentStorageRequestHandler : public UObject
{
public:
	GENERATED_BODY()
    
public:
    UPersistentStorageRequestHandler();
    
	static void GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP = FPersistentStorageItemsResponseDelegateBP(), const FPersistentStorageItemsResponseDelegate& OnCompletedRequest = FPersistentStorageItemsResponseDelegate());
    
    static void GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegateBP& OnCompletedRequestBP = FPersistentStorageItemResponseDelegateBP(), const FPersistentStorageItemResponseDelegate& OnCompletedRequest = FPersistentStorageItemResponseDelegate());
    
    static void AddItemsToPersistentStorage(const TArray<FPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP = FPersistentStorageItemsResponseDelegateBP(), const FPersistentStorageItemsResponseDelegate& OnCompletedRequest = FPersistentStorageItemsResponseDelegate());
    
    static void DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP = FPersistentStorageItemsResponseDelegateBP(), const FPersistentStorageItemsResponseDelegate& OnCompletedRequest = FPersistentStorageItemsResponseDelegate());
    
    static void GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegateBP& OnCompletedRequestBP = FPersistentStorageItemsResponseDelegateBP(), const FPersistentStorageItemsResponseDelegate& OnCompletedRequest = FPersistentStorageItemsResponseDelegate());
    
    static UHttpClient* HttpClient;
};
