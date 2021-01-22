// Copyright (c) 2021 LootLocker

#include "AdminAPI/AdminMissionsRequestHandler.h"

#include "AdminAPI/LootLockerAdminEndpoints.h"
#include "Utils/LootLockerUtilities.h"

FResponseCallback UAdminMissionsRequestHandler::sessionResponse = nullptr;
UHttpClient* UAdminMissionsRequestHandler::HttpClient = NewObject<UHttpClient>();

void UAdminMissionsRequestHandler::CreateMission(const FAMission& MissionData, const FAMissionResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAMissionResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAMissionResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                
                //Parse custom fields for checkpoints
                TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(response.FullTextFromServer);
                FJsonSerializer::Deserialize(JsonReader, JsonObject);
                
                ResponseStruct.mission.checkpoints = LootLockerUtilities::ParseMissionCheckpoints(JsonObject->GetObjectField("mission"));
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("CreateMission failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString = LootLockerUtilities::SerializeMission(MissionData);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::CreateMissionEndpoint;
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("CreateMission: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminMissionsRequestHandler::UpdateMission(int MissionId, const FAMission& MissionData, const FAMissionResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAMissionResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAMissionResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                
                //Parse custom fields for checkpoints
                TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(response.FullTextFromServer);
                FJsonSerializer::Deserialize(JsonReader, JsonObject);
                
                ResponseStruct.mission.checkpoints = LootLockerUtilities::ParseMissionCheckpoints(JsonObject->GetObjectField("mission"));
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("UpdateMission failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString = LootLockerUtilities::SerializeMission(MissionData);
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::UpdateMissionEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { MissionId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("UpdateMission: Admin API calls are only allowed in Editor"));
#endif
}

void UAdminMissionsRequestHandler::GetAllMissions(int GameId, const FAMissionsResponseDelegate& OnComplete)
{
#if WITH_EDITOR
    sessionResponse = FResponseCallback::CreateLambda([OnComplete](FLootLockerResponse response)
        {
            FAMissionsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FAMissionsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                
                //Parse custom fields for checkpoints
                TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(response.FullTextFromServer);
                FJsonSerializer::Deserialize(JsonReader, JsonObject);
                
                TArray<TSharedPtr<FJsonValue>> missionsJsonArray = JsonObject->GetArrayField("missions");
                
                for (int i = 0; i < ResponseStruct.missions.Num(); i++)
                {
                    ResponseStruct.missions[i].checkpoints = LootLockerUtilities::ParseMissionCheckpoints(missionsJsonArray[i]->AsObject());
                }
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetAllMissions failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnComplete.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    
    FEndPoints Endpoint = LootLockerAdminEndpoints::GetAllMissionsEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { GameId });
    FString requestMethod = ULootLockerConfig::GetRequestMethodString(Endpoint.requestMethod);
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true, true);
#else
    UE_LOG(LogTemp, Warning, TEXT("GetAllMissions: Admin API calls are only allowed in Editor"));
#endif
}
