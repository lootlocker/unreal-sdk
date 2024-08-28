// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerMetadataRequestHandler.generated.h"

//==================================================
// Enum Definitions
//==================================================

/*
 Possible metadata sources
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerMetadataSources : uint8
{
    reward = 0,
    leaderboard = 1,
    catalog_item = 2,
    progression = 3,
};

/*
 Possible metadata types
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerMetadataTypes : uint8
{
    String = 0,
    Number = 1,
    Bool = 2,
    Json = 3,
    Base64 = 4,
};

/*
 Possible metadata parser output types
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerMetadataParserOutputTypes : uint8
{
    OnString = 0 UMETA(ToolTip="Triggered when the parsed entry is of type String. The String Value field will be populated"),
    OnInteger = 1 UMETA(ToolTip = "Triggered when the parsed entry is of type Integer (non decimal number). The Integer Value field will be populated"),
    OnDouble = 2 UMETA(ToolTip = "Triggered when the parsed entry is of type Double (decimal number). The Double Value field will be populated"),
    OnNumber = 3 UMETA(ToolTip = "Triggered when the parsed entry is a number but not a regular integer or double (could for example be too big to fit in either of those types, or the decimal precision is higher than can be solved with either of the types). The NumberString value field will be populated"),
    OnBool = 4 UMETA(ToolTip = "Triggered when the parsed entry is of type Bool. The Bool Value field will be populated"),
    OnJson = 5 UMETA(ToolTip = "Triggered when the parsed entry is of type Json. The JsonString Value field will be populated with the string representation of the json, convert to a JSON object or straight to a USTRUCT of your design"),
    OnBase64 = 6 UMETA(ToolTip = "Triggered when the parsed entry is of type Base64. The Base64 Value field will be populated"),
    OnError = 7 UMETA(ToolTip = "Triggered when the entry could not be parsed. The ErrorMessage Value field will be populated"),
};


//==================================================
// Data Type Definitions
//==================================================

/*
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerMetadataBase64Value
{
    GENERATED_BODY()
    /*
     The type of content that the base64 string encodes. Could be for example "image/jpeg" if it is a base64 encoded jpeg, or "application/x-redacted" if loading of files has been disabled
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Content_type;
    /*
     The encoded content in the form of a Base64 String. If this is unexpectedly empty, check if Content_type is set to "application/x-redacted". If it is, then the request for metadata was made with the ignoreFiles parameter set to true
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Content;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerMetadataEntry
{
    GENERATED_BODY()
    /*
     The metadata key
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Key;
    /*
     The type of value this metadata contains. Use this to parse the value.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerMetadataTypes Type;
    /*
     List of tags applied to this metadata
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> Tags;

    /*
     Get the value as a String. Returns true if value could be parsed in which case Output contains the string value untouched, returns false if parsing failed.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsString(FString& Output) const;
    /*
     Get the value as a double. Returns true if value could be parsed in which case Output contains the double, returns false if parsing failed which can happen if the value is not numeric, the conversion under or overflows, or the string value precision is larger than can be dealt within a double.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsDouble(double& Output) const;
    /*
     Get the value as an integer. TReturns true if value could be parsed in which case Output contains the int, returns false if parsing failed which can happen if
     */
    LOOTLOCKERSDK_API bool TryGetValueAsInteger(int& Output) const;
    /*
     Get the value as a boolean. Returns true if value could be parsed in which case Output contains the bool, returns false if parsing failed which can happen if the string is not a convertible to a boolean (those are for example "0", "1", "true", "False", "yes", "NO", etc).
     */
    LOOTLOCKERSDK_API bool TryGetValueAsBool(bool& Output) const;
    /*
     Get the value as an unparsed json value. Returns true if value could be found in which case Output contains the JsonValue, returns false if the value field was not present.
     */
    LOOTLOCKERSDK_API bool TryGetRawValue(TSharedPtr<FJsonValue>& Output) const;
    LOOTLOCKERSDK_API bool TryGetSerializedValue(FString& Output) const;
    /*
     Get the value as an unparsed json value. Returns true if value could be found in which case Output contains the JsonValue, returns false if the value field was not present.
     */
    template<typename T>
    LOOTLOCKERSDK_API bool TryGetValueAsUStruct(T& Output) const;
    /*
     Get the value as a Json Object. Returns true if value could be parsed in which case Output contains the Json Object, returns false if parsing failed which can happen if the value is not a valid json object string.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsJsonObject(TSharedPtr<FJsonObject>& Output) const;
    /*
     Get the value as a Json Array. Returns true if value could be parsed in which case Output contains the Json Array, returns false if parsing failed which can happen if the value is not a valid json array string
     */
    LOOTLOCKERSDK_API bool TryGetValueAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const;
    /*
     Get the value as a LootLockerMetadataBase64Value object. Returns true if value could be parsed in which case Output contains the FLootLockerMetadataBase64Value, returns false if parsing failed.
     */
    LOOTLOCKERSDK_API bool TryGetValueAsBase64(FLootLockerMetadataBase64Value& Output) const;

    /*
     */
    void _INTERNAL_SetJsonRepresentation(const FJsonObject& obj);
private:
    FJsonObject EntryAsJson;
};

//==================================================
// Request Definitions
//==================================================

//==================================================
// Response Definitions
//==================================================

/*
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListMetadataResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /*
     List of metadata entries on this page of metadata
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerMetadataEntry> Entries;
    /*
     Pagination data for this set of metadata entries
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerExtendedIndexBasedPagination Pagination;
    /*
    
     */
    int __INTERNAL_GetEntryIndexByKey(const FString Key) const;
    /*
    
     */
    void __INTERNAL_GenerateKeyMap();
private:
    TMap<FString, int> KeyToEntryIndex = TMap<FString, int>();
};

/*
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerGetMetadataResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /*
     The requested metadata entry
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerMetadataEntry Entry;
};

//==================================================
// Blueprint Delegate Definitions
//==================================================

/*
 Blueprint response delegate for listing metadata
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListMetadataResponseBP, FLootLockerListMetadataResponse, Response);
/*
 Blueprint response delegate for getting a single metadata entry
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetMetadataResponseBP, FLootLockerGetMetadataResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/*
 C++ response delegate for listing metadata
 */
DECLARE_DELEGATE_OneParam(FLootLockerListMetadataResponseDelegate, FLootLockerListMetadataResponse);
/*
 C++ response delegate for getting a single metadata entry
 */
DECLARE_DELEGATE_OneParam(FLootLockerGetMetadataResponseDelegate, FLootLockerGetMetadataResponse);

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerMetadataRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerMetadataRequestHandler();

    static void ListMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const FString& Key, const TArray<FString>& Tags, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnCompleteBP = FLootLockerListMetadataResponseBP(), const FLootLockerListMetadataResponseDelegate& OnComplete = FLootLockerListMetadataResponseDelegate());
    static void GetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerGetMetadataResponseBP& OnCompleteBP = FLootLockerGetMetadataResponseBP(), const FLootLockerGetMetadataResponseDelegate& OnComplete = FLootLockerGetMetadataResponseDelegate());
private:

    static ULootLockerHttpClient* HttpClient;
};
