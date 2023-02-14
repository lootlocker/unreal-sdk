// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/Base64.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerUserGeneratedContentRequestHandler::HttpClient = nullptr;

ULootLockerUserGeneratedContentRequestHandler::ULootLockerUserGeneratedContentRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(HttpClient, AssetCandidateData,ULootLockerGameEndpoints::CreateAssetCandidateEndpoint,{}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(HttpClient, AssetCandidateData,ULootLockerGameEndpoints::UpdateAssetCandidateEndpoint, { AssetCandidateId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(HttpClient, LootLockerEmptyRequest,ULootLockerGameEndpoints::DeleteAssetCandidateEndpoint, { AssetCandidateId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(const FAssetCandidatesResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidatesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest,ULootLockerGameEndpoints::GetAllAssetCandidatesEndpoint, { },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(HttpClient, LootLockerEmptyRequest,ULootLockerGameEndpoints::GetAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    FString purpose = ULootLockerConfig::GetEnum(TEXT("ELootLockerAssetFilePurpose"), static_cast<int32>(FilePurpose));
    TMap<FString, FString> AdditionalData;
    AdditionalData.Add("purpose", purpose);
	
    LLAPI<FLootLockerResponse>::UploadFileAPI(HttpClient, FilePath, ULootLockerGameEndpoints::AddFileToAssetCandidateEndpoint, { AssetCandidateId },AdditionalData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(HttpClient, LootLockerEmptyRequest,ULootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint, { AssetCandidateId, FileId },EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest);
}
