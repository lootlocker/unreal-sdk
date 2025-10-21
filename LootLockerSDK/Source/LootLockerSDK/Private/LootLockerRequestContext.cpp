#pragma once

#include "CoreMinimal.h"
#include "LootLockerRequestContext.h"

bool FLootLockerRequestParameterValue::TryGetValueAsString(FString& Output) const
{
    return Value.IsValid() && Value->TryGetString(Output);
}

bool FLootLockerRequestParameterValue::TryGetValueAsFloat(float& Output) const
{
#if ENGINE_MAJOR_VERSION > 5
    return Value.IsValid() && Value->TryGetNumber(Output);
#else
    double outDouble = 0.0f;
    bool success = Value.IsValid() && Value->TryGetNumber(outDouble);
    Output = static_cast<float>(outDouble);
    return success;
#endif
}

bool FLootLockerRequestParameterValue::TryGetValueAsInteger(int& Output) const
{
    return Value.IsValid() && Value->TryGetNumber(Output);
}

bool FLootLockerRequestParameterValue::TryGetValueAsBool(bool& Output) const
{
    return Value.IsValid() && Value->TryGetBool(Output);
}

bool FLootLockerRequestParameterValue::TryGetValueAsStringArray(TArray<FString>& Output) const
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;
    if (!TryGetValueAsJsonArray(jsonArray))
    {
        return false;
    }

    Output = TArray<FString>();
    bool allSucceeded = true;
    for (TSharedPtr<FJsonValue> JsonValue : jsonArray)
    {
        FString convertedValue = "";
        if (JsonValue->TryGetString(convertedValue))
        {
            Output.Add(convertedValue);
        }
        else
        {
            allSucceeded = false;
        }
    }
    return allSucceeded;
}

bool FLootLockerRequestParameterValue::TryGetValueAsFloatArray(TArray<float>& Output) const
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;
    if (!TryGetValueAsJsonArray(jsonArray))
    {
        return false;
    }

    Output = TArray<float>();
    bool allSucceeded = true;
    for (TSharedPtr<FJsonValue> JsonValue : jsonArray)
    {
        float convertedValue = 0.0f;
#if ENGINE_MAJOR_VERSION > 5
        if (!(Value.IsValid() && Value->TryGetNumber(convertedValue)))
        {
            allSucceeded = false;
            continue;
        }
#else
        double outDouble = 0.0f;
        if (!(Value.IsValid() && Value->TryGetNumber(outDouble)))
        {
            allSucceeded = false;
            continue;
        }
        convertedValue = static_cast<float>(outDouble);
#endif
        Output.Add(convertedValue);
    }
    return allSucceeded;
}

bool FLootLockerRequestParameterValue::TryGetValueAsIntegerArray(TArray<int>& Output) const
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;
    if (!TryGetValueAsJsonArray(jsonArray))
    {
        return false;
    }

    Output = TArray<int>();
    bool allSucceeded = true;
    for (TSharedPtr<FJsonValue> JsonValue : jsonArray)
    {
        int convertedValue = 0;
        if (JsonValue->TryGetNumber(convertedValue))
        {
            Output.Add(convertedValue);
        }
        else
        {
            allSucceeded = false;
        }
    }
    return allSucceeded;
}

bool FLootLockerRequestParameterValue::TryGetValueAsBoolArray(TArray<bool>& Output) const
{
    TArray<TSharedPtr<FJsonValue>> jsonArray;
    if (!TryGetValueAsJsonArray(jsonArray))
    {
        return false;
    }

    Output = TArray<bool>();
    bool allSucceeded = true;
    for (TSharedPtr<FJsonValue> JsonValue : jsonArray)
    {
        bool convertedValue = false;
        if (JsonValue->TryGetBool(convertedValue))
        {
            Output.Add(convertedValue);
        }
        else
        {
            allSucceeded = false;
        }
    }
    return allSucceeded;
}

bool FLootLockerRequestParameterValue::TryGetRawValue(TSharedPtr<FJsonValue>& Output) const
{
    if (Value.IsValid())
    {
        Output = Value;
        return true;
    }
    return false;
}

bool FLootLockerRequestParameterValue::TryGetValueAsJsonObject(TSharedPtr<FJsonObject>& Output) const
{
    if (Value.IsValid() && Value->Type == EJson::Object)
    {
        Output = Value->AsObject();
        return Output.IsValid();
    }
    return false;
}

bool FLootLockerRequestParameterValue::TryGetValueAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const
{
    if (Value.IsValid() && Value->Type == EJson::Array)
    {
        Output = Value->AsArray();
        return true;
    }
    return false;
}