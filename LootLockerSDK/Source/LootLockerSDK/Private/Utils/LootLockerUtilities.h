// Copyright (c) 2021 LootLocker

#pragma once

#include "Dom/JsonValue.h"
#include "LootLockerConfig.h"
#include "LootLockerStateData.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerSDK.h"
#include "GameAPI/LootLockerCharacterRequestHandler.h"
#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "LootLockerUtilities.generated.h"

constexpr FLootLockerEmptyRequest LootLockerEmptyRequest;

const TMultiMap<FString,FString> EmptyQueryParams;

struct FObfuscationDetails
{
    FString key;
    FString replacementChar;
    int visibleCharsFromBeginning = 0;
    int visibleCharsFromEnd = 0;
    bool hideCharactersForShortStrings = false;

    FObfuscationDetails(const FString& Key, const FString& ReplacementChar, int VisibleCharsFromBeginning, int VisibleCharsFromEnd, bool HideCharactersForShortStrings)
        : key(Key), replacementChar(ReplacementChar), visibleCharsFromBeginning(VisibleCharsFromBeginning),
        visibleCharsFromEnd(VisibleCharsFromEnd), hideCharactersForShortStrings(HideCharactersForShortStrings)
    {
    }
};

struct UObfuscationSettings
{
    static const TArray<FObfuscationDetails> FieldsToObfuscate;
};

UCLASS()
class LOOTLOCKERSDK_API ULootLockerEnumUtils : public UObject
{
    GENERATED_BODY()
public:
    static FString GetEnum(const TCHAR* Enum, int32 EnumValue);
};

