// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/Base64.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerUserGeneratedContentRequestHandler::HttpClient = nullptr;

ULootLockerUserGeneratedContentRequestHandler::ULootLockerUserGeneratedContentRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(const FLootLockerAssetCandidate2& AsssetCandidate, const FCreateAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerCreateAssetCandidateResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerCreateAssetCandidateResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("CreateAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FLootLockerAssetCandidate2::StaticStruct(), &AsssetCandidate, ContentString, 0, 0);
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::CreateAssetCandidateEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(int AssetCandidateId, const FLootLockerAssetCandidate2& AsssetCandidate, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetCandidateResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetCandidateResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("UpdateAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FLootLockerAssetCandidate2::StaticStruct(), &AsssetCandidate, ContentString, 0, 0);
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::UpdateAssetCandidateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    FResponseCallback  sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("DeleteAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::DeleteAssetCandidateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(const FAssetCandidatesResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetCandidatesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetCandidatesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetAllAssetCandidates failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetAllAssetCandidatesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerAssetCandidateResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerAssetCandidateResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetAssetCandidateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    FResponseCallback  sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
    {
        FLootLockerResponse ResponseStruct;

        ResponseStruct.success = response.success;
        if (response.success)
        {
            FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
        }
        else {
            UE_LOG(LogLootLocker, Error, TEXT("AddFileToAssetCandidate failed from lootlocker"));
        }
        ResponseStruct.FullTextFromServer = response.FullTextFromServer;
        OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
        OnCompletedRequest.ExecuteIfBound(ResponseStruct);
    });
    
    FString purpose = ULootLockerConfig::GetEnum(TEXT("ELootLockerAssetFilePurpose"), static_cast<int32>(FilePurpose));

    TMap<FString, FString> AdditionalData;
    AdditionalData.Add("purpose", purpose);
    
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::AddFileToAssetCandidateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->UploadFile(endpoint, requestMethod, FilePath, AdditionalData, sessionResponse, true);
}

void ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("DeleteFileFromAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId, FileId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
