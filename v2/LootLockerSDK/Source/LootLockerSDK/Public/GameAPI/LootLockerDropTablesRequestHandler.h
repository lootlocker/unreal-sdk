// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "LootLockerHttpClient.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LootLockerDropTablesRequestHandler.generated.h"



USTRUCT(BlueprintType)
struct FLootLockerComputeAndLockItem
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_rental_option_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id;
};

USTRUCT(BlueprintType)
struct FLootLockerComputeAndLockDropTableResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerComputeAndLockItem> items;
};

USTRUCT(BlueprintType)
struct FLootLockerPickDropsFromDropTableItem
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int instance_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rental_option_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int quantity;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerPickDropsFromDropTableResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray <FLootLockerPickDropsFromDropTableItem> items;
};


USTRUCT(BlueprintType)
struct FLootLockerPickDropsFromDropTableRequest
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
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
class LOOTLOCKERSDK_API ULootLockerDropTablesRequestHandler : public UObject
{
	GENERATED_BODY()
public:
    ULootLockerDropTablesRequestHandler();
    static ULootLockerHttpClient* HttpClient;
    static void ComputeAndLockDropTable(int TableId,const FLootLockerComputeAndLockDropTableResponseBP& OnCompletedRequestBP = FLootLockerComputeAndLockDropTableResponseBP(), const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest = FLootLockerComputeAndLockDropTableResponseDelegate());
    static void PickDropsFromDropTable(const FLootLockerPickDropsFromDropTableRequest& request, int TableId,const FFLootLockerPickDropsFromDropTableResponseBP& OnCompletedRequestBP = FFLootLockerPickDropsFromDropTableResponseBP(), const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest = FFLootLockerPickDropsFromDropTableResponseDelegate());
	
};
