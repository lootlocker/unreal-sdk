// Copyright (c) 2021 LootLocker

#pragma once

#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION > 4

#include "CoreMinimal.h"

/**
 * Response from an admin API call.
 */
struct FLootLockerAdminResponse
{
	bool    bSuccess   = false;
	int32   StatusCode = 0;
	FString Body;
};

/**
 * Synchronous (blocking) HTTP transport for the LootLocker admin API.
 *
 * Intended exclusively for use in automation test code. All Send() calls block the
 * calling thread until a response is received — safe to call from LatentIt thread-pool
 * executors alongside the std::promise-based helpers already used in TestUtils.h.
 *
 * Credentials are resolved in order:
 *   1. Environment variables: LOOTLOCKER_ADMIN_EMAIL, LOOTLOCKER_ADMIN_PASSWORD
 *   2. Command-line args:     -adminemail=<email>  -adminpassword=<password>
 *
 * The admin API base URL defaults to https://api.lootlocker.io/ and can be
 * overridden via the LOOTLOCKER_ADMIN_API_URL env var.
 */
class FLootLockerAdminRequest
{
public:
	/** Admin bearer token obtained after Login(). Stored statically for the whole test run. */
	static FString AdminToken;

	/** Organisation ID extracted from the login response. Required when creating games. */
	static int32 OrganisationId;

	/** The currently active game ID. Substituted for #GAMEID# in all endpoint paths. */
	static int32 ActiveGameId;

	/**
	 * Ensure the admin user is signed in.
	 * Reads credentials from env vars / command-line args and calls Login() if needed.
	 * Returns false if credentials are unavailable or login fails.
	 */
	static bool EnsureSignedIn();

	/**
	 * Authenticate with the given credentials and populate AdminToken / OrganisationId.
	 */
	static bool Login(const FString& Email, const FString& Password);

	/**
	 * Send a synchronous (blocking) admin API request.
	 *
	 * #GAMEID# in Endpoint is replaced with ActiveGameId before the request is sent.
	 * Automatically retries up to MaxRetries times on HTTP 429 (rate limited), honouring
	 * the retry_after_seconds field in the response body.
	 *
	 * @param Endpoint  Path relative to the admin base URL.
	 *                  Examples: "v1/game", "game/#GAMEID#/leaderboards"
	 * @param Method    HTTP verb as an uppercase string: GET, POST, PUT, DELETE, PATCH.
	 * @param JsonBody  JSON request body. Pass an empty string for bodyless requests.
	 */
	static FLootLockerAdminResponse Send(
		const FString& Endpoint,
		const FString& Method,
		const FString& JsonBody = TEXT(""));

	/** Returns the admin base URL (LOOTLOCKER_ADMIN_API_URL env var, or https://api.lootlocker.io/). */
	static FString GetBaseUrl();

private:
	static constexpr int32 MaxRetries = 10;

	static bool GetCredentials(FString& OutEmail, FString& OutPassword);

	/** Execute a single HTTP request without any retry logic. */
	static FLootLockerAdminResponse SendOnce(
		const FString& FullUrl,
		const FString& Method,
		const FString& JsonBody);
};

#endif // ENGINE_MAJOR_VERSION > 4
