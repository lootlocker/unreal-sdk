// Copyright (c) 2021 LootLocker

#include "Demo/DemoUserGeneratedContent.h"

void ADemoUserGeneratedContent::DemoCreateAssetCandidate()
{
   ULootLockerSDKManager::CreateAssetCandidate(AsssetCandidate, FCreateAssetCandidateResponseDelegate::CreateUObject(this, &ADemoUserGeneratedContent::OnCreateAssetCandidateCompleted));
}

void ADemoUserGeneratedContent::DemoUpdateAssetCandidate()
{
   ULootLockerSDKManager::UpdateAssetCandidate(AssetCandidateId, AsssetCandidate, FAssetCandidateResponseDelegate::CreateUObject(this, &ADemoUserGeneratedContent::OnUpdateAssetCandidateCompleted));
}

void ADemoUserGeneratedContent::DemoDeleteAssetCandidate()
{
   ULootLockerSDKManager::DeleteAssetCandidate(AssetCandidateId, FResponseCallback::CreateUObject(this, &ADemoUserGeneratedContent::OnDeleteAssetCandidateCompleted));
}

void ADemoUserGeneratedContent::DemoGetAllAssetCandidates()
{
   ULootLockerSDKManager::GetAllAssetCandidates(FAssetCandidatesResponseDelegate::CreateUObject(this, &ADemoUserGeneratedContent::OnGetAllAssetCandidatesCompleted));
}

void ADemoUserGeneratedContent::DemoGetAssetCandidate()
{
   ULootLockerSDKManager::GetAssetCandidate(AssetCandidateId, FAssetCandidateResponseDelegate::CreateUObject(this, &ADemoUserGeneratedContent::OnGetAssetCandidateCompleted));
}

void ADemoUserGeneratedContent::DemoAddFileToAssetCandidate()
{
   ULootLockerSDKManager::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, FResponseCallback::CreateUObject(this, &ADemoUserGeneratedContent::OnAddFileToAssetCandidateCompleted));
}

void ADemoUserGeneratedContent::DemoDeleteFileFromAssetCandidate()
{
   ULootLockerSDKManager::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, FResponseCallback::CreateUObject(this, &ADemoUserGeneratedContent::OnDeleteFileFromAssetCandidateCompleted));
}

void ADemoUserGeneratedContent::OnCreateAssetCandidateCompleted(FLootLockerCreateAssetCandidateResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCreateAssetCandidate Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCreateAssetCandidate Failed"));
    }
}

void ADemoUserGeneratedContent::OnUpdateAssetCandidateCompleted(FLootLockerAssetCandidateResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnUpdateAssetCandidate Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnUpdateAssetCandidate Failed"));
    }
}

void ADemoUserGeneratedContent::OnDeleteAssetCandidateCompleted(FLootLockerResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnDeleteAssetCandidate Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnDeleteAssetCandidate Failed"));
    }
}

void ADemoUserGeneratedContent::OnGetAllAssetCandidatesCompleted(FLootLockerAssetCandidatesResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAllAssetCandidates Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAllAssetCandidates Failed"));
    }
}

void ADemoUserGeneratedContent::OnGetAssetCandidateCompleted(FLootLockerAssetCandidateResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetCandidate Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetCandidate Failed"));
    }
}

void ADemoUserGeneratedContent::OnAddFileToAssetCandidateCompleted(FLootLockerResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnAddFileToAssetCandidate Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnAddFileToAssetCandidate Failed"));
    }
}

void ADemoUserGeneratedContent::OnDeleteFileFromAssetCandidateCompleted(FLootLockerResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnDeleteFileFromAssetCandidate Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnDeleteFileFromAssetCandidate Failed"));
    }
}
