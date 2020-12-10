// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "HttpClient.h"
#include "PurchasesRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAssetPurchaseData {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int asset_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int variation_id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int rental_option_id;
};

USTRUCT(BlueprintType)
struct FAndroidAssetPurchaseData : public FAssetPurchaseData {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString purchase_token;
};

USTRUCT(BlueprintType)
struct FVerifyPurchaseIosData {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString receipt_data;
};

USTRUCT(BlueprintType)
struct FPurchaseResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool overlay;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int order_id;
};

USTRUCT(BlueprintType)
struct FPurchaseStatusResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FString status;
};

USTRUCT(BlueprintType)
struct FActivateRentalAssetResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int time_left;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPurchaseResponseDelegateBP, FPurchaseResponse, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPurchaseStatusResponseDelegateBP, FPurchaseStatusResponse, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivateRentalAssetResponseDelegateBP, FActivateRentalAssetResponse, Response);
DECLARE_DELEGATE_OneParam(FPurchaseResponseDelegate, FPurchaseResponse);
DECLARE_DELEGATE_OneParam(FPurchaseStatusResponseDelegate, FPurchaseStatusResponse);
DECLARE_DELEGATE_OneParam(FActivateRentalAssetResponseDelegate, FActivateRentalAssetResponse);

UCLASS()
class LOOTLOCKERSDK_API UPurchasesRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    static void PurchaseAssets(const TArray<FAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP = FPurchaseResponseDelegateBP(), const FPurchaseResponseDelegate& OnCompletedRequest = FPurchaseResponseDelegate());
    
    static void PurchaseAssetsAndroid(const TArray<FAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP = FPurchaseResponseDelegateBP(), const FPurchaseResponseDelegate& OnCompletedRequest = FPurchaseResponseDelegate());
    
    static void VerifyPurchaseIos(const TArray<FVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP = FPurchaseResponseDelegateBP(), const FPurchaseResponseDelegate& OnCompletedRequest = FPurchaseResponseDelegate());
    
    static void PollPurchaseStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnCompletedRequestBP = FPurchaseStatusResponseDelegateBP(), const FPurchaseStatusResponseDelegate& OnCompletedRequest = FPurchaseStatusResponseDelegate());
    
    static void ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegateBP& OnCompletedRequestBP = FActivateRentalAssetResponseDelegateBP(), const FActivateRentalAssetResponseDelegate& OnCompletedRequest = FActivateRentalAssetResponseDelegate());
public:
    UPurchasesRequestHandler();
    
    static FResponseCallback sessionResponse;
    static UHttpClient* HttpClient;
};
