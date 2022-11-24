﻿#pragma once
#include "LootLockerPersistentData.h"

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
		
		ULootLockerSDKManager::StartSession("1", Delegate);

		const auto Response = Promise ->get_future().get();
		ULootLockerPersistentData::Token = Response.session_token;
		delete(Promise);
	}

	inline void EndSession()
	{
	}
}
#endif
