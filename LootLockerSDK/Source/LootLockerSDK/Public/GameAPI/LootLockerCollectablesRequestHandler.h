// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LootLockerCollectablesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerCollectableReward {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAsset asset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_rental_option_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerCollectableItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool collected = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCollectableReward> rewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool grants_all_rewards = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool just_collected = false;
};

USTRUCT(BlueprintType)
struct FLootLockerCollectableItemGroup {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int completion_percentage = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCollectableItem> items;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCollectableReward> rewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool grants_all_rewards = false;
};

USTRUCT(BlueprintType)
struct FLootLockerCollectable {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCollectableItemGroup> groups;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int completion_percentage = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCollectableReward> rewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool grants_all_rewards = false;
};

USTRUCT(BlueprintType)
struct FLootLockerCollectItemPayload {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString slug;
};

USTRUCT(BlueprintType)
struct FLootLockerCollectablesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCollectable> collectables;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FCollectablesResponseDelegateBP, FLootLockerCollectablesResponse, Response);
DECLARE_DELEGATE_OneParam(FCollectablesResponseDelegate, FLootLockerCollectablesResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerCollectablesRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    
    static void GetAllCollectables(const FCollectablesResponseDelegateBP& OnCompletedRequestBP = FCollectablesResponseDelegateBP(), const FCollectablesResponseDelegate& OnCompletedRequest = FCollectablesResponseDelegate());
    
    static void CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCompletedRequestBP = FCollectablesResponseDelegateBP(), const FCollectablesResponseDelegate& OnCompletedRequest = FCollectablesResponseDelegate());
public:
    ULootLockerCollectablesRequestHandler();
    
    static ULootLockerHttpClient* HttpClient;
};
