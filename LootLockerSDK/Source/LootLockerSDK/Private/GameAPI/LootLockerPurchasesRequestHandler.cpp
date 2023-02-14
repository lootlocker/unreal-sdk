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
    // This is handled outside of the template due to the usage of a top-level json-array
    TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
    for (auto Item : PurchaseData)
    {
        TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
        if (FJsonObjectConverter::UStructToJsonObject(FLootLockerAssetPurchaseData::StaticStruct(), &Item, ItemJson, 0, 0))
        {
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
        }
    }

    FString ContentString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemsJsonArray, Writer);
    
    LLAPI<FLootLockerPurchaseResponse>::CallAPIUsingRawJSON(HttpClient, ContentString, ULootLockerGameEndpoints::PurchaseEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    // This is handled outside of the template due to the usage of a top-level json-array
    TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
    for (auto Item : PurchaseData)
    {
        TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
        if (FJsonObjectConverter::UStructToJsonObject(FLootLockerAndroidAssetPurchaseData::StaticStruct(), &Item, ItemJson, 0, 0))
        {
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
        }
    }

    FString ContentString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemsJsonArray, Writer);
    
    LLAPI<FLootLockerPurchaseResponse>::CallAPIUsingRawJSON(HttpClient, ContentString, ULootLockerGameEndpoints::AndroidPurchaseEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegateBP& OnCompletedRequestBP, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    // This is handled outside of the template due to the usage of a top-level json-array
    TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
    for (auto Item : PurchaseData)
    {
        TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
        if (FJsonObjectConverter::UStructToJsonObject(FLootLockerVerifyPurchaseIosData::StaticStruct(), &Item, ItemJson, 0, 0))
        {
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
        }
    }

    FString ContentString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
    FJsonSerializer::Serialize(ItemsJsonArray, Writer);
    
    LLAPI<FLootLockerPurchaseResponse>::CallAPIUsingRawJSON(HttpClient, ContentString, ULootLockerGameEndpoints::IOSPurchaseEndpoint, { }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegateBP& OnCompletedRequestBP, const FPurchaseStatusResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerPurchaseStatusResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::PollingOrderStatusEndpoint, {  PurchaseId}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegateBP& OnCompletedRequestBP, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerActivateRentalAssetResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ActivateRentalAssetEndpoint, { AssetId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerPurchasesRequestHandler::GetOrderDetails(int32 OrderId, const bool noProducts, const FOrderStatusDetailsBP &OnCompleteBP, const FOrderStatusDetailsDelegate &OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    QueryParams.Add(TEXT("no_products"), noProducts ? TEXT("true") : TEXT("false"));
    LLAPI<FLootLockerOrderDetailsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOrderDetailsEndpoint, { OrderId }, QueryParams, OnCompleteBP, OnComplete);
}
