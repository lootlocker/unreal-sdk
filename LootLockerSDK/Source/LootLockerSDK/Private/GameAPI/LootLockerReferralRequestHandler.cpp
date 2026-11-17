// Copyright LootLocker AB

#include "GameAPI/LootLockerReferralRequestHandler.h"

#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

namespace
{
    // Builds the page/per_page query map shared by the referral list. Both are only sent when positive,
    // so the server applies its own defaults.
    TMultiMap<FString, FString> MakePageQueryParams(int32 Page, int32 PerPage)
    {
        TMultiMap<FString, FString> QueryParams;
        if (Page > 0) { QueryParams.Add("page", FString::FromInt(Page)); }
        if (PerPage > 0) { QueryParams.Add("per_page", FString::FromInt(PerPage)); }
        return QueryParams;
    }

    // FJsonObjectConverter only fills a struct field when the JSON key is present, so a null referrer_cap
    // leaves the member defaulted. This flag records which programs actually carried a cap.
    void MarkReferrerCaps(FLootLockerReferralInviteResponse& Response)
    {
        if (Response.FullTextFromServer.IsEmpty())
        {
            return;
        }

        const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
        if (!JsonObject.IsValid())
        {
            return;
        }

        const TArray<TSharedPtr<FJsonValue>>* ProgramsJson = nullptr;
        if (!JsonObject->TryGetArrayField(TEXT("programs"), ProgramsJson) || ProgramsJson == nullptr)
        {
            return;
        }

        const int32 ProgramCount = FMath::Min(ProgramsJson->Num(), Response.programs.Num());
        for (int32 ProgramIndex = 0; ProgramIndex < ProgramCount; ++ProgramIndex)
        {
            if (!(*ProgramsJson)[ProgramIndex].IsValid())
            {
                continue;
            }

            const TSharedPtr<FJsonObject>* ProgramObject = nullptr;
            if (!(*ProgramsJson)[ProgramIndex]->TryGetObject(ProgramObject) || ProgramObject == nullptr)
            {
                continue;
            }

            const TSharedPtr<FJsonValue>* CapValue = (*ProgramObject)->Values.Find(TEXT("referrer_cap"));
            Response.programs[ProgramIndex].HasReferrerCap = CapValue != nullptr && (*CapValue).IsValid() && (*CapValue)->Type != EJson::Null;
        }
    }
}

FString ULLReferralRequestHandler::GetInvite(const FLootLockerPlayerData& PlayerData, const FLootLockerReferralInviteResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerReferralInviteResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetReferralInviteEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerReferralInviteResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerReferralInviteResponse& Response)
        {
            if (Response.success)
            {
                MarkReferrerCaps(Response);
            }
        }));
}

FString ULLReferralRequestHandler::ListMyReferrals(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerReferralListResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerReferralListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListMyReferralsEndpoint, { }, MakePageQueryParams(Page, PerPage), PlayerData, OnCompletedRequest);
}
