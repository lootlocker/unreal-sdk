#include "GameAPI/LootLockerFriendsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

// List friends for the requesting player
FString ULootLockerFriendsRequestHandler::ListFriends(const FLootLockerPlayerData& PlayerData, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted)
{
    return LLAPI<FLootLockerListFriendsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFriendsEndpoint, {}, {}, PlayerData, OnResponseCompleted);
}

// List friends (paginated)
FString ULootLockerFriendsRequestHandler::ListFriendsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    return LLAPI<FLootLockerListFriendsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFriendsEndpoint, {}, QueryParams, PlayerData, OnResponseCompleted);
}

// List incoming friend requests for the requesting player
FString ULootLockerFriendsRequestHandler::ListIncomingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    return LLAPI<FLootLockerListIncomingFriendRequestsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListIncomingFriendRequestsEndpoint, {}, {}, PlayerData, OnResponseCompleted);
}

// List incoming friend requests (paginated)
FString ULootLockerFriendsRequestHandler::ListIncomingFriendRequestsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    return LLAPI<FLootLockerListIncomingFriendRequestsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListIncomingFriendRequestsEndpoint, {}, QueryParams, PlayerData, OnResponseCompleted);
}

// List outgoing friend requests for the requesting player
FString ULootLockerFriendsRequestHandler::ListOutgoingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    return LLAPI<FLootLockerListOutgoingFriendRequestsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListOutgoingFriendRequestsEndpoint, {}, {}, PlayerData, OnResponseCompleted);
}

// List outgoing friend requests (paginated)
FString ULootLockerFriendsRequestHandler::ListOutgoingFriendRequestsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    return LLAPI<FLootLockerListOutgoingFriendRequestsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListOutgoingFriendRequestsEndpoint, {}, QueryParams, PlayerData, OnResponseCompleted);
}

// Send a friend request to a player
FString ULootLockerFriendsRequestHandler::SendFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    return LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::SendFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Delete a friend
FString ULootLockerFriendsRequestHandler::DeleteFriend(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    return LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::DeleteFriendEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Cancel outgoing friend request
FString ULootLockerFriendsRequestHandler::CancelOutgoingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    return LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::CancelOutgoingFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Accept incoming friend request
FString ULootLockerFriendsRequestHandler::AcceptIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    return LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::AcceptIncomingFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Decline incoming friend request
FString ULootLockerFriendsRequestHandler::DeclineIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    return LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::DeclineIncomingFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// List blocked players
FString ULootLockerFriendsRequestHandler::ListBlockedPlayers(const FLootLockerPlayerData& PlayerData, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted)
{
    return LLAPI<FLootLockerListBlockedPlayersResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListBlockedPlayersEndpoint, {}, {}, PlayerData, OnResponseCompleted);
}

// List blocked players (paginated)
FString ULootLockerFriendsRequestHandler::ListBlockedPlayersPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    return LLAPI<FLootLockerListBlockedPlayersResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListBlockedPlayersEndpoint, {}, QueryParams, PlayerData, OnResponseCompleted);
}

// Get a specific friend
FString ULootLockerFriendsRequestHandler::GetFriend(const FLootLockerPlayerData& PlayerData, const FString& FriendUlid, const FLootLockerGetFriendResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(FriendUlid);
    return LLAPI<FLootLockerGetFriendResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetFriendEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Block a player
FString ULootLockerFriendsRequestHandler::BlockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    return LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::BlockPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Unblock a player
FString ULootLockerFriendsRequestHandler::UnblockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    return LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::UnblockPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}
