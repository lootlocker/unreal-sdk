// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"
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

DECLARE_DYNAMIC_DELEGATE_OneParam(FPurchaseResponseDelegateBP, FLootLockerPurchaseResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPurchaseStatusResponseDelegateBP, FLootLockerPurchaseStatusResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FActivateRentalAssetResponseDelegateBP, FLootLockerActivateRentalAssetResponse, Response);
DECLARE_DELEGATE_OneParam(FPurchaseResponseDelegate, FLootLockerPurchaseResponse);
DECLARE_DELEGATE_OneParam(FPurchaseStatusResponseDelegate, FLootLockerPurchaseStatusResponse);
DECLARE_DELEGATE_OneParam(FActivateRentalAssetResponseDelegate, FLootLockerActivateRentalAssetResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerPurchasesRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP = FPurchaseResponseDelegateBP(), const FPurchaseResponseDelegate& OnCompletedRequest = FPurchaseResponseDelegate());
    
    static void PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP = FPurchaseResponseDelegateBP(), const FPurchaseResponseDelegate& OnCompletedRequest = FPurchaseResponseDelegate());
    
    static void PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP = FPurchaseResponseDelegateBP(), const FPurchaseResponseDelegate& OnCompletedRequest = FPurchaseResponseDelegate());
    
    static void PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnCompletedRequestBP = FPurchaseStatusResponseDelegateBP(), const FPurchaseStatusResponseDelegate& OnCompletedRequest = FPurchaseStatusResponseDelegate());
    
    static void ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegateBP& OnCompletedRequestBP = FActivateRentalAssetResponseDelegateBP(), const FActivateRentalAssetResponseDelegate& OnCompletedRequest = FActivateRentalAssetResponseDelegate());
public:
    ULootLockerPurchasesRequestHandler();
    
    static ULootLockerHttpClient* HttpClient;
};
