// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerProgressionsRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerProgressionsRequestHandler::HttpClient = nullptr;

ULootLockerProgressionsRequestHandler::ULootLockerProgressionsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerProgressionsRequestHandler::GetPlayerProgressions(const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseBP& OnCompletedRequestBP /*= FLootLockerPaginatedPlayerProgressionsResponseBP()*/, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete /*= FLootLockerPaginatedPlayerProgressionsResponseDelegate()*/)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("after", After); }

    LLAPI<FLootLockerPaginatedPlayerProgressionResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllPlayerProgressions, {}, QueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::GetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseBP& OnCompletedRequestBP /*= FLootLockerPlayerProgressionResponseBP()*/, const FLootLockerPlayerProgressionResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionResponseDelegate()*/)
{
    LLAPI<FLootLockerPlayerProgressionResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSinglePlayerProgression, { ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}
void ULootLockerProgressionsRequestHandler::AddPointsToPlayerProgression(const FString& ProgressionKey, const int32 Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerPlayerProgressionWithRewardsResponseBP()*/, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionWithRewardsResponseDelegate()*/)
{
    LLAPI<FLootLockerPlayerProgressionWithRewardsResponse>::CallAPI(HttpClient, FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::AddPointsToPlayerProgression, { ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::SubtractPointsFromPlayerProgression(const FString& ProgressionKey, const int32 Amount, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerPlayerProgressionWithRewardsResponseBP()*/, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionWithRewardsResponseDelegate()*/)
{
    LLAPI<FLootLockerPlayerProgressionWithRewardsResponse>::CallAPI(HttpClient, FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::SubtractPointsFromPlayerProgression, { ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::ResetPlayerProgression(const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerPlayerProgressionWithRewardsResponseBP()*/, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionWithRewardsResponseDelegate()*/)
{
    LLAPI<FLootLockerPlayerProgressionWithRewardsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ResetPlayerProgression, { ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::DeletePlayerProgression(const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP /*= FLootLockerDeleteProgressionBP()*/, const FLootLockerDeleteProgressionDelegate& OnComplete /*= FLootLockerDeleteProgressionDelegate()*/)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeletePlayerProgression, { ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::GetCharacterProgressions(const int32 CharacterId, const int32 Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseBP& OnCompletedRequestBP /*= FLootLockerPaginatedCharacterProgressionsResponseBP()*/, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete /*= FLootLockerPaginatedCharacterProgressionsResponseDelegate()*/)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("after", After); }

    LLAPI<FLootLockerPaginatedCharacterProgressionResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllCharacterProgressions, { CharacterId }, QueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::GetCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseBP& OnCompletedRequestBP /*= FLootLockerCharacterProgressionResponseBP()*/, const FLootLockerCharacterProgressionResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionResponseDelegate()*/)
{
    LLAPI<FLootLockerCharacterProgressionResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::AddPointsToCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const int32 Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerCharacterProgressionWithRewardsResponseBP()*/, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionWithRewardsResponseDelegate()*/)
{
    LLAPI<FLootLockerCharacterProgressionWithRewardsResponse>::CallAPI(HttpClient, FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::AddPointsToCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::SubtractPointsFromCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const int32 Amount, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerCharacterProgressionWithRewardsResponseBP()*/, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionWithRewardsResponseDelegate()*/)
{
    LLAPI<FLootLockerCharacterProgressionWithRewardsResponse>::CallAPI(HttpClient, FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::SubtractPointsFromCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::ResetCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseBP& OnCompletedRequestBP /*= FLootLockerCharacterProgressionWithRewardsResponseBP()*/, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionWithRewardsResponseDelegate()*/)
{
    LLAPI<FLootLockerCharacterProgressionWithRewardsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ResetCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::DeleteCharacterProgression(const int32 CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP /*= FLootLockerDeleteProgressionBP()*/, const FLootLockerDeleteProgressionDelegate& OnComplete /*= FLootLockerDeleteProgressionDelegate()*/)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}


void ULootLockerProgressionsRequestHandler::GetProgressions(const int32 Count, const FString& After, const FLootLockerPaginatedProgressionsResponseBP& OnCompletedRequestBP /*= FLootLockerPaginatedProgressionsResponseBP()*/, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete /*= FLootLockerPaginatedProgressionsResponseDelegate()*/)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("after", After); }

    LLAPI<FLootLockerPaginatedProgressionsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllProgressions, {}, QueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::GetProgression(const FString& ProgressionKey, const FLootLockerProgressionResponseBP& OnCompletedRequestBP /*= FLootLockerProgressionResponseBP()*/, const FLootLockerProgressionResponseDelegate& OnComplete /*= FLootLockerProgressionResponseDelegate()*/)
{
    LLAPI<FLootLockerProgressionResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleProgression, { ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::GetProgressionTiers(const FString& ProgressionKey, const int32 Count, const int32 After, const FLootLockerPaginatedProgressionTiersResponseBP& OnCompletedRequestBP /*= FLootLockerPaginatedProgressionTiersResponseBP()*/, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete /*= FLootLockerPaginatedProgressionTiersResponseDelegate()*/)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (After > 0) { QueryParams.Add("after", FString::FromInt(After)); }
    LLAPI<FLootLockerPaginatedProgressionTiersResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetProgressionTiers, { ProgressionKey }, QueryParams, OnCompletedRequestBP, OnComplete);
}

void ULootLockerProgressionsRequestHandler::GetInstanceProgressions(const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseBP& OnCompletedRequestBP, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("after", After); }

    LLAPI<FLootLockerPaginatedInstanceProgressionResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllInstanceProgressions, { AssetInstanceId }, QueryParams, OnCompletedRequestBP, OnComplete);

}

void ULootLockerProgressionsRequestHandler::GetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseBP& OnCompletedRequestBP, const FLootLockerInstanceProgressionResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerInstanceProgressionResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);

}

void ULootLockerProgressionsRequestHandler::AddPointsToInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerInstanceProgressionWithRewardsResponse>::CallAPI(HttpClient, FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::AddPointsToInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);

}

void ULootLockerProgressionsRequestHandler::SubtractPointsFromInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerInstanceProgressionWithRewardsResponse>::CallAPI(HttpClient, FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::SubtractPointsFromInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);

}

void ULootLockerProgressionsRequestHandler::ResetInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseBP& OnCompletedRequestBP, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete)
{
    LLAPI<FLootLockerInstanceProgressionWithRewardsResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ResetInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);

}

void ULootLockerProgressionsRequestHandler::DeleteInstanceProgression(const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionBP& OnCompletedRequestBP, const FLootLockerDeleteProgressionDelegate& OnComplete)
{
    LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, OnCompletedRequestBP, OnComplete);

}
