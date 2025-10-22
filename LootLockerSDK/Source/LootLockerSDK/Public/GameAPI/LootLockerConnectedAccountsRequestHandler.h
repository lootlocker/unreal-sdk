// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerResponse.h"
#include "LootLockerPlayerData.h"
#include "LootLockerConnectedAccountsRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================
/**
 * Account providers possible to use for connected accounts
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerAccountProvider : uint8
{
    Guest = 0,
    Google = 1,
    Apple = 2,
    Steam = 3,
    Epic_games = 4,
    Credentials = 5, // White Label Login
    Nintendo = 6,
    Xbox = 7,
    Playstation = 8,
    Twitch = 9,
    Discord = 10
};

/**
 * Google OAuth2 Client platform
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class EGoogleAccountProviderPlatform : uint8
{
    web = 0,
    android = 1,
    ios = 2,
    desktop = 4
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConnectedAccountProvider
{
    GENERATED_BODY()
    /**
     * The account provider
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerAccountProvider Provider = ELootLockerAccountProvider::Guest;
    /**
     * Decorated name of this provider to use for displaying
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Provider_name = "";
};

//==================================================
// Request Definitions
//==================================================
/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConnectGoogleProviderToAccountRequest
{
    GENERATED_BODY()
    /**
     * The Id Token from google sign in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id_token = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConnectGoogleProviderToAccountWithPlatformRequest
{
    GENERATED_BODY()
    /**
     * The Id Token from google sign in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Id_token = "";
    /**
     * Google OAuth2 ClientID platform
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Platform = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConnectAppleRestProviderToAccountRequest
{
    GENERATED_BODY()
    /**
     * Authorization code, provided by apple during Sign In
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Authorization_code = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConnectEpicProviderToAccountRequest
{
    GENERATED_BODY()
    /**
     * The token from epic sign in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Token = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConnectPlaystationProviderToAccountRequest
{
    GENERATED_BODY()
    /**
     * The environment for the playstation account (dev, qa, prod)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Environment = "";
    /**
     * The code from playstation sign in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConnectDiscordProviderToAccountRequest
{
    GENERATED_BODY()
    /**
     * The token from discord sign in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Token = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConnectTwitchProviderToAccountRequest
{
    GENERATED_BODY()
    /**
     * The authorization code from twitch sign in
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Authorization_code = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerConnectRemoteSessionToAccountRequest
{
    GENERATED_BODY()
    /**
     * The unique code for this leasing process, this is what identifies the leasing process and that is used to interact with it
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Code = "";
    /**
     * The nonce used to sign usage of the lease code
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Nonce = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerTransferProvidersBetweenAccountsRequest
{
    GENERATED_BODY()
    /**
     * Session token belonging to the player to move platforms FROM
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Source_token = "";
    /**
     * Session token belonging to the player to move platforms TO
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Target_token = "";
    /**
     * List of identity providers to move FROM the account authenticated by the source token TO the account authenticated by the target token
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FString> Identity_providers;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAccountConnectedStruct
{
    GENERATED_BODY()
    /**
     * The account provider
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerAccountProvider Provider = ELootLockerAccountProvider::Guest;
    /**
     * Decorated name of this provider to use for displaying
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Provider_name = "";
};

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerAccountConnectedResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * Information about the connected account
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerAccountConnectedStruct Connected_account;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerListConnectedAccountsResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * List of the accounts connected (allowed to start sessions for) to this LootLocker account
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TArray<FLootLockerConnectedAccountProvider> ConnectedAccounts;
};

//==================================================
// Delegate Definitions
//==================================================
/**
 * C++ response delegate for connecting a provider to an account
 */
DECLARE_DELEGATE_OneParam(FLootLockerAccountConnectedResponseDelegate, FLootLockerAccountConnectedResponse);
/**
 * C++ response delegate for listing connected accounts
 */
DECLARE_DELEGATE_OneParam(FLootLockerListConnectedAccountsResponseDelegate, FLootLockerListConnectedAccountsResponse);

//==================================================
// API Class Definition
//==================================================

UCLASS()
class LOOTLOCKERSDK_API ULootLockerConnectedAccountsRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerConnectedAccountsRequestHandler() {};

    static FString ListConnectedAccounts(const FLootLockerPlayerData& PlayerData, const FLootLockerListConnectedAccountsResponseDelegate& OnComplete);
    static FString DisconnectAccount(const FLootLockerPlayerData& PlayerData, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultDelegate& OnComplete);
    static FString ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, const FLootLockerAccountConnectedResponseDelegate& OnComplete);
    static FString ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseDelegate& OnComplete);
    static FString ConnectAppleAccountByRestSignIn(const FLootLockerPlayerData& PlayerData, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete);
    static FString ConnectEpicAccount(const FLootLockerPlayerData& PlayerData, const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete);
    static FString ConnectPlaystationAccount(const FLootLockerPlayerData& PlayerData, const FString& Environment, const FString& Code, const FLootLockerAccountConnectedResponseDelegate& OnComplete);
    static FString ConnectDiscordAccount(const FLootLockerPlayerData& PlayerData, const FString& Token, const FLootLockerAccountConnectedResponseDelegate& OnComplete);
    static FString ConnectTwitchAccount(const FLootLockerPlayerData& PlayerData, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseDelegate& OnComplete);
    static FString ConnectRemoteSessionAccount(const FLootLockerPlayerData& PlayerData, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseDelegate& OnComplete);
    static FString TransferIdentityProvidersBetweenAccounts(const FLootLockerPlayerData& SourcePlayerData, const FLootLockerPlayerData& TargetPlayerData, TArray<ELootLockerAccountProvider> ProvidersToTransfer, const FLootLockerListConnectedAccountsResponseDelegate& OnComplete);
};
