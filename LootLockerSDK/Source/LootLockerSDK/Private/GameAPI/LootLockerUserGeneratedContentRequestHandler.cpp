// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "Misc/FileHelper.h"
#include "Misc/Base64.h"
#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

void ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(TArray<FLootLockerAssetFile>& Files)
{
    for (FLootLockerAssetFile& File : Files)
    {
        if (File.purpose.Equals("primary_thumbnail", ESearchCase::IgnoreCase))
        {
            File.purpose_enum = ELootLockerAssetFilePurpose::PRIMARY_THUMBNAIL;
        }
        else if (File.purpose.Equals("thumbnail", ESearchCase::IgnoreCase))
        {
            File.purpose_enum = ELootLockerAssetFilePurpose::THUMBNAIL;
        }
        else
        {
            File.purpose_enum = ELootLockerAssetFilePurpose::FILE;
        }
    }
}

void ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(FLootLockerCreateAssetCandidateData{ AssetCandidateData.data }, ULootLockerGameEndpoints::CreateAssetCandidateEndpoint, {}, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerCreateAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerCreateAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

void ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidateAndMarkComplete(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(FLootLockerUpdateAssetCandidateData{ true, AssetCandidateData.data }, ULootLockerGameEndpoints::CreateAssetCandidateEndpoint, {}, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerCreateAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerCreateAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

void ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(AssetCandidateData, ULootLockerGameEndpoints::UpdateAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

void ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FResponseCallback& OnCompletedRequest)
{
    LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

void ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(const FLootLockerPlayerData& PlayerData, const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidatesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllAssetCandidatesEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerAssetCandidatesResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAssetCandidatesResponse& Response) {
        if(Response.success && Response.asset_candidates.Num() > 0)
        {
            for(FLootLockerResponseAssetCandidate& Candidate : Response.asset_candidates)
            {
                ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Candidate.Files);
            }
        }
    }));
}

void ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

void ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    FString purpose = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerAssetFilePurpose"), static_cast<int32>(FilePurpose));
    TMap<FString, FString> AdditionalData;
    AdditionalData.Add("purpose", purpose);

    LLAPI<FLootLockerAssetCandidateResponse>::UploadFileAPI(FilePath, ULootLockerGameEndpoints::AddFileToAssetCandidateEndpoint, { AssetCandidateId }, AdditionalData, PlayerData, OnCompletedRequest, LLAPI<FLootLockerAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

void ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest)
{
    LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint, { AssetCandidateId, FileId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}
