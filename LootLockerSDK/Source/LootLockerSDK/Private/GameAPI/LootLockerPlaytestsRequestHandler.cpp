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

FLootLockerPlaytestAnswerSubmission FLootLockerPlaytestAnswerSubmission::FromText(const FString& MetadataKey, const FString& Value)
{
    FLootLockerPlaytestAnswerSubmission Answer;
    Answer.Metadata_key = MetadataKey;
    Answer.Value = Value;
    Answer.Type = ELootLockerMetadataTypes::String;
    return Answer;
}

FLootLockerPlaytestAnswerSubmission FLootLockerPlaytestAnswerSubmission::FromNumber(const FString& MetadataKey, double Value)
{
    FLootLockerPlaytestAnswerSubmission Answer;
    Answer.Metadata_key = MetadataKey;
    Answer.Value = FString::SanitizeFloat(Value, 0);
    Answer.Type = ELootLockerMetadataTypes::Number;
    return Answer;
}

FLootLockerPlaytestAnswerSubmission FLootLockerPlaytestAnswerSubmission::FromBool(const FString& MetadataKey, bool Value)
{
    FLootLockerPlaytestAnswerSubmission Answer;
    Answer.Metadata_key = MetadataKey;
    Answer.Value = Value ? TEXT("true") : TEXT("false");
    Answer.Type = ELootLockerMetadataTypes::Bool;
    return Answer;
}

FLootLockerPlaytestAnswerSubmission FLootLockerPlaytestAnswerSubmission::FromMultiSelect(const FString& MetadataKey, const TArray<FString>& SelectedValues)
{
    TArray<TSharedPtr<FJsonValue>> JsonValues;
    JsonValues.Reserve(SelectedValues.Num());
    for (const FString& SelectedValue : SelectedValues)
    {
        JsonValues.Add(MakeShared<FJsonValueString>(SelectedValue));
    }

    FLootLockerPlaytestAnswerSubmission Answer;
    Answer.Metadata_key = MetadataKey;
    Answer.Value = LootLockerUtilities::FStringFromJsonArray(JsonValues);
    Answer.Type = ELootLockerMetadataTypes::Json;
    return Answer;
}

namespace
{
    // Build the metadata entry for an answer, using the metadata layer's typed factories rather
    // than declaring every answer as a String.
    FLootLockerMetadataEntry MakeEntryForAnswer(const FLootLockerPlaytestAnswerSubmission& Answer)
    {
        switch (Answer.Type)
        {
        case ELootLockerMetadataTypes::Number:
        {
            double Number = 0.0;
            if (!LexTryParseString(Number, *Answer.Value))
            {
                // Not a number. The struct is BlueprintReadWrite, so a caller can bypass
                // FromNumber; storing a String instead of silently coercing to 0 keeps the
                // answer as typed rather than persisting a wrong value.
                return FLootLockerMetadataEntry::MakeStringEntry(Answer.Metadata_key, {}, {}, Answer.Value);
            }
            return FLootLockerMetadataEntry::MakeFloatEntry(Answer.Metadata_key, {}, {}, static_cast<float>(Number));
        }
        case ELootLockerMetadataTypes::Bool:
        {
            const FString Trimmed = Answer.Value.TrimStartAndEnd();
            return FLootLockerMetadataEntry::MakeBoolEntry(Answer.Metadata_key, {}, {},
                Trimmed.Equals(TEXT("true"), ESearchCase::IgnoreCase) || Trimmed == TEXT("1"));
        }
        case ELootLockerMetadataTypes::Json:
        {
            TArray<TSharedPtr<FJsonValue>> JsonValues;
            LootLockerUtilities::JsonArrayFromFString(Answer.Value, JsonValues);
            return FLootLockerMetadataEntry::MakeJsonArrayEntry(Answer.Metadata_key, {}, {}, JsonValues);
        }
        case ELootLockerMetadataTypes::String:
        case ELootLockerMetadataTypes::Base64:
        default:
            // Base64 is folded into String: a playtest question cannot produce one.
            return FLootLockerMetadataEntry::MakeStringEntry(Answer.Metadata_key, {}, {}, Answer.Value);
        }
    }
}

FString ULootLockerPlaytestsRequestHandler::SubmitAnswers(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerPlaytestAnswerSubmission>& Answers, const FLootLockerSetMetadataResponseDelegate& OnComplete)
{
    TArray<FLootLockerSetMetadataAction> Actions;
    Actions.Reserve(Answers.Num());
    for (const FLootLockerPlaytestAnswerSubmission& Answer : Answers)
    {
        Actions.Add(FLootLockerSetMetadataAction{ ELootLockerMetadataActions::Create_or_Update, MakeEntryForAnswer(Answer) });
    }

    return ULootLockerMetadataRequestHandler::SetMetadata(PlayerData, ELootLockerMetadataSources::self, TEXT("self"), Actions, OnComplete);
}
