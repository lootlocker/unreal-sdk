// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerPlayerData.h"
#include "GameAPI/LootLockerAssetInstancesRequestHandler.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "GameAPI/LootLockerBalanceRequestHandler.h"
#include "GameAPI/LootLockerBroadcastRequestHandler.h"
#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "GameAPI/LootLockerCollectablesRequestHandler.h"
#include "GameAPI/LootLockerConnectedAccountsRequestHandler.h"
#include "GameAPI/LootLockerCurrencyRequestHandler.h"
#include "GameAPI/LootLockerDropTablesRequestHandler.h"
#include "GameAPI/LootLockerEntitlementRequestHandler.h"
#include "GameAPI/LootLockerFollowersRequestHandler.h"
#include "GameAPI/LootLockerFriendsRequestHandler.h"
#include "GameAPI/LootLockerHeroRequestHandler.h"
#include "GameAPI/LootLockerLeaderboardRequestHandler.h"
#include "GameAPI/LootLockerLeaderboardArchiveRequestHandler.h"
#include "GameAPI/LootLockerMapsRequestHandler.h"
#include "GameAPI/LootLockerMessagesRequestHandler.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "GameAPI/LootLockerPersistentStorageRequestHandler.h"
#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"
#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "GameAPI/LootLockerProgressionsRequestHandler.h"
#include "GameAPI/LootLockerPurchasesRequestHandler.h"
#include "GameAPI/LootLockerRemoteSessionRequestHandler.h"
#include "GameAPI/LootLockerTriggersRequestHandler.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "GameAPI/LootLockerFeedbackRequestHandler.h"
#include "GameAPI/LootLockerNotificationsRequestHandler.h"
#include "LootLockerSessionOptionals.h"
#include "LootLockerManagerAsync.generated.h"

USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAsyncSessionResponse
{
	GENERATED_BODY()
	/**
	 The session token that can now be used to use further LootLocker functionality. We store and use this for you.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	FString session_token = "";
  /**
	 * The player's name if it has been set by using SetPlayerName().
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	FString player_name = "";
	/**
	 * The player id
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	int32 player_id = 0;
	/**
	 * The public UID for this player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	FString public_uid = "";
	/**
	 * The player ULID for this player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	FString player_ulid = "";
	/**
	 * The date that this player was created
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	FString player_created_at = "";
	/**
	 * Whether this player has been seen before (true) or is new (false)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	bool seen_before = false;
	/**
	 * Whether this player has new information to check in grants
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	bool check_grant_notifications = false;
	/**
	 * Whether this player has new information to check in deactivations
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	bool check_deactivation_notifications = false;
	/**
	 * The current xp of this player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	int32 xp = 0;
	/**
	 * The current level of this player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	int32 level = 0;
	/**
	 * The level_thresholds that the level and xp data relates to
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	FLootLockerLevelThresholds level_thresholds;
	/**
	 * The current balance in this account
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	int32 account_balance = 0;
	/**
	 * The player identifier of the player
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	FString player_identifier = "";
	/**
	 The id of the wallet for this account
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker | Authentication")
	FString wallet_id = "";
};

/**
 * Multicast Delegate for events triggered from the LootLockerAsyncStartGuestSession node
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FLootLockerGuestSessionAsyncDelegate, FLootLockerAsyncSessionResponse, SessionData, int, StatusCode, FString, FullTextFromServer, FLootLockerErrorData, ErrorData, FLootLockerRequestContext, RequestContext);
/***/
UCLASS()
class ULootLockerAsyncStartGuestSession : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()
public:
    /**
     Start a guest session. Optionally provide a custom unique PlayerIdentifier (otherwise one will be generated).

     On success, SessionData will contain the session token and player details.

     On failure, ErrorData will contain the details of the failure.
     
     @param WorldContextObject Non input: Automatic context for async node
     @param PlayerIdentifier Optional: Custom unique identifier to associate with this guest player (auto-generated if empty)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "LootLocker | Authentication", WorldContext = "WorldContextObject", AdvancedDisplay = "PlayerIdentifier,Optionals", PlayerIdentifier = "", AutoCreateRefTerm = "Optionals"))
    static LOOTLOCKERSDK_API ULootLockerAsyncStartGuestSession* AsyncStartGuestSession(UObject* WorldContextObject, const FString& PlayerIdentifier, const FLootLockerSessionOptionals& Optionals);


	  /** Triggered on success */
    UPROPERTY(BlueprintAssignable)
    FLootLockerGuestSessionAsyncDelegate OnSuccess;
    /** Triggered on failure */
    UPROPERTY(BlueprintAssignable)
    FLootLockerGuestSessionAsyncDelegate OnFailure;

    /** Execute the actual operation */
    LOOTLOCKERSDK_API virtual void Activate() override;

protected:
    // Store the player identifier to use later
    FString PlayerIdentifier;
    // Store the optionals to use later
    FLootLockerSessionOptionals Optionals;
};

/**
 * Multicast Delegate for events triggered from the LootLockerAsyncStartGuestSession node
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLootLockerGuestSessionAsync2Delegate, FLootLockerAuthenticationResponse, ResponseInformation);
/***/
UCLASS()
class ULootLockerAsyncStartGuestSession2 : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()
public:
    /**
     Start a guest session. Optionally provide a custom unique PlayerIdentifier (otherwise one will be generated).

     On success, SessionData will contain the session token and player details.

     On failure, ErrorData will contain the details of the failure.
     
     @param WorldContextObject Non input: Automatic context for async node
     @param PlayerIdentifier Optional: Custom unique identifier to associate with this guest player (auto-generated if empty)
     @param Optionals Optional: Additional session options applied when starting the session
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "LootLocker | Authentication", WorldContext = "WorldContextObject", AdvancedDisplay = "PlayerIdentifier,Optionals", PlayerIdentifier = "", AutoCreateRefTerm = "Optionals"))
    static LOOTLOCKERSDK_API ULootLockerAsyncStartGuestSession2* AsyncStartGuestSession2(UObject* WorldContextObject, const FString& PlayerIdentifier, const FLootLockerSessionOptionals& Optionals);


	  /** Triggered on success */
    UPROPERTY(BlueprintAssignable)
    FLootLockerGuestSessionAsync2Delegate OnSuccess;
    /** Triggered on failure */
    UPROPERTY(BlueprintAssignable)
    FLootLockerGuestSessionAsync2Delegate OnFailure;

    /** Execute the actual operation */
    LOOTLOCKERSDK_API virtual void Activate() override;

protected:
    // Store the player identifier to use later
    FString PlayerIdentifier;
    // Store the optionals to use later
    FLootLockerSessionOptionals Optionals;
};
