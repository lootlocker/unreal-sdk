// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LootLockerDropTablesRequestHandler.generated.h"



USTRUCT(BlueprintType)
struct FLootLockerComputeAndLockItem
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_rental_option_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int id = 0;
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
    int instance_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rental_option_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int quantity = 0;
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


DECLARE_DELEGATE_OneParam(FLootLockerComputeAndLockDropTableResponseDelegate, FLootLockerComputeAndLockDropTableResponse);
DECLARE_DELEGATE_OneParam(FFLootLockerPickDropsFromDropTableResponseDelegate, FLootLockerPickDropsFromDropTableResponse);
/**
 * 
 */
UCLASS()
class LOOTLOCKERSDK_API ULootLockerDropTablesRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerDropTablesRequestHandler() {};

    static FString ComputeAndLockDropTable(const FLootLockerPlayerData& PlayerData, int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest);
    static FString PickDropsFromDropTable(const FLootLockerPlayerData& PlayerData, const FLootLockerPickDropsFromDropTableRequest& request, int TableId, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest);
};
