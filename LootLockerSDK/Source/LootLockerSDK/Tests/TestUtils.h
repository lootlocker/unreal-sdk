#pragma once
#include "HAL/PlatformMisc.h"
#include "LootLockerConfig.h"
#include "LootLockerPlatformManager.h"
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

		const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAuthenticationResponse,FLootLockerSessionResponse>();

		ULootLockerSDKManager::GuestLogin(Delegate, TEXT("unreal_unit_test_user"));

		const auto Response = Promise->get_future().get();
		FLootLockerPlayerData NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, "", "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest), FDateTime::Now().ToString(), Response.player_created_at);
		ULootLockerStateData::SavePlayerData(NewPlayerData);
		delete(Promise);
	}

	inline void EndSession()
	{
	}
}
#endif
