#pragma once

#include "CoreMinimal.h"
#include "LootLockerHttpClient.h"
#include "LootLockerResponse.h"
#include "LootLockerFollowersRequestHandler.generated.h"


//==================================================
// Data Type Definitions
//==================================================


/**
 * Represents a single follower or following player
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerFollower
{
    GENERATED_BODY()

    /** The ULID of the player. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Player_id = "";

    /** The name (if any has been set) of the player. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Player_name = "";

    /** The public UID of the player. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Public_uid = "";

    /** When the player's account was created. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
};

//==================================================
// Response Definitions
//==================================================


/**
 * Response struct for listing followers or following players.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListFollowersResponse : public FLootLockerResponse
{
    GENERATED_BODY()

    /** List of followers for the specified player. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerFollower> Followers;

    /** Pagination data for the request. */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerIndexBasedPagination Pagination;
};

/**
 * Response struct for follow/unfollow actions. Empty unless the request failed
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerFollowActionResponse : public FLootLockerResponse
{
    GENERATED_BODY()
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/**
 * Blueprint response delegate for listing followers/following.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListFollowersResponseBP, FLootLockerListFollowersResponse, Response);

/**
 * Blueprint response delegate for follow/unfollow actions.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerFollowActionResponseBP, FLootLockerFollowActionResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/**
 * C++ response delegate for listing followers/following.
 */
DECLARE_DELEGATE_OneParam(FLootLockerListFollowersResponseDelegate, FLootLockerListFollowersResponse);

/**
 * C++ response delegate for follow/unfollow actions.
 */
DECLARE_DELEGATE_OneParam(FLootLockerFollowActionResponseDelegate, FLootLockerFollowActionResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerFollowersRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerFollowersRequestHandler();


    static void ListFollowers(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP = FLootLockerListFollowersResponseBP(), const FLootLockerListFollowersResponseDelegate& OnResponseCompleted = FLootLockerListFollowersResponseDelegate());

    static void ListFollowers(const FLootLockerPlayerData& PlayerData, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP = FLootLockerListFollowersResponseBP(), const FLootLockerListFollowersResponseDelegate& OnResponseCompleted = FLootLockerListFollowersResponseDelegate());

    static void ListFollowing(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP = FLootLockerListFollowersResponseBP(), const FLootLockerListFollowersResponseDelegate& OnResponseCompleted = FLootLockerListFollowersResponseDelegate());

    static void ListFollowing(const FLootLockerPlayerData& PlayerData, const FLootLockerListFollowersResponseBP& OnResponseCompletedBP = FLootLockerListFollowersResponseBP(), const FLootLockerListFollowersResponseDelegate& OnResponseCompleted = FLootLockerListFollowersResponseDelegate());

    static void FollowPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP = FLootLockerFollowActionResponseBP(), const FLootLockerFollowActionResponseDelegate& OnResponseCompleted = FLootLockerFollowActionResponseDelegate());

    static void UnfollowPlayer(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicId, const FLootLockerFollowActionResponseBP& OnResponseCompletedBP = FLootLockerFollowActionResponseBP(), const FLootLockerFollowActionResponseDelegate& OnResponseCompleted = FLootLockerFollowActionResponseDelegate());

    static ULootLockerHttpClient* HttpClient;
};
