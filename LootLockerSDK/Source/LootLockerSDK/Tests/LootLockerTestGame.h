// Copyright (c) 2021 LootLocker

#pragma once

#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION > 4

#include "CoreMinimal.h"
#include "LootLockerAdminRequest.h"

/** A single broadcast entry from the admin list-broadcasts response. */
struct FLootLockerAdminBroadcast
{
	FString id;
	FString name;
	/** Start time from the first publication setting (ISO 8601 UTC). */
	FString start_time;
};

/** Response from the admin list-broadcasts endpoint. */
struct FLootLockerAdminListBroadcastsResponse
{
	bool success = false;
	TArray<FLootLockerAdminBroadcast> broadcasts;
};

/**
 * Credentials and metadata for a single admin-provisioned test game.
 *
 * Usage pattern (mirrors the Unity LootLockerTestGame):
 *
 *   // --- Setup ---
 *   FLootLockerTestGame Game;
 *   bool bOk = FLootLockerTestGame::CreateGame(Game, TEXT("MyTest"));
 *   bOk = bOk && Game.EnableGuestLogin();
 *   // Provision any feature-specific entities:
 *   bOk = bOk && Game.CreateLeaderboard(TEXT("global"), TEXT("player"), TEXT("Descending"));
 *   Game.InitializeLootLockerSDK();       // points the SDK at the provisioned game
 *   test_util::StartSession();            // regular guest login
 *
 *   // --- Teardown (always, even on failure) ---
 *   Game.DeleteGame();
 *
 * Environment-variable shortcut:
 *   If LOOTLOCKER_GAME_API_KEY is set, CreateGame() skips admin provisioning and
 *   uses that key directly. DeleteGame() is a no-op in this case.
 *   Pair with LOOTLOCKER_GAME_DOMAIN_KEY if the game has a domain key configured.
 */
struct FLootLockerTestGame
{
	// ─── Prod game ───────────────────────────────────────────────────────────
	int32   GameId    = 0;
	FString GameName;
	FString GameDomainKey;
	FString GameApiKey;

	// ─── Dev / stage game ────────────────────────────────────────────────────
	int32   DevelopmentGameId     = 0;
	FString DevelopmentGameApiKey;

	// ─── Active context (switches between prod and dev) ──────────────────────
	int32 ActiveGameId = 0;

	bool IsValid() const { return GameId != 0; }

	FString GetActiveApiKey() const
	{
		return (ActiveGameId == GameId) ? GameApiKey : DevelopmentGameApiKey;
	}

	void SwitchToProdEnvironment()
	{
		ActiveGameId = GameId;
		FLootLockerAdminRequest::ActiveGameId = GameId;
	}

	void SwitchToStageEnvironment()
	{
		ActiveGameId = DevelopmentGameId;
		FLootLockerAdminRequest::ActiveGameId = DevelopmentGameId;
	}

	// ─── Lifecycle ────────────────────────────────────────────────────────────

	/**
	 * Create an isolated test game via the admin API and populate OutGame.
	 *
	 * If LOOTLOCKER_GAME_API_KEY is set the admin API is not called — that key is
	 * used directly and DeleteGame() becomes a no-op. Pair with
	 * LOOTLOCKER_GAME_DOMAIN_KEY for the domain key.
	 *
	 * @param OutGame   Populated on success.
	 * @param TestName  Optional label embedded in the generated game name.
	 * @return false if sign-in or game creation fails.
	 */
	static bool CreateGame(FLootLockerTestGame& OutGame, const FString& TestName = TEXT(""));

	/**
	 * Delete this game via the admin API.
	 * Safe to call even when setup partially failed. Always call in test teardown.
	 */
	bool DeleteGame();

	// ─── Feature enablement ───────────────────────────────────────────────────

	/** Enable guest login for this game. */
	bool EnableGuestLogin();

	// ─── Entity provisioning ──────────────────────────────────────────────────

	/**
	 * Create a leaderboard.
	 * @param Key         Unique leaderboard key (also used as the display name).
	 * @param MemberType  "player" or "generic".
	 * @param Direction   "Descending" or "Ascending".
	 */
	bool CreateLeaderboard(
		const FString& Key,
		const FString& MemberType = TEXT("player"),
		const FString& Direction  = TEXT("Descending"));

	/**
	 * Create a trigger with unlimited invocations (limit = 0).
	 */
	bool CreateTrigger(const FString& Key, const FString& Name);

	/**
	 * Create a soft virtual currency and enable game-side writes on it.
	 * @param OutCurrencyId  Populated with the created currency's UUID.
	 */
	bool CreateCurrency(const FString& Name, const FString& Code, FString& OutCurrencyId);

	/**
	 * * Create a player progression with an additional tier at step = 2 so points can accumulate.
	 */
	bool CreateProgression(const FString& Key, const FString& Name);

	/**
	 * Create an asset (default context) and activate it.
	 * @param OutAssetId  Populated with the numeric asset ID.
	 */
	bool CreateAsset(int32& OutAssetId, const FString& Name);

	/**
	 * Grant an asset instance to a player identified by legacy player_id.
	 * @param PlayerLegacyId  Numeric legacy player ID (player_id), passed as a string.
	 * @param OutInstanceId   Populated with the created asset instance ID.
	 */
	bool GrantAssetToPlayer(const FString& PlayerLegacyId, int32 AssetId, int32& OutInstanceId);

	/**
	 * Create a broadcast visible to this game.
	 * The broadcast is published immediately (start = now, no end).
	 * @param Name         Internal broadcast name.
	 * @param Headline     English headline text.
	 * @param Body         English body text.
	 * @param OutBroadcastId  Populated with the created broadcast's UUID string.
	 */
	bool CreateBroadcast(const FString& Name, const FString& Headline, const FString& Body, FString& OutBroadcastId);

	/**
	 * List broadcasts for this organisation via the admin API (synchronous).
	 * Invokes OnComplete inline before returning.
	 * @param Languages  Language codes to filter localizations (e.g. {"en"}).
	 * @param Limit      Maximum number of broadcasts to return.
	 * @param OnComplete Called with the parsed response.
	 */
	void ListBroadcasts(
		const TArray<FString>& Languages,
		int32 Limit,
		TFunction<void(const FLootLockerAdminListBroadcastsResponse&)> OnComplete) const;

	// ─── SDK initialization ───────────────────────────────────────────────────

	/**
	 * Configure ULootLockerConfig with this game's credentials so that subsequent
	 * SDK calls (GuestLogin etc.) target the provisioned game.
	 * Call this after game creation and feature enablement, before StartSession().
	 */
	void InitializeLootLockerSDK() const;
};

#endif // ENGINE_MAJOR_VERSION > 4
