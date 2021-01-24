// Copyright (c) 2021 LootLocker

#include "GameAPI/MissionsRequestHandler.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerGameEndpoints.h"

UHttpClient* UMissionsRequestHandler::HttpClient = nullptr;

UMissionsRequestHandler::UMissionsRequestHandler()
{
    HttpClient = NewObject<UHttpClient>();
}

void UMissionsRequestHandler::GetAllMissions(const FMissionsResponseDelegateBP& OnCompletedRequestBP, const FMissionsResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FMissionsResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FMissionsResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                
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
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::GetAllMissionsEndpoint;
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(Endpoint.endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UMissionsRequestHandler::GetMission(int MissionId, const FMissionResponseDelegateBP& OnCompletedRequestBP, const FMissionResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FMissionResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FMissionResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
                //Parse custom fields for checkpoints
                TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
                TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(response.FullTextFromServer);
                FJsonSerializer::Deserialize(JsonReader, JsonObject);
                
                ResponseStruct.mission.checkpoints = LootLockerUtilities::ParseMissionCheckpoints(JsonObject->GetObjectField("mission"));
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("GetMission failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::GetMissionEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { MissionId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UMissionsRequestHandler::StartMission(int MissionId, const FStartMissionResponseDelegateBP& OnCompletedRequestBP, const FStartMissionResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FStartMissionResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FStartMissionResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("StartMission failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::StartMissionEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { MissionId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}

void UMissionsRequestHandler::FinishMission(int MissionId, const FFinishMissionData& MissionData, const FFinishMissionResponseDelegateBP& OnCompletedRequestBP, const FFinishMissionResponseDelegate& OnCompletedRequest)
{
    FResponseCallback sessionResponse = FResponseCallback::CreateLambda([OnCompletedRequestBP, OnCompletedRequest](FLootLockerResponse response)
        {
            FFinishMissionResponse ResponseStruct;

            ResponseStruct.success = response.success;
            if (response.success)
            {
                FJsonObjectConverter::JsonObjectStringToUStruct<FFinishMissionResponse>(response.FullTextFromServer, &ResponseStruct, 0, 0);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("FinishMission failed from lootlocker"));
            }
            ResponseStruct.FullTextFromServer = response.FullTextFromServer;
            OnCompletedRequestBP.ExecuteIfBound(ResponseStruct);
            OnCompletedRequest.ExecuteIfBound(ResponseStruct);
        });

    FString ContentString;
    FJsonObjectConverter::UStructToJsonObjectString(FFinishMissionData::StaticStruct(), &MissionData, ContentString, 0, 0);
    const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
    FEndPoints Endpoint = LootLockerGameEndpoints::FinishMissionEndpoint;
    FString endpoint = FString::Format(*(Endpoint.endpoint), { MissionId });
    FString requestMethod = ULootLockerConfig::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(Endpoint.requestMethod));
    HttpClient->SendApi(endpoint, requestMethod, ContentString, sessionResponse, true);
}
