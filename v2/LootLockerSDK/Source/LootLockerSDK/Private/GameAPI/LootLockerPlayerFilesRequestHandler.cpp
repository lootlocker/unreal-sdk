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
	AdditionalData.Add(TEXT("public"), Request.isPublic ? "true" : "false");

	FLootLockerUploadFileDelegate::CreateLambda([OnComplete, OnCompleteBP](FLootLockerFileResponse Response)
	{
		if(Response.success)
		{
			// Add "public" to is_public field manually if it exists
			TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
			TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Response.FullTextFromServer);
			FJsonSerializer::Deserialize(JsonReader, JsonObject);
			Response.is_public = JsonObject->GetBoolField("public");
		}
	    OnCompleteBP.ExecuteIfBound(Response);
		OnComplete.ExecuteIfBound(Response);
	});
	LLAPI<FLootLockerFileResponse>::UploadFileAPI(HttpClient, Request.file, ULootLockerGameEndpoints::FileUploadEndpoint, { },AdditionalData,OnCompleteBP, OnComplete, true);
}

void ULLPlayerFilesRequestHandler::ListFiles(const FLootLockerFileListBP &OnCompleteBP, const FLootLockerFileListDelegate &OnComplete)
{
	LLAPI<FLootLockerFileListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListFilesEndpoint, { },EmptyQueryParams,OnCompleteBP, OnComplete);
}

void ULLPlayerFilesRequestHandler::GetSingleFile(const int32 FileID, const FLootLockerUploadFileBP &OnCompleteBP, const FLootLockerUploadFileDelegate &OnComplete)
{
	LLAPI<FLootLockerFileResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleFileEndpoint, {FileID },EmptyQueryParams,OnCompleteBP, OnComplete);
}

void ULLPlayerFilesRequestHandler::DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedBP &OnCompleteBP, const FLootLockerFileDeletedDelegate &OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteFileEndpoint, { FileID }, EmptyQueryParams,OnCompleteBP, OnComplete);
}
