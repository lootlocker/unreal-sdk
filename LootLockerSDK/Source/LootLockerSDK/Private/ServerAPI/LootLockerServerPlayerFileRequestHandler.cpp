// Copyright (c) 2021 LootLocker


#include "ServerAPI/LootLockerServerPlayerFileRequestHandler.h"
#include "LootLockerHttpClient.h"
#include "LootLockerServerEndpoints.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerServerPlayerFileRequestHandler::HttpClient = nullptr;

ULootLockerServerPlayerFileRequestHandler::ULootLockerServerPlayerFileRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerServerPlayerFileRequestHandler::ListPlayerFiles(const FString& PlayerId, const FLootLockerServerListPlayerFilesResponseDelegateBP& OnCompletedRequestBP /*= FLootLockerServerListPlayerFilesResponseDelegateBP()*/, const FLootLockerServerListPlayerFilesResponseDelegate& OnCompletedRequest /*= FLootLockerServerListPlayerFilesResponseDelegate()*/)
{
	LLAPI<FLootLockerServerListPlayerFilesResponse>::CallServerAPI(HttpClient, LootLockerEmptyRequest, ULootLockerServerEndpoints::ListPlayerFiles, { PlayerId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerServerListPlayerFilesResponse>::FResponseInspectorCallback());
}

void ULootLockerServerPlayerFileRequestHandler::GetPlayerFile(const FString& PlayerId, int FileId, const FLootLockerServerGetPlayerFileResponseDelegateBP& OnCompletedRequestBP /*= FLootLockerServerGetPlayerFileResponseDelegateBP()*/, const FLootLockerServerGetPlayerFileResponseDelegate& OnCompletedRequest /*= FLootLockerServerGetPlayerFileResponseDelegate()*/)
{
	LLAPI<FLootLockerResponse>::CallServerAPI(HttpClient, LootLockerEmptyRequest, ULootLockerServerEndpoints::GetPlayerFile, { PlayerId, FileId}, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback());
}

void ULootLockerServerPlayerFileRequestHandler::UploadPlayerFile(const FString& PlayerId, const FString& FileName, const FString& ContentAsString, const FString& Purpose, const FLootLockerServerUploadPlayerFileResponseDelegateBP& OnCompletedRequestBP /*= FLootLockerServerUploadPlayerFileResponseDelegateBP()*/, const FLootLockerServerUploadPlayerFileResponseDelegate& OnCompletedRequest /*= FLootLockerServerUploadPlayerFileResponseDelegate()*/)
{
	TMap<FString, FString> AdditionalData;
	AdditionalData.Add(TEXT("purpose"), Purpose);

	TArray<uint8> Bytes;
	Bytes.SetNumUninitialized(ContentAsString.Len());
	StringToBytes(ContentAsString, Bytes.GetData(), Bytes.Num());

	LLAPI<FLootLockerServerPlayerFileResponse>::UploadRawDataAPI(HttpClient, Bytes, FileName, ULootLockerServerEndpoints::UploadPlayerFile, {PlayerId}, AdditionalData, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerServerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerServerPlayerFileResponse& Response)
	{
		if (Response.success)
		{
			// Add "public" to is_public field manually if it exists
			const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
		}
	}));
}

void ULootLockerServerPlayerFileRequestHandler::DeletePlayerFile(const FString& PlayerId, int FileId, const FLootLockerServerDeletePlayerFileResponseDelegateBP& OnCompletedRequestBP /*= FLootLockerServerDeletePlayerFileResponseDelegateBP()*/, const FLootLockerServerDeletePlayerFileResponseDelegate& OnCompletedRequest /*= FLootLockerServerDeletePlayerFileResponseDelegate()*/)
{
	LLAPI<FLootLockerResponse>::CallServerAPI(HttpClient, LootLockerEmptyRequest, ULootLockerServerEndpoints::UploadPlayerFile, { PlayerId, FileId }, EmptyQueryParams, OnCompletedRequestBP, OnCompletedRequest, LLAPI<FLootLockerResponse>::FResponseInspectorCallback());
}
