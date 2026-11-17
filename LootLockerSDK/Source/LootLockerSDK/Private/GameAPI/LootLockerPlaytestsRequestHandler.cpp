// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerPlaytestsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

namespace
{
    // The acknowledge body is optional for documents without statements, so it is only built when
    // statement ids were supplied. Sending an empty object would be rejected by the server.
    FString AcknowledgeRequestToJsonString(const FLootLockerAcknowledgePlaytestDocumentRequest& Request)
    {
        const TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
        TArray<TSharedPtr<FJsonValue>> StatementIds;
        StatementIds.Reserve(Request.statement_ids.Num());
        for (const FString& StatementId : Request.statement_ids)
        {
            StatementIds.Add(MakeShared<FJsonValueString>(StatementId));
        }
        JsonObject->SetArrayField(TEXT("statement_ids"), StatementIds);

        return LootLockerUtilities::JsonObjectToString(JsonObject);
    }
}

FString ULootLockerPlaytestsRequestHandler::GetOnboardingStatus(const FLootLockerPlayerData& PlayerData, const FString& Subdomain, const FLootLockerPlaytestOnboardingStatusResponseDelegate& OnComplete)
{
    if (Subdomain.IsEmpty())
    {
        OnComplete.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerPlaytestOnboardingStatusResponse>(TEXT("subdomain is required"), 0, PlayerData.PlayerUlid));
        return FString();
    }

    return LLAPI<FLootLockerPlaytestOnboardingStatusResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetPlaytestOnboardingStatusEndpoint, { Subdomain }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerPlaytestsRequestHandler::CompleteOnboarding(const FLootLockerPlayerData& PlayerData, const FString& Subdomain, const FLootLockerCompletePlaytestOnboardingResponseDelegate& OnComplete)
{
    if (Subdomain.IsEmpty())
    {
        OnComplete.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerCompletePlaytestOnboardingResponse>(TEXT("subdomain is required"), 0, PlayerData.PlayerUlid));
        return FString();
    }

    return LLAPI<FLootLockerCompletePlaytestOnboardingResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::CompletePlaytestOnboardingEndpoint, { Subdomain }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerPlaytestsRequestHandler::AcknowledgeDocument(const FLootLockerPlayerData& PlayerData, const FString& Subdomain, const FString& DocumentId, const FLootLockerAcknowledgePlaytestDocumentRequest& Request, const FLootLockerAcknowledgePlaytestDocumentResponseDelegate& OnComplete)
{
    if (Subdomain.IsEmpty() || DocumentId.IsEmpty())
    {
        OnComplete.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerAcknowledgePlaytestDocumentResponse>(TEXT("subdomain and document_id are required"), 0, PlayerData.PlayerUlid));
        return FString();
    }

    if (Request.statement_ids.Num() == 0)
    {
        return LLAPI<FLootLockerAcknowledgePlaytestDocumentResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::AcknowledgePlaytestDocumentEndpoint, { Subdomain, DocumentId }, EmptyQueryParams, PlayerData, OnComplete);
    }

    FString ContentString = AcknowledgeRequestToJsonString(Request);
    return LLAPI<FLootLockerAcknowledgePlaytestDocumentResponse>::CallAPIUsingRawJSON(ContentString, ULootLockerGameEndpoints::AcknowledgePlaytestDocumentEndpoint, { Subdomain, DocumentId }, EmptyQueryParams, PlayerData, OnComplete);
}
