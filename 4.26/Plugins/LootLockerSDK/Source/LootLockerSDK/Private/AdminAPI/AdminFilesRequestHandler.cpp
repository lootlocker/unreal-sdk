// Copyright (c) 2020 LootLocker

#include "AdminAPI/AdminFilesRequestHandler.h"

#include "AdminAPI/LootLockerAdminEndpoints.h"
#include "Utils/LootLockerUtilities.h"
#if WITH_EDITOR
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "EditorDirectories.h"
#include "Framework/Application/SlateApplication.h"
#endif
FResponseCallback UAdminFilesRequestHandler::sessionResponse = nullptr;
UHttpClient* UAdminFilesRequestHandler::HttpClient = NewObject<UHttpClient>();

void UAdminFilesRequestHandler::UploadFile(const FString& FilePath, const FAFileAssociationData& AssociationData, const FAFileResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAFileResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAFileResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UploadFile failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });
    
    TMap<FString, FString> AdditionalFields;
    
    AdditionalFields.Add("game_id", FString::FromInt(AssociationData.game_id));
    
    if (AssociationData.asset_id >= 0) {
        AdditionalFields.Add("asset_id", FString::FromInt(AssociationData.asset_id));
    }
    if (AssociationData.item_id >= 0) {
        AdditionalFields.Add("item_id", FString::FromInt(AssociationData.item_id));
    }
    if (AssociationData.player_id >= 0) {
        AdditionalFields.Add("player_id", FString::FromInt(AssociationData.player_id));
    }
    if (AssociationData.tags.Num() > 0) {
        
        FString TagsString;
        for (int i = 0; i < AssociationData.tags.Num(); i++) {
            TagsString += i == 0 ? "" : ";";
            TagsString += AssociationData.tags[i];
        }
        
        AdditionalFields.Add("tags", TagsString);
    }

    FString ContentString;
    FEndPoints Endpoint = LootLockerAdminEndpoints::UploadFileEndpoint;
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->UploadFile(Endpoint.endpoint, requestMethod, FilePath, AdditionalFields, sessionResponse, true, true);
    
#else
    UE_LOG(LogTemp, Warning, TEXT("UploadFile: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminFilesRequestHandler::GetFiles(int GameId, const FString& Filter, const FAFilesResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAFilesResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAFilesResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetFiles failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetFilesEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    if (!Filter.IsEmpty()) {
        endpoint = LootLockerUtilities::AppendParameterToUrl(endpoint, "filter=" + Filter);
    }
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetFiles: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminFilesRequestHandler::UpdateFileTags(int GameId, int FileId, const FAFileTagsData& TagsData, const FAFileResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAFileResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAFileResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateFileTags failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(TagsData, ContentString);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::UpdateFileTagsEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, FileId });
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("UpdateFileTags: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminFilesRequestHandler::DeleteFile(int GameId, int FileId, const FLootLockerResponseCallback& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            if (!response.success)
            {
                UE_LOG(LogTemp, Error, TEXT("DeleteFile failed from lootlocker"));
            }
        
            OnComplete.ExecuteIfBound(response);
        });

    FString ContentString;
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::DeleteFileEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId, FileId });
    
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("DeleteFile: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminFilesRequestHandler::ShowFilePicker(const FString& DialogTitle, TArray<FString>& OutFileNames)
{
#if WITH_EDITOR
    //const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
    //IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    //if (DesktopPlatform)
    //{
    //    //Opening the file picker!
    //    uint32 SelectionFlag = 0; //A value of 0 represents single file selection while a value of 1 represents multiple file selection
    //    DesktopPlatform->OpenFileDialog(ParentWindowHandle, DialogTitle, FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_IMPORT), FString(""), FString(""), SelectionFlag, OutFileNames);
    //}
#endif
}
