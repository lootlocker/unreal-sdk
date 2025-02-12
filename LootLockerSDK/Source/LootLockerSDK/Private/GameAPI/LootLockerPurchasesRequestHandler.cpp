// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerPurchasesRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerPurchasesRequestHandler::HttpClient = nullptr;

ULootLockerPurchasesRequestHandler::ULootLockerPurchasesRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerPurchasesRequestHandler::PurchaseAssets(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    FString ContentString = LootLockerUtilities::JsonStringWithTopLevelArrayOfObjects<FLootLockerAssetPurchaseData>(PurchaseData);
    LLAPI<FLootLockerPurchaseResponse>::CallAPIUsingRawJSON(HttpClient, ContentString, ULootLockerGameEndpoints::PurchaseEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::PurchaseAssetsAndroid(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    FString ContentString = LootLockerUtilities::JsonStringWithTopLevelArrayOfObjects<FLootLockerAndroidAssetPurchaseData>(PurchaseData);
    LLAPI<FLootLockerPurchaseResponse>::CallAPIUsingRawJSON(HttpClient, ContentString, ULootLockerGameEndpoints::AndroidPurchaseEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::PurchaseAssetsIOS(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    FString ContentString = LootLockerUtilities::JsonStringWithTopLevelArrayOfObjects<FLootLockerVerifyPurchaseIosData>(PurchaseData);
    LLAPI<FLootLockerPurchaseResponse>::CallAPIUsingRawJSON(HttpClient, ContentString, ULootLockerGameEndpoints::IOSPurchaseEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::PollingOrderStatus(const FLootLockerPlayerData& PlayerData, int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnCompletedRequestBP, const FPurchaseStatusResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPurchaseStatusResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::PollingOrderStatusEndpoint, { PurchaseId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::ActivateRentalAsset(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnCompletedRequestBP, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerActivateRentalAssetResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ActivateRentalAssetEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::GetOrderDetails(const FLootLockerPlayerData& PlayerData, int32 OrderId, const bool noProducts, const FOrderStatusDetailsBP& OnCompleteBP, const FOrderStatusDetailsDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("no_products"), noProducts ? TEXT("true") : TEXT("false"));
    LLAPI<FLootLockerOrderDetailsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOrderDetailsEndpoint, { OrderId }, QueryParams, PlayerData, OnCompleteBP, OnComplete);
}

void ULootLockerPurchasesRequestHandler::PurchaseCatalogItems(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const TArray<FLootLockerCatalogItemAndQuantityPair>& ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerPurchaseCatalogItemRequest{ WalletID, ItemsToPurchase }, ULootLockerGameEndpoints::PurchaseCatalogItem, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& TransactionId, const bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerRedeemAppleAppStorePurchaseForPlayerRequest{ Sandboxed, TransactionId }, ULootLockerGameEndpoints::RedeemAppleAppStorePurchase, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& TransactionId, const bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    FLootLockerRedeemAppleAppStorePurchaseForClassRequest PurchaseRequest = FLootLockerRedeemAppleAppStorePurchaseForClassRequest();
    PurchaseRequest.Class_id = ClassId;
    PurchaseRequest.Sandboxed = Sandboxed;
    PurchaseRequest.Transaction_id = TransactionId;
    FString JsonString = LootLockerUtilities::UStructToJsonString(PurchaseRequest);
    JsonString.ReplaceInline(TEXT("Class_id"), TEXT("character_id"), ESearchCase::IgnoreCase);
    LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(HttpClient, JsonString, ULootLockerGameEndpoints::RedeemAppleAppStorePurchase, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerRedeemGooglePlayStorePurchaseForPlayerRequest{ ProductId, PurchaseToken }, ULootLockerGameEndpoints::RedeemGooglePlayStorePurchase, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    FLootLockerRedeemGooglePlayStorePurchaseForClassRequest PurchaseRequest = FLootLockerRedeemGooglePlayStorePurchaseForClassRequest();
    PurchaseRequest.Class_id = ClassId;
    PurchaseRequest.Product_id = ProductId;
    PurchaseRequest.Purchase_token = PurchaseToken;
    FString JsonString = LootLockerUtilities::UStructToJsonString(PurchaseRequest);
    JsonString.ReplaceInline(TEXT("Class_id"), TEXT("character_id"), ESearchCase::IgnoreCase);
    LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(HttpClient, JsonString, ULootLockerGameEndpoints::RedeemGooglePlayStorePurchase, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemption(const FLootLockerPlayerData& PlayerData, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedBP, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted)
{
    const FLootLockerBeginSteamPurchaseRedemptionRequest PurchaseRequest = FLootLockerBeginSteamPurchaseRedemptionRequest{
        SteamId,
        Currency,
        Language,
        CatalogItemId
    };
    LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::CallAPI(HttpClient, PurchaseRequest, ULootLockerGameEndpoints::BeginSteamPurchaseRedemption, {}, {}, PlayerData, OnCompletedBP, OnCompleted, LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerBeginSteamPurchaseRedemptionResponse& Response)
        {
            const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
            Response.isSuccess = JsonObject->GetBoolField(TEXT("success"));
        }));
}

void ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemptionForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedBP, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted)
{
    FLootLockerBeginSteamPurchaseRedemptionForClassRequest PurchaseRequest;
    PurchaseRequest.Steam_id = SteamId;
    PurchaseRequest.Currency = Currency;
    PurchaseRequest.Language = Language;
    PurchaseRequest.Catalog_item_id = CatalogItemId;
    PurchaseRequest.Class_id = ClassId;
    FString JsonString = LootLockerUtilities::UStructToJsonString(PurchaseRequest);
    JsonString.ReplaceInline(TEXT("Class_id"), TEXT("character_id"), ESearchCase::IgnoreCase);
    LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::CallAPIUsingRawJSON(HttpClient, JsonString, ULootLockerGameEndpoints::BeginSteamPurchaseRedemption, {}, {}, PlayerData, OnCompletedBP, OnCompleted, LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerBeginSteamPurchaseRedemptionResponse& Response)
        {
            const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
            Response.isSuccess = JsonObject->GetBoolField(TEXT("success"));
        }));
}

void ULootLockerPurchasesRequestHandler::QuerySteamPurchaseRedemptionStatus(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedBP, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate& OnCompleted)
{
    LLAPI<FLootLockerQuerySteamPurchaseRedemptionStatusResponse>::CallAPI(HttpClient, FLootLockerQuerySteamPurchaseRedemptionStatusRequest{ EntitlementId }, ULootLockerGameEndpoints::QuerySteamPurchaseRedemptionStatus, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::FinalizeSteamPurchaseRedemption(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerFinalizeSteamPurchaseRedemptionRequest{ EntitlementId }, ULootLockerGameEndpoints::FinalizeSteamPurchaseRedemption, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}
