// Copyright (c) 2021 LootLocker

#include "LootLockerUtilities.h"

#include "JsonObjectConverter.h"
#include "Policies/JsonPrintPolicy.h"

const TArray<FObfuscationDetails> UObfuscationSettings::FieldsToObfuscate =
{
    FObfuscationDetails(FString("game_key"), "*", 4, 3, false),
    FObfuscationDetails(FString("email"), "*", 3, 3, true),
    FObfuscationDetails(FString("password"), "*", 0, 0, true),
    FObfuscationDetails(FString("domain_key"), "*", 3, 3, true),
    FObfuscationDetails(FString("session_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("token"), "*", 3, 3, true)
};

FString ULootLockerEnumUtils::GetEnum(const TCHAR* Enum, int32 EnumValue)
{
    const UEnum* EnumPtr = FindObject<UEnum>(StaticClass()->GetOuter(), Enum, true);
    if (!EnumPtr)
        return NSLOCTEXT("Invalid", "Invalid", "Invalid").ToString();

    return EnumPtr->GetDisplayNameTextByValue(EnumValue).ToString();
}

namespace LootLockerUtilities
{
    FString AppendParameterToUrl(const FString& Url, const FString& Parameter)
    {
	    const FString AppendSymbol = Url.Contains("?") ? "&" : "?";
        return Url + AppendSymbol + Parameter;
    }

    TArray<FLootLockerMissionCheckpoint> ParseMissionCheckpoints(const TSharedPtr<FJsonObject>& MissionJson)
    {
        TArray<FLootLockerMissionCheckpoint> Checkpoints;
        if (MissionJson->HasTypedField<EJson::Array>(TEXT("checkpoints")))
        {
            TArray<TSharedPtr<FJsonValue>> CheckPointsJson = MissionJson->GetArrayField(TEXT("checkpoints"));
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
	        const TSharedPtr<FJsonObject> JsonCheckPoint = FJsonObjectConverter::UStructToJsonObject(Checkpoints[i]);
            JsonCheckPoint->RemoveField(TEXT("parameters"));
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
        if(!FJsonSerializer::Deserialize(JsonReader, JsonObject))
        {
            JsonObject = nullptr;
        };
        return JsonObject;
    }

    TSharedPtr<FJsonValue> JsonValueFromFString(const FString& JsonString)
    {
        TSharedPtr<FJsonValue> JsonValue = MakeShareable(new FJsonValueNull());
        const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
        if (!FJsonSerializer::Deserialize(JsonReader, JsonValue))
        {
            JsonValue = nullptr;
        };
        return JsonValue;
    }

    bool JsonArrayFromFString(const FString& JsonString, TArray<TSharedPtr<FJsonValue>>& JsonArrayOutput)
    {
        TArray<TSharedPtr<FJsonValue>> JsonArray;
        const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
        if (!FJsonSerializer::Deserialize(JsonReader, JsonArray))
        {
            return false;
        };
        JsonArrayOutput = JsonArray;
        return true;
    }

    FString FStringFromJsonObject(const TSharedPtr<FJsonObject>& JsonObject)
    {
        FString OutJsonString;
        TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutJsonString);

        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter, true);

        return OutJsonString;
    }

    FString FStringFromJsonArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray)
    {
        FString OutJsonString;
        TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutJsonString);

        FJsonSerializer::Serialize(JsonArray, JsonWriter, true);

        return OutJsonString;
    }

    FString ObfuscateJsonStringForLogging(const FString& JsonBody)
    {
        return ObfuscateJsonStringForLogging(UObfuscationSettings::FieldsToObfuscate, JsonBody);
    }

    FString ObfuscateJsonStringForLogging(const TArray<FObfuscationDetails>& ObfuscationDetails, const FString& JsonBody)
    {
	    const TSharedPtr<FJsonObject> jsonObject = JsonObjectFromFString(JsonBody);
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

    FString JsonObjectToString(const TSharedRef<FJsonObject>& JsonObject)
    {
	    FString OutJsonString;
	    TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJsonString, 0);
	    bool bSuccess = FJsonSerializer::Serialize(JsonObject, JsonWriter);
	    JsonWriter->Close();
	    return bSuccess ? OutJsonString : "";
    }

    FString JsonValueToString(const TSharedRef<FJsonValue>& JsonValue)
    {
	    FString OutJsonString;
	    TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJsonString, 0);
	    bool bSuccess = FJsonSerializer::Serialize(JsonValue, "", JsonWriter);
	    JsonWriter->Close();
        // The Unreal serializer in certain versions has a bug where it inserts a comma at the beginning of pure values
        if (!bSuccess && OutJsonString.StartsWith(","))
        {
            bool charRemoved = false;
            OutJsonString.TrimCharInline(',', &charRemoved);
            bSuccess = charRemoved;
        }
	    return bSuccess ? OutJsonString : "";
    }
}
