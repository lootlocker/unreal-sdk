// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "GameAPI/AssetsRequestHandler.h"
#include "CollectablesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FCollectableReward {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FLootLockerAsset asset;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_rental_option_id;
};

USTRUCT(BlueprintType)
struct FCollectableItem {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool collected;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FCollectableReward> rewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool grants_all_rewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool just_collected;
};

USTRUCT(BlueprintType)
struct FCollectableItemGroup {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int completion_percentage;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FCollectableItem> items;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FCollectableReward> rewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool grants_all_rewards;
};

USTRUCT(BlueprintType)
struct FLootLockerCollectable {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FCollectableItemGroup> groups;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int completion_percentage;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FCollectableReward> rewards;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool grants_all_rewards;
};

USTRUCT(BlueprintType)
struct FCollectItemPayload {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString slug;
};

USTRUCT(BlueprintType)
struct FCollectablesResponse : public FLootLockerResponse {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FLootLockerCollectable> collectables;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FCollectablesResponseDelegateBP, FCollectablesResponse, Response);
DECLARE_DELEGATE_OneParam(FCollectablesResponseDelegate, FCollectablesResponse);

UCLASS()
class LOOTLOCKERSDK_API UCollectablesRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    
    static void GetAllCollectables(const FCollectablesResponseDelegateBP& OnCompletedRequestBP = FCollectablesResponseDelegateBP(), const FCollectablesResponseDelegate& OnCompletedRequest = FCollectablesResponseDelegate());
    
    static void CollectItem(const FCollectItemPayload& Item, const FCollectablesResponseDelegateBP& OnCompletedRequestBP = FCollectablesResponseDelegateBP(), const FCollectablesResponseDelegate& OnCompletedRequest = FCollectablesResponseDelegate());
public:
    UCollectablesRequestHandler();
    
    static UHttpClient* HttpClient;
};
