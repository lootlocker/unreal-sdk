// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerHttpClient.h"
#include "LootLockerResponse.h"
#include "LootLockerCurrencyRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================

/**
 * Details about a particular currency
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCurrency
{
    GENERATED_BODY()
    /**
     * The unique id of the currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    /**
     * The name of the currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name;
    /**
     * The unique short code of the currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code;
    /**
     * True if this currency can be awarded to the player from the game api
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool Game_api_writes_enabled = false;
    /**
     * The time that this currency was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at;
    /**
     * The time that this currency was published
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Published_at;
};

/**
 * Represents a denomination of a currency
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerDenomination
{
    GENERATED_BODY()
    /**
     * The unique id of the denomination
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    /**
     * The id of the currency this is a denomination of
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency;
    /**
     * The name of this denomination
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Name;
    /**
     * The value of this denomination in units of the currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int Value = 0;
    /**
     * The time that this denomination was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at;
};

//==================================================
// Request Definitions
//==================================================

// N/A

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListCurrenciesResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * List of available currencies
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerCurrency> Currencies;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListDenominationsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * List of available denominations
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerDenomination> Denominations;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================

/**
 * Blueprint response delegate for listing currencies
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListCurrenciesResponseBP, FLootLockerListCurrenciesResponse, Response);
/**
 * Blueprint response delegate for listing denominations on a currency
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListDenominationsResponseBP, FLootLockerListDenominationsResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================

/**
 * C++ response delegate for listing currencies
 */
DECLARE_DELEGATE_OneParam(FLootLockerListCurrenciesResponseDelegate, FLootLockerListCurrenciesResponse);
/**
 * C++ response delegate for listing denominations on a currency
 */
DECLARE_DELEGATE_OneParam(FLootLockerListDenominationsResponseDelegate, FLootLockerListDenominationsResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerCurrencyRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerCurrencyRequestHandler();

    static void ListCurrencies(const FLootLockerListCurrenciesResponseBP& OnResponseCompletedBP = FLootLockerListCurrenciesResponseBP(), const FLootLockerListCurrenciesResponseDelegate& OnResponseCompleted = FLootLockerListCurrenciesResponseDelegate());
    static void GetCurrencyDenominationsByCode(const FString& CurrencyCode, const FLootLockerListDenominationsResponseBP& OnResponseCompletedBP = FLootLockerListDenominationsResponseBP(), const FLootLockerListDenominationsResponseDelegate& OnResponseCompleted = FLootLockerListDenominationsResponseDelegate());

    static ULootLockerHttpClient* HttpClient;
};
