// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerConfig.h"
#include "LootLockerStateData.h"
#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "Launch/Resources/Version.h"

constexpr FLootLockerEmptyRequest LootLockerEmptyRequest;

const TMultiMap<FString,FString> EmptyQueryParams;

namespace LootLockerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter);

    TArray<FLootLockerMissionCheckpoint> ParseMissionCheckpoints(const TSharedPtr<FJsonObject>& MissionJson);

    TArray<TSharedPtr<FJsonValue>> SerializeMissionCheckpoints(const TArray<FLootLockerMissionCheckpoint>& Checkpoints);

    TSharedPtr<FJsonObject> JsonObjectFromFString(const FString& JsonString);
}

template<typename ResponseType>
struct LLAPI
{
    DECLARE_DELEGATE_OneParam(FResponseInspectorCallback, ResponseType&);

    template<typename BluePrintDelegate, typename CppDelegate>
    static FResponseCallback CreateLambda(const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const FResponseInspectorCallback& ResponseInspectorCallback)
    {
        FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback](FLootLockerResponse response)
        {
            ResponseType ResponseStruct;
            
            if(!response.FullTextFromServer.IsEmpty())
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<ResponseType>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            if (response.ServerCallStatusCode == 200 || response.ServerCallStatusCode == 204)
            {
                ResponseStruct.success = true;
                if (ResponseStruct.session_token != "")
                {
                    ULootLockerStateData::SetToken(ResponseStruct.session_token);
                }
            }
            else
            {
                ResponseStruct.success = false;
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            ResponseInspectorCallback.ExecuteIfBound(ResponseStruct);
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });
        return sessionResponse;
    }

    template<typename RequestType, typename BluePrintDelegate , typename CppDelegate>
    static void CallAPI(ULootLockerHttpClient* HttpClient, RequestType RequestStruct, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const FResponseInspectorCallback& ResponseInspectorCallback = LLAPI<ResponseType>::FResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
    {
        FString ContentString;
#if ENGINE_MAJOR_VERSION < 5
        FJsonObjectConverter::UStructToJsonObjectString(RequestType::StaticStruct(), &RequestStruct, ContentString, 0, 0);
        if (IsEmptyJsonString(ContentString))
        {
            ContentString = FString();
        }
#else
        if (!std::is_same_v<RequestType, FLootLockerEmptyRequest>)
        {
            FJsonObjectConverter::UStructToJsonObjectString(RequestType::StaticStruct(), &RequestStruct, ContentString, 0, 0);
        }
#endif
        
        // calculate endpoint
        FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, InOrderedArguments);
        CustomHeaders.Add(TEXT("x-session-token"), ULootLockerStateData::GetToken());

        if (QueryParams.Num() != 0)
        {
            FString Delimiter = "?";
            for (const TPair<FString, FString>& Pair : QueryParams)
            {
                EndpointWithArguments = EndpointWithArguments + Delimiter + Pair.Key + "=" + Pair.Value;
                Delimiter = "&";
            }
        }
#if WITH_EDITOR
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("Request:"));
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("ContentString:%s"), *ContentString);
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("EndpointWithArguments:%s"), *EndpointWithArguments);
#endif //WITH_EDITOR
        const FString RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);

        // send request
        HttpClient->SendApi(EndpointWithArguments, RequestMethod, ContentString, SessionResponse, CustomHeaders);
    }

    template<typename BluePrintDelegate, typename CppDelegate>
    static void UploadFileAPI(ULootLockerHttpClient* HttpClient, FString File, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMap<FString, FString> AdditionalData, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const FResponseInspectorCallback& ResponseInspectorCallback = LLAPI<ResponseType>::FResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
    {
        
        // calculate endpoint
        const FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, InOrderedArguments);
        
        const FString RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
        CustomHeaders.Add(TEXT("x-session-token"), ULootLockerStateData::GetToken());

#if WITH_EDITOR
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("Request:"));
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("EndpointWithArguments:%s"), *EndpointWithArguments);
#endif //WITH_EDITOR

        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);

        // send request
        HttpClient->UploadFile(EndpointWithArguments, RequestMethod, File, AdditionalData, SessionResponse, CustomHeaders);
    }

    template<typename BluePrintDelegate , typename CppDelegate>
    static void CallAPIUsingRawJSON(ULootLockerHttpClient* HttpClient, FString& ContentString, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const FResponseInspectorCallback& ResponseInspectorCallback = LLAPI<ResponseType>::FResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
    {
        
        // calculate endpoint
        FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, InOrderedArguments);

        if (QueryParams.Num() != 0)
        {
            FString Delimiter = "?";
            for (const TPair<FString, FString>& Pair : QueryParams)
            {
                EndpointWithArguments = EndpointWithArguments + Delimiter + Pair.Key + "=" + Pair.Value;
                Delimiter = "&";
            }
        }
        
        const FString RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
        CustomHeaders.Add(TEXT("x-session-token"), GetDefault<ULootLockerConfig>()->LootLockerGameKey);

        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);
    
        // send request
        HttpClient->SendApi(EndpointWithArguments, RequestMethod, ContentString, SessionResponse, CustomHeaders);
    }

private:
    static bool IsEmptyJsonString(const FString& JsonString)
    {
        return JsonString.Equals(FString("{}")) ||
            JsonString.Equals(FString("{\r\n}")) ||
            JsonString.Equals(FString("{\n}")) ||
            JsonString.Equals(FString("{ }"));
    }
};
