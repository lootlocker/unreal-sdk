// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerProgressionsRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

FString ULootLockerProgressionsRequestHandler::GetPlayerProgressions(const FLootLockerPlayerData& PlayerData, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete /*= FLootLockerPaginatedPlayerProgressionsResponseDelegate()*/)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("after", After); }

    return LLAPI<FLootLockerPaginatedPlayerProgressionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllPlayerProgressions, {}, QueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::GetPlayerProgression(const FLootLockerPlayerData& PlayerData, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionResponseDelegate()*/)
{
    return LLAPI<FLootLockerPlayerProgressionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSinglePlayerProgression, { ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}
FString ULootLockerProgressionsRequestHandler::AddPointsToPlayerProgression(const FLootLockerPlayerData& PlayerData, const FString& ProgressionKey, const int32 Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionWithRewardsResponseDelegate()*/)
{
    return LLAPI<FLootLockerPlayerProgressionWithRewardsResponse>::CallAPI(FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::AddPointsToPlayerProgression, { ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::SubtractPointsFromPlayerProgression(const FLootLockerPlayerData& PlayerData, const FString& ProgressionKey, const int32 Amount, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionWithRewardsResponseDelegate()*/)
{
    return LLAPI<FLootLockerPlayerProgressionWithRewardsResponse>::CallAPI(FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::SubtractPointsFromPlayerProgression, { ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::ResetPlayerProgression(const FLootLockerPlayerData& PlayerData, const FString& ProgressionKey, const FLootLockerPlayerProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerPlayerProgressionWithRewardsResponseDelegate()*/)
{
    return LLAPI<FLootLockerPlayerProgressionWithRewardsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ResetPlayerProgression, { ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::DeletePlayerProgression(const FLootLockerPlayerData& PlayerData, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete /*= FLootLockerDeleteProgressionDelegate()*/)
{
    return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeletePlayerProgression, { ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::GetOtherPlayersProgressions(const FLootLockerPlayerData& PlayerData, const FString& PlayerUlid, const int32 Count, const FString& After, const FLootLockerPaginatedPlayerProgressionsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("after", After); }

    return LLAPI<FLootLockerPaginatedPlayerProgressionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllOtherPlayersProgressions, { PlayerUlid }, QueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::GetOtherPlayersProgression(const FLootLockerPlayerData& PlayerData, const FString& PlayerUlid, const FString& ProgressionKey, const FLootLockerPlayerProgressionResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerPlayerProgressionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleOtherPlayersProgression, { ProgressionKey, PlayerUlid }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::GetCharacterProgressions(const FLootLockerPlayerData& PlayerData, const int32 CharacterId, const int32 Count, const FString& After, const FLootLockerPaginatedCharacterProgressionsResponseDelegate& OnComplete /*= FLootLockerPaginatedCharacterProgressionsResponseDelegate()*/)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("after", After); }

    return LLAPI<FLootLockerPaginatedCharacterProgressionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllCharacterProgressions, { CharacterId }, QueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::GetCharacterProgression(const FLootLockerPlayerData& PlayerData, const int32 CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionResponseDelegate()*/)
{
    return LLAPI<FLootLockerCharacterProgressionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::AddPointsToCharacterProgression(const FLootLockerPlayerData& PlayerData, const int32 CharacterId, const FString& ProgressionKey, const int32 Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionWithRewardsResponseDelegate()*/)
{
    return LLAPI<FLootLockerCharacterProgressionWithRewardsResponse>::CallAPI(FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::AddPointsToCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::SubtractPointsFromCharacterProgression(const FLootLockerPlayerData& PlayerData, const int32 CharacterId, const FString& ProgressionKey, const int32 Amount, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionWithRewardsResponseDelegate()*/)
{
    return LLAPI<FLootLockerCharacterProgressionWithRewardsResponse>::CallAPI(FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::SubtractPointsFromCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::ResetCharacterProgression(const FLootLockerPlayerData& PlayerData, const int32 CharacterId, const FString& ProgressionKey, const FLootLockerCharacterProgressionWithRewardsResponseDelegate& OnComplete /*= FLootLockerCharacterProgressionWithRewardsResponseDelegate()*/)
{
    return LLAPI<FLootLockerCharacterProgressionWithRewardsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ResetCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::DeleteCharacterProgression(const FLootLockerPlayerData& PlayerData, const int32 CharacterId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete /*= FLootLockerDeleteProgressionDelegate()*/)
{
    return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteCharacterProgression, { CharacterId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}


FString ULootLockerProgressionsRequestHandler::GetProgressions(const FLootLockerPlayerData& PlayerData, const int32 Count, const FString& After, const FLootLockerPaginatedProgressionsResponseDelegate& OnComplete /*= FLootLockerPaginatedProgressionsResponseDelegate()*/)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("after", After); }

    return LLAPI<FLootLockerPaginatedProgressionsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllProgressions, {}, QueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::GetProgression(const FLootLockerPlayerData& PlayerData, const FString& ProgressionKey, const FLootLockerProgressionResponseDelegate& OnComplete /*= FLootLockerProgressionResponseDelegate()*/)
{
    return LLAPI<FLootLockerProgressionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleProgression, { ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::GetProgressionTiers(const FLootLockerPlayerData& PlayerData, const FString& ProgressionKey, const int32 Count, const int32 After, const FLootLockerPaginatedProgressionTiersResponseDelegate& OnComplete /*= FLootLockerPaginatedProgressionTiersResponseDelegate()*/)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (After > 0) { QueryParams.Add("after", FString::FromInt(After)); }
    return LLAPI<FLootLockerPaginatedProgressionTiersResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetProgressionTiers, { ProgressionKey }, QueryParams, PlayerData, OnComplete);
}

FString ULootLockerProgressionsRequestHandler::GetInstanceProgressions(const FLootLockerPlayerData& PlayerData, const int32 AssetInstanceId, const int32 Count, const FString& After, const FLootLockerPaginatedInstanceProgressionsResponseDelegate& OnComplete)
{
    TMultiMap<FString, FString> QueryParams;
    if (Count > 0) { QueryParams.Add("count", FString::FromInt(Count)); }
    if (!After.IsEmpty()) { QueryParams.Add("after", After); }

    return LLAPI<FLootLockerPaginatedInstanceProgressionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllInstanceProgressions, { AssetInstanceId }, QueryParams, PlayerData, OnComplete);

}

FString ULootLockerProgressionsRequestHandler::GetInstanceProgression(const FLootLockerPlayerData& PlayerData, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerInstanceProgressionResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);

}

FString ULootLockerProgressionsRequestHandler::AddPointsToInstanceProgression(const FLootLockerPlayerData& PlayerData, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerInstanceProgressionWithRewardsResponse>::CallAPI(FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::AddPointsToInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);

}

FString ULootLockerProgressionsRequestHandler::SubtractPointsFromInstanceProgression(const FLootLockerPlayerData& PlayerData, const int32 AssetInstanceId, const FString& ProgressionKey, const int32 Amount, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerInstanceProgressionWithRewardsResponse>::CallAPI(FLootLockerModifyScoreRequest{ Amount }, ULootLockerGameEndpoints::SubtractPointsFromInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);

}

FString ULootLockerProgressionsRequestHandler::ResetInstanceProgression(const FLootLockerPlayerData& PlayerData, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerInstanceProgressionWithRewardsResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerInstanceProgressionWithRewardsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ResetInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);

}

FString ULootLockerProgressionsRequestHandler::DeleteInstanceProgression(const FLootLockerPlayerData& PlayerData, const int32 AssetInstanceId, const FString& ProgressionKey, const FLootLockerDeleteProgressionDelegate& OnComplete)
{
    return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteInstanceProgression, { AssetInstanceId, ProgressionKey }, EmptyQueryParams, PlayerData, OnComplete);

}
