// Copyright (c) 2021 LootLocker

#pragma once

#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "GameAPI/LootLockerMissionsRequestHandler.h"

constexpr FLootLockerEmptyRequest LootLockerEmptyRequest;

const TMap<FString,FString> EmptyQueryParams;

namespace LootLockerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter);

    TArray<FLootLockerMissionCheckpoint> ParseMissionCheckpoints(const TSharedPtr<FJsonObject>& MissionJson);

    TArray<TSharedPtr<FJsonValue>> SerializeMissionCheckpoints(const TArray<FLootLockerMissionCheckpoint>& Checkpoints);
}

template<typename W>
struct LLAPI
{
    template<typename T, typename U>
    static FResponseCallback CreateLambda(const T& OnCompletedRequestBP, const U& OnCompletedRequest)
    {
        FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            W ResponseStruct;
            if (response.success)
            {
                ResponseStruct.success = FJsonObjectConverter::JsonObjectStringToUStruct<W>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                if (ResponseStruct.session_token != "")
                {
                    ULootLockerPersistentDataHolder::Token = ResponseStruct.session_token;
                }
            }
            else
            {
                ResponseStruct.success = false;
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });
        return sessionResponse;
    }

    template<typename S, typename T , typename U>
    static void CallAPI(ULootLockerHttpClient* HttpClient, S RequestStruct, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMap<FString,FString> QueryParams,  const T& OnCompletedRequestBP, const U& OnCompletedRequest)
    {
        FString ContentString;        
        if (!std::is_same_v<S, FLootLockerEmptyRequest>) 
        {
            FJsonObjectConverter::UStructToJsonObjectString(S::StaticStruct(), &RequestStruct, ContentString, 0, 0);
        }
		  
        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<T,U>(OnCompletedRequestBP, OnCompletedRequest);
        
        // calculate endpoint
        FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, InOrderedArguments);

        if (!QueryParams.Num() == 0)
        {
            FString Delimiter = "?";
            for (const TPair<FString, FString>& Pair : QueryParams)
            {
                EndpointWithArguments = EndpointWithArguments + Delimiter + Pair.Key + "=" + Pair.Value;
                Delimiter = "&";
            }
        }
        
        const FString RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    
        // send request
        HttpClient->SendApi(EndpointWithArguments, RequestMethod, ContentString, SessionResponse, true);
    }

    template<typename T , typename U>
    static void UploadFileAPI(ULootLockerHttpClient* HttpClient,FString File, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMap<FString, FString> AdditionalData,  const T& OnCompletedRequestBP, const U& OnCompletedRequest)
    {
        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<T,U>(OnCompletedRequestBP, OnCompletedRequest);
        
        // calculate endpoint
        FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, InOrderedArguments);
        
        const FString RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    
        // send request
        HttpClient->UploadFile(Endpoint.endpoint, RequestMethod, File, AdditionalData, SessionResponse, true);
    }

    template<typename T , typename U>
    static void CallAPIUsingRawJSON(ULootLockerHttpClient* HttpClient,FString& ContentString, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMap<FString,FString> QueryParams,  const T& OnCompletedRequestBP, const U& OnCompletedRequest)
    {
        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<T,U>(OnCompletedRequestBP, OnCompletedRequest);
        
        // calculate endpoint
        FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, InOrderedArguments);

        if (!QueryParams.Num() == 0)
        {
            FString Delimiter = "?";
            for (const TPair<FString, FString>& Pair : QueryParams)
            {
                EndpointWithArguments = EndpointWithArguments + Delimiter + Pair.Key + "=" + Pair.Value;
                Delimiter = "&";
            }
        }
        
        const FString RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    
        // send request
        HttpClient->SendApi(EndpointWithArguments, RequestMethod, ContentString, SessionResponse, true);
    }
};
