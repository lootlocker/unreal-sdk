// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerAuthenticationRequestHandler.h"
#include "LootLockerHttpClient.h"
#include "LootLockerResponse.h"
#include "TimerManager.h"
#include "Utils/LootLockerUtilities.h"
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

//==================================================
// Request Definitions
//==================================================

/**
 * 
 */
USTRUCT(BlueprintType, Category = "LootLocker")
struct FLootLockerLeaseRemoteSessionRequest
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
    FString Code;
    /**
     * The nonce used to sign usage of the lease code
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Nonce;
    /**
     * A url with the code and nonce baked in that can be used to immediately start the remote authentication process on the device that uses it
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Redirect_url;
    /**
     * A QR code representation of the redirect_url encoded in Base64
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Redirect_url_qr_base64;
    /**
     * A clean version of the redirect_url without the code visible that you can use in your UI
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Display_url;
    /**
     * The status of this lease process
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    ELootLockerRemoteSessionLeaseStatus Status;
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
    ELootLockerRemoteSessionLeaseStatus Lease_status;
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
    ELootLockerRemoteSessionLeaseStatus Lease_Status;
    /**
     * A refresh token that can be used to refresh the remote session instead of signing in each time the session token expires
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Refresh_token;
};


//==================================================
// Blueprint Delegate Definitions
//==================================================

/**
 * Blueprint response delegate for receiving the remote session lease information
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerLeaseRemoteSessionResponseDelegateBP, FLootLockerLeaseRemoteSessionResponse, Response);
/**
 * Blueprint response delegate for receiving continual polling updates
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerRemoteSessionStatusPollingResponseDelegateBP, FLootLockerRemoteSessionStatusPollingResponse, Response);
/**
 * Blueprint response delegate for receiving the finalized remote session data (whether successful or not)
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FLootLockerStartRemoteSessionResponseDelegateBP, FLootLockerStartRemoteSessionResponse, Response);

//==================================================
// C++ Delegate Definitions
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
    ULootLockerRemoteSessionRequestHandler();

    static void CancelRemoteSessionProcess(const FString& ProcessID);
    static FString StartRemoteSession(const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformationBP = FLootLockerLeaseRemoteSessionResponseDelegateBP(), const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation = FLootLockerLeaseRemoteSessionResponseDelegate(), const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdateBP = FLootLockerRemoteSessionStatusPollingResponseDelegateBP(), const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate = FLootLockerRemoteSessionStatusPollingResponseDelegate(), const FLootLockerStartRemoteSessionResponseDelegateBP& OnCompleteBP = FLootLockerStartRemoteSessionResponseDelegateBP(), const FLootLockerStartRemoteSessionResponseDelegate& OnComplete = FLootLockerStartRemoteSessionResponseDelegate(), float PollingIntervalSeconds = 1.0f, float TimeOutAfterMinutes = 5.0f);
protected:
    static void ContinualPollingAction(const FString& ProcessID,
        const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformationBP = FLootLockerLeaseRemoteSessionResponseDelegateBP(),
        const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation = FLootLockerLeaseRemoteSessionResponseDelegate(),
        const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdateBP = FLootLockerRemoteSessionStatusPollingResponseDelegateBP(),
        const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate = FLootLockerRemoteSessionStatusPollingResponseDelegate(),
        const FLootLockerStartRemoteSessionResponseDelegateBP& OnCompleteBP = FLootLockerStartRemoteSessionResponseDelegateBP(),
        const FLootLockerStartRemoteSessionResponseDelegate& OnComplete = FLootLockerStartRemoteSessionResponseDelegate());
    static void KillProcess(const FString& ProcessID);
    static void LeaseRemoteSession(const LLAPI<FLootLockerLeaseRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback);
    static void StartRemoteSession(const FString& LeaseCode, const FString& LeaseNonce, const LLAPI<FLootLockerStartRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback);
    static void SetTimer(FTimerHandle TimerHandle, const FTimerDelegate& BaseDelegate, float TimeToNextPoll);
    static void ClearTimer(FTimerHandle TimerHandle);
private:
    static ULootLockerHttpClient* HttpClient;
    static TMap<FString, FLootLockerRemoteSessionProcess> RemoteSessionProcesses;
};
