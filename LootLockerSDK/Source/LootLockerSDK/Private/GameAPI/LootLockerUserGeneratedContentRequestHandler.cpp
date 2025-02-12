// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "Misc/FileHelper.h"
#include "Misc/Base64.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerUserGeneratedContentRequestHandler::HttpClient = nullptr;

ULootLockerUserGeneratedContentRequestHandler::ULootLockerUserGeneratedContentRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(HttpClient, FLootLockerCreateAssetCandidateData{ AssetCandidateData.data }, ULootLockerGameEndpoints::CreateAssetCandidateEndpoint, {}, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidateAndMarkComplete(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(HttpClient, FLootLockerUpdateAssetCandidateData{ true, AssetCandidateData.data }, ULootLockerGameEndpoints::CreateAssetCandidateEndpoint, {}, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(HttpClient, AssetCandidateData, ULootLockerGameEndpoints::UpdateAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(const FLootLockerPlayerData& PlayerData, const FAssetCandidatesResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidatesResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllAssetCandidatesEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FAssetCandidateResponseDelegateBP& OnCompletedRequestBP, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    FString purpose = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerAssetFilePurpose"), static_cast<int32>(FilePurpose));
    TMap<FString, FString> AdditionalData;
    AdditionalData.Add("purpose", purpose);

    LLAPI<FLootLockerResponse>::UploadFileAPI(HttpClient, FilePath, ULootLockerGameEndpoints::AddFileToAssetCandidateEndpoint, { AssetCandidateId }, AdditionalData, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, int FileId, const FResponseCallbackBP& OnCompletedRequestBP, const FResponseCallback& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint, { AssetCandidateId, FileId }, EmptyQueryParams, PlayerData, OnCompletedRequestBP, OnCompletedRequest);
}
