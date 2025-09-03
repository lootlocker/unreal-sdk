#pragma once

#include "CoreMinimal.h"
#include "LootLockerHttpClient.h"
#include "LootLockerResponse.h"
#include "LootLockerFriendsRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 * Represents a single friend
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerFriend
{
    GENERATED_BODY()

    /**
     * The ulid of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Player_id = "";
    /**
     * The name (if any has been set) of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Player_name = "";
    /**
     * The public uid of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Public_uid = "";
    /**
     * The creation date of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
};


/**
 * Represents a single friend with online status
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerFriendWithOnlineStatus : public FLootLockerFriend
{
    GENERATED_BODY()

    /**
     * The online status of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Online = false;
    /**
     * The creation date of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Accepted_at = "";
};

/**
 * Represents a single blocked player
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerBlockedPlayer : public FLootLockerFriend
{
    GENERATED_BODY()
    
    /**
     * The creation date of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Blocked_at = "";
};

//==================================================
// Request Definitions
//==================================================

// No custom request struct needed for list friends/incoming/outgoing

//==================================================
// Response Definitions
//==================================================


/**
 * Response struct for listing friends.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListFriendsResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerFriendWithOnlineStatus> Friends;
};

/**
 * Response struct for listing incoming friend requests.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListIncomingFriendRequestsResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerFriend> Incoming;
};

/**
 * Response struct for listing outgoing friend requests.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListOutgoingFriendRequestsResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerFriend> Outgoing;
};

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerFriendActionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListBlockedPlayersResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerBlockedPlayer> Blocked;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================


/** Blueprint response delegate for listing friends */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListFriendsResponseBP, FLootLockerListFriendsResponse, Response);
/** Blueprint response delegate for listing incoming friend requests */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListIncomingFriendRequestsResponseBP, FLootLockerListIncomingFriendRequestsResponse, Response);
/** Blueprint response delegate for listing outgoing friend requests */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListOutgoingFriendRequestsResponseBP, FLootLockerListOutgoingFriendRequestsResponse, Response);
/** Blueprint response delegate for actions taken towards the friends list */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerFriendActionResponseBP, FLootLockerFriendActionResponse, Response);
/** Blueprint response delegate for listing blocked players */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListBlockedPlayersResponseBP, FLootLockerListBlockedPlayersResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================


/** C++ response delegate for listing friends */
DECLARE_DELEGATE_OneParam(FLootLockerListFriendsResponseDelegate, FLootLockerListFriendsResponse);
/** C++ response delegate for listing incoming friend requests */
DECLARE_DELEGATE_OneParam(FLootLockerListIncomingFriendRequestsResponseDelegate, FLootLockerListIncomingFriendRequestsResponse);
/** C++ response delegate for listing outgoing friend requests */
DECLARE_DELEGATE_OneParam(FLootLockerListOutgoingFriendRequestsResponseDelegate, FLootLockerListOutgoingFriendRequestsResponse);
/** C++ response delegate for actions taken towards the friends list */
DECLARE_DELEGATE_OneParam(FLootLockerFriendActionResponseDelegate, FLootLockerFriendActionResponse);
/** C++ response delegate for listing blocked players */
DECLARE_DELEGATE_OneParam(FLootLockerListBlockedPlayersResponseDelegate, FLootLockerListBlockedPlayersResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerFriendsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerFriendsRequestHandler();

    static void ListFriends(const FLootLockerPlayerData& PlayerData, const FLootLockerListFriendsResponseBP& OnResponseCompletedBP = FLootLockerListFriendsResponseBP(), const FLootLockerListFriendsResponseDelegate& OnResponseCompleted = FLootLockerListFriendsResponseDelegate());

    static void ListIncomingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListIncomingFriendRequestsResponseBP& OnResponseCompletedBP = FLootLockerListIncomingFriendRequestsResponseBP(), const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted = FLootLockerListIncomingFriendRequestsResponseDelegate());

    static void ListOutgoingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListOutgoingFriendRequestsResponseBP& OnResponseCompletedBP = FLootLockerListOutgoingFriendRequestsResponseBP(), const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted = FLootLockerListOutgoingFriendRequestsResponseDelegate());

    static void SendFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP = FLootLockerFriendActionResponseBP(), const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static void DeleteFriend(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP = FLootLockerFriendActionResponseBP(), const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static void CancelOutgoingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP = FLootLockerFriendActionResponseBP(), const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static void AcceptIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP = FLootLockerFriendActionResponseBP(), const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static void DeclineIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP = FLootLockerFriendActionResponseBP(), const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static void ListBlockedPlayers(const FLootLockerPlayerData& PlayerData, const FLootLockerListBlockedPlayersResponseBP& OnResponseCompletedBP = FLootLockerListBlockedPlayersResponseBP(), const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted = FLootLockerListBlockedPlayersResponseDelegate());

    static void BlockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP = FLootLockerFriendActionResponseBP(), const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static void UnblockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseBP& OnResponseCompletedBP = FLootLockerFriendActionResponseBP(), const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static ULootLockerHttpClient* HttpClient;
};
