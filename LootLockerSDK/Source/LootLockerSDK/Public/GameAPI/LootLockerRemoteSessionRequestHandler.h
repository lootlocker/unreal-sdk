// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerAuthenticationRequestHandler.h"
#include "LootLockerResponse.h"
#include "TimerManager.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "LootLockerSDK/Private/Utils/LootLockerUtilities.h"
#include "LootLockerRemoteSessionRequestHandler.generated.h"

//==================================================
// Data Type Definitions
//==================================================
/**
 * Possible entity kinds that catalog entries can have
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerRemoteSessionLeaseStatus : uint8
{
    Created = 0,
    Claimed = 1,
    Verified = 2,
    Authorized = 3,
    Cancelled = 4,
    Timed_out = 5,
    Failed = 6
};

/**
 * Possible intents for remote sessions
 */
UENUM(BlueprintType, Category = "LootLocker")
enum class ELootLockerRemoteSessionLeaseIntent : uint8
{
    /**
     * Intent is to log in using a leased remote session
     */
    login = 0,
    /**
     * Intent is to link different providers
     */
    link = 1
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRemoteSessionPlayerData
{
    GENERATED_BODY()
    /**
     * The player's name if it has been set by using SetPlayerName().
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString player_name = "";
    /**
     * The player id
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 player_id = 0;
    /**
     * The public UID for this player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString public_uid = "";
    /**
     * The player ULID for this player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString player_ulid = "";
    /**
     * Whether this player has been seen before (true) or is new (false)
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool seen_before = false;
    /**
     * Whether this player has new information to check in grants
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool check_grant_notifications = false;
    /**
     * Whether this player has new information to check in deactivations
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool check_deactivation_notifications = false;
    /**
     * The current xp of this player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 xp = 0;
    /**
     * The current level of this player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 level = 0;
    /**
     * The level_thresholds that the level and xp data relates to
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FLootLockerLevelThresholds level_thresholds;
    /**
     * The current balance in this account
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 account_balance = 0;
    /**
     * The player identifier of the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString player_identifier = "";
    /**
     * When this player was first created
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString player_created_at = "";
    /**
     The id of the wallet for this account
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString wallet_id = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRemoteSessionLeaseData
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
    /**
     * A url with the code and nonce baked in that can be used to immediately start the remote authentication process on the device that uses it
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Redirect_url = "";
    /**
     * A QR code representation of the redirect_url encoded in Base64
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Redirect_url_qr_base64 = "";
    /**
     * A clean version of the redirect_url without the code visible that you can use in your UI
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Display_url = "";
};

//==================================================
// Request Definitions
//==================================================

/**
 * Request body for remote session lease (now required fields)
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerLeaseRemoteSessionRequest
{
    GENERATED_BODY()
    /**
     * The title id for the game, this is the same as the Title ID in the LootLocker dashboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Title_id = "";
    /**
     * The environment id for the game, this is the same as the Environment ID in the LootLocker dashboard
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Environment_id = "";
    /**
     * The Game Version configured for the game
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Game_version = "";
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerStartRemoteSessionRequest
{
    GENERATED_BODY()
    /**
     * The Game Key configured for the game
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Game_key = "";
    /**
     * The Game Version configured for the game
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Game_version = "";
    /**
     * The lease code returned with the response when starting a lease process
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Lease_code = "";
    /**
     * The nonce returned with the response when starting a lease process
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Nonce = "";
};

USTRUCT(BlueprintType)
struct FLootLockerRefreshRemoteSessionRequest : public FLootLockerBaseAuthRequest_Old
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
    FString refresh_token = "";
};

//==================================================
// Response Definitions
//==================================================

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerLeaseRemoteSessionResponse : public FLootLockerResponse
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
    /**
     * A url with the code and nonce baked in that can be used to immediately start the remote authentication process on the device that uses it
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Redirect_url = "";
    /**
     * A QR code representation of the redirect_url encoded in Base64
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Redirect_url_qr_base64 = "";
    /**
     * A clean version of the redirect_url without the code visible that you can use in your UI
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Display_url = "";
    /**
     * The status of this lease process
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRemoteSessionLeaseStatus Status = ELootLockerRemoteSessionLeaseStatus::Created;
    /**
     * The intent for this lease request
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRemoteSessionLeaseIntent Intent = ELootLockerRemoteSessionLeaseIntent::login;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRemoteSessionStatusPollingResponse : public FLootLockerResponse
{
    GENERATED_BODY()
    /**
     * The current status of this lease process.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRemoteSessionLeaseStatus Lease_status = ELootLockerRemoteSessionLeaseStatus::Created;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerStartRemoteSessionResponse : public FLootLockerAuthenticationResponse
{
    GENERATED_BODY()
    /**
     * The current status of this lease process. If this is not of the status Authorized, the rest of the fields in this object will be empty.
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRemoteSessionLeaseStatus Lease_Status = ELootLockerRemoteSessionLeaseStatus::Created;
    /**
     * A refresh token that can be used to refresh the remote session instead of signing in each time the session token expires
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Refresh_token = "";
    /**
     * The intent for this lease request
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRemoteSessionLeaseIntent Intent = ELootLockerRemoteSessionLeaseIntent::login;
};

/**
 *
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerRefreshRemoteSessionResponse : public FLootLockerAuthenticationResponse
{
    GENERATED_BODY()
    /**
     * A refresh token that can be used to refresh the remote session instead of signing in each time the session token expires
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Refresh_token = "";
};

//==================================================
// Delegate Definitions
//==================================================

/**
 * C++ response delegate for receiving the remote session lease information
 */
DECLARE_DELEGATE_OneParam(FLootLockerLeaseRemoteSessionResponseDelegate, FLootLockerLeaseRemoteSessionResponse);
/**
 * C++ response delegate for receiving continual polling updates
 */
DECLARE_DELEGATE_OneParam(FLootLockerRemoteSessionStatusPollingResponseDelegate, FLootLockerRemoteSessionStatusPollingResponse);
/**
 * C++ response delegate for receiving the finalized remote session data (whether successful or not)
 */
DECLARE_DELEGATE_OneParam(FLootLockerStartRemoteSessionResponseDelegate, FLootLockerStartRemoteSessionResponse);
/**
 * C++ response delegate for receiving the refreshed remote session
 */
DECLARE_DELEGATE_OneParam(FLootLockerRefreshRemoteSessionResponseDelegate, FLootLockerRefreshRemoteSessionResponse);


//==================================================
// API Class Definition
//==================================================

struct FLootLockerRemoteSessionProcess
{
    static constexpr int RetryLimit = 5;
    FString LeaseCode = "";
    FString LeaseNonce = "";
    ELootLockerRemoteSessionLeaseStatus LastUpdatedStatus = ELootLockerRemoteSessionLeaseStatus::Failed;
    FDateTime LeasingProcessTimeoutTime;
    float PollingIntervalSeconds = 1.0f;
    FDateTime LastUpdatedAt;
    int Retries = 0;
    bool ShouldCancel = false;
    FTimerHandle RemoteSessionProcessTimerHandle;

    FLootLockerRemoteSessionProcess(float _PollingIntervalSeconds, float timeOutAfterMinutes);
};

UCLASS()
class LOOTLOCKERSDK_API ULootLockerRemoteSessionRequestHandler : public UObject
{
    GENERATED_BODY()
public:
    ULootLockerRemoteSessionRequestHandler() {};

    static void CancelRemoteSessionProcess(const FString& ProcessID);
    static FString StartRemoteSession(
        ELootLockerRemoteSessionLeaseIntent Intent = ELootLockerRemoteSessionLeaseIntent::login,
        const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation = FLootLockerLeaseRemoteSessionResponseDelegate(),
        const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate = FLootLockerRemoteSessionStatusPollingResponseDelegate(),
        const FLootLockerStartRemoteSessionResponseDelegate& OnComplete = FLootLockerStartRemoteSessionResponseDelegate(),
        float PollingIntervalSeconds = 1.0f,
        float TimeOutAfterMinutes = 5.0f,
        const FString& ForPlayerWithUlid = "");
    static FString RefreshRemoteSession(const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegate& OnComplete);
    static FString ContinualPollingAction(const FString& ProcessID,
        const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate = FLootLockerRemoteSessionStatusPollingResponseDelegate(),
        const FLootLockerStartRemoteSessionResponseDelegate& OnComplete = FLootLockerStartRemoteSessionResponseDelegate());
    static void KillProcess(const FString& ProcessID);

protected:
    static FString LeaseRemoteSession(
        const FString& TitleId,
        const FString& EnvironmentId,
        ELootLockerRemoteSessionLeaseIntent Intent,
        const FString& ForPlayerWithUlid,
        const LLAPI<FLootLockerLeaseRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback);
    static FString StartRemoteSession(const FString& LeaseCode, const FString& LeaseNonce, const LLAPI<FLootLockerStartRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback);
    static void SetTimer(FTimerHandle TimerHandle, const FTimerDelegate& BaseDelegate, float TimeToNextPoll);
    static void ClearTimer(FTimerHandle TimerHandle);
private:
    
    static TMap<FString, FLootLockerRemoteSessionProcess> RemoteSessionProcesses;
};

//==================================================
// Async Blueprint Delegate Definitions
//==================================================

/**
 * Multicast Delegate for events triggered from the Async Remote Session node
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FLootLockerAsyncRemoteSessionMulticastDelegate, FString, LeaseProcessID, FLootLockerRemoteSessionLeaseData, LeaseData, bool, HasPlayerData, FString, SessionTokenOnSuccess, FString, RefreshTokenOnSuccess, FLootLockerRemoteSessionPlayerData, PlayerDataOnSuccess, FLootLockerResponse, ResponseOnFailure);

//==================================================
// Async Blueprint Node Definitions
//==================================================

/***/
UCLASS()
class ULootLockerAsyncStartRemoteSession : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()
public:
    /**
     * Start a remote session
     * If you want to let your local user sign in using another device then you use this method.
     * First you will get the lease information (the LeaseData property will be populated) needed to allow a secondary device to authenticate and the OnProcessStarted event will trigger.
     *
     * Once the lease process status changes, the corresponding event will be triggered.
     * 
     * When the process has come to an end successfully, the OnProcessFinished event will trigger and the SessionTokenOnSuccess, RefreshTokenOnSuccess, and PlayerDataOnSuccess properties will be populated if present in the response.
     *
     * If the process is cancelled by the user, the OnProcessCanceled event will trigger.
     *
     * If the process times out, the OnProcessTimedOut event will trigger.
     * 
     * If the process fails, the OnProcessFailed event will trigger and the ResponseOnFailure property will be populated and contain error data.
     *
     * @param WorldContextObject Non input: Automatic context for async node
     * @param PollingIntervalSeconds Optional: How often to poll the status of the remote session process
     * @param TimeOutAfterMinutes Optional: How long to allow the process to take in its entirety
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "LootLocker Methods | Remote Session", WorldContext = "WorldContextObject", AdvancedDisplay = "PollingIntervalSeconds,TimeOutAfterMinutes,ForPlayerWithUlid", PollingIntervalSeconds = 1.0f, TimeOutAfterMinutes = 5.0f, ForPlayerWithUlid = ""))
    static LOOTLOCKERSDK_API ULootLockerAsyncStartRemoteSession* AsyncStartRemoteSession(UObject* WorldContextObjectfloat, float PollingIntervalSeconds, float TimeOutAfterMinutes);

    /**
     * Start a remote session with the intent to use the remote session for connecting accounts
     * If you want to let your local user sign in using another device then you use this method.
     * First you will get the lease information (the LeaseData property will be populated) needed to allow a secondary device to authenticate and the OnProcessStarted event will trigger.
     *
     * Once the lease process status changes, the corresponding event will be triggered.
     * 
     * When the process has come to an end successfully, the OnProcessFinished event will trigger and the SessionTokenOnSuccess, RefreshTokenOnSuccess, and PlayerDataOnSuccess properties will be populated if present in the response.
     *
     * If the process is cancelled by the user, the OnProcessCanceled event will trigger.
     *
     * If the process times out, the OnProcessTimedOut event will trigger.
     * 
     * If the process fails, the OnProcessFailed event will trigger and the ResponseOnFailure property will be populated and contain error data.
     *
     * @param WorldContextObject Non input: Automatic context for async node
     * @param ForPlayerWithUlid Execute the request for the specified player (the player that you intend to link the remote account into).
     * @param PollingIntervalSeconds Optional: How often to poll the status of the remote session process
     * @param TimeOutAfterMinutes Optional: How long to allow the process to take in its entirety
     * @return
     */
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "LootLocker Methods | Remote Session", WorldContext = "WorldContextObject", AdvancedDisplay = "PollingIntervalSeconds,TimeOutAfterMinutes,ForPlayerWithUlid", PollingIntervalSeconds = 1.0f, TimeOutAfterMinutes = 5.0f, ForPlayerWithUlid = ""))
    static LOOTLOCKERSDK_API ULootLockerAsyncStartRemoteSession* AsyncStartRemoteSessionForLinking(UObject* WorldContextObject, FString ForPlayerWithUlid, float PollingIntervalSeconds, float TimeOutAfterMinutes);


	/** Triggered once the lease process has successfully been started and the LeaseData property has been populated with the necessary information */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncRemoteSessionMulticastDelegate OnProcessStarted;
    /** Triggered once the remote lease has been claimed (external process) */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncRemoteSessionMulticastDelegate OnLeaseClaimed;
    /** Triggered once the remote lease has been verified (external process) */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncRemoteSessionMulticastDelegate OnLeaseVerified;
    /** Triggered if the process was canceled using the CancelRemoteSessionProcess method */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncRemoteSessionMulticastDelegate OnProcessCancelled;
    /** Triggered if the process times out */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncRemoteSessionMulticastDelegate OnProcessTimedOut;
    /** Triggered if the process has concluded and was not a success. The ResponseOnFailure will be populated with the relevant error information */
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncRemoteSessionMulticastDelegate OnProcessFailed;
    /** Triggered if the process concluded successfully. The SessionTokenOnSuccess, RefreshTokenOnSuccess, and PlayerDataOnSuccess properties will be populated (if present in the response).*/
    UPROPERTY(BlueprintAssignable)
    FLootLockerAsyncRemoteSessionMulticastDelegate OnProcessFinished;

    /** Execute the actual operation */
    LOOTLOCKERSDK_API virtual void Activate() override;

protected:
    FString ForPlayerWithUlid = "";
    ELootLockerRemoteSessionLeaseIntent Intent = ELootLockerRemoteSessionLeaseIntent::login;
    FString LeaseProcessID = "";
    float PollingIntervalInSeconds = 0.0f;
    float TimeoutAfterMinutes = 0.0f;
    FLootLockerRemoteSessionLeaseData LeaseData;

    UFUNCTION()
    LOOTLOCKERSDK_API virtual void HandleLeaseProcessStarted(const FLootLockerLeaseRemoteSessionResponse& LeaseProcessStartedResponse);
    UFUNCTION()
    LOOTLOCKERSDK_API virtual void HandleLeaseProcessUpdate(const FLootLockerRemoteSessionStatusPollingResponse& LeaseProcessUpdateResponse);
    UFUNCTION()
    LOOTLOCKERSDK_API virtual void HandleLeaseProcessCompleted(const FLootLockerStartRemoteSessionResponse& LeaseProcessCompletedResponse);
};
