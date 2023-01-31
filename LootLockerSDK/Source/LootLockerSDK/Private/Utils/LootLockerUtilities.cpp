// Copyright (c) 2021 LootLocker

#include "LootLockerUtilities.h"

#include "JsonObjectConverter.h"

namespace LootLockerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter)
    {
        FString AppendSymbol = Url.Contains("?") ? "&" : "?";
        return Url + AppendSymbol + Parameter;
    }

    TArray<FLootLockerMissionCheckpoint> ParseMissionCheckpoints(const TSharedPtr<FJsonObject>& MissionJson)
    {
        TArray<FLootLockerMissionCheckpoint> Checkpoints;
        if (MissionJson->HasTypedField<EJson::Array>("checkpoints"))
        {
            TArray<TSharedPtr<FJsonValue>> CheckPointsJson = MissionJson->GetArrayField("checkpoints");
            for (int i = 0; i < CheckPointsJson.Num(); i++) {
                TSharedPtr<FJsonObject> temp = CheckPointsJson[i]->AsObject();
                TMap<FString, FString> parameters;
                FLootLockerMissionCheckpoint checkpoint;
                for (auto FormDataIt = temp->Values.CreateIterator(); FormDataIt; ++FormDataIt)
                {
                    FString Key = FormDataIt.Key();
                    if (Key == "index") {
                        checkpoint.index = (int)FormDataIt.Value().Get()->AsNumber();
                    }
                    else if (Key == "time") {
                        checkpoint.time = (int)FormDataIt.Value().Get()->AsNumber();
                    }
                    else {
                        parameters.Add(Key, FormDataIt.Value().Get()->AsString());
                    }
                }
                checkpoint.parameters = parameters;
                Checkpoints.Add(checkpoint);
            }
        }
        
        return Checkpoints;
    }

    TArray<TSharedPtr<FJsonValue>> SerializeMissionCheckpoints(const TArray<FLootLockerMissionCheckpoint>& Checkpoints)
    {
        TArray<TSharedPtr<FJsonValue>> ItemsJsonArray;
        for (int i = 0; i < Checkpoints.Num(); i++)
        {
            TSharedPtr<FJsonObject> JsonCheckPoint = FJsonObjectConverter::UStructToJsonObject(Checkpoints[i]);
            JsonCheckPoint->RemoveField("parameters");
            for (auto& KeyValuePair : Checkpoints[i].parameters) {
                JsonCheckPoint->SetStringField(KeyValuePair.Key, KeyValuePair.Value);
            }
            
            ItemsJsonArray.Push(MakeShareable(new FJsonValueObject(JsonCheckPoint)));
        }
        return ItemsJsonArray;
    }

    TSharedPtr<FJsonObject> JsonObjectFromFString(const FString& JsonString)
    {
        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
        const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
        FJsonSerializer::Deserialize(JsonReader, JsonObject);
        return JsonObject;
    }
}
