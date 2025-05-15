// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerHttpClient.h"
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
    Twitch = 9
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
// Blueprint Delegate Definitions
//==================================================
/**
 * Blueprint response delegate for connecting a provider to an account
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerAccountConnectedResponseBP, FLootLockerAccountConnectedResponse, Response);
/**
 * Blueprint response delegate for listing connected accounts
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerListConnectedAccountsResponseBP, FLootLockerListConnectedAccountsResponse, Response);

//==================================================
// C++ Delegate Definitions
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
    ULootLockerConnectedAccountsRequestHandler();

    static void ListConnectedAccounts(const FLootLockerPlayerData& PlayerData, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP = FLootLockerListConnectedAccountsResponseBP(), const FLootLockerListConnectedAccountsResponseDelegate& OnComplete = FLootLockerListConnectedAccountsResponseDelegate());
    static void DisconnectAccount(const FLootLockerPlayerData& PlayerData, const ELootLockerAccountProvider AccountToDisconnect, const FLootLockerDefaultResponseBP& OnCompleteBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate& OnComplete = FLootLockerDefaultDelegate());
    static void ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, const FLootLockerAccountConnectedResponseBP& OnCompleteBP = FLootLockerAccountConnectedResponseBP(), const FLootLockerAccountConnectedResponseDelegate& OnComplete = FLootLockerAccountConnectedResponseDelegate());
    static void ConnectGoogleAccount(const FLootLockerPlayerData& PlayerData, const FString& IdToken, EGoogleAccountProviderPlatform Platform, const FLootLockerAccountConnectedResponseBP& OnCompleteBP = FLootLockerAccountConnectedResponseBP(), const FLootLockerAccountConnectedResponseDelegate& OnComplete = FLootLockerAccountConnectedResponseDelegate());
    static void ConnectAppleAccountByRestSignIn(const FLootLockerPlayerData& PlayerData, const FString& AuthorizationCode, const FLootLockerAccountConnectedResponseBP& OnCompleteBP = FLootLockerAccountConnectedResponseBP(), const FLootLockerAccountConnectedResponseDelegate& OnComplete = FLootLockerAccountConnectedResponseDelegate());
    static void ConnectRemoteSessionAccount(const FLootLockerPlayerData& PlayerData, const FString& Code, const FString& Nonce, const FLootLockerAccountConnectedResponseBP& OnCompleteBP = FLootLockerAccountConnectedResponseBP(), const FLootLockerAccountConnectedResponseDelegate& OnComplete = FLootLockerAccountConnectedResponseDelegate());
    static void TransferIdentityProvidersBetweenAccounts(const FLootLockerPlayerData& SourcePlayerData, const FLootLockerPlayerData& TargetPlayerData, TArray<ELootLockerAccountProvider> ProvidersToTransfer, const FLootLockerListConnectedAccountsResponseBP& OnCompleteBP = FLootLockerListConnectedAccountsResponseBP(), const FLootLockerListConnectedAccountsResponseDelegate& OnComplete = FLootLockerListConnectedAccountsResponseDelegate());
private:
    static ULootLockerHttpClient* HttpClient;
};
