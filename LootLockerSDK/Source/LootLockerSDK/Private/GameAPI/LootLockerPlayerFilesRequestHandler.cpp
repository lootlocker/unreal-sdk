#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"

#include "LootLockerGameEndpoints.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "Utils/LootLockerUtilities.h"

FString ULLPlayerFilesRequestHandler::UploadFile(const FLootLockerPlayerData& PlayerData, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileDelegate& OnComplete)
{
	TMap<FString, FString> AdditionalData;
	AdditionalData.Add(TEXT("purpose"), *Request.purpose);
	AdditionalData.Add(TEXT("public"), Request.IsPublic ? TEXT("true") : TEXT("false"));
	if (!Request.key.IsEmpty())
	{
		AdditionalData.Add(TEXT("key"), *Request.key);
	}

	return LLAPI<FLootLockerPlayerFileResponse>::UploadFileAPI(Request.file, ULootLockerGameEndpoints::FileUploadEndpoint, { }, AdditionalData, PlayerData, OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to is_public field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				if (!JsonObject.IsValid()) return;
				Response.IsPublic = JsonObject->GetBoolField(TEXT("public"));
			}
		}));
}

FString ULLPlayerFilesRequestHandler::UpdateFile(const FLootLockerPlayerData& PlayerData, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerFileResponse>::UploadFileAPI(Request.file, ULootLockerGameEndpoints::FileUpdateEndpoint, { FileId }, TMap<FString, FString>(), PlayerData, OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to is_public field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				if (!JsonObject.IsValid()) return;
				Response.IsPublic = JsonObject->GetBoolField(TEXT("public"));
			}
		}));
}

FString ULLPlayerFilesRequestHandler::ListFiles(const FLootLockerPlayerData& PlayerData, const FLootLockerFileListDelegate& OnComplete)
{
	return LLAPI<FLootLockerFileListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListFilesEndpoint, { }, EmptyQueryParams, PlayerData, OnComplete, LLAPI<FLootLockerFileListResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerFileListResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to IsPublic field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				if (!JsonObject.IsValid()) return;
				ParsePublicFlagOnFileList(Response.items, JsonObject->GetArrayField(TEXT("items")));
			}
		}));
}

FString ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(const FLootLockerPlayerData& PlayerData, const int32 PlayerID, const FLootLockerFileListDelegate& OnComplete)
{
	return LLAPI<FLootLockerFileListResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListOtherPlayersFilesEndpoint, { PlayerID }, EmptyQueryParams, PlayerData, OnComplete, LLAPI<FLootLockerFileListResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerFileListResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to IsPublic field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				if (!JsonObject.IsValid()) return;
				ParsePublicFlagOnFileList(Response.items, JsonObject->GetArrayField(TEXT("items")));
			}
		}));
}

FString ULLPlayerFilesRequestHandler::GetSingleFile(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerUploadFileDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerFileResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleFileEndpoint, { FileID }, EmptyQueryParams, PlayerData, OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to IsPublic field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				if (!JsonObject.IsValid()) return;
				Response.IsPublic = JsonObject->GetBoolField(TEXT("public"));
			}
		}));
}

FString ULLPlayerFilesRequestHandler::DeletePlayerFile(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerFileDeletedDelegate& OnComplete)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteFileEndpoint, { FileID }, EmptyQueryParams, PlayerData, OnComplete);
}

