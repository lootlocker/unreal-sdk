// Copyright (c) 2020 LootLocker

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

void ADemoUserGeneratedContent::OnCreateAssetCandidateCompleted(FCreateAssetCandidateResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnCreateAssetCandidateCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoUserGeneratedContent::OnUpdateAssetCandidateCompleted(FAssetCandidateResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnUpdateAssetCandidateCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoUserGeneratedContent::OnDeleteAssetCandidateCompleted(FLootLockerResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnDeleteAssetCandidateCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoUserGeneratedContent::OnGetAllAssetCandidatesCompleted(FAssetCandidatesResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetAllAssetCandidatesCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoUserGeneratedContent::OnGetAssetCandidateCompleted(FAssetCandidateResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnGetAssetCandidateCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoUserGeneratedContent::OnAddFileToAssetCandidateCompleted(FLootLockerResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnAddFileToAssetCandidateCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}

void ADemoUserGeneratedContent::OnDeleteFileFromAssetCandidateCompleted(FLootLockerResponse Response)
{
    UE_LOG(LogTemp, Verbose, TEXT("OnDeleteFileFromAssetCandidateCompleted Response: \nSuccess: %b\nFull text from server: %s"), Response.success, *Response.FullTextFromServer);
}
