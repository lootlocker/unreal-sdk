// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerPlayerData.h"
#include "LootLockerResponse.h"
#include "Interfaces/IHttpRequest.h"
#include "LootLockerHttpClient.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ULootLockerHttpClient : public UObject
{
	GENERATED_BODY()

public:
    ULootLockerHttpClient();
    void SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders = TMap<FString, FString>()) const;
    void UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString>& AdditionalFields, const FResponseCallback& onCompleteRequest, const FLootLockerPlayerData& PlayerData, TMap<FString, FString> customHeaders = TMap<FString, FString>()) const;

    static void LogSuccessfulRequestInformation(const FLootLockerResponse& Response, const FString& RequestMethod, const FString& Endpoint, const FString& Data, const FString& AllHeadersDelimited);
    static void LogFailedRequestInformation(const FLootLockerResponse& Response, const FString& RequestMethod, const FString& Endpoint, const FString& Data, const FString& AllHeadersDelimited);
private:
    static bool ResponseIsSuccess(const FHttpResponsePtr& InResponse, bool bWasSuccessful);
    static const FString UserAgent;
    static const FString UserInstanceIdentifier;
    static FString SDKVersion;
};