namespace LootLockerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter);

    TArray<FLootLockerMissionCheckpoint> ParseMissionCheckpoints(const TSharedPtr<FJsonObject>& MissionJson);

    TArray<TSharedPtr<FJsonValue>> SerializeMissionCheckpoints(const TArray<FLootLockerMissionCheckpoint>& Checkpoints);

    template<typename T>
    static FString JsonStringWithTopLevelArrayOfObjects(const TArray<T>& ItemArray)
    {
        TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
        for (auto Item : ItemArray)
        {
            TSharedRef<FJsonObject> ItemJson = MakeShareable(new FJsonObject());
            if (FJsonObjectConverter::UStructToJsonObject(T::StaticStruct(), &Item, ItemJson, 0, 0))
            {
                ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(ItemJson)));
            }
        }

        FString JsonString;
        const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
        FJsonSerializer::Serialize(ItemsJsonArray, Writer);
        return JsonString;
    }

    FString FStringFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject);

    FString FStringFromJsonArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray);

    TSharedPtr<FJsonObject> JsonObjectFromFString(const FString& JsonString);

    bool JsonArrayFromFString(const FString& JsonString, TArray<TSharedPtr<FJsonValue>>& JsonArrayOutput);

    FString ObfuscateJsonStringForLogging(const FString& JsonBody);

    FString ObfuscateJsonStringForLogging(const TArray<FObfuscationDetails>& ObfuscationDetails, const FString& JsonBody);

    FString ObfuscateString(const FObfuscationDetails& ObfuscationDetail, const FString& StringToObfuscate);

    static bool IsEmptyJsonString(const FString& JsonString)
    {
        return JsonString.Equals(FString("{}")) ||
            JsonString.Equals(FString("{\r\n}")) ||
            JsonString.Equals(FString("{\n}")) ||
            JsonString.Equals(FString("{ }"));
    }

    template<typename RequestType>
    static FString UStructToJsonString(RequestType RequestStruct)
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
        return ContentString;
    }

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
            ResponseStruct.success = response.success;
            ResponseStruct.StatusCode = response.StatusCode;
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            if (!ResponseStruct.success)
            {
                ResponseStruct.ErrorData = response.ErrorData;
            }
            ResponseInspectorCallback.ExecuteIfBound(ResponseStruct);
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });
        return sessionResponse;
    }

    template<typename RequestType, typename BluePrintDelegate , typename CppDelegate>
    static void CallAPI(ULootLockerHttpClient* HttpClient, RequestType RequestStruct, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const FResponseInspectorCallback& ResponseInspectorCallback = LLAPI<ResponseType>::FResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
    {
        FString ContentString = LootLockerUtilities::UStructToJsonString(RequestStruct);
        LLAPI<ResponseType>::CallAPIUsingRawJSON(HttpClient, ContentString, Endpoint, InOrderedArguments, QueryParams, OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback, CustomHeaders);
    }

    template<typename BluePrintDelegate, typename CppDelegate>
    static void CallAPIUsingRawJSON(ULootLockerHttpClient* HttpClient, FString& ContentString, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMultiMap<FString, FString> QueryParams, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const FResponseInspectorCallback& ResponseInspectorCallback = LLAPI<ResponseType>::FResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
    {
        // calculate endpoint
        const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
        FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, FStringFormatNamedArguments{ {"domainKey", Config && !Config->DomainKey.IsEmpty() ? Config->DomainKey + "." : ""} });
        EndpointWithArguments = FString::Format(*EndpointWithArguments, InOrderedArguments);
        const FString& Token = ULootLockerStateData::GetToken();
        if (!Token.IsEmpty())
        {
            CustomHeaders.Add(TEXT("x-session-token"), Token);	        
        }

        if (QueryParams.Num() != 0)
        {
            FString Delimiter = "?";
            for (const TPair<FString, FString>& Pair : QueryParams)
            {
                EndpointWithArguments = EndpointWithArguments + Delimiter + Pair.Key + "=" + Pair.Value;
                Delimiter = "&";
            }
        }
        const FString RequestMethod = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
#if WITH_EDITOR
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("Request:"));
        if (!ContentString.IsEmpty() && !LootLockerUtilities::IsEmptyJsonString(ContentString)) {
            UE_LOG(LogLootLockerGameSDK, Log, TEXT("ContentString:%s"), *LootLockerUtilities::ObfuscateJsonStringForLogging(ContentString));
        }
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("EndpointWithArguments: %s to %s"), *RequestMethod, *EndpointWithArguments);
#endif //WITH_EDITOR

        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);

        // send request
        HttpClient->SendApi(EndpointWithArguments, RequestMethod, ContentString, SessionResponse, CustomHeaders);
    }

    template<typename BluePrintDelegate, typename CppDelegate>
    static void UploadFileAPI(ULootLockerHttpClient* HttpClient, FString File, FLootLockerEndPoints Endpoint, const TArray<FStringFormatArg>& InOrderedArguments, const TMap<FString, FString> AdditionalData, const BluePrintDelegate& OnCompletedRequestBP, const CppDelegate& OnCompletedRequest, const FResponseInspectorCallback& ResponseInspectorCallback = LLAPI<ResponseType>::FResponseInspectorCallback::CreateLambda([](const ResponseType& Ignored) {}), TMap<FString, FString> CustomHeaders = TMap<FString, FString>())
    {
        
        // calculate endpoint
        const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
        FString EndpointWithArguments = FString::Format(*Endpoint.endpoint, FStringFormatNamedArguments{ {"domainKey", Config && !Config->DomainKey.IsEmpty() ? Config->DomainKey + "." : ""} });
        EndpointWithArguments = FString::Format(*EndpointWithArguments, InOrderedArguments);
        
        const FString RequestMethod = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
        const FString& Token = ULootLockerStateData::GetToken();
        if (!Token.IsEmpty())
        {
            CustomHeaders.Add(TEXT("x-session-token"), Token);
        }

#if WITH_EDITOR
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("Request:"));
        UE_LOG(LogLootLockerGameSDK, Log, TEXT("EndpointWithArguments:%s"), *EndpointWithArguments);
#endif //WITH_EDITOR

        // create callback lambda
        const FResponseCallback SessionResponse = CreateLambda<BluePrintDelegate, CppDelegate>(OnCompletedRequestBP, OnCompletedRequest, ResponseInspectorCallback);

        // send request
        HttpClient->UploadFile(EndpointWithArguments, RequestMethod, File, AdditionalData, SessionResponse, CustomHeaders);
    }
};
