// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LootLockerPlayerRequestHandler.generated.h"

/**
A set of important information about a player
*/
USTRUCT(BlueprintType)
struct FLootLockerPlayerInfo 
{
	GENERATED_BODY()
	/**
	When this player was first created
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	FString Created_at = "";
	/**
	When this player was last seen (last time this player logged in)
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	FString Last_seen = "";
	/**
	The name of the player expressly configured through a SetPlayerName call
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	FString Name = "";
	/**
	The public uid of the player. This id is in the form of a UID
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	FString Public_uid = "";
	/**
	The legacy id of the player. This id is in the form of an integer and are sometimes called simply player_id or id
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	int Legacy_id = 0;
	/**
	The id of the player. This id is in the form a ULID and is sometimes called player_ulid or similar
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	FString Id = "";
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerListPlayerInfoRequest
{
	GENERATED_BODY()
	/**
	A list of ULID ids of players to look up. These ids are in the form of ULIDs and are sometimes called player_ulid or similar
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	TArray<FString> Player_id;
	/**
	A list of legacy ids of players to look up. These ids are in the form of integers and are sometimes called simply player_id or id
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	TArray<int> Player_legacy_id;
	/**
	A list of public uids to look up. These ids are in the form of UIDs
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	TArray<FString> Player_public_uid;
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerGetCurrentPlayerInfoResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	/**
	Important player information for the currently logged in player
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	FLootLockerPlayerInfo Info;
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerListPlayerInfoResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	/**
	A list of important player information for the successfully looked up players
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
	TArray<FLootLockerPlayerInfo> Info;
};

USTRUCT(BlueprintType)
struct FLootLockerBalanceResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	float balance = 0.0f;
};

USTRUCT(BlueprintType)
struct FLootLockerDlcResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FString> dlcs;
};

USTRUCT(BlueprintType)
struct FLootLockerRental {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_rental = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString time_left = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString duration = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString is_active = "";
};
USTRUCT(BlueprintType)
struct FLootLockerInventory {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString rental_option_id = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerRental rental;
};
USTRUCT(BlueprintType)
struct FLootLockerInventoryResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerInventory> inventory;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerLevel {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp_threshold = 0;
};
USTRUCT(BlueprintType)
struct FLootLockerXp {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 previous = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 current = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerObjects
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString reason = "";
};
USTRUCT(BlueprintType)
struct FLootLockerPlayerAssetNotificationResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerObjects> objects;
};

USTRUCT(BlueprintType)
struct FLootLockerNameResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerNameRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerXpInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString id = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
};


USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayersNames
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_id = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_public_uid = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString ulid = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString last_active_platform = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString platform_player_id = "";
};

USTRUCT(BlueprintType)
struct FLootLockerPlatformIds
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 steam_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString xbox_id = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 psn_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayersPlatformIds
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_id = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_public_uid = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString last_active_platform = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerPlatformIds platform_ids;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayersPlatformIdsResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerMultiplePlayersPlatformIds> players;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayersNamesResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerMultiplePlayersNames> players;
};

/**
 */
UENUM(BlueprintType)
enum class ELootLockerPlayerDataLookupIdType : uint8
{
	Player_id = 0,
	Player_public_uid = 1,
	Player_guest_login_id = 2,
	Steam_id = 3,
	Psn_id = 4,
	Xbox_id = 5,
	Player_ulid = 6,
	Player_name = 7,
	Epic_games_id = 8,
	Google_play_games_id = 9
};

/**
 */
USTRUCT(BlueprintType)
struct FLootLockerPlayerDataLookupPair
{
	GENERATED_BODY()
	/*
	 The type of id that you want to look up
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	ELootLockerPlayerDataLookupIdType IdType = ELootLockerPlayerDataLookupIdType::Player_id;
	/*
	 The id you want to look up
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Id = "";
};

/**
 Deprecated date 20250304
 */
USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayerNameRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString platform = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_id = "";
};

/**
 Deprecated date 20250304
 */
USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayerNamesRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerMultiplePlayerNameRequest> player_ids;
};

USTRUCT(BlueprintType)
struct FLootLockerLookupMultiplePlayersDataRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerDataLookupPair> player_ids;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayerNamesAndPlatformsRequest {
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		TArray<FString> player_ids;
	    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		TArray<FString> player_public_uids;
};

/**
 * A simplified inventory item for optimized inventory listing
 */
