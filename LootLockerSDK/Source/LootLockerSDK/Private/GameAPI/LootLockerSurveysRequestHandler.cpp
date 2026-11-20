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

namespace
{
    // Build the metadata entry for an answer, using the metadata layer's typed factories rather
    // than declaring every answer as a String.
    FLootLockerMetadataEntry MakeEntryForAnswer(const FLootLockerSurveyAnswer& Answer)
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
            // Base64 is folded into String: a survey question cannot produce one.
            return FLootLockerMetadataEntry::MakeStringEntry(Answer.Metadata_key, {}, {}, Answer.Value);
        }
    }
}

FString ULootLockerSurveysRequestHandler::SubmitSurveyAnswers(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerSurveyAnswer>& Answers, const FLootLockerSetMetadataResponseDelegate& OnComplete)
{
    TArray<FLootLockerSetMetadataAction> Actions;
    Actions.Reserve(Answers.Num());
    for (const FLootLockerSurveyAnswer& Answer : Answers)
    {
        Actions.Add(FLootLockerSetMetadataAction{ ELootLockerMetadataActions::Create_or_Update, MakeEntryForAnswer(Answer) });
    }

    return ULootLockerMetadataRequestHandler::SetMetadata(PlayerData, ELootLockerMetadataSources::self, TEXT("self"), Actions, OnComplete);
}
