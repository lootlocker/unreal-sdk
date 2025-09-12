#include "GameAPI/LootLockerFriendsRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerFriendsRequestHandler::HttpClient = nullptr;

ULootLockerFriendsRequestHandler::ULootLockerFriendsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}


// List friends for the requesting player
void ULootLockerFriendsRequestHandler::ListFriends(const FLootLockerPlayerData& PlayerData, const FLootLockerListFriendsResponseBP& OnResponseCompletedBP, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListFriendsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFriendsEndpoint, {}, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List friends (paginated)
void ULootLockerFriendsRequestHandler::ListFriendsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListFriendsResponseBP& OnResponseCompletedBP, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    LLAPI<FLootLockerListFriendsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFriendsEndpoint, {}, QueryParams, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List incoming friend requests for the requesting player
void ULootLockerFriendsRequestHandler::ListIncomingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListIncomingFriendRequestsResponseBP& OnResponseCompletedBP, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListIncomingFriendRequestsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListIncomingFriendRequestsEndpoint, {}, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List incoming friend requests (paginated)
void ULootLockerFriendsRequestHandler::ListIncomingFriendRequestsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseBP& OnResponseCompletedBP, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    LLAPI<FLootLockerListIncomingFriendRequestsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListIncomingFriendRequestsEndpoint, {}, QueryParams, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List outgoing friend requests for the requesting player
void ULootLockerFriendsRequestHandler::ListOutgoingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListOutgoingFriendRequestsResponseBP& OnResponseCompletedBP, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListOutgoingFriendRequestsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListOutgoingFriendRequestsEndpoint, {}, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List outgoing friend requests (paginated)
void ULootLockerFriendsRequestHandler::ListOutgoingFriendRequestsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseBP& OnResponseCompletedBP, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    LLAPI<FLootLockerListOutgoingFriendRequestsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListOutgoingFriendRequestsEndpoint, {}, QueryParams, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// Send a friend request to a player
void ULootLockerFriendsRequestHandler::SendFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::SendFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// Delete a friend
void ULootLockerFriendsRequestHandler::DeleteFriend(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::DeleteFriendEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// Cancel outgoing friend request
void ULootLockerFriendsRequestHandler::CancelOutgoingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::CancelOutgoingFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// Accept incoming friend request
void ULootLockerFriendsRequestHandler::AcceptIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::AcceptIncomingFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// Decline incoming friend request
void ULootLockerFriendsRequestHandler::DeclineIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::DeclineIncomingFriendRequestEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List blocked players
void ULootLockerFriendsRequestHandler::ListBlockedPlayers(const FLootLockerPlayerData& PlayerData, const FLootLockerListBlockedPlayersResponseBP& OnResponseCompletedBP, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListBlockedPlayersResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListBlockedPlayersEndpoint, {}, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List blocked players (paginated)
void ULootLockerFriendsRequestHandler::ListBlockedPlayersPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseBP& OnResponseCompletedBP, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted)
{
    TMultiMap<FString, FString> QueryParams;
    if (Page > 0) QueryParams.Add(TEXT("page"), FString::FromInt(Page));
    if (PerPage > 0) QueryParams.Add(TEXT("per_page"), FString::FromInt(PerPage));
    LLAPI<FLootLockerListBlockedPlayersResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListBlockedPlayersEndpoint, {}, QueryParams, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// Get a specific friend
void ULootLockerFriendsRequestHandler::GetFriend(const FLootLockerPlayerData& PlayerData, const FString& FriendUlid, const FLootLockerGetFriendResponseBP& OnResponseCompletedBP, const FLootLockerGetFriendResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(FriendUlid);
    LLAPI<FLootLockerGetFriendResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::GetFriendEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// Block a player
void ULootLockerFriendsRequestHandler::BlockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::BlockPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// Unblock a player
void ULootLockerFriendsRequestHandler::UnblockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerULID);
    LLAPI<FLootLockerFriendActionResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::UnblockPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}
