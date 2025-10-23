// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerPlayerData.h"
#include "LootLockerRequestContext.h"
#include "LootLockerResponse.h"
#include "Interfaces/IHttpRequest.h"
#include "LootLockerHttpClient.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ULootLockerHttpClient : public UObject
{
	GENERATED_BODY()
     
public:
    ULootLockerHttpClient();
    static FString SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders = TMap<FString, FString>(), bool bIsRetryAttempt = false);
    static FString UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString>& AdditionalFields, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders = TMap<FString, FString>(), bool bIsRetryAttempt = false);

    static void LogSuccessfulRequestInformation(const FLootLockerResponse& Response, const FString& AllHeadersDelimited);
    static void LogFailedRequestInformation(const FLootLockerResponse& Response, const FString& AllHeadersDelimited);
private:
    static bool ResponseIsSuccess(const FHttpResponsePtr& InResponse, bool bWasSuccessful);
    
    // Token refresh functionality
    static bool ShouldRefreshSession(int32 StatusCode, const FLootLockerPlayerData& PlayerData, bool bIsRetryAttempt = false);
    static bool CanRefreshSession(const FLootLockerPlayerData& PlayerData);
    static void RefreshSessionForPlatform(const FLootLockerPlayerData& PlayerData, TFunction<void(bool)> OnRefreshCompleted);
    
    // Structure to hold original request data for retry after refresh
    struct FLootLockerRetryRequestData
    {
        FString EndPoint;
        FString RequestType;
        FString Data;
        FResponseCallback OnCompleteRequest;
        FLootLockerPlayerData PlayerData;
        TMap<FString, FString> CustomHeaders;
        bool bIsFileUpload = false;
        bool bIsRetryAttempt = false;
        FString FilePath;
        TMap<FString, FString> AdditionalFields;
        
        FLootLockerRetryRequestData() = default;
        
        // Constructor for regular API calls
        FLootLockerRetryRequestData(const FString& InEndPoint, const FString& InRequestType, const FString& InData, 
                                   const FResponseCallback& InOnCompleteRequest, const FLootLockerPlayerData& InPlayerData, 
                                   const TMap<FString, FString>& InCustomHeaders, bool InIsRetryAttempt = false)
            : EndPoint(InEndPoint), RequestType(InRequestType), Data(InData), OnCompleteRequest(InOnCompleteRequest)
            , PlayerData(InPlayerData), CustomHeaders(InCustomHeaders), bIsFileUpload(false), bIsRetryAttempt(InIsRetryAttempt) {}
        
        // Constructor for file upload calls
        FLootLockerRetryRequestData(const FString& InEndPoint, const FString& InRequestType, const FString& InFilePath,
                                   const TMap<FString, FString>& InAdditionalFields, const FResponseCallback& InOnCompleteRequest, 
                                   const FLootLockerPlayerData& InPlayerData, const TMap<FString, FString>& InCustomHeaders, bool InIsRetryAttempt = false)
            : EndPoint(InEndPoint), RequestType(InRequestType), OnCompleteRequest(InOnCompleteRequest)
            , PlayerData(InPlayerData), CustomHeaders(InCustomHeaders), bIsFileUpload(true), bIsRetryAttempt(InIsRetryAttempt)
            , FilePath(InFilePath), AdditionalFields(InAdditionalFields) {}
    };
    
    static void RetryOriginalRequest(const FLootLockerRetryRequestData& RetryData);
    
    static const FString UserAgent;
    static const FString UserInstanceIdentifier;
    static FString SDKVersion;

    static TWeakObjectPtr<ULootLockerHttpClient> SingletonInstance;
    static FCriticalSection SingletonMutex;
};



