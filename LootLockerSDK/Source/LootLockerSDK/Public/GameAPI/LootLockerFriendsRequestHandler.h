#pragma once

#include "CoreMinimal.h"
#include "LootLockerPlayerData.h"
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
 * Represents a single friend
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAcceptedFriend : public FLootLockerFriend
{
    GENERATED_BODY()

    /**
     * The online status of the player
     */
    //UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    //bool Online = false;
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
    TArray<FLootLockerAcceptedFriend> Friends;
    /** Pagination info */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;
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
    /** Pagination info */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;
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
    /** Pagination info */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;
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
    /** Pagination info */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;
};

/** Response struct for getting a single friend */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerGetFriendResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** The id of the player */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Player_id = "";
    /** The name of the player */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Player_name = "";
    /** The public uid of the player */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Public_uid = "";
    /** When the player's account was created */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /** When the friend request was accepted */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Accepted_at = "";
};

//==================================================
// Delegate Definitions
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
/** C++ response delegate for getting a friend */
DECLARE_DELEGATE_OneParam(FLootLockerGetFriendResponseDelegate, FLootLockerGetFriendResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerFriendsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerFriendsRequestHandler() {};

    static FString ListFriends(const FLootLockerPlayerData& PlayerData, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted = FLootLockerListFriendsResponseDelegate());
    static FString ListFriendsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListFriendsResponseDelegate& OnResponseCompleted = FLootLockerListFriendsResponseDelegate());

    static FString ListIncomingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted = FLootLockerListIncomingFriendRequestsResponseDelegate());
    static FString ListIncomingFriendRequestsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListIncomingFriendRequestsResponseDelegate& OnResponseCompleted = FLootLockerListIncomingFriendRequestsResponseDelegate());

    static FString ListOutgoingFriendRequests(const FLootLockerPlayerData& PlayerData, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted = FLootLockerListOutgoingFriendRequestsResponseDelegate());
    static FString ListOutgoingFriendRequestsPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListOutgoingFriendRequestsResponseDelegate& OnResponseCompleted = FLootLockerListOutgoingFriendRequestsResponseDelegate());

    static FString SendFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static FString DeleteFriend(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static FString CancelOutgoingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static FString AcceptIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static FString DeclineIncomingFriendRequest(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static FString ListBlockedPlayers(const FLootLockerPlayerData& PlayerData, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted = FLootLockerListBlockedPlayersResponseDelegate());
    static FString ListBlockedPlayersPaginated(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerListBlockedPlayersResponseDelegate& OnResponseCompleted = FLootLockerListBlockedPlayersResponseDelegate());

    static FString GetFriend(const FLootLockerPlayerData& PlayerData, const FString& FriendUlid, const FLootLockerGetFriendResponseDelegate& OnResponseCompleted = FLootLockerGetFriendResponseDelegate());

    static FString BlockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());

    static FString UnblockPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerULID, const FLootLockerFriendActionResponseDelegate& OnResponseCompleted = FLootLockerFriendActionResponseDelegate());
};
