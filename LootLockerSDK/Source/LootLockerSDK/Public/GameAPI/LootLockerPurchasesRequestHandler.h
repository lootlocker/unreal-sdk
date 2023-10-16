// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LootLockerPurchasesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerAssetPurchaseData {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int asset_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int variation_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int rental_option_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerAndroidAssetPurchaseData : public FLootLockerAssetPurchaseData {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString purchase_token;
};

USTRUCT(BlueprintType)
struct FLootLockerVerifyPurchaseIosData {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString receipt_data;
};

USTRUCT(BlueprintType)
struct FLootLockerPurchaseResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool overlay = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int order_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerPurchaseStatusResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString status;
};

USTRUCT(BlueprintType)
struct FLootLockerActivateRentalAssetResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int time_left = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerProduct
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 instance_id = 0;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 rental_option_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString acquistion_source;
    FLootLockerAsset asset;
};

USTRUCT(BlueprintType)
struct FLootLockerOrderDetailsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString order_status;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerProduct> products;
};

/**
 * 
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCatalogItemAndQuantityPair
{
    GENERATED_BODY()
    /**
     * The unique listing id of the catalog item to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Catalog_listing_id;
    /**
     * The quantity of the specified item to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Quantity = 0;
};

/**
 * 
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct  FLootLockerPurchaseCatalogItemRequest
{
    GENERATED_BODY()
    /**
     * The id of the wallet to be used for the purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id;
    /**
     * A list of items to purchase
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCatalogItemAndQuantityPair> Items;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FPurchaseResponseDelegateBP, FLootLockerPurchaseResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPurchaseStatusResponseDelegateBP, FLootLockerPurchaseStatusResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FActivateRentalAssetResponseDelegateBP, FLootLockerActivateRentalAssetResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOrderStatusDetailsBP, FLootLockerOrderDetailsResponse, Response);
DECLARE_DELEGATE_OneParam(FPurchaseResponseDelegate, FLootLockerPurchaseResponse);
DECLARE_DELEGATE_OneParam(FPurchaseStatusResponseDelegate, FLootLockerPurchaseStatusResponse);
DECLARE_DELEGATE_OneParam(FActivateRentalAssetResponseDelegate, FLootLockerActivateRentalAssetResponse);
DECLARE_DELEGATE_OneParam(FOrderStatusDetailsDelegate, FLootLockerOrderDetailsResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerPurchasesRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP = FPurchaseResponseDelegateBP(), const FPurchaseResponseDelegate& OnCompletedRequest = FPurchaseResponseDelegate());

    static void PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP = FPurchaseResponseDelegateBP(), const FPurchaseResponseDelegate& OnCompletedRequest = FPurchaseResponseDelegate());

    static void PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP = FPurchaseResponseDelegateBP(), const FPurchaseResponseDelegate& OnCompletedRequest = FPurchaseResponseDelegate());

    static void PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnCompletedRequestBP = FPurchaseStatusResponseDelegateBP(), const FPurchaseStatusResponseDelegate& OnCompletedRequest = FPurchaseStatusResponseDelegate());

    static void ActivateRentalAsset(int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnCompletedRequestBP = FActivateRentalAssetResponseDelegateBP(), const FActivateRentalAssetResponseDelegate& OnCompletedRequest = FActivateRentalAssetResponseDelegate());

    static void GetOrderDetails(int32 OrderId, const bool noProducts = false, const FOrderStatusDetailsBP& OnCompleteBP = FOrderStatusDetailsBP(), const FOrderStatusDetailsDelegate& OnComplete = FOrderStatusDetailsDelegate());

    static void PurchaseCatalogItems(const FString& WalletID, const TArray<FLootLockerCatalogItemAndQuantityPair>& ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnCompleted = FLootLockerDefaultDelegate());

public:
    ULootLockerPurchasesRequestHandler();

    static ULootLockerHttpClient* HttpClient;
};
