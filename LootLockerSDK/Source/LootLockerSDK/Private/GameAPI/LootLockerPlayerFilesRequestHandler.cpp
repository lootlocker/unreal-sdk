#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"
#include <JsonObjectConverter.h>

#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULLPlayerFilesRequestHandler::HttpClient = nullptr;

ULLPlayerFilesRequestHandler::ULLPlayerFilesRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULLPlayerFilesRequestHandler::UploadFile(const FLootLockerFileUploadRequest &Request, const FLootLockerUploadFileBP &OnCompleteBP, const FLootLockerUploadFileDelegate &OnComplete)
{
	TMap<FString, FString> AdditionalData;
	AdditionalData.Add(TEXT("purpose"), *Request.purpose);
	AdditionalData.Add(TEXT("public"), Request.bIsPublic ? TEXT("true") : TEXT("false"));
	
	LLAPI<FLootLockerFileResponse>::UploadFileAPI(HttpClient, Request.file, ULootLockerGameEndpoints::FileUploadEndpoint, { },AdditionalData,OnCompleteBP, OnComplete);
}

void ULLPlayerFilesRequestHandler::ListFiles(const FLootLockerFileListBP &OnCompleteBP, const FLootLockerFileListDelegate &OnComplete)
{
	LLAPI<FLootLockerFileListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListFilesEndpoint, { },EmptyQueryParams,OnCompleteBP, OnComplete);
}

void ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP, const FLootLockerFileListDelegate& OnComplete)
{
	LLAPI<FLootLockerFileListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListOtherPlayersFilesEndpoint, { PlayerID }, EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULLPlayerFilesRequestHandler::GetSingleFile(const int32 FileID, const FLootLockerUploadFileBP &OnCompleteBP, const FLootLockerUploadFileDelegate &OnComplete)
{
	LLAPI<FLootLockerFileResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleFileEndpoint, {FileID },EmptyQueryParams,OnCompleteBP, OnComplete);
}

void ULLPlayerFilesRequestHandler::DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedBP &OnCompleteBP, const FLootLockerFileDeletedDelegate &OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteFileEndpoint, { FileID }, EmptyQueryParams,OnCompleteBP, OnComplete);
}
