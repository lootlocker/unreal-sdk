// Copyright (c) 2021 LootLocker

#include "LootLockerUtilities.h"

#include "JsonObjectConverter.h"

const TArray<FObfuscationDetails> UObfuscationSettings::FieldsToObfuscate =
{
    FObfuscationDetails(FString("game_key"), "*", 4, 3, false),
    FObfuscationDetails(FString("email"), "*", 3, 3, true),
    FObfuscationDetails(FString("password"), "*", 0, 0, true),
    FObfuscationDetails(FString("domain_key"), "*", 3, 3, true),
    FObfuscationDetails(FString("session_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("token"), "*", 3, 3, true)
};

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

    FString FStringFromJsonObject(const TSharedPtr<FJsonObject> JsonObject)
    {
        FString OutJsonString;
        TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutJsonString);

        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter, true);

        return OutJsonString;
    }

    FString ObfuscateJsonStringForLogging(const FString& JsonBody)
    {
        return ObfuscateJsonStringForLogging(UObfuscationSettings::FieldsToObfuscate, JsonBody);
    }

    FString ObfuscateJsonStringForLogging(const TArray<FObfuscationDetails>& ObfuscationDetails, const FString& JsonBody)
    {
        TSharedPtr<FJsonObject> jsonObject = JsonObjectFromFString(JsonBody);
        if (!jsonObject.IsValid())
        {
            return JsonBody;
        }
        FString valueToObfuscate;
        for (auto& obfuscationInfo : ObfuscationDetails) {

            if (jsonObject.Get()->TryGetStringField(obfuscationInfo.key, valueToObfuscate))
            {
                jsonObject->SetStringField(obfuscationInfo.key, ObfuscateString(obfuscationInfo, valueToObfuscate));
            }
        }
        return FStringFromJsonObject(jsonObject);
    }

    FString ObfuscateString(const FObfuscationDetails& ObfuscationDetail, const FString& StringToObfuscate)
    {
        if (!ObfuscationDetail.hideCharactersForShortStrings && (StringToObfuscate.Len() <= (ObfuscationDetail.visibleCharsFromBeginning + ObfuscationDetail.visibleCharsFromEnd)))
        {
            return StringToObfuscate;
        }

        FString ObfuscatedString;
        int i = 0;
        for (auto& c : StringToObfuscate) {
            if (i >= ObfuscationDetail.visibleCharsFromBeginning && i < StringToObfuscate.Len() - ObfuscationDetail.visibleCharsFromEnd) {
                ObfuscatedString.Append(ObfuscationDetail.replacementChar);
            }
            else {
                ObfuscatedString.AppendChar(c);
            }
            ++i;
        }
        return ObfuscatedString;
    }
}