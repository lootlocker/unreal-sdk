// Copyright (c) 2021 LootLocker

#pragma once


#include "CoreMinimal.h"
#include "LootLockerCurrencyRequestHandler.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerBalanceRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================


/// @addtogroup Balances
/// @{
UENUM(BlueprintType, Category = "LootLocker")
/**
 * Possible wallet holder types
 */
enum class ELootLockerWalletHolderTypes : uint8
{
    character = 0,
    player = 1,
};
/// @}

/**
 * Represents a currency balance in a wallet, including the amount, currency details, wallet identifier, and creation timestamp.
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerBalance
{
    GENERATED_BODY()
    /**
     * Current amount of the given currency in this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount = "";
    /**
     * Information about the currency that this balance is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCurrency Currency;
    /**
     * The id of the wallet holding this balance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id = "";
    /**
     * The time that this balance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
};

/**
 * Describes a currency balance modifier with a scaling factor, currency reference, and optional expiration time that adjusts effective wallet balances.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerBalanceModifiers
{
    GENERATED_BODY()
    /**
     * The id of the currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_id = "";
    /**
     * The name of the currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_name = "";
    /**
     * The currency code
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_code = "";
    /**
     * The factor of this currency
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Factor = "";
    /**
     * When this currency modifier was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
    /**
     * When this currency modifier expires
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Expires_at = "";
};

//==================================================
// Request Definitions
//==================================================

/**
 * Request to create a wallet for a specified holder, identified by ULID and holder type.
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerCreateWalletRequest
{
    GENERATED_BODY()
    /**
     * ULID of the holder you want to create a wallet for
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Holder_id = "";
    /**
     * The type of holder that this holder id refers to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Holder_type = "";
    /**
     * The id of the created wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
};

/**
 * Request to credit a specified amount of a given currency to a wallet.
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerCreditRequest
{
    GENERATED_BODY()
    /**
     * Amount of the given currency to debit/credit to/from the given wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount = "";
    /**
     * The id of the currency that the amount is given in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_id = "";
    /** The id of the wallet to credit/debit to/from
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id = "";
};

/**
 * Request to debit a specified amount of a given currency from a wallet.
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerDebitRequest
{
    GENERATED_BODY()
    /**
     * Amount of the given currency to debit/credit to/from the given wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount = "";
    /**
     * The id of the currency that the amount is given in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Currency_id = "";
    /** The id of the wallet to credit/debit to/from
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id = "";
};


//==================================================
// Response Definitions
//==================================================

/**
 * Response containing the list of currency balances held in a specific wallet.
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
 * Response containing a wallet's holder identifier, holder type, and active balance modifiers.
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerGetWalletResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The unique id of the holder of this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Holder_id = "";
    /**
     * The unique id of this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id = "";
    /**
     * The type of entity that holds this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerWalletHolderTypes type = ELootLockerWalletHolderTypes::player;
    /**
     * The modifiers for this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerBalanceModifiers Modifiers;
};

/**
 * Response containing the resulting balance entry after crediting currency to a wallet.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerCreditWalletResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Current amount of the given currency in this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount = "";
    /**
     * Information about the currency that this balance is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCurrency Currency;
    /**
     * The id of the wallet holding this balance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id = "";
    /**
     * The time that this balance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
};

/**
 * Response containing the resulting balance entry after debiting currency from a wallet.
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerDebitWalletResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Current amount of the given currency in this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Amount = "";
    /**
     * Information about the currency that this balance is in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerCurrency Currency;
    /**
     * The id of the wallet holding this balance
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id = "";
    /**
     * The time that this balance was created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Created_at = "";
};

/**
 * Response containing the unique identifier of the newly created wallet.
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerCreateWalletResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The unique id of this wallet
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Wallet_id = "";
};
//==================================================
// Delegate Definitions
//==================================================
/// @addtogroup Balances
/// @{
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

/// @}
UCLASS()
class LOOTLOCKERSDK_API ULootLockerBalanceRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerBalanceRequestHandler() {};

    static FString ListBalancesInWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FLootLockerListBalancesForWalletResponseDelegate& OnComplete);
    static FString GetWalletByWalletID(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FLootLockerGetWalletResponseDelegate& OnComplete);
    static FString GetWalletByHolderID(const FLootLockerPlayerData& PlayerData, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerGetWalletResponseDelegate& OnComplete);
    static FString CreditBalanceToWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerCreditWalletResponseDelegate& OnComplete);
    static FString DebitBalanceToWallet(const FLootLockerPlayerData& PlayerData, const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerDebitWalletResponseDelegate& OnComplete);
private:
    static FString CreateWallet(const FLootLockerPlayerData& PlayerData, const FString& HolderULID, const ELootLockerWalletHolderTypes& HolderType, const FLootLockerCreateWalletResponseDelegate& OnComplete);
};
