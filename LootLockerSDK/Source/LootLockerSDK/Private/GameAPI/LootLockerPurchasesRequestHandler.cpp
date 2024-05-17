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

void ULootLockerPurchasesRequestHandler::PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    FString ContentString = LootLockerUtilities::JsonStringWithTopLevelArrayOfObjects<FLootLockerAssetPurchaseData>(PurchaseData);
    LLAPI<FLootLockerPurchaseResponse>::CallAPIUsingRawJSON(HttpClient, ContentString, ULootLockerGameEndpoints::PurchaseEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    FString ContentString = LootLockerUtilities::JsonStringWithTopLevelArrayOfObjects<FLootLockerAndroidAssetPurchaseData>(PurchaseData);
    LLAPI<FLootLockerPurchaseResponse>::CallAPIUsingRawJSON(HttpClient, ContentString, ULootLockerGameEndpoints::AndroidPurchaseEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    FString ContentString = LootLockerUtilities::JsonStringWithTopLevelArrayOfObjects<FLootLockerVerifyPurchaseIosData>(PurchaseData);
    LLAPI<FLootLockerPurchaseResponse>::CallAPIUsingRawJSON(HttpClient, ContentString, ULootLockerGameEndpoints::IOSPurchaseEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnCompletedRequestBP, const FPurchaseStatusResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPurchaseStatusResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::PollingOrderStatusEndpoint, {  PurchaseId}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::ActivateRentalAsset(int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnCompletedRequestBP, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerActivateRentalAssetResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ActivateRentalAssetEndpoint, { AssetInstanceId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::GetOrderDetails(int32 OrderId, const bool noProducts, const FOrderStatusDetailsBP &OnCompleteBP, const FOrderStatusDetailsDelegate &OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("no_products"), noProducts ? TEXT("true") : TEXT("false"));
    LLAPI<FLootLockerOrderDetailsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOrderDetailsEndpoint, { OrderId }, QueryParams, OnCompleteBP, OnComplete);
}

void ULootLockerPurchasesRequestHandler::PurchaseCatalogItems(const FString& WalletID, const TArray<FLootLockerCatalogItemAndQuantityPair>& ItemsToPurchase, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerPurchaseCatalogItemRequest{ WalletID, ItemsToPurchase }, ULootLockerGameEndpoints::PurchaseCatalogItem, {}, {}, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForPlayer(const FString& TransactionId, const bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerRedeemAppleAppStorePurchaseForPlayerRequest{ Sandboxed, TransactionId }, ULootLockerGameEndpoints::RedeemAppleAppStorePurchase, {}, {}, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForClass(const int ClassId, const FString& TransactionId, const bool Sandboxed, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
	FLootLockerRedeemAppleAppStorePurchaseForClassRequest PurchaseRequest =FLootLockerRedeemAppleAppStorePurchaseForClassRequest();
    PurchaseRequest.Class_id = ClassId;
    PurchaseRequest.Sandboxed = Sandboxed;
    PurchaseRequest.Transaction_id = TransactionId;
    FString JsonString = LootLockerUtilities::UStructToJsonString(PurchaseRequest);
    JsonString.ReplaceInline(TEXT("Class_id"), TEXT("character_id"), ESearchCase::IgnoreCase);
    LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(HttpClient, JsonString, ULootLockerGameEndpoints::RedeemAppleAppStorePurchase, {}, {}, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForPlayer(const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerRedeemGooglePlayStorePurchaseForPlayerRequest{ ProductId, PurchaseToken }, ULootLockerGameEndpoints::RedeemGooglePlayStorePurchase, {}, {}, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForClass(const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    FLootLockerRedeemGooglePlayStorePurchaseForClassRequest PurchaseRequest = FLootLockerRedeemGooglePlayStorePurchaseForClassRequest();
    PurchaseRequest.Class_id = ClassId;
    PurchaseRequest.Product_id = ProductId;
    PurchaseRequest.Purchase_token = PurchaseToken;
    FString JsonString = LootLockerUtilities::UStructToJsonString(PurchaseRequest);
    JsonString.ReplaceInline(TEXT("Class_id"), TEXT("character_id"), ESearchCase::IgnoreCase);
    LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(HttpClient, JsonString, ULootLockerGameEndpoints::RedeemGooglePlayStorePurchase, {}, {}, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemption(const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedBP, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted)
{
    const FLootLockerBeginSteamPurchaseRedemptionRequest PurchaseRequest = FLootLockerBeginSteamPurchaseRedemptionRequest{
        SteamId,
        Currency,
        Language,
        CatalogItemId
    };
    LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::CallAPI(HttpClient, PurchaseRequest, ULootLockerGameEndpoints::BeginSteamPurchaseRedemption, {}, {}, OnCompletedBP, OnCompleted, LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerBeginSteamPurchaseRedemptionResponse& Response)
    {
        const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
        Response.isSuccess = JsonObject->GetBoolField(TEXT("success"));
    }));
}

void ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemptionForClass(const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegateBP& OnCompletedBP, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted)
{
    FLootLockerBeginSteamPurchaseRedemptionForClassRequest PurchaseRequest;
	PurchaseRequest.Steam_id = SteamId;
	PurchaseRequest.Currency = Currency;
	PurchaseRequest.Language = Language;
	PurchaseRequest.Catalog_item_id = CatalogItemId;
	PurchaseRequest.Class_id = ClassId;
	FString JsonString = LootLockerUtilities::UStructToJsonString(PurchaseRequest);
    JsonString.ReplaceInline(TEXT("Class_id"), TEXT("character_id"), ESearchCase::IgnoreCase);
    LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::CallAPIUsingRawJSON(HttpClient, JsonString, ULootLockerGameEndpoints::BeginSteamPurchaseRedemption, {}, {}, OnCompletedBP, OnCompleted, LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerBeginSteamPurchaseRedemptionResponse& Response)
    {
        const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
        Response.isSuccess = JsonObject->GetBoolField(TEXT("success"));
    }));
}

void ULootLockerPurchasesRequestHandler::QuerySteamPurchaseRedemptionStatus(const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegateBP& OnCompletedBP, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate& OnCompleted)
{
    LLAPI<FLootLockerQuerySteamPurchaseRedemptionStatusResponse>::CallAPI(HttpClient, FLootLockerQuerySteamPurchaseRedemptionStatusRequest{ EntitlementId }, ULootLockerGameEndpoints::QuerySteamPurchaseRedemptionStatus, {}, {}, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::FinalizeSteamPurchaseRedemption(const FString& EntitlementId, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, FLootLockerFinalizeSteamPurchaseRedemptionRequest{ EntitlementId }, ULootLockerGameEndpoints::FinalizeSteamPurchaseRedemption, {}, {}, OnCompletedBP, OnCompleted);
}
