#include "GameAPI/LootLockerPlayerFilesRequestHandler.h"

#include "LootLockerGameEndpoints.h"
#include "GameAPI/LootLockerUserGeneratedContentRequestHandler.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULLPlayerFilesRequestHandler::HttpClient = nullptr;

ULLPlayerFilesRequestHandler::ULLPlayerFilesRequestHandler()
{
	HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULLPlayerFilesRequestHandler::UploadFile(const FLootLockerPlayerData& PlayerData, const FLootLockerFileUploadRequest& Request, const FLootLockerUploadFileDelegate& OnComplete)
{
	TMap<FString, FString> AdditionalData;
	AdditionalData.Add(TEXT("purpose"), *Request.purpose);
	AdditionalData.Add(TEXT("public"), Request.IsPublic ? TEXT("true") : TEXT("false"));

	LLAPI<FLootLockerPlayerFileResponse>::UploadFileAPI(HttpClient, Request.file, ULootLockerGameEndpoints::FileUploadEndpoint, { }, AdditionalData, PlayerData, FLootLockerUploadFileBP(), OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to is_public field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				Response.IsPublic = JsonObject->GetBoolField(TEXT("public"));
			}
		}));
}

void ULLPlayerFilesRequestHandler::UpdateFile(const FLootLockerPlayerData& PlayerData, const int32 FileId, const FLootLockerFileUpdateRequest& Request, const FLootLockerUploadFileDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerFileResponse>::UploadFileAPI(HttpClient, Request.file, ULootLockerGameEndpoints::FileUpdateEndpoint, { FileId }, TMap<FString, FString>(), PlayerData, FLootLockerUploadFileBP(), OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to is_public field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				Response.IsPublic = JsonObject->GetBoolField(TEXT("public"));
			}
		}));
}

void ULLPlayerFilesRequestHandler::ListFiles(const FLootLockerPlayerData& PlayerData, const FLootLockerFileListDelegate& OnComplete)
{
	LLAPI<FLootLockerFileListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListFilesEndpoint, { }, EmptyQueryParams, PlayerData, FLootLockerFileListBP(), OnComplete, LLAPI<FLootLockerFileListResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerFileListResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to IsPublic field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				ParsePublicFlagOnFileList(Response.items, JsonObject->GetArrayField(TEXT("items")));
			}
		}));
}

void ULLPlayerFilesRequestHandler::ListOtherPlayersPublicFiles(const FLootLockerPlayerData& PlayerData, const int32 PlayerID, const FLootLockerFileListDelegate& OnComplete)
{
	LLAPI<FLootLockerFileListResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::ListOtherPlayersFilesEndpoint, { PlayerID }, EmptyQueryParams, PlayerData, FLootLockerFileListBP(), OnComplete, LLAPI<FLootLockerFileListResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerFileListResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to IsPublic field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				ParsePublicFlagOnFileList(Response.items, JsonObject->GetArrayField(TEXT("items")));
			}
		}));
}

void ULLPlayerFilesRequestHandler::GetSingleFile(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerUploadFileDelegate& OnComplete)
{
	LLAPI<FLootLockerPlayerFileResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::GetSingleFileEndpoint, { FileID }, EmptyQueryParams, PlayerData, FLootLockerUploadFileBP(), OnComplete, LLAPI<FLootLockerPlayerFileResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerPlayerFileResponse& Response)
		{
			if (Response.success)
			{
				// Add "public" to IsPublic field manually if it exists
				const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
				Response.IsPublic = JsonObject->GetBoolField(TEXT("public"));
			}
		}));
}

void ULLPlayerFilesRequestHandler::DeletePlayerFile(const FLootLockerPlayerData& PlayerData, const int32 FileID, const FLootLockerFileDeletedDelegate& OnComplete)
{
	LLAPI<FLootLockerResponse>::CallAPI(HttpClient, LootLockerEmptyRequest, ULootLockerGameEndpoints::DeleteFileEndpoint, { FileID }, EmptyQueryParams, PlayerData, FLootLockerFileDeletedBP(), OnComplete);
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
