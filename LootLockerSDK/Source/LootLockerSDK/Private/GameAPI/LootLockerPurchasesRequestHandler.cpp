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

void ULootLockerPurchasesRequestHandler::ActivateRentalAsset(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FActivateRentalAssetResponseDelegateBP& OnCompletedRequestBP, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerActivateRentalAssetResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ActivateRentalAssetEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
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

void ULootLockerPurchasesRequestHandler::RedeemEpicStorePurchase(const FLootLockerPlayerData& PlayerData, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    FLootLockerRedeemEpicStorePurchaseForPlayerRequest PurchaseRequest{
        AccountId,
        BearerToken,
        EntitlementIds,
        SandboxId
    };

    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, PurchaseRequest, ULootLockerGameEndpoints::RedeemEpicStorePurchase, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemEpicStorePurchaseForCharacter(const FLootLockerPlayerData& PlayerData, const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    FLootLockerRedeemEpicStorePurchaseForCharacterRequest PurchaseRequest;
    PurchaseRequest.Account_id = AccountId;
	PurchaseRequest.Bearer_token = BearerToken;
	PurchaseRequest.Entitlement_ids = EntitlementIds;
	PurchaseRequest.Sandbox_id = SandboxId;
	PurchaseRequest.Character_id = CharacterId;

    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, PurchaseRequest, ULootLockerGameEndpoints::RedeemEpicStorePurchase, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("transaction_id"), TransactionId);
    JsonObject->SetStringField(TEXT("auth_code"), AuthCode);
    JsonObject->SetStringField(TEXT("entitlement_label"), EntitlementLabel);
    
    // Add optional parameters if they are set
    if (!ServiceLabel.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("service_label"), ServiceLabel);
    }
    if (!ServiceName.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("service_name"), ServiceName);
    }
    if (Environment != -1)
    {
        JsonObject->SetNumberField(TEXT("environment"), Environment);
    }
    if (UseCount != -1)
    {
        JsonObject->SetNumberField(TEXT("use_count"), UseCount);
    }
    
    FString JsonString = LootLockerUtilities::FStringFromJsonObject(JsonObject);

    LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(HttpClient, JsonString, ULootLockerGameEndpoints::RedeemPlayStationStorePurchase, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}

void ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForCharacter(const FLootLockerPlayerData& PlayerData, const FString& CharacterId, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultResponseBP& OnCompletedBP, const FLootLockerDefaultDelegate& OnCompleted)
{
    TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("transaction_id"), TransactionId);
    JsonObject->SetStringField(TEXT("auth_code"), AuthCode);
    JsonObject->SetStringField(TEXT("entitlement_label"), EntitlementLabel);
    JsonObject->SetStringField(TEXT("character_id"), CharacterId);
    
    // Add optional parameters if they are set
    if (!ServiceLabel.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("service_label"), ServiceLabel);
    }
    if (!ServiceName.IsEmpty())
    {
        JsonObject->SetStringField(TEXT("service_name"), ServiceName);
    }
    if (Environment != -1)
    {
        JsonObject->SetNumberField(TEXT("environment"), Environment);
    }
    if (UseCount != -1)
    {
        JsonObject->SetNumberField(TEXT("use_count"), UseCount);
    }
    
    FString JsonString = LootLockerUtilities::FStringFromJsonObject(JsonObject);

    LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(HttpClient, JsonString, ULootLockerGameEndpoints::RedeemPlayStationStorePurchase, {}, {}, PlayerData, OnCompletedBP, OnCompleted);
}
