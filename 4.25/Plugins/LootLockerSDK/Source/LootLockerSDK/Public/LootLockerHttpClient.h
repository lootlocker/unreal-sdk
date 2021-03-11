// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerGameEndpoints.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "LootLockerConfig.h"
#include "Runtime/Launch/Resources/Version.h"
#include "LootLockerHttpClient.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ULootLockerHttpClient : public UObject
{
	GENERATED_BODY()
    
public:
    ULootLockerHttpClient();
    void SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, bool useHeader = false, bool useAdmin = false);
    void TokenRefresh(const FResponseCallback onCompleteRequest);
    void VerifyRefresh(const FResponseCallback onCompleteRequest);
    void UploadFile(const FString& endPoint, const FString& requestType, const FString& FilePath, const TMap<FString, FString> AdditionalFields, const FResponseCallback& onCompleteRequest, bool useHeader = false, bool useAdmin = false);
public:
    bool ResponseIsValid(const FHttpResponsePtr& InResponse, bool bWasSuccessful);
    FResponseCallback savedOnCompleteRequest;
    FResponseCallback verifyRefreshCompleteRequest;
    FResponseCallback refreshCompleteRequest;
};



