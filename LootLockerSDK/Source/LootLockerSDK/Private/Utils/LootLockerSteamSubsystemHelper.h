// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerSteamSubsystemHelper.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLootLockerSDKSteamSubsystemHelper, Log, All);

/**
 * Object containing the relevant information from an attempt to get the steam auth token
 */
USTRUCT(BlueprintType)
struct FLootLockerSteamSubsystemAuthTokenResult
{
    GENERATED_BODY()
    /** Whether the auth token could be successfully retrieved */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | Helpers | SteamSubsystemHelper")
    bool Success;
    /** The Auth token for the specified local user */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | Helpers | SteamSubsystemHelper")
    FString AuthToken;
    /** The Steam id for the specified local user */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | Helpers | SteamSubsystemHelper")
    FString SteamID;
    /** The local user number that this auth token is for */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | Helpers | SteamSubsystemHelper")
    int LocalUserNumber;
    /** If the auth token could not be retrieved, this holds the corresponding error message */
    UPROPERTY(BlueprintReadOnly, Category = "LootLocker | Helpers | SteamSubsystemHelper")
    FString Error;
};


/*
 * Delegate for responses upon login process completion
 */
DECLARE_DYNAMIC_DELEGATE_FourParams(FLootLockerSteamSubsystemLoginCompletedCallback, bool, Success, int, LocalUserNumber, const FString&, ErrorMsg, const FString&, AuthToken);
/*
 * Delegate for responses upon logout process completion
 */
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FLootLockerSteamSubsystemLogoutCompletedCallback, bool, Success, int, LocalUserNumber, const FString&, ErrorMsg);

UCLASS()
class ULootLockerSteamSubsystemHelper : public UObject
{
    GENERATED_BODY()

public:
    /**
     * Does the Steam Subsystem exist and is initialized
     *
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Helpers | SteamSubsystemHelper")
    static bool HasSteamOnlineSubsystem();

    /**
     * Initialize Steam Subsystem Helper
     *
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Helpers | SteamSubsystemHelper")
    static void Initialize();

    /**
     * Check whether the specified local user has an active steam user
     *
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Helpers | SteamSubsystemHelper")
    static bool IsLoggedIn(int LocalUserNumber);

    /**
     * Do sign in using Steam asynchronously and call callback on completion
     *
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     * <param name="Callback">Callback that will be called when method completes</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Helpers | SteamSubsystemHelper")
    static void SignInWithSteam(int LocalUserNumber, const FLootLockerSteamSubsystemLoginCompletedCallback Callback);

    /**
     * Do sign out using Steam asynchronously and call callback on completion
     *
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     * <param name="Callback">Callback that will be called when method completes</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Helpers | SteamSubsystemHelper")
    static void SignOutWithSteam(int LocalUserNumber, const FLootLockerSteamSubsystemLogoutCompletedCallback Callback);

    /**
     * Get the Auth Token for the google user signed in for the provided local user number
     *
     * NOTE: The online subsystem needs to be enabled, included and configured for the project for this to work
     *
     * <param name="LocalUserNumber">Which local user to do sign in for</param>
     */
    UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | Helpers | SteamSubsystemHelper")
    static FLootLockerSteamSubsystemAuthTokenResult GetAuthToken(int LocalUserNumber);
private:
    static void InvokeSteamLoginCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerSteamSubsystemLoginCompletedCallback Callback);
    static void InvokeSteamLogoutCallbackWithErrorResponseAndLog(const FString& Message, int LocalUserNumber, const FLootLockerSteamSubsystemLogoutCompletedCallback Callback);
    static FDelegateHandle LoginDelegateHandle;
    static FDelegateHandle LogoutDelegateHandle;
    static bool IsInitialized;
};