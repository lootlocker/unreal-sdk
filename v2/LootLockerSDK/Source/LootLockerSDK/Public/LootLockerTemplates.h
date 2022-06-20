#pragma once
#include "CoreMinimal.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "LootLockerHttpClient.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLootLockerTemplates, Log, All);
DEFINE_LOG_CATEGORY(LogLootLockerTemplates);

//==================================================
// Meta Template for API request resolvers.
//==================================================

/**
 * Meta Struct for API invoker
 * @param FResponseStruct  Response structure, e.g. what end user receives from their delegates.
 * @param OnComplete  C++ Delegate type
 * @param OnCompleteBP  Blueprint Delegate type
 * @see TLootLockerServerCall
 */
template <typename FResponseStruct>
struct TLootLockerServerCall{
	static TArray<FStringFormatArg> NoParams()
	{
		return *new TArray<FStringFormatArg>({});
	}
	/**
	 * Create FResponseStruct and copy generic values from FLootLockerResponse
	 * @param Response Unparsed FLootLockerResponse
	 * @returns FResponseStruct
	 */
	static FResponseStruct BuildResponse(const FLootLockerResponse& Response)
	{
		FResponseStruct ResponseStruct;
		ResponseStruct.success				= Response.success;
		ResponseStruct.ServerCallHasError	= Response.ServerCallHasError;
		ResponseStruct.ServerCallStatusCode	= Response.ServerCallStatusCode;
		ResponseStruct.ServerError			= Response.ServerError;
		ResponseStruct.message				= Response.message;
		ResponseStruct.error				= Response.error;
		ResponseStruct.FullTextFromServer	= Response.FullTextFromServer;
		if (Response.success)
		{
			if (!FJsonObjectConverter::JsonObjectStringToUStruct<FResponseStruct>(Response.FullTextFromServer, &ResponseStruct, 0, 0))
			{
				UE_LOG(LogLootLockerGameSDK, Error, TEXT("Failed to deserialize JSON property."));
			}
		}
		return ResponseStruct;
	}
	/**
	 * Invoke SendApi with our template parameters
	 * @param OnCompletedRequest
	 * @param OnCompletedRequestBP
	 * @param Endpoint
	 * @param UrlParams
	 * @param ContentString
	 * @param UseHeader
	 * @param UseAdmin
	 * @param UseDomainKey
	 * @param UseDevHeaders
	 */
	static void TInvoke
	(
		const TDelegate<void(FResponseStruct)>* OnCompletedRequest,
		const TBaseDynamicDelegate<FWeakObjectPtr, void, FResponseStruct>* OnCompletedRequestBP,
		const FLootLockerEndPoints& Endpoint,
		const TArray<FStringFormatArg>& UrlParams = {},
		const FString& ContentString = TEXT(""),
		const bool UseHeader = false,
		#ifdef LOOTLOCKER_SERVER_SDK
		const bool UseAdmin = true,
		#else
		const bool UseAdmin = false,
		#endif
		const bool UseDomainKey = false,
		const bool UseDevHeaders = false
	)
	{
		const FString RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
		const FString FormattedEndpoint = UrlParams.IsEmpty() ? FString::Format(*Endpoint.endpoint, UrlParams) : Endpoint.endpoint;

		NewObject<ULootLockerHttpClient>()->SendApi(
			*FormattedEndpoint,
			*RequestMethod,
			*ContentString,
			FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](const FLootLockerResponse& Response)
			{
				FResponseStruct ResponseStruct = BuildResponse(Response);
				// if (!OnCompletedRequestBP->ExecuteIfBound(ResponseStruct))
				// {
				// 	UE_LOG(LogLootLockerGameSDK, Error, TEXT("Failed to execute blueprint delegate."));
				// };
				// if (!OnCompletedRequest->ExecuteIfBound(ResponseStruct))
				// {
				// 	UE_LOG(LogLootLockerGameSDK, Error, TEXT("Failed to execute delegate."));
				// }
			},
			UseHeader,
			UseAdmin,
			UseDomainKey,
			UseDevHeaders
			),
		true);
	}
};
