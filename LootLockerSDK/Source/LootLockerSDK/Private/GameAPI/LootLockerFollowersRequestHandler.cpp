#include "GameAPI/LootLockerFollowersRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

// List followers for a specific player
FString ULootLockerFollowersRequestHandler::ListFollowers(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerPublicId);
    return LLAPI<FLootLockerListFollowersResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFollowersEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

FString ULootLockerFollowersRequestHandler::ListFollowersPaginated(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams; PathParams.Add(PlayerPublicId);
    TMultiMap<FString, FString> QueryParams;
    if(!Cursor.IsEmpty()) { QueryParams.Add(TEXT("cursor"), Cursor); }
    if(Count>0){ QueryParams.Add(TEXT("per_page"), FString::FromInt(Count)); }
    return LLAPI<FLootLockerListFollowersResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFollowersEndpoint, PathParams, QueryParams, PlayerData, OnResponseCompleted);
}

// List followers for the requesting player
FString ULootLockerFollowersRequestHandler::ListFollowers(const FLootLockerPlayerData& PlayerData, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    return ListFollowers(PlayerData, PlayerData.PlayerPublicUid, OnResponseCompleted);
}

FString ULootLockerFollowersRequestHandler::ListFollowersPaginated(const FLootLockerPlayerData& PlayerData, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    return ListFollowersPaginated(PlayerData, PlayerData.PlayerPublicUid, Cursor, Count, OnResponseCompleted);
}

// List following for a specific player
FString ULootLockerFollowersRequestHandler::ListFollowing(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerPublicId);
    return LLAPI<FLootLockerListFollowersResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFollowingEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

FString ULootLockerFollowersRequestHandler::ListFollowingPaginated(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams; PathParams.Add(PlayerPublicId);
    TMultiMap<FString, FString> QueryParams;
    if(!Cursor.IsEmpty()) { QueryParams.Add(TEXT("cursor"), Cursor); }
    if(Count>0){ QueryParams.Add(TEXT("per_page"), FString::FromInt(Count)); }
    return LLAPI<FLootLockerListFollowersResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFollowingEndpoint, PathParams, QueryParams, PlayerData, OnResponseCompleted);
}

// List following for the requesting player
FString ULootLockerFollowersRequestHandler::ListFollowing(const FLootLockerPlayerData& PlayerData, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    return ListFollowing(PlayerData, PlayerData.PlayerPublicUid, OnResponseCompleted);
}

FString ULootLockerFollowersRequestHandler::ListFollowingPaginated(const FLootLockerPlayerData& PlayerData, const FString& Cursor, int32 Count, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    return ListFollowingPaginated(PlayerData, PlayerData.PlayerPublicUid, Cursor, Count, OnResponseCompleted);
}

// Follow a player
FString ULootLockerFollowersRequestHandler::FollowPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerPublicId);
    return LLAPI<FLootLockerFollowActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::FollowPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Unfollow a player
FString ULootLockerFollowersRequestHandler::UnfollowPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerPublicId);
    return LLAPI<FLootLockerFollowActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::UnfollowPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}
