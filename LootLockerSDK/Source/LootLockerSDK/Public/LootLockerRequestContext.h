// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerRequestContext.generated.h"

/**
 * Enum of the different types of values that can be in the request parameter dictionary. Use this to know how to parse the value.
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerRequestParameterType : uint8
{
    none = 0,
    null = 1,
    string_value = 2,
    integer_value = 3,
    decimal_value = 4,
    bool_value = 5,
    json_object = 6,
    array = 7,
    array_string = 8,
    array_integer = 9,
    array_decimal = 10,
    array_bool = 11,
    array_object = 12,
    unknown = 13,
};

/**
*/
USTRUCT(BlueprintType)
struct FLootLockerRequestParameterValue
{
    GENERATED_BODY()
    /**
      The type of value stored in this parameter. Use this to know how to parse the Value.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRequestParameterType ValueType = ELootLockerRequestParameterType::unknown;
    /**
      The value for this parameter as a json string, use the dedicated methods to parse this
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString ValueAsString = "";
    /**
      The value for this parameter as a json value, use the dedicated methods to parse this
     */
    TSharedPtr<FJsonValue> Value = nullptr;

    /*
     Get the contained value as a String. Returns true if value could be parsed in which case Output contains the string value untouched, returns false if parsing failed.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsString(FString& Output) const;
    /*
     Get the contained value as a float. Returns true if value could be parsed in which case Output contains the float, returns false if parsing failed which can happen if the value is not numeric, the conversion under or overflows, or the string value precision is larger than can be dealt within a float.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsFloat(float& Output) const;
    /*
     Get the contained value as an integer. Returns true if value could be parsed in which case Output contains the int, returns false if parsing failed.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsInteger(int& Output) const;
    /*
     Get the contained value as a boolean. Returns true if value could be parsed in which case Output contains the bool, returns false if parsing failed which can happen if the string is not a convertible to a boolean (those are for example "0", "1", "true", "False", "yes", "NO", etc).
     */
    LOOTLOCKERSDK_API bool TryGetValueAsBool(bool& Output) const;
    /*
     Get the contained value as a String. Returns true if value could be parsed in which case Output contains the string value untouched, returns false if parsing failed.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsStringArray(TArray<FString>& Output) const;
    /*
     Get the contained value as a float. Returns true if value could be parsed in which case Output contains the float, returns false if parsing failed which can happen if the value is not numeric, the conversion under or overflows, or the string value precision is larger than can be dealt within a float.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsFloatArray(TArray<float>& Output) const;
    /*
     Get the contained value as an integer. TReturns true if value could be parsed in which case Output contains the int, returns false if parsing failed which can happen if
     */
    LOOTLOCKERSDK_API bool TryGetValueAsIntegerArray(TArray<int>& Output) const;
    /*
     Get the contained value as a boolean. Returns true if value could be parsed in which case Output contains the bool, returns false if parsing failed which can happen if the string is not a convertible to a boolean (those are for example "0", "1", "true", "False", "yes", "NO", etc).
     */
    LOOTLOCKERSDK_API bool TryGetValueAsBoolArray(TArray<bool>& Output) const;
    /*
     Get the contained value as an unparsed json value. Returns true if value could be found in which case Output contains the JsonValue, returns false if the value field was not present.
     */
    LOOTLOCKERSDK_API bool TryGetRawValue(TSharedPtr<FJsonValue>& Output) const;
    /*
     Get the contained value as a Json Object. Returns true if value could be parsed in which case Output contains the Json Object, returns false if parsing failed which can happen if the value is not a valid json object string.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsJsonObject(TSharedPtr<FJsonObject>& Output) const;
    /*
     Get the contained value as a Json Array. Returns true if value could be parsed in which case Output contains the Json Array, returns false if parsing failed which can happen if the value is not a valid json array string
     */
    LOOTLOCKERSDK_API bool TryGetValueAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const;
};

USTRUCT(BlueprintType)
struct FLootLockerRequestContext
{
    GENERATED_BODY()
    // What player this request was made on behalf of
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString PlayerUlid = "";
    // The time that this request was made
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestTime = "";
    // The unique identifier for this request
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestId = "";
    // The url that this request was made to
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestURL = "";
    // The url that this request was made to
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestMethod = "";
    // The parameters that were sent with this request. This is empty by default unless enabled in LootLocker configuration.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FLootLockerRequestParameterValue> RequestParameters;
    // The request parameters as a json string.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString RequestParametersJsonString = "";
};
