// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "LootLockerHttpClient.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LLDropTablesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerComputeAndLockDropTableResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    bool success;
    TArray<FLootLockerComputeAndLockItem> items;
};

USTRUCT(BlueprintType)
struct FLootLockerComputeAndLockItem
{
    GENERATED_BODY()
    int asset_id;
    int  asset_variation_id;
    int  asset_rental_option_id;
    int id;
};

USTRUCT(BlueprintType)
struct FLootLockerPickDropsFromDropTableResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    bool success;
    TArray <FLootLockerPickDropsFromDropTableItem> items;
};

USTRUCT(BlueprintType)
struct FLootLockerPickDropsFromDropTableItem
{
    GENERATED_BODY()
    int instance_id;
    int variation_id;
    int rental_option_id;
    int quantity;
    FLootLockerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerPickDropsFromDropTableRequest
{
    GENERATED_BODY()
    TArray<int> picks;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerComputeAndLockDropTableResponseBP, FLootLockerComputeAndLockDropTableResponse, Response);
DECLARE_DELEGATE_OneParam(FLootLockerComputeAndLockDropTableResponseDelegate, FLootLockerComputeAndLockDropTableResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FFLootLockerPickDropsFromDropTableResponseBP, FLootLockerPickDropsFromDropTableResponse, Response);
DECLARE_DELEGATE_OneParam(FFLootLockerPickDropsFromDropTableResponseDelegate, FLootLockerPickDropsFromDropTableResponse);
/**
 * 
 */
UCLASS()
class LOOTLOCKERSDK_API ULLDropTablesRequestHandler : public UObject
{
	GENERATED_BODY()
public:
    ULLDropTablesRequestHandler();
    static ULootLockerHttpClient* HttpClient;
    static void ComputeAndLockDropTable(int TableId,const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP = FLootLockerComputeAndLockDropTableResponseBP(), const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest = FLootLockerComputeAndLockDropTableResponseDelegate());
    static void PickDropsFromDropTable(const FLootLockerPickDropsFromDropTableRequest& request, int TableId,const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP = FFLootLockerPickDropsFromDropTableResponseBP(), const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest = FFLootLockerPickDropsFromDropTableResponseDelegate());
	
};