void ULLPlayerFilesRequestHandler::ParsePublicFlagOnFileList(TArray<FLootLockerPlayerFile>& ParsedFilesList, const TArray<TSharedPtr<FJsonValue>>& JsonFilesList)
{
	for (FLootLockerPlayerFile& Item : ParsedFilesList)
	{
		if (const TSharedPtr<FJsonValue>* MatchedItem = JsonFilesList.FindByPredicate([&Item](const TSharedPtr<FJsonValue>& JsonItemValue)
			{
				if (!JsonItemValue || !JsonItemValue.IsValid())
				{
					return false;
				}
				const TSharedPtr<FJsonObject>* JsonItemObject;
				JsonItemValue->TryGetObject(JsonItemObject);
				return JsonItemObject && JsonItemObject->Get()->GetIntegerField(TEXT("id")) == Item.id;
			}))
	    {
			if (MatchedItem && MatchedItem->IsValid()) {
				const TSharedPtr<FJsonObject>* MatchedItemObject;
				MatchedItem->Get()->TryGetObject(MatchedItemObject);
				if (MatchedItemObject && MatchedItemObject->IsValid()) {
					Item.IsPublic = MatchedItemObject->Get()->GetBoolField(TEXT("public"));
				}
			}
		}
	}
}

FString ULLPlayerFilesRequestHandler::ListFileRevisions(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerFileRevisionsDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerFileRevisionsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListFileRevisionsEndpoint, { FileID }, EmptyQueryParams, PlayerData, OnComplete, LLAPI<FLootLockerPlayerFileRevisionsResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileRevisionsResponse& Response)
		{
			if (Response.success)
			{
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				if (!JsonObject.IsValid()) return;
				const TSharedPtr<FJsonObject>* FileObject;
				if (JsonObject->TryGetObjectField(TEXT("file"), FileObject) && FileObject && FileObject->IsValid())
				{
					Response.file.IsPublic = FileObject->Get()->GetBoolField(TEXT("public"));
				}
			}
		}));
}

FString ULLPlayerFilesRequestHandler::GetFileRevision(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FString& RevisionID, const FLootLockerFileContentDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerFileContentResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetFileRevisionEndpoint, { FileID, RevisionID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULLPlayerFilesRequestHandler::PromoteFileRevision(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FString& RevisionID, const FLootLockerDefaultDelegate& OnComplete)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::PromoteFileRevisionEndpoint, { FileID, RevisionID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULLPlayerFilesRequestHandler::GetFileByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FLootLockerUploadFileDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerFileResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetFileByKeyEndpoint, { Key }, EmptyQueryParams, PlayerData, OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
		{
			if (Response.success)
			{
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				if (!JsonObject.IsValid()) return;
				Response.IsPublic = JsonObject->GetBoolField(TEXT("public"));
			}
		}));
}

FString ULLPlayerFilesRequestHandler::ListFileRevisionsByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FLootLockerFileRevisionsDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerFileRevisionsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListFileRevisionsByKeyEndpoint, { Key }, EmptyQueryParams, PlayerData, OnComplete, LLAPI<FLootLockerPlayerFileRevisionsResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileRevisionsResponse& Response)
		{
			if (Response.success)
			{
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				if (!JsonObject.IsValid()) return;
				const TSharedPtr<FJsonObject>* FileObject;
				if (JsonObject->TryGetObjectField(TEXT("file"), FileObject) && FileObject && FileObject->IsValid())
				{
					Response.file.IsPublic = FileObject->Get()->GetBoolField(TEXT("public"));
				}
			}
		}));
}

FString ULLPlayerFilesRequestHandler::GetFileRevisionByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FString& RevisionID, const FLootLockerFileContentDelegate& OnComplete)
{
	return LLAPI<FLootLockerPlayerFileContentResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetFileRevisionByKeyEndpoint, { Key, RevisionID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULLPlayerFilesRequestHandler::PromoteFileRevisionByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FString& RevisionID, const FLootLockerDefaultDelegate& OnComplete)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::PromoteFileRevisionByKeyEndpoint, { Key, RevisionID }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULLPlayerFilesRequestHandler::DeletePlayerFileByKey(const FLootLockerPlayerData& PlayerData, const FString& Key, const FLootLockerFileDeletedDelegate& OnComplete)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteFileByKeyEndpoint, { Key }, EmptyQueryParams, PlayerData, OnComplete);
}
