// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerPurchasesRequestHandler.h"

#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerStateData.h"
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

            Response.isSuccess = JsonObject->HasField(TEXT("success")) ? JsonObject->GetBoolField(TEXT("success")) : false;
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
            Response.isSuccess = JsonObject->HasField(TEXT("success")) ? JsonObject->GetBoolField(TEXT("success")) : false;
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

FString ULootLockerPurchasesRequestHandler::RefundByEntitlementIds(const FLootLockerPlayerData& PlayerData, const TArray<FString>& EntitlementIds, const FLootLockerRefundByEntitlementIdsDelegate& OnCompleted)
{
    return LLAPI<FLootLockerRefundByEntitlementIdsResponse>::CallAPI(FLootLockerRefundByEntitlementIdsRequest{ EntitlementIds }, ULootLockerGameEndpoints::RefundByEntitlementIds, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::CreateStripeCheckoutSession(const FLootLockerPlayerData& PlayerData, const FString& CatalogItemId, const FLootLockerCreateStripeCheckoutSessionDelegate& OnCompleted)
{
    const FLootLockerCreateStripeCheckoutSessionRequest Request{ CatalogItemId };
    return LLAPI<FLootLockerCreateStripeCheckoutSessionResponse>::CallAPI(Request, ULootLockerGameEndpoints::CreateStripeCheckoutSession, {}, {}, PlayerData, OnCompleted);
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

//==================================================
// Async Purchase Static Data
//==================================================

TMap<FString, FLootLockerAsyncPurchaseProcess> ULootLockerPurchasesRequestHandler::AsyncPurchaseProcesses = TMap<FString, FLootLockerAsyncPurchaseProcess>();

FLootLockerAsyncPurchaseProcess::FLootLockerAsyncPurchaseProcess(float _PollingIntervalSeconds, float TimeoutAfterMinutes)
    : TimeoutTime(FDateTime::UtcNow() + FTimespan::FromMinutes(TimeoutAfterMinutes))
    , PollingIntervalSeconds(FMath::Max(1.0f, _PollingIntervalSeconds))
{
}

//==================================================
// Async Purchase Primitive Methods
//==================================================

FString ULootLockerPurchasesRequestHandler::InitiateAsyncPurchase(const FLootLockerPlayerData& PlayerData, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair>& Items, const FLootLockerAsyncPurchaseInitiatedDelegate& OnCompleted)
{
    return LLAPI<FLootLockerAsyncPurchaseInitiatedResponse>::CallAPI(FLootLockerPurchaseCatalogItemRequest{ WalletId, Items }, ULootLockerGameEndpoints::InitiateAsyncPurchase, {}, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::GetAsyncPurchaseStatus(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FLootLockerAsyncPurchaseStatusDelegate& OnCompleted)
{
    return LLAPI<FLootLockerAsyncPurchaseStatusResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::PollAsyncPurchaseStatus, { EntitlementId }, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::GetAsyncPurchaseStatus(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const LLAPI<FLootLockerAsyncPurchaseStatusResponse>::FResponseInspectorCallback& OnCompleted)
{
    return LLAPI<FLootLockerAsyncPurchaseStatusResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::PollAsyncPurchaseStatus, { EntitlementId }, {}, PlayerData, OnCompleted);
}

FString ULootLockerPurchasesRequestHandler::RetryAsyncPurchase(const FLootLockerPlayerData& PlayerData, const FString& EntitlementId, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair>& Items, const FLootLockerAsyncPurchaseInitiatedDelegate& OnCompleted)
{
    return LLAPI<FLootLockerAsyncPurchaseInitiatedResponse>::CallAPI(FLootLockerPurchaseCatalogItemRequest{ WalletId, Items }, ULootLockerGameEndpoints::RetryAsyncPurchase, { EntitlementId }, {}, PlayerData, OnCompleted);
}

//==================================================
// Async Purchase Polling
//==================================================

FString ULootLockerPurchasesRequestHandler::StartAsyncPurchasePolling(const FLootLockerPlayerData& PlayerData, const FString& WalletId, const TArray<FLootLockerCatalogItemAndQuantityPair>& Items, const FLootLockerAsyncPurchaseStatusDelegate& OnStatusUpdate, const FLootLockerAsyncPurchaseStatusDelegate& OnComplete, float PollingIntervalSeconds, float TimeoutAfterMinutes)
{
    const FString ProcessID = FGuid::NewGuid().ToString();
    FLootLockerAsyncPurchaseProcess NewProcess(PollingIntervalSeconds, TimeoutAfterMinutes);
    NewProcess.WalletId = WalletId;
    NewProcess.Items = Items;
    NewProcess.PlayerData = PlayerData;
    AsyncPurchaseProcesses.Add(ProcessID, NewProcess);

    InitiateAsyncPurchase(PlayerData, WalletId, Items, FLootLockerAsyncPurchaseInitiatedDelegate::CreateLambda([ProcessID, OnStatusUpdate, OnComplete](FLootLockerAsyncPurchaseInitiatedResponse InitiateResponse)
    {
        FLootLockerAsyncPurchaseProcess* _processPtr = AsyncPurchaseProcesses.Find(ProcessID);
        if (nullptr == _processPtr)
        {
            return;
        }
        if (!InitiateResponse.success)
        {
            FLootLockerAsyncPurchaseStatusResponse ErrorResponse;
            ErrorResponse.success = false;
            ErrorResponse.StatusCode = InitiateResponse.StatusCode;
            ErrorResponse.FullTextFromServer = InitiateResponse.FullTextFromServer;
            ErrorResponse.ErrorData = InitiateResponse.ErrorData;
            OnComplete.ExecuteIfBound(ErrorResponse);
            KillAsyncPurchaseProcess(ProcessID);
            return;
        }
        _processPtr->EntitlementId = InitiateResponse.Entitlement_id;
        ContinualAsyncPurchasePollAction(ProcessID, OnStatusUpdate, OnComplete);
    }));

    return ProcessID;
}

void ULootLockerPurchasesRequestHandler::CancelAsyncPurchasePolling(const FString& ProcessID)
{
    FLootLockerAsyncPurchaseProcess* _processPtr = AsyncPurchaseProcesses.Find(ProcessID);
    if (nullptr != _processPtr)
    {
        _processPtr->ShouldCancel = true;
    }
}

FString ULootLockerPurchasesRequestHandler::ContinualAsyncPurchasePollAction(const FString& ProcessID, const FLootLockerAsyncPurchaseStatusDelegate& OnStatusUpdate, const FLootLockerAsyncPurchaseStatusDelegate& OnComplete)
{
    const FLootLockerAsyncPurchaseProcess* _processPtr = AsyncPurchaseProcesses.Find(ProcessID);
    if (nullptr == _processPtr)
    {
        return TEXT("");
    }
    const FLootLockerAsyncPurchaseProcess& _process = *_processPtr;

    if (_process.TimeoutTime <= FDateTime::UtcNow())
    {
        FLootLockerAsyncPurchaseStatusResponse TimedOutResponse;
        TimedOutResponse.success = false;
        TimedOutResponse.Status = ELootLockerAsyncPurchaseStatus::TimedOut;
        OnComplete.ExecuteIfBound(TimedOutResponse);
        KillAsyncPurchaseProcess(ProcessID);
        return TEXT("");
    }

    if (_process.ShouldCancel)
    {
        FLootLockerAsyncPurchaseStatusResponse CancelledResponse;
        CancelledResponse.success = false;
        CancelledResponse.Status = ELootLockerAsyncPurchaseStatus::Cancelled;
        OnComplete.ExecuteIfBound(CancelledResponse);
        KillAsyncPurchaseProcess(ProcessID);
        return TEXT("");
    }

    return GetAsyncPurchaseStatus(_process.PlayerData, _process.EntitlementId, LLAPI<FLootLockerAsyncPurchaseStatusResponse>::FResponseInspectorCallback::CreateLambda([ProcessID, OnStatusUpdate, OnComplete](FLootLockerAsyncPurchaseStatusResponse& StatusResponse)
    {
        FLootLockerAsyncPurchaseProcess* _innerProcessPtr = AsyncPurchaseProcesses.Find(ProcessID);
        if (nullptr == _innerProcessPtr)
        {
            return;
        }
        FLootLockerAsyncPurchaseProcess& _innerProcess = *_innerProcessPtr;

        auto _scheduleNextPoll = [OnStatusUpdate, OnComplete](FTimerHandle& TimerHandle, const float TimeToNextPoll, const FString& PID)
        {
            FTimerDelegate TimerDelegate;
            TimerDelegate.BindLambda([OnStatusUpdate, OnComplete, PID]()
            {
                ContinualAsyncPurchasePollAction(PID, OnStatusUpdate, OnComplete);
            });
            SetAsyncPurchaseTimer(TimerHandle, TimerDelegate, TimeToNextPoll);
        };

        if (!StatusResponse.success)
        {
            if (StatusResponse.StatusCode >= 500 && StatusResponse.StatusCode <= 599 && _innerProcess.Retries < _innerProcess.RetryLimit)
            {
                _innerProcess.Retries++;
                _scheduleNextPoll(_innerProcess.AsyncPurchaseProcessTimerHandle, _innerProcess.PollingIntervalSeconds, ProcessID);
                return;
            }
            OnComplete.ExecuteIfBound(StatusResponse);
            KillAsyncPurchaseProcess(ProcessID);
            return;
        }

        _innerProcess.Retries = 0;

        if (ELootLockerAsyncPurchaseStatus::Active == StatusResponse.Status || ELootLockerAsyncPurchaseStatus::Failed == StatusResponse.Status)
        {
            OnComplete.ExecuteIfBound(StatusResponse);
            KillAsyncPurchaseProcess(ProcessID);
            return;
        }

        // Still pending — notify and reschedule
        OnStatusUpdate.ExecuteIfBound(StatusResponse);
        _scheduleNextPoll(_innerProcess.AsyncPurchaseProcessTimerHandle, _innerProcess.PollingIntervalSeconds, ProcessID);
    }));
}

void ULootLockerPurchasesRequestHandler::KillAsyncPurchaseProcess(const FString& ProcessID)
{
    FLootLockerAsyncPurchaseProcess* _processPtr = AsyncPurchaseProcesses.Find(ProcessID);
    if (nullptr == _processPtr)
    {
        return;
    }
    ClearAsyncPurchaseTimer(_processPtr->AsyncPurchaseProcessTimerHandle);
    AsyncPurchaseProcesses.Remove(ProcessID);
}

void ULootLockerPurchasesRequestHandler::SetAsyncPurchaseTimer(FTimerHandle& TimerHandle, const FTimerDelegate& Delegate, float Time)
{
    if (GEngine && GEngine->GameViewport && GEngine->GameViewport->GetWorld())
    {
        GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, Time, false);
    }
}

void ULootLockerPurchasesRequestHandler::ClearAsyncPurchaseTimer(FTimerHandle& TimerHandle)
{
    if (GEngine && GEngine->GameViewport && GEngine->GameViewport->GetWorld())
    {
        GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(TimerHandle, -1.0f, false);
    }
}

//==================================================
// Async Blueprint Node
//==================================================

ULootLockerAsyncPollAsyncPurchase* ULootLockerAsyncPollAsyncPurchase::AsyncPollAsyncPurchase(UObject* WorldContextObject, FString PlayerWithUlid, FString InWalletId, TArray<FLootLockerCatalogItemAndQuantityPair> InItems, float InPollingIntervalSeconds, float InTimeoutAfterMinutes)
{
    ULootLockerAsyncPollAsyncPurchase* Instance = NewObject<ULootLockerAsyncPollAsyncPurchase>();
    Instance->ForPlayerWithUlid = PlayerWithUlid;
    Instance->WalletId = InWalletId;
    Instance->Items = InItems;
    Instance->PollingIntervalInSeconds = InPollingIntervalSeconds;
    Instance->TimeoutAfterMinutes = InTimeoutAfterMinutes;
    Instance->RegisterWithGameInstance(WorldContextObject);
    return Instance;
}

void ULootLockerAsyncPollAsyncPurchase::Activate()
{
    Super::Activate();
    const TSharedPtr<FLootLockerPlayerData> PlayerDataPtr = ULootLockerStateData::GetStateForPlayerOrDefaultFromCache(ForPlayerWithUlid);
    FLootLockerPlayerData PlayerData = PlayerDataPtr.IsValid() ? *PlayerDataPtr : FLootLockerPlayerData();

    ProcessID = ULootLockerPurchasesRequestHandler::StartAsyncPurchasePolling(
        PlayerData,
        WalletId,
        Items,
        FLootLockerAsyncPurchaseStatusDelegate::CreateLambda([this](FLootLockerAsyncPurchaseStatusResponse Response)
        {
            OnPending.Broadcast(ProcessID, Response);
        }),
        FLootLockerAsyncPurchaseStatusDelegate::CreateLambda([this](FLootLockerAsyncPurchaseStatusResponse Response)
        {
            if (Response.success && Response.Status == ELootLockerAsyncPurchaseStatus::Active)
            {
                OnActive.Broadcast(ProcessID, Response);
            }
            else if (Response.success && Response.Status == ELootLockerAsyncPurchaseStatus::Failed)
            {
                OnFailed.Broadcast(ProcessID, Response);
            }
            else if (Response.Status == ELootLockerAsyncPurchaseStatus::TimedOut)
            {
                OnTimedOut.Broadcast(ProcessID, Response);
            }
            else if (Response.Status == ELootLockerAsyncPurchaseStatus::Cancelled)
            {
                OnCancelled.Broadcast(ProcessID, Response);
            }
            else
            {
                OnFailed.Broadcast(ProcessID, Response);
            }
            SetReadyToDestroy();
        }),
        PollingIntervalInSeconds,
        TimeoutAfterMinutes
    );
}
