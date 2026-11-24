// Copyright LootLocker AB

#include "GameAPI/LootLockerReferralRequestHandler.h"

#include "LootLockerGameEndpoints.h"
#include "LootLockerLogger.h"
#include "Utils/LootLockerUtilities.h"

namespace
{
    // FJsonObjectConverter skips a JSON null entirely, leaving the struct member at its default. That makes
    // an absent value indistinguishable from a real one, so these flags record which keys actually carried a
    // value. Non-null values are converted by FJsonObjectConverter itself.
    bool HasNonNullField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName)
    {
        if (!JsonObject.IsValid())
        {
            return false;
        }

        const TSharedPtr<FJsonValue> Value = JsonObject->TryGetField(FieldName);
        return Value.IsValid() && Value->Type != EJson::Null;
    }

    // Collects the objects of a top-level array field, or an empty array when the key is absent.
    TArray<TSharedPtr<FJsonObject>> GetObjectArrayField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName)
    {
        TArray<TSharedPtr<FJsonObject>> Objects;
        const TArray<TSharedPtr<FJsonValue>>* Values = nullptr;
        if (!JsonObject.IsValid() || !JsonObject->TryGetArrayField(FieldName, Values) || Values == nullptr)
        {
            return Objects;
        }

        for (const TSharedPtr<FJsonValue>& Value : *Values)
        {
            const TSharedPtr<FJsonObject>* Object = nullptr;
            if (Value.IsValid() && Value->TryGetObject(Object) && Object != nullptr)
            {
                Objects.Add(*Object);
            }
        }
        return Objects;
    }
}

void FLootLockerReferralInviteResponse::PopulateConvenienceStructures()
{
    const TSharedPtr<FJsonObject> ResponseAsJson = LootLockerUtilities::JsonObjectFromFString(FullTextFromServer);
    if (!ResponseAsJson.IsValid())
    {
        return;
    }

    const TArray<TSharedPtr<FJsonObject>> ProgramsJson = GetObjectArrayField(ResponseAsJson, TEXT("programs"));
    if (ProgramsJson.Num() != programs.Num())
    {
        FLootLockerLogger::LogWarning("Failed to properly parse referral invite programs");
        return;
    }

    for (int32 Index = 0; Index < programs.Num(); ++Index)
    {
        programs[Index].HasReferrerCap = HasNonNullField(ProgramsJson[Index], TEXT("referrer_cap"));
    }
}

void FLootLockerReferralListResponse::PopulateConvenienceStructures()
{
    const TSharedPtr<FJsonObject> ResponseAsJson = LootLockerUtilities::JsonObjectFromFString(FullTextFromServer);
    if (!ResponseAsJson.IsValid())
    {
        return;
    }

    const TArray<TSharedPtr<FJsonObject>> ReferralsJson = GetObjectArrayField(ResponseAsJson, TEXT("referrals"));
    if (ReferralsJson.Num() != referrals.Num())
    {
        FLootLockerLogger::LogWarning("Failed to properly parse referrals");
        return;
    }

    for (int32 Index = 0; Index < referrals.Num(); ++Index)
    {
        referrals[Index].HasRefereePublicUid = HasNonNullField(ReferralsJson[Index], TEXT("referee_public_uid"));
        referrals[Index].HasQualifiedAt = HasNonNullField(ReferralsJson[Index], TEXT("qualified_at"));
    }
}

FString ULLReferralRequestHandler::GetInvite(const FLootLockerPlayerData& PlayerData, const FLootLockerReferralInviteResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerReferralInviteResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetReferralInviteEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerReferralInviteResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerReferralInviteResponse& Response)
        {
            if (Response.success)
            {
                Response.PopulateConvenienceStructures();
            }
        }));
}

FString ULLReferralRequestHandler::ListMyReferrals(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerReferralListResponseDelegate& OnCompletedRequest)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) { QueryParams.Add("page", FString::FromInt(Page)); }
    if (PerPage > 0) { QueryParams.Add("per_page", FString::FromInt(PerPage)); }

    return LLAPI<FLootLockerReferralListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListMyReferralsEndpoint, { }, QueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerReferralListResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerReferralListResponse& Response)
        {
            if (Response.success)
            {
                Response.PopulateConvenienceStructures();
            }
        }));
}
