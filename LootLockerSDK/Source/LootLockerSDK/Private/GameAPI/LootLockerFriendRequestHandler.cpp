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

// List incoming friend requests for the requesting player
void ULootLockerFriendsRequestHandler::ListIncomingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListIncomingFriendRequestsResponseBP& OnResponseCompletedBP, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListIncomingFriendRequestsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListIncomingFriendRequestsEndpoint, {}, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List outgoing friend requests for the requesting player
void ULootLockerFriendsRequestHandler::ListOutgoingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListOutgoingFriendRequestsResponseBP& OnResponseCompletedBP, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted)
{
    LLAPI<FLootLockerListOutgoingFriendRequestsResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListOutgoingFriendRequestsEndpoint, {}, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
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
