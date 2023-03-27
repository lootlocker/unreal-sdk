#pragma once
#include "LootLockerStateData.h"
#include "Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION > 4
namespace test_util
{
	static FString PlayerIdentifier = "1";

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

		const auto Response = Promise ->get_future().get();
		ULootLockerStateData::SetToken(Response.session_token);
		delete(Promise);
	}

	inline void StartGuestSession(FString& OutPlayerId)
	{
		const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerAuthenticationResponse, FLootLockerSessionResponse>();

		ULootLockerSDKManager::GuestLogin(Delegate, PlayerIdentifier);

		const auto Response = Promise->get_future().get();
		ULootLockerStateData::SetToken(Response.session_token);
		OutPlayerId = FString::Printf(TEXT("%i"), Response.player_id);
		delete(Promise);
	}

	inline void StartServerSession()
	{
		const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerAuthenticationResponse, FServerAuthResponseDelegate>();

		ULootLockerSDKManager::Server_StartSession(Delegate);

		const auto Response = Promise->get_future().get();
		delete(Promise);
	}

	inline void EndServerSession()
	{
		const auto [Promise, Delegate] = test_util::CreateDelegate<FLootLockerServerEndSessionResponse, FServerEndSessionResponseDelegate>();

		ULootLockerSDKManager::Server_EndSession(Delegate);

		const auto Response = Promise->get_future().get();
		delete(Promise);
	}

	inline void EndSession()
	{
	}
}
#endif
