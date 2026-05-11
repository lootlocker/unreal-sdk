#pragma once
#include <chrono>
#include <future>
#include "HAL/PlatformMisc.h"
#include "LootLockerConfig.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerSessionOptionals.h"
#include "LootLockerStateData.h"

#if ENGINE_MAJOR_VERSION > 4
namespace test_util
{
	template <typename ResponseType,typename DelegateType>
	static std::pair<std::promise<ResponseType>*,DelegateType> CreateDelegate()
	{
		std::promise<ResponseType>* ResponsePromise = new std::promise<ResponseType>();

		DelegateType Delegate =
			DelegateType::CreateLambda(
				[ResponsePromise](const ResponseType Response)
				{
					ResponsePromise->set_value(Response);
				});

		return make_pair(ResponsePromise,Delegate);
	}

	/**
	 * Wait up to TimeoutSeconds for the promise to be fulfilled, then return the value.
	 * On success the promise is deleted. On timeout the promise is intentionally leaked
	 * (the HTTP callback may still fire and call set_value on it later).
	 * Returns a default-constructed (success=false) ResponseType on timeout.
	 */
	template <typename ResponseType>
	static ResponseType WaitAndGet(std::promise<ResponseType>* Promise, int32 TimeoutSeconds = 30)
	{
		std::future<ResponseType> Future = Promise->get_future();
		if (Future.wait_for(std::chrono::seconds(TimeoutSeconds)) == std::future_status::timeout)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("LootLockerTest: WaitAndGet timed out after %ds — the HTTP callback may still be in flight"),
				TimeoutSeconds);
			// Do NOT delete Promise: the in-flight callback may still call set_value.
			return ResponseType{};
		}
		ResponseType Result = Future.get();
		delete Promise;
		return Result;
	}


	inline void StartSession()
	{
		// Allow LOOTLOCKER_GAME_API_KEY env var to configure the SDK without project settings.
		// Useful for local test runs where admin provisioning is not available.
		// Tests that use FLootLockerTestGame::CreateGame() + InitializeLootLockerSDK() do not
		// need this — the config is already set before StartSession() is called.
		const FString EnvKey = FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_GAME_API_KEY"));
		if (!EnvKey.IsEmpty())
		{
			ULootLockerConfig* Config = GetMutableDefault<ULootLockerConfig>();
			Config->LootLockerGameKey = EnvKey;
			if (Config->GameVersion.IsEmpty())
			{
				Config->GameVersion = TEXT("0.0.0.1");
			}
			const FString DomainKey =
				FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_GAME_DOMAIN_KEY"));
			if (!DomainKey.IsEmpty())
			{
				Config->DomainKey = DomainKey;
			}
		}

		// Clear any saved state from a previous test so GuestLogin always creates a fresh session
		// for the newly-provisioned game instead of reusing a stale token from an old game.
		ULootLockerStateData::ClearAllSavedStates();

		const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAuthenticationResponse,FLootLockerSessionResponse>();

		FLootLockerSessionOptionals Optionals;
		Optionals.Timezone = TEXT("UTC");
		ULootLockerSDKManager::GuestLogin(Delegate, TEXT("unreal_unit_test_user"), Optionals);

		const auto Response = WaitAndGet(Promise, 60);
		if(!Response.success)
		{
			UE_LOG(LogTemp, Error, TEXT("LootLockerTest: GuestLogin failed in StartSession()"));
			return;
		}
		FLootLockerPlayerData NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, "", "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest), FDateTime::Now().ToString(), Response.player_created_at);
		ULootLockerStateData::SavePlayerData(NewPlayerData);
	}

	inline void EndSession()
	{
	}

	struct FTestPlayerSession
	{
		FString PlayerUlid;
		FString PlayerPublicUid;
		bool bSuccess = false;
	};

	/**
	 * Log in a second (or Nth) guest player and register their session data alongside the first player.
	 * Returns the new player's ULID and public UID so tests can reference them in ForPlayerWithUlid calls.
	 */
	inline FTestPlayerSession StartAdditionalSession()
	{
		const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAuthenticationResponse, FLootLockerSessionResponse>();
		FLootLockerSessionOptionals Optionals;
		Optionals.Timezone = TEXT("UTC");
		ULootLockerSDKManager::GuestLogin(Delegate, FGuid::NewGuid().ToString(), Optionals);
		const auto Response = WaitAndGet(Promise, 60);
		FTestPlayerSession Out;
		if (Response.success)
		{
			FLootLockerPlayerData NewPlayerData = FLootLockerPlayerData::Create(
				Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid,
				"", "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest),
				FDateTime::Now().ToString(), Response.player_created_at);
			ULootLockerStateData::SavePlayerData(NewPlayerData);
			Out.PlayerUlid = Response.player_ulid;
			Out.PlayerPublicUid = Response.public_uid;
			Out.bSuccess = true;
		}
		return Out;
	}
}
#endif
