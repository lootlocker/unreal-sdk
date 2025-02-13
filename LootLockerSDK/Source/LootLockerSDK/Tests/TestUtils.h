#pragma once
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
		const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerAuthenticationResponse,FLootLockerSessionResponse>();

		ULootLockerSDKManager::GuestLogin(Delegate, TEXT("unreal_unit_test_user"));

		const auto Response = Promise->get_future().get();
		FLootLockerPlayerData NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, "", Response.player_identifier, Response.player_ulid, Response.public_uid, "", "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest), FDateTime::Now().ToString());
		ULootLockerStateData::SavePlayerData(NewPlayerData);
		delete(Promise);
	}

	inline void EndSession()
	{
	}
}
#endif
