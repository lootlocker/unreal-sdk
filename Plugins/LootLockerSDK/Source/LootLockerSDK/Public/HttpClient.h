// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/IHttpRequest.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "LootLockerConfig.h"
#include "LootLockerPersitentDataHolder.h"
#include "HttpClient.generated.h"

UCLASS()
class LOOTLOCKERSDK_API UHttpClient : public UObject
{
	GENERATED_BODY()
    
public:
    UHttpClient();
    void SendApi(const FString& endPoint, const FString& requestType, const FString& data, const FResponseCallback& onCompleteRequest, const bool& useHeader = false);
    void TokenRefresh(const FResponseCallback onCompleteRequest);
    void VerifyRefresh(const FResponseCallback onCompleteRequest);
    void UploadFile(const FString& endPoint, const FString& requestType, const FString& Boundary, const TArray<uint8>& data, const FResponseCallback& onCompleteRequest, const bool& useHeader = false);
public:
    bool ResponseIsValid(const FHttpResponsePtr& InResponse, const bool& bWasSuccessful);
    FResponseCallback savedOnCompleteRequest;
    FResponseCallback verifyRefreshCompleteRequest;
    FResponseCallback refreshCompleteRequest;
};



