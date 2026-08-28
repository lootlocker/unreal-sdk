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
    FObfuscationDetails(FString("token"), "*", 3, 3, true),
    // Auth & session credentials
    FObfuscationDetails(FString("steam_ticket"), "*", 3, 3, true),
    FObfuscationDetails(FString("id_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("auth_code"), "*", 3, 3, true),
    FObfuscationDetails(FString("apple_authorization_code"), "*", 3, 3, true),
    FObfuscationDetails(FString("xbox_user_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("nsa_id_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("access_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("refresh_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("nonce"), "*", 3, 3, true),
    FObfuscationDetails(FString("signature"), "*", 3, 3, true),
    FObfuscationDetails(FString("salt"), "*", 3, 3, true),
    FObfuscationDetails(FString("source_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("target_token"), "*", 3, 3, true),
    // Purchase / IAP credentials
    FObfuscationDetails(FString("purchase_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("bearer_token"), "*", 3, 3, true),
    FObfuscationDetails(FString("user_collections_id"), "*", 3, 3, true),
    FObfuscationDetails(FString("service_ticket"), "*", 3, 3, true)
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
        // Trim to ensure spaces don't break primitive evaluation
        const FString TrimmedString = JsonString.TrimStartAndEnd();

        // 1. Attempt to parse as JSON Array or Object
        if (TrimmedString.StartsWith(TEXT("[")) || TrimmedString.StartsWith(TEXT("{")))
        {
            TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(TrimmedString);
            TSharedPtr<FJsonValue> ParsedValue;
            
            if (FJsonSerializer::Deserialize(Reader, ParsedValue) && ParsedValue.IsValid())
            {
                return ParsedValue;
            }
            // If it starts with [ or { but fails JSON parsing, it falls through to String
        }

        // 2. Evaluate Boolean
        if (TrimmedString.Equals(TEXT("true"), ESearchCase::IgnoreCase))
        {
            return MakeShared<FJsonValueBoolean>(true);
        }
        if (TrimmedString.Equals(TEXT("false"), ESearchCase::IgnoreCase))
        {
            return MakeShared<FJsonValueBoolean>(false);
        }

        // 3. Evaluate Null
        if (TrimmedString.Equals(TEXT("null"), ESearchCase::IgnoreCase))
        {
            return MakeShared<FJsonValueNull>();
        }

        // 4. Evaluate Number
        if (TrimmedString.IsNumeric())
        {
            return MakeShared<FJsonValueNumber>(FCString::Atod(*TrimmedString));
        }

        // 5. Fallback to String
        // Uses the original InputString to preserve any intentionally placed whitespace
        return MakeShared<FJsonValueString>(JsonString);
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
