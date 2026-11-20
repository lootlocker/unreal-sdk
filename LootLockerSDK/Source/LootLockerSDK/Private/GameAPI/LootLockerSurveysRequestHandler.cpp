// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerSurveysRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerSurveysRequestHandler::ListSurveys(const FLootLockerPlayerData& PlayerData, const FLootLockerListSurveysResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerListSurveysResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListSurveysEndpoint, {}, {}, PlayerData, OnComplete);
}

FString ULootLockerSurveysRequestHandler::GetSurvey(const FLootLockerPlayerData& PlayerData, const FString& SurveyId, const FLootLockerGetSurveyResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerGetSurveyResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::GetSurveyEndpoint, { SurveyId }, {}, PlayerData, OnComplete);
}

FString ULootLockerSurveysRequestHandler::CompleteSurvey(const FLootLockerPlayerData& PlayerData, const FString& SurveyId, const FLootLockerCompleteSurveyResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerCompleteSurveyResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::CompleteSurveyEndpoint, { SurveyId }, {}, PlayerData, OnComplete);
}

FLootLockerSurveyAnswer FLootLockerSurveyAnswer::FromText(const FString& MetadataKey, const FString& Value)
{
    FLootLockerSurveyAnswer Answer;
    Answer.Metadata_key = MetadataKey;
    Answer.Value = Value;
    Answer.Type = ELootLockerMetadataTypes::String;
    return Answer;
}

FLootLockerSurveyAnswer FLootLockerSurveyAnswer::FromNumber(const FString& MetadataKey, double Value)
{
    FLootLockerSurveyAnswer Answer;
    Answer.Metadata_key = MetadataKey;
    Answer.Value = FString::SanitizeFloat(Value, 0);
    Answer.Type = ELootLockerMetadataTypes::Number;
    return Answer;
}

FLootLockerSurveyAnswer FLootLockerSurveyAnswer::FromBool(const FString& MetadataKey, bool Value)
{
    FLootLockerSurveyAnswer Answer;
    Answer.Metadata_key = MetadataKey;
    Answer.Value = Value ? TEXT("true") : TEXT("false");
    Answer.Type = ELootLockerMetadataTypes::Bool;
    return Answer;
}

FLootLockerSurveyAnswer FLootLockerSurveyAnswer::FromMultiSelect(const FString& MetadataKey, const TArray<FString>& SelectedValues)
{
    TArray<TSharedPtr<FJsonValue>> JsonValues;
    JsonValues.Reserve(SelectedValues.Num());
    for (const FString& SelectedValue : SelectedValues)
    {
        JsonValues.Add(MakeShared<FJsonValueString>(SelectedValue));
    }

    FLootLockerSurveyAnswer Answer;
    Answer.Metadata_key = MetadataKey;
    Answer.Value = LootLockerUtilities::FStringFromJsonArray(JsonValues);
    Answer.Type = ELootLockerMetadataTypes::Json;
    return Answer;
}

FLootLockerMetadataEntry FLootLockerSurveyAnswer::MakeEntry() const
{
    switch (Type)
    {
    case ELootLockerMetadataTypes::Number:
    {
        double Number = 0.0;
        LexTryParseString(Number, *Value);
        return FLootLockerMetadataEntry::MakeFloatEntry(Metadata_key, {}, {}, static_cast<float>(Number));
    }
    case ELootLockerMetadataTypes::Bool:
    {
        const FString Trimmed = Value.TrimStartAndEnd();
        return FLootLockerMetadataEntry::MakeBoolEntry(Metadata_key, {}, {},
            Trimmed.Equals(TEXT("true"), ESearchCase::IgnoreCase) || Trimmed == TEXT("1"));
    }
    case ELootLockerMetadataTypes::Json:
    {
        TArray<TSharedPtr<FJsonValue>> JsonValues;
        LootLockerUtilities::JsonArrayFromFString(Value, JsonValues);
        return FLootLockerMetadataEntry::MakeJsonArrayEntry(Metadata_key, {}, {}, JsonValues);
    }
    case ELootLockerMetadataTypes::String:
    case ELootLockerMetadataTypes::Base64:
    default:
        // Base64 is folded into String: a survey question cannot produce one.
        return FLootLockerMetadataEntry::MakeStringEntry(Metadata_key, {}, {}, Value);
    }
}

FString ULootLockerSurveysRequestHandler::SubmitSurveyAnswers(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerSurveyAnswer>& Answers, const FLootLockerSetMetadataResponseDelegate& OnComplete)
{
    TArray<FLootLockerSetMetadataAction> Actions;
    Actions.Reserve(Answers.Num());
    for (const FLootLockerSurveyAnswer& Answer : Answers)
    {
        // An answer is a single upsert of the player's own metadata under the question's
        // metadata_key, so this reuses the metadata layer's typed entry factories rather than
        // declaring every answer as a String.
        Actions.Add(FLootLockerSetMetadataAction{ ELootLockerMetadataActions::Create_or_Update, Answer.MakeEntry() });
    }

    return ULootLockerMetadataRequestHandler::SetMetadata(PlayerData, ELootLockerMetadataSources::self, TEXT("self"), Actions, OnComplete);
}