USTRUCT(BlueprintType)
struct FLootLockerSimpleInventoryItem
{
	GENERATED_BODY()
	/**
	 * The ID of the asset
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 Asset_id = 0;
	/**
	 * The instance ID of this specific asset instance
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 Instance_id = 0;
	/**
	 * How this asset was acquired (e.g., purchase, loot_box, etc.)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Acquisition_source = "";
	/**
	 * When this asset was acquired
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString Acquisition_date = "";
};

/**
 * Request filters for simplified inventory listing
 */
USTRUCT(BlueprintType)
struct FLootLockerListSimplifiedInventoryRequest
{
	GENERATED_BODY()
	/**
	 * A list of asset ids to filter the inventory items by
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<int32> Asset_ids;
	/**
	 * A list of context ids to filter the inventory items by
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<int32> Context_ids;
};

/**
 * Response for simplified inventory listing
 */
USTRUCT(BlueprintType)
struct FLootLockerSimpleInventoryResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	/**
	 * List of simplified inventory items according to the requested filters
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerSimpleInventoryItem> Items;
	/**
	 * Pagination information for the inventory items returned
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerIndexBasedPagination Pagination;
};

DECLARE_DELEGATE_OneParam(FLootLockerGetCurrentPlayerInfoResponseDelegate, FLootLockerGetCurrentPlayerInfoResponse);

DECLARE_DELEGATE_OneParam(FLootLockerListPlayerInfoResponseDelegate, FLootLockerListPlayerInfoResponse);

DECLARE_DELEGATE_OneParam(FInventoryResponse, FLootLockerInventoryResponse);

DECLARE_DELEGATE_OneParam(FLootLockerAssetNotificationResponse, FLootLockerPlayerAssetNotificationResponse);

DECLARE_DELEGATE_OneParam(FPBalanceResponse, FLootLockerBalanceResponse);

DECLARE_DELEGATE_OneParam(FPDlcResponse, FLootLockerDlcResponse);

DECLARE_DELEGATE_OneParam(FPNameResponse, FLootLockerNameResponse);

DECLARE_DELEGATE_OneParam(FPMultiplePlayerNames, FLootLockerMultiplePlayersNamesResponse)

DECLARE_DELEGATE_OneParam(FPMultiplePlayersPlatformIdsNames, FLootLockerMultiplePlayersPlatformIdsResponse);

DECLARE_DELEGATE_OneParam(FLootLockerSimpleInventoryResponseDelegate, FLootLockerSimpleInventoryResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerPlayerRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerPlayerRequestHandler() {};

	static FString GetCurrentPlayerInfo(const FLootLockerPlayerData& PlayerData, const FLootLockerGetCurrentPlayerInfoResponseDelegate& OnCompletedRequest);
	static FString ListPlayerInfo(const FLootLockerPlayerData& PlayerData, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseDelegate& OnCompletedRequest);
	static FString GetInventory(const FLootLockerPlayerData& PlayerData, const FInventoryResponse& OnCompletedRequest);
	static FString GetFullInventory(const FLootLockerPlayerData& PlayerData, const FInventoryResponse& OnCompletedRequest, int32 StartIndex = 0);
	static FString CheckPlayerAssetNotification(const FLootLockerPlayerData& PlayerData, const FLootLockerAssetNotificationResponse& OnCompletedRequest);
	static FString GetCurrencyBalance(const FLootLockerPlayerData& PlayerData, const FPBalanceResponse& OnCompletedRequest);
	static FString InitiateDLCMigration(const FLootLockerPlayerData& PlayerData, const FResponseCallback& OnCompletedRequest);
	static FString GetDLCsMigration(const FLootLockerPlayerData& PlayerData, const FPDlcResponse& OnCompletedRequest);
	static FString SetProfilePrivate(const FLootLockerPlayerData& PlayerData, const FResponseCallback& OnCompletedRequest);
	static FString SetProfilePublic(const FLootLockerPlayerData& PlayerData, const FResponseCallback& OnCompletedRequest);
	static FString SetPlayerName(const FLootLockerPlayerData& PlayerData, FString Name, const FPNameResponse& OnCompletedRequest);
	static FString GetPlayerName(const FLootLockerPlayerData& PlayerData, const FPNameResponse& OnCompletedRequest);
	// Deprecated date 20250304
	static FString LookupMultiplePlayerNamesUsingIDs(const FLootLockerPlayerData& PlayerData, FLootLockerMultiplePlayerNamesRequest Request, const FPMultiplePlayerNames& OnCompletedRequest);
	static FString LookupMultiplePlayersDataUsingIDs(const FLootLockerPlayerData& PlayerData, FLootLockerLookupMultiplePlayersDataRequest Request, const FPMultiplePlayerNames& OnCompletedRequest);
	static FString LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerPlayerData& PlayerData, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest);
    static FString DeletePlayer(const FLootLockerPlayerData& PlayerData, const FLootLockerDefaultDelegate OnCompletedRequest);
	
	// Simple inventory listing methods
	static FString ListPlayerInventory(const FLootLockerPlayerData& PlayerData, const FLootLockerListSimplifiedInventoryRequest& Request, int32 PerPage, int32 Page, const FLootLockerSimpleInventoryResponseDelegate& OnCompletedRequest);
	static FString ListCharacterInventory(const FLootLockerPlayerData& PlayerData, const FLootLockerListSimplifiedInventoryRequest& Request, int32 CharacterId, int32 PerPage, int32 Page, const FLootLockerSimpleInventoryResponseDelegate& OnCompletedRequest);
};
