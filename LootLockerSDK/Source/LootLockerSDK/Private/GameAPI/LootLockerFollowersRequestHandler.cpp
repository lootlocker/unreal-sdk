#include "GameAPI/LootLockerFollowersRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerFollowersRequestHandler::HttpClient = nullptr;

ULootLockerFollowersRequestHandler::ULootLockerFollowersRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}


// List followers for a specific player
void ULootLockerFollowersRequestHandler::ListFollowers(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerPublicId);
    LLAPI<FLootLockerListFollowersResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFollowersEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List followers for the requesting player
void ULootLockerFollowersRequestHandler::ListFollowers(const FLootLockerPlayerData& PlayerData, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    ListFollowers(PlayerData, PlayerData.PlayerPublicUid, OnResponseCompletedBP, OnResponseCompleted);
}

// List following for a specific player
void ULootLockerFollowersRequestHandler::ListFollowing(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerPublicId);
    LLAPI<FLootLockerListFollowersResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::ListFollowingEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// List following for the requesting player
void ULootLockerFollowersRequestHandler::ListFollowing(const FLootLockerPlayerData& PlayerData, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP, const FLootLockerListFollowersResponseDelegate& OnResponseCompleted)
{
    ListFollowing(PlayerData, PlayerData.PlayerPublicUid, OnResponseCompletedBP, OnResponseCompleted);
}

// Follow a player
void ULootLockerFollowersRequestHandler::FollowPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerPublicId);
    LLAPI<FLootLockerFollowActionResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::FollowPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}

// Unfollow a player
void ULootLockerFollowersRequestHandler::UnfollowPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP, const FLootLockerFollowActionResponseDelegate& OnResponseCompleted)
{
    TArray<FStringFormatArg> PathParams;
    PathParams.Add(PlayerPublicId);
    LLAPI<FLootLockerFollowActionResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest{}, ULootLockerGameEndpoints::UnfollowPlayerEndpoint, PathParams, {}, PlayerData, OnResponseCompletedBP, OnResponseCompleted);
}
