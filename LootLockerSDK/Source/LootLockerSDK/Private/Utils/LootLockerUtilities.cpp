// Copyright (c) 2021 LootLocker

#include "LootLockerUtilities.h"

#include "JsonObjectConverter.h"
#include "Policies/CondensedJsonPrintPolicy.h"

const TArray<FObfuscationDetails> UObfuscationSettings::FieldsToObfuscate =
{
    FObfuscationDetails(FString("game_key"), "*", 4, 3, false),
    FObfuscationDetails(FString("game_api_key"), "*", 4, 3, false),
    FObfuscationDetails(FString("api_key"), "*", 4, 3, false),
    FObfuscationDetails(FString("key"), "*", 4, 3, false),
    FObfuscationDetails(FString("email"), "*", 3, 3, true),
    FObfuscationDetails(FString("password"), "*", 0, 0, true),
    FObfuscationDetails(FString("domain_key"), "*", 3, 3, true),
    FObfuscationDetails(FString("session_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("token"), "*", 3, 3, true)
};

FString ULootLockerEnumUtils::GetEnum(const TCHAR* Enum, int32 EnumValue)
{
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 7
    const UEnum* EnumPtr = FindObject<UEnum>(StaticClass()->GetOuter(), Enum, EFindObjectFlags::ExactClass);
#else
    const UEnum* EnumPtr = FindObject<UEnum>(StaticClass()->GetOuter(), Enum, true);
#endif
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
        FString OutJsonString = "";
        TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutJsonString);

        FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter, true);

        return OutJsonString;
    }

    FString FStringFromJsonArray(const TArray<TSharedPtr<FJsonValue>>& JsonArray)
    {
        FString OutJsonString = "";
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
        FString valueToObfuscate = "";
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

        FString ObfuscatedString = "";
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
	    FString OutJsonString = "";
	    TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>> > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutJsonString, 0);
	    bool bSuccess = FJsonSerializer::Serialize(JsonObject, JsonWriter);
	    JsonWriter->Close();
	    return bSuccess ? OutJsonString : "";
    }

    FString JsonValueToString(const TSharedRef<FJsonValue>& JsonValue)
    {
	    FString OutJsonString = "";
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
