#include "GameAPI/LootLockerFriendsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

// List friends for the requesting player
void ULootLockerFriendsRequestHandler::ListFriends(const FLootLockerPlayerData& PlayerData, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListFriendsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFriendsEndpoint, {}, {}, PlayerData, OnResponseCompleted);
}

// List friends (paginated)
void ULootLockerFriendsRequestHandler::ListFriendsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    LLAPI<FLootLockerListFriendsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFriendsEndpoint, {}, QueryParams, PlayerData, OnResponseCompleted);
}

// List incoming friend requests for the requesting player
void ULootLockerFriendsRequestHandler::ListIncomingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListIncomingFriendRequestsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListIncomingFriendRequestsEndpoint, {}, {}, PlayerData, OnResponseCompleted);
}

// List incoming friend requests (paginated)
void ULootLockerFriendsRequestHandler::ListIncomingFriendRequestsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    LLAPI<FLootLockerListIncomingFriendRequestsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListIncomingFriendRequestsEndpoint, {}, QueryParams, PlayerData, OnResponseCompleted);
}

// List outgoing friend requests for the requesting player
void ULootLockerFriendsRequestHandler::ListOutgoingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListOutgoingFriendRequestsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListOutgoingFriendRequestsEndpoint, {}, {}, PlayerData, OnResponseCompleted);
}

// List outgoing friend requests (paginated)
void ULootLockerFriendsRequestHandler::ListOutgoingFriendRequestsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    LLAPI<FLootLockerListOutgoingFriendRequestsResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListOutgoingFriendRequestsEndpoint, {}, QueryParams, PlayerData, OnResponseCompleted);
}

// Send a friend request to a player
void ULootLockerFriendsRequestHandler::SendFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::SendFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Delete a friend
void ULootLockerFriendsRequestHandler::DeleteFriend(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::DeleteFriendEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Cancel outgoing friend request
void ULootLockerFriendsRequestHandler::CancelOutgoingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::CancelOutgoingFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Accept incoming friend request
void ULootLockerFriendsRequestHandler::AcceptIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::AcceptIncomingFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Decline incoming friend request
void ULootLockerFriendsRequestHandler::DeclineIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::DeclineIncomingFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// List blocked players
void ULootLockerFriendsRequestHandler::ListBlockedPlayers(const FLootLockerPlayerData& PlayerData, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListBlockedPlayersResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListBlockedPlayersEndpoint, {}, {}, PlayerData, OnResponseCompleted);
}

// List blocked players (paginated)
void ULootLockerFriendsRequestHandler::ListBlockedPlayersPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    LLAPI<FLootLockerListBlockedPlayersResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListBlockedPlayersEndpoint, {}, QueryParams, PlayerData, OnResponseCompleted);
}

// Get a specific friend
void ULootLockerFriendsRequestHandler::GetFriend(const FLootLockerPlayerData& PlayerData, const FString& FriendUlid, const FLootLockerGetFriendResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(FriendUlid);
    LLAPI<FLootLockerGetFriendResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetFriendEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Block a player
void ULootLockerFriendsRequestHandler::BlockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::BlockPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}

// Unblock a player
void ULootLockerFriendsRequestHandler::UnblockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::UnblockPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompleted);
}
