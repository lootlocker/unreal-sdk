// Copyright (c) 2021 LootLocker

#pragma once

#include "LootLockerStateData.h"
#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "LootLockerConfig.h"
#include "LootLockerRequiresManualPostSerialization.h"

constexpr FLootLockerEmptyRequest LootLockerEmptyRequest;

const TMultiMap<FString,FString> EmptyQueryParams;

namespace LootLockerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter);

    TArray<FLootLockerMissionCheckpoint> ParseMissionCheckpoints(const TSharedPtr<FJsonObject>& MissionJson);

    TArray<TSharedPtr<FJsonValue>> SerializeMissionCheckpoints(const TArray<FLootLockerMissionCheckpoint>& Checkpoints);

    class CurrentPlatformFString
    {
    public:
        static FString Get()
        {
            if (PlatformOverride.Compare(EmptyFString) == 0)
            {
                const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
                return ULootLockerConfig::GetEnum(TEXT("ELootLockerPlatformType"), static_cast<int32>(Config->Platform));
            } else
            {
                return PlatformOverride;
            }
        }
        static void Override(FString Override)
        {
            PlatformOverride = Override;
        }
        static void Reset()
        {
            PlatformOverride = EmptyFString;
        }
    private:
        static const FString EmptyFString;
        static FString PlatformOverride;
    };

    TSharedPtr<FJsonObject> JsonObjectFromFString(const FString& JsonString);
}

template<typename ResponseType>
struct LLAPI
{
    DECLARE_DELEGATE_OneParam(ResponseInspectorCallback, ResponseType&);
    template<typename BluePrintDelegate, typename CppDelegate>
    static FResponseCallback CreateLambda(const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const ResponseInspectorCallback& ResponseInspectorCallback = ResponseInspectorCallback())
    {
        FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback](FLootLockerResponse response)
        {
            ResponseType ResponseStruct;
            
            if(!response.FullTextFromServer.IsEmpty())
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<ResponseType>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                ResponseStruct.ManualPostDeserialization(response.FullTextFromServer);
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
    static void CallAPI(ULootLockerHttpClient* HttpClient, RequestType RequestStruct, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, bool useDomainKey = false, bool useDevHeaders = false, const ResponseInspectorCallback& ResponseInspectorCallback = ResponseInspectorCallback())
    {
        FString ContentString;        
        if (!std::is_same_v<RequestType, FLootLockerEmptyRequest>) 
        {
            TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(RequestStruct);
            if (std::is_base_of<FLootLockerRequiresManualPostSerialization, RequestType>())
            {
                ((FLootLockerRequiresManualPostSerialization*)&RequestStruct)->DoManualPostDeserialization(JsonObject);
            }
            FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&ContentString), true);
        }
        
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
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("Request:"));
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("ContentString:%s"), *ContentString);
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("EndpointWithArguments:%s"), *EndpointWithArguments);
        const FString RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));

        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);

        // send request
        HttpClient->SendApi(EndpointWithArguments, RequestMethod, ContentString, SessionResponse, true, useDomainKey, useDevHeaders);
    }

    template<typename BluePrintDelegate, typename CppDelegate>
    static void UploadFileAPI(ULootLockerHttpClient* HttpClient, FString File, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMap<FString, FString> AdditionalData, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const ResponseInspectorCallback& ResponseInspectorCallback = ResponseInspectorCallback())
    {
        
        // calculate endpoint
        const FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, InOrderedArguments);
        
        const FString RequestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("Request:"));
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("EndpointWithArguments:%s"), *EndpointWithArguments);

        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);

        // send request
        HttpClient->UploadFile(EndpointWithArguments, RequestMethod, File, AdditionalData, SessionResponse, true);
    }

    template<typename BluePrintDelegate , typename CppDelegate>
    static void CallAPIUsingRawJSON(ULootLockerHttpClient* HttpClient, FString& ContentString, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const ResponseInspectorCallback& ResponseInspectorCallback = ResponseInspectorCallback())
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

        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);
    
        // send request
        HttpClient->SendApi(EndpointWithArguments, RequestMethod, ContentString, SessionResponse, true);
    }
};
