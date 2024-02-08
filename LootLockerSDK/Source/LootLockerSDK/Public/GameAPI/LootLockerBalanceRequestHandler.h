// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerCurrencyRequestHandler.h"
#include "LootLockerResponse.h"
#include "LootLockerHttpClient.h"
#include "LootLockerBalanceRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================


/**
 * Possible wallet holder types
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerWalletHolderTypes : uint8
{
    character = 0,
    player = 1,
};

/**
 * 
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerBalance
{
    GENERATED_BODY()
    /**
     * Current amount of the given currency in this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount;
    /**
     * Information about the currency that this balance is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCurrency Currency;
    /**
     * The id of the wallet holding this balance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id;
    /**
     * The time that this balance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at;
};

//==================================================
// Request Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerCreateWalletRequest
{
    GENERATED_BODY()
    /**
     * ULID of the holder you want to create a wallet for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Holder_id;
    /**
     * The type of holder that this holder id refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Holder_type;
    /**
     * The id of the created wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerCreditRequest
{
    GENERATED_BODY()
    /**
     * Amount of the given currency to debit/credit to/from the given wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount;
    /**
     * The id of the currency that the amount is given in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_id;
    /** The id of the wallet to credit/debit to/from
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id;
};

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerDebitRequest
{
    GENERATED_BODY()
    /**
     * Amount of the given currency to debit/credit to/from the given wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount;
    /**
     * The id of the currency that the amount is given in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_id;
    /** The id of the wallet to credit/debit to/from
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id;
};


//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerListBalancesForWalletResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * List of balances in different currencies in the requested wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerBalance> Balances;
};

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerGetWalletResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The unique id of the holder of this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Holder_id;
    /**
     * The unique id of this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id;
    /**
     * The type of entity that holds this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerWalletHolderTypes type = ELootLockerWalletHolderTypes::player;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCreditWalletResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Current amount of the given currency in this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount;
    /**
     * Information about the currency that this balance is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCurrency Currency;
    /**
     * The id of the wallet holding this balance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id;
    /**
     * The time that this balance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerDebitWalletResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Current amount of the given currency in this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount;
    /**
     * Information about the currency that this balance is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCurrency Currency;
    /**
     * The id of the wallet holding this balance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id;
    /**
     * The time that this balance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at;
};

/**
 *
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerCreateWalletResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The unique id of this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================
/**
 * Blueprint response delegate for listing balances in a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListBalancesForWalletResponseBP, FLootLockerListBalancesForWalletResponse, Response);
/**
 * Blueprint response delegate for getting a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerGetWalletResponseBP, FLootLockerGetWalletResponse, Response);
/**
 * Blueprint response delegate for crediting currency to a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCreditWalletResponseBP, FLootLockerCreditWalletResponse, Response);
/**
 * Blueprint response delegate for debiting currency from a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerDebitWalletResponseBP, FLootLockerDebitWalletResponse, Response);
/**
 * Blueprint response delegate for creating a wallet
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerCreateWalletResponseBP, FLootLockerCreateWalletResponse, Response);

//==================================================
// C++ Delegate Definitions
//==================================================
/**
 * C++ response delegate for listing balances in a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerListBalancesForWalletResponseDelegate, FLootLockerListBalancesForWalletResponse);
/**
 * C++ response delegate for getting a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerGetWalletResponseDelegate, FLootLockerGetWalletResponse);
/**
 * C++ response delegate for crediting currency to a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerCreditWalletResponseDelegate, FLootLockerCreditWalletResponse);
/**
 * C++ response delegate for debiting currency from a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerDebitWalletResponseDelegate, FLootLockerDebitWalletResponse);
/**
 * C++ response delegate for creating a wallet
 */
DECLARE_DELEGATE_OneParam(FLootLockerCreateWalletResponseDelegate, FLootLockerCreateWalletResponse);


//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerBalanceRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerBalanceRequestHandler();
    static void ListBalancesInWallet(const FString& WalletID, const FLootLockerListBalancesForWalletResponseBP& OnCompleteBP = FLootLockerListBalancesForWalletResponseBP(), const FLootLockerListBalancesForWalletResponseDelegate& OnComplete = FLootLockerListBalancesForWalletResponseDelegate());
    static void GetWalletByWalletID(const FString& WalletID, const FLootLockerGetWalletResponseBP& OnCompleteBP = FLootLockerGetWalletResponseBP(), const FLootLockerGetWalletResponseDelegate& OnComplete = FLootLockerGetWalletResponseDelegate());
    static void GetWalletByHolderID(const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseBP& OnCompleteBP = FLootLockerGetWalletResponseBP(), const FLootLockerGetWalletResponseDelegate& OnComplete = FLootLockerGetWalletResponseDelegate());
    static void CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseBP& OnCompleteBP = FLootLockerCreditWalletResponseBP(), const FLootLockerCreditWalletResponseDelegate& OnComplete = FLootLockerCreditWalletResponseDelegate());
    static void DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseBP& OnCompleteBP = FLootLockerDebitWalletResponseBP(), const FLootLockerDebitWalletResponseDelegate& OnComplete = FLootLockerDebitWalletResponseDelegate());
private:
	static void CreateWallet(const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerCreateWalletResponseBP& OnCompleteBP = FLootLockerCreateWalletResponseBP(), const FLootLockerCreateWalletResponseDelegate& OnComplete = FLootLockerCreateWalletResponseDelegate());

    static ULootLockerHttpClient* HttpClient;
};
