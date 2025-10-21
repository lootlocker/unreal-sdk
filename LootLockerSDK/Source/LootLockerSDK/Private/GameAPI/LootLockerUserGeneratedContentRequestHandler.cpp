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

FString ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(FLootLockerCreateAssetCandidateData{ AssetCandidateData.data }, ULootLockerGameEndpoints::CreateAssetCandidateEndpoint, {}, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerCreateAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerCreateAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

FString ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidateAndMarkComplete(const FLootLockerPlayerData& PlayerData, const FLootLockerCreateAssetCandidateData& AssetCandidateData, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(FLootLockerUpdateAssetCandidateData{ true, AssetCandidateData.data }, ULootLockerGameEndpoints::CreateAssetCandidateEndpoint, {}, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerCreateAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerCreateAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

FString ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FLootLockerUpdateAssetCandidateData& AssetCandidateData, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(AssetCandidateData, ULootLockerGameEndpoints::UpdateAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

FString ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FResponseCallback& OnCompletedRequest)
{
    return LLAPI<FLootLockerCreateAssetCandidateResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(const FLootLockerPlayerData& PlayerData, const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetCandidatesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAllAssetCandidatesEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerAssetCandidatesResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAssetCandidatesResponse& Response) {
        if(Response.success && Response.asset_candidates.Num() > 0)
        {
            for(FLootLockerResponseAssetCandidate& Candidate : Response.asset_candidates)
            {
                ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Candidate.Files);
            }
        }
    }));
}

FString ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetAssetCandidateEndpoint, { AssetCandidateId }, EmptyQueryParams, PlayerData, OnCompletedRequest, LLAPI<FLootLockerAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

FString ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    FString purpose = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerAssetFilePurpose"), static_cast<int32>(FilePurpose));
    TMap<FString, FString> AdditionalData;
    AdditionalData.Add("purpose", purpose);

    return LLAPI<FLootLockerAssetCandidateResponse>::UploadFileAPI(FilePath, ULootLockerGameEndpoints::AddFileToAssetCandidateEndpoint, { AssetCandidateId }, AdditionalData, PlayerData, OnCompletedRequest, LLAPI<FLootLockerAssetCandidateResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerAssetCandidateResponse& Response) {
        if(Response.success && Response.asset_candidate.Files.Num() > 0)
        {
            ULootLockerUserGeneratedContentRequestHandler::ParseFilePurposeEnumsInline(Response.asset_candidate.Files);
        }
    }));
}

FString ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(const FLootLockerPlayerData& PlayerData, int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest)
{
    return LLAPI<FLootLockerAssetCandidateResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteFileFromAssetCandidateEndpoint, { AssetCandidateId, FileId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}
