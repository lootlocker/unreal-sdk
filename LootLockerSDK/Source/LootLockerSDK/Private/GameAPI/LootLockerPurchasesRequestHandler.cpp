// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerPurchasesRequestHandler.h"

#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerPurchasesRequestHandler::ActivateRentalAsset(const FLootLockerPlayerData& PlayerData, int AssetInstanceId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerActivateRentalAssetResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ActivateRentalAssetEndpoint, { AssetInstanceId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPurchasesRequestHandler::PurchaseCatalogItems(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const TArray<FLootLockerCatalogItemAndQuantityPair>& ItemsToPurchase, const FLootLockerDefaultDelegate& OnCompleted)
{
    return LLAPI<FLootLockerResponse>::CallAPI(FLootLockerPurchaseCatalogItemRequest{ WalletID, ItemsToPurchase }, ULootLockerGameEndpoints::PurchaseCatalogItem, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& TransactionId, const bool Sandboxed, const FLootLockerDefaultDelegate& OnCompleted)
{
    return LLAPI<FLootLockerResponse>::CallAPI(FLootLockerRedeemAppleAppStorePurchaseForPlayerRequest{ Sandboxed, TransactionId }, ULootLockerGameEndpoints::RedeemAppleAppStorePurchase, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::RedeemAppleAppStorePurchaseForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& TransactionId, const bool Sandboxed, const FLootLockerDefaultDelegate& OnCompleted)
{
    FLootLockerRedeemAppleAppStorePurchaseForClassRequest PurchaseRequest = FLootLockerRedeemAppleAppStorePurchaseForClassRequest();
    PurchaseRequest.Class_id = ClassId;
    PurchaseRequest.Sandboxed = Sandboxed;
    PurchaseRequest.Transaction_id = TransactionId;
    FString JsonString = LootLockerUtilities::UStructToJsonString(PurchaseRequest);
    JsonString.ReplaceInline(TEXT("Class_id"), TEXT("character_id"), ESearchCase::IgnoreCase);
    return LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(JsonString, ULootLockerGameEndpoints::RedeemAppleAppStorePurchase, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompleted)
{
    return LLAPI<FLootLockerResponse>::CallAPI(FLootLockerRedeemGooglePlayStorePurchaseForPlayerRequest{ ProductId, PurchaseToken }, ULootLockerGameEndpoints::RedeemGooglePlayStorePurchase, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::RedeemGooglePlayStorePurchaseForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& ProductId, const FString& PurchaseToken, const FLootLockerDefaultDelegate& OnCompleted)
{
    FLootLockerRedeemGooglePlayStorePurchaseForClassRequest PurchaseRequest = FLootLockerRedeemGooglePlayStorePurchaseForClassRequest();
    PurchaseRequest.Class_id = ClassId;
    PurchaseRequest.Product_id = ProductId;
    PurchaseRequest.Purchase_token = PurchaseToken;
    FString JsonString = LootLockerUtilities::UStructToJsonString(PurchaseRequest);
    JsonString.ReplaceInline(TEXT("Class_id"), TEXT("character_id"), ESearchCase::IgnoreCase);
    return LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(JsonString, ULootLockerGameEndpoints::RedeemGooglePlayStorePurchase, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemption(const FLootLockerPlayerData& PlayerData, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted)
{
    const FLootLockerBeginSteamPurchaseRedemptionRequest PurchaseRequest = FLootLockerBeginSteamPurchaseRedemptionRequest{
        SteamId,
        Currency,
        Language,
        CatalogItemId
    };
    return LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::CallAPI(PurchaseRequest, ULootLockerGameEndpoints::BeginSteamPurchaseRedemption, {}, {}, PlayerData, OnCompleted, LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerBeginSteamPurchaseRedemptionResponse& Response)
        {
            const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
            Response.isSuccess = JsonObject->GetBoolField(TEXT("success"));
        }));
}

FString ULootLockerPurchasesRequestHandler::BeginSteamPurchaseRedemptionForClass(const FLootLockerPlayerData& PlayerData, const int ClassId, const FString& SteamId, const FString& Currency, const FString& Language, const FString& CatalogItemId, const FLootLockerBeginSteamPurchaseRedemptionDelegate& OnCompleted)
{
    FLootLockerBeginSteamPurchaseRedemptionForClassRequest PurchaseRequest;
    PurchaseRequest.Steam_id = SteamId;
    PurchaseRequest.Currency = Currency;
    PurchaseRequest.Language = Language;
    PurchaseRequest.Catalog_item_id = CatalogItemId;
    PurchaseRequest.Class_id = ClassId;
    FString JsonString = LootLockerUtilities::UStructToJsonString(PurchaseRequest);
    JsonString.ReplaceInline(TEXT("Class_id"), TEXT("character_id"), ESearchCase::IgnoreCase);
    return LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::CallAPIUsingRawJSON(JsonString, ULootLockerGameEndpoints::BeginSteamPurchaseRedemption, {}, {}, PlayerData, OnCompleted, LLAPI<FLootLockerBeginSteamPurchaseRedemptionResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerBeginSteamPurchaseRedemptionResponse& Response)
        {
            const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
            Response.isSuccess = JsonObject->GetBoolField(TEXT("success"));
        }));
}

FString ULootLockerPurchasesRequestHandler::QuerySteamPurchaseRedemptionStatus(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerQuerySteamPurchaseRedemptionStatusDelegate& OnCompleted)
{
    return LLAPI<FLootLockerQuerySteamPurchaseRedemptionStatusResponse>::CallAPI(FLootLockerQuerySteamPurchaseRedemptionStatusRequest{ EntitlementId }, ULootLockerGameEndpoints::QuerySteamPurchaseRedemptionStatus, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::FinalizeSteamPurchaseRedemption(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerDefaultDelegate& OnCompleted)
{
    return LLAPI<FLootLockerResponse>::CallAPI(FLootLockerFinalizeSteamPurchaseRedemptionRequest{ EntitlementId }, ULootLockerGameEndpoints::FinalizeSteamPurchaseRedemption, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::RedeemEpicStorePurchase(const FLootLockerPlayerData& PlayerData, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompleted)
{
    FLootLockerRedeemEpicStorePurchaseForPlayerRequest PurchaseRequest{
        AccountId,
        BearerToken,
        EntitlementIds,
        SandboxId
    };

    return LLAPI<FLootLockerResponse>::CallAPI(PurchaseRequest, ULootLockerGameEndpoints::RedeemEpicStorePurchase, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::RedeemEpicStorePurchaseForCharacter(const FLootLockerPlayerData& PlayerData, const FString& CharacterId, const FString& AccountId, const FString& BearerToken, const TArray<FString>& EntitlementIds, const FString& SandboxId, const FLootLockerDefaultDelegate& OnCompleted)
{
    FLootLockerRedeemEpicStorePurchaseForCharacterRequest PurchaseRequest;
    PurchaseRequest.Account_id = AccountId;
	PurchaseRequest.Bearer_token = BearerToken;
	PurchaseRequest.Entitlement_ids = EntitlementIds;
	PurchaseRequest.Sandbox_id = SandboxId;
	PurchaseRequest.Character_id = CharacterId;

    return LLAPI<FLootLockerResponse>::CallAPI(PurchaseRequest, ULootLockerGameEndpoints::RedeemEpicStorePurchase, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForPlayer(const FLootLockerPlayerData& PlayerData, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultDelegate& OnCompleted)
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

    return LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(JsonString, ULootLockerGameEndpoints::RedeemPlayStationStorePurchase, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::RedeemPlayStationStorePurchaseForCharacter(const FLootLockerPlayerData& PlayerData, const FString& CharacterId, const FString& TransactionId, const FString& AuthCode, const FString& EntitlementLabel, const FString& ServiceLabel, const FString& ServiceName, const int Environment, const int UseCount, const FLootLockerDefaultDelegate& OnCompleted)
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

    return LLAPI<FLootLockerResponse>::CallAPIUsingRawJSON(JsonString, ULootLockerGameEndpoints::RedeemPlayStationStorePurchase, {}, {}, PlayerData, OnCompleted);
}
