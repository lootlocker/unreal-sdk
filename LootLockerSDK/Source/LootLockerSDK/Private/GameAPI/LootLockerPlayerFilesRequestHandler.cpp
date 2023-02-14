#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"
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
	AdditionalData.Add(TEXT("public"), Request.IsPublic ? TEXT("true") : TEXT("false"));

	LLAPI<FLootLockerPlayerFileResponse>::UploadFileAPI(HttpClient, Request.file, ULootLockerGameEndpoints::FileUploadEndpoint, { }, AdditionalData, OnCompleteBP, OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
	{
		if (Response.success)
		{
			// Add "public" to is_public field manually if it exists
            const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
			Response.IsPublic = JsonObject->GetBoolField("public");
		}
	}));
}

void ULLPlayerFilesRequestHandler::UpdateFile(const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileBP& OnCompleteBP, const FLootLockerUploadFileDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerFileResponse>::UploadFileAPI(HttpClient, Request.file, ULootLockerGameEndpoints::FileUpdateEndpoint, { FileId }, TMap<FString, FString>(), OnCompleteBP, OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
	{
		if (Response.success)
		{
			// Add "public" to is_public field manually if it exists
			const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
			Response.IsPublic = JsonObject->GetBoolField("public");
		}
	}));
}

void ULLPlayerFilesRequestHandler::ListFiles(const FLootLockerFileListBP &OnCompleteBP, const FLootLockerFileListDelegate &OnComplete)
{
	LLAPI<FLootLockerFileListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListFilesEndpoint, { },EmptyQueryParams, OnCompleteBP, OnComplete, LLAPI<FLootLockerFileListResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerFileListResponse& Response)
    {
        if (Response.success)
        {
            // Add "public" to IsPublic field manually if it exists
            const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
            ParsePublicFlagOnFileList(Response.items, JsonObject->GetArrayField("items"));
        }
    }));
}

void ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(const int32 PlayerID, const FLootLockerFileListBP& OnCompleteBP, const FLootLockerFileListDelegate& OnComplete)
{
	LLAPI<FLootLockerFileListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListOtherPlayersFilesEndpoint, { PlayerID }, EmptyQueryParams, OnCompleteBP, OnComplete, LLAPI<FLootLockerFileListResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerFileListResponse& Response)
    {
        if (Response.success)
        {
            // Add "public" to IsPublic field manually if it exists
            const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
            ParsePublicFlagOnFileList(Response.items, JsonObject->GetArrayField("items"));
        }
    }));
}

void ULLPlayerFilesRequestHandler::GetSingleFile(const int32 FileID, const FLootLockerUploadFileBP &OnCompleteBP, const FLootLockerUploadFileDelegate &OnComplete)
{
	LLAPI<FLootLockerPlayerFileResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleFileEndpoint, {FileID },EmptyQueryParams, OnCompleteBP, OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
    {
        if (Response.success)
        {
            // Add "public" to IsPublic field manually if it exists
            const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
            Response.IsPublic = JsonObject->GetBoolField("public");
        }
    }));
}

void ULLPlayerFilesRequestHandler::DeletePlayerFile(const int32 FileID, const FLootLockerFileDeletedBP &OnCompleteBP, const FLootLockerFileDeletedDelegate &OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteFileEndpoint, { FileID }, EmptyQueryParams, OnCompleteBP, OnComplete);
}

void ULLPlayerFilesRequestHandler::ParsePublicFlagOnFileList(TArray<FLootLockerPlayerFile>& ParsedFilesList, const TArray<TSharedPtr<FJsonValue>>& JsonFilesList)
{
	for (FLootLockerPlayerFile& Item : ParsedFilesList)
	{
		if (const TSharedPtr<FJsonValue>* MatchedItem = JsonFilesList.FindByPredicate([&Item](const TSharedPtr<FJsonValue> JsonItemValue)
			{
				if (!JsonItemValue || !JsonItemValue.IsValid())
				{
					return false;
				}
				const TSharedPtr<FJsonObject>* JsonItemObject;
				JsonItemValue->TryGetObject(JsonItemObject);
				return JsonItemObject && JsonItemObject->Get()->GetIntegerField("id") == Item.id;
			}))
	    {
			if (MatchedItem && MatchedItem->IsValid()) {
				const TSharedPtr<FJsonObject>* MatchedItemObject;
				MatchedItem->Get()->TryGetObject(MatchedItemObject);
				if (MatchedItemObject && MatchedItemObject->IsValid()) {
					Item.IsPublic = MatchedItemObject->Get()->GetBoolField("public");
				}
			}
		}
	}
}
