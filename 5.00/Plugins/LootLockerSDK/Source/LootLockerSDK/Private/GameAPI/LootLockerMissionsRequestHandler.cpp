// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMissionsRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

ULootLockerHttpClient* ULootLockerMissionsRequestHandler::HttpClient = nullptr;

ULootLockerMissionsRequestHandler::ULootLockerMissionsRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerMissionsRequestHandler::GetAllMissions(const FMissionsResponseDelegateBP& OnCompletedRequestBP, const FMissionsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerMissionsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerMissionsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                
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
                UE_LOG(LogLootLocker, Error, TEXT("GetAllMissions failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetAllMissionsEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerMissionsRequestHandler::GetMission(int MissionId, const FMissionResponseDelegateBP& OnCompletedRequestBP, const FMissionResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerMissionResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerMissionResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                //Parse custom fields for checkpoints
                TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(response.FullTextFromServer);
                FJsonSerializer::Deserialize(JsonReader, JsonObject);
                
                ResponseStruct.mission.checkpoints = LootLockerUtilities::ParseMissionCheckpoints(JsonObject->GetObjectField("mission"));
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("GetMission failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::GetMissionEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { MissionId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerMissionsRequestHandler::StartMission(int MissionId, const FStartMissionResponseDelegateBP& OnCompletedRequestBP, const FStartMissionResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerStartMissionResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerStartMissionResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("StartMission failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::StartMissionEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { MissionId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void ULootLockerMissionsRequestHandler::FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnCompletedRequestBP, const FFinishMissionResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FLootLockerFinishMissionResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerFinishMissionResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogLootLocker, Error, TEXT("FinishMission failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FLootLockerFinishMissionData::StaticStruct(), &MissionData, ContentString, 0, 0);
    FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::FinishMissionEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { MissionId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
