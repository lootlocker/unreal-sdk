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
    FString SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders = TMap<FString, FString>()) const;
    FString UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString>& AdditionalFields, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders = TMap<FString, FString>()) const;

    static void LogSuccessfulRequestInformation(const FLootLockerResponse& Response, const FString& AllHeadersDelimited);
    static void LogFailedRequestInformation(const FLootLockerResponse& Response, const FString& AllHeadersDelimited);

    // Singleton accessors. These create the UObject on demand in the transient package.
    // Use Get() when you need a UObject pointer, or GetRef() for convenient dereferencing (ensure not null).
    static ULootLockerHttpClient* Get();
    static ULootLockerHttpClient& GetRef();
private:
    static bool ResponseIsSuccess(const FHttpResponsePtr& InResponse, bool bWasSuccessful);
    static TMap<FString, FLootLockerRequestParameterValue> ParseRequestParametersFromJsonString(FString jsonString);
    static const FString UserAgent;
    static const FString UserInstanceIdentifier;
    static FString SDKVersion;

    // Internal singleton instance (weak to allow GC if nothing else holds it; we keep a strong ref in creation scope)
    static TWeakObjectPtr<ULootLockerHttpClient> SingletonInstance;
    static FCriticalSection SingletonMutex; // to guard creation in multithreaded contexts
};



