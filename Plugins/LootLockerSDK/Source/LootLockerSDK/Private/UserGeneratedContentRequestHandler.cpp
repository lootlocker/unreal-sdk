// Fill out your copyright notice in the Description page of Project Settings.

#include "UserGeneratedContentRequestHandler.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/Base64.h"

FResponseCallback UUserGeneratedContentRequestHandler::sessionResponse = nullptr;
UHttpClient* UUserGeneratedContentRequestHandler::HttpClient = nullptr;

UUserGeneratedContentRequestHandler::UUserGeneratedContentRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UUserGeneratedContentRequestHandler::CreateAssetCandidate(const FAssetCandidate& AsssetCandidate, const FCreateAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FCreateAssetCandidateResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FCreateAssetCandidateResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("CreateAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FAssetCandidate::StaticStruct(), &AsssetCandidate, ContentString, 0, 0);
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->CreateAssetCandidateEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UUserGeneratedContentRequestHandler::UpdateAssetCandidate(int AssetCandidateId, const FAssetCandidate& AsssetCandidate, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetCandidateResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetCandidateResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FAssetCandidate::StaticStruct(), &AsssetCandidate, ContentString, 0, 0);
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->UpdateAssetCandidateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UUserGeneratedContentRequestHandler::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("DeleteAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->DeleteAssetCandidateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UUserGeneratedContentRequestHandler::GetAllAssetCandidates(const FAssetCandidatesResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetCandidatesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetCandidatesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAllAssetCandidates failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->GetAllAssetCandidatesEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UUserGeneratedContentRequestHandler::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FAssetCandidateResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAssetCandidateResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->GetAssetCandidateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UUserGeneratedContentRequestHandler::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, EAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
    {
        FLootLockerResponse ResponseStruct;

        ResponseStruct.success = response.success;
        if (response.success)
        {
            FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("AddFileToAssetCandidate failed from lootlocker"));
        }
        ResponseStruct.FullTextFromServer = response.FullTextFromServer;
        OnCompletedRequestBP.Broadcast(ResponseStruct);
        OnCompletedRequest.ExecuteIfBound(ResponseStruct);
    });
    
    TArray<uint8> FileContents;
    
    if (FFileHelper::LoadFileToArray(FileContents, *FilePath))
    {
        FString purpose = ULootLockerConfig::GetEnum(TEXT("EAssetFilePurpose"), static_cast<int32>(FilePurpose));
        
        const FString Boundary = TEXT("lootlockerboundary");
        const FString BeginBoundary = TEXT("\r\n--" + Boundary + "\r\n");
        const FString EndBoundary = TEXT("\r\n--" + Boundary + "--\r\n");

        FString Header = TEXT("Content-Disposition: form-data; name=\"file\"; purpose=\"" + purpose + "\" \r\nContent-Type: application/octet-stream \r\n\r\n file=");

        TArray<uint8> UploadContent;
        
        UploadContent.Append((uint8*)TCHAR_TO_ANSI(*BeginBoundary), BeginBoundary.Len());
        UploadContent.Append((uint8*)TCHAR_TO_ANSI(*Header), Header.Len());
        UploadContent.Append(FileContents);
        UploadContent.Append((uint8*)TCHAR_TO_ANSI(*EndBoundary), EndBoundary.Len());

        const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
        FEndPoints Endpoint = config->AddFileToAssetCandidateEndpoint;
        FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId });
        FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
        HttpClient->UploadFile(endpoint, requestMethod, Boundary, UploadContent, sessionResponse, true);
    } else {
        UE_LOG(LogTemp, Error, TEXT("FILE NOT READ!"));
    }
}

void UUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("DeleteFileFromAssetCandidate failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.Broadcast(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = config->DeleteFileFromAssetCandidateEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { AssetCandidateId, FileId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
