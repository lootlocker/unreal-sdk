// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dom/JsonObject.h"
#include "Containers/CircularQueue.h"
#include "Containers/Queue.h"
#include "LootLockerPlayerData.h"
#include "LootLockerErrorData.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPresenceClient.generated.h"

// Forward declarations
class IWebSocket;

// ========================================================================
// ENUMS AND DATA STRUCTURES
// ========================================================================

/**
 * Connection states for the presence WebSocket
 */
UENUM(BlueprintType)
enum class ELootLockerPresenceConnectionState : uint8
{
    Disconnected    UMETA(DisplayName = "Disconnected"),
    Initializing    UMETA(DisplayName = "Initializing"),
    Connecting      UMETA(DisplayName = "Connecting"),
    Connected       UMETA(DisplayName = "Connected"),
    Authenticating  UMETA(DisplayName = "Authenticating"),
    Active          UMETA(DisplayName = "Active"),
    Reconnecting    UMETA(DisplayName = "Reconnecting"),
    Failed          UMETA(DisplayName = "Failed"),
    Destroyed       UMETA(DisplayName = "Destroyed")
};

/**
 * Connection statistics for presence client
 */
USTRUCT(BlueprintType)
struct LOOTLOCKERSDK_API FLootLockerPresenceConnectionStats
{
    GENERATED_BODY()

    /** Player ULID this connection belongs to */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString PlayerUlid;

    /** Current connection state */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    ELootLockerPresenceConnectionState ConnectionState;

    /** Last status sent to the server */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FString LastSentStatus;

    /** Current round-trip latency in milliseconds */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    float CurrentLatencyMs;

    /** Average latency over recent pings in milliseconds */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    float AverageLatencyMs;

    /** Minimum recorded latency in milliseconds */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    float MinLatencyMs;

    /** Maximum recorded latency in milliseconds */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    float MaxLatencyMs;

    /** Total number of pings sent */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    int32 TotalPingsSent;

    /** Total number of pongs received */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    int32 TotalPongsReceived;

    /** Time when connection was established */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FDateTime ConnectionStartTime;

    /** Time when connection was terminated (MinValue if still connected) */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FDateTime ConnectionEndTime;

    /** Duration since connection was established */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LootLocker")
    FTimespan ConnectionDuration;

    FLootLockerPresenceConnectionStats()
    {
        PlayerUlid = TEXT("");
        ConnectionState = ELootLockerPresenceConnectionState::Destroyed;
        LastSentStatus = TEXT("");
        CurrentLatencyMs = 0.0f;
        AverageLatencyMs = 0.0f;
        MinLatencyMs = FLT_MAX;
        MaxLatencyMs = 0.0f;
        TotalPingsSent = 0;
        TotalPongsReceived = 0;
        ConnectionStartTime = FDateTime::MinValue();
        ConnectionEndTime = FDateTime::MinValue();
        ConnectionDuration = FTimespan::Zero();
    }

    FString ToLogString() const
    {
        return FString::Printf(TEXT("PlayerUlid: %s, State: %d, LastStatus: %s, PingsSent=%d, PongsReceived=%d, ConnectionDuration=%s, Latency(ms): Current=%.2f, Avg=%.2f, Min=%.2f, Max=%.2f"),
            *PlayerUlid,
            static_cast<int32>(ConnectionState),
            *LastSentStatus,
            TotalPingsSent,
            TotalPongsReceived,
            *ConnectionDuration.ToString(),
            CurrentLatencyMs,
            AverageLatencyMs,
            MinLatencyMs,
            MaxLatencyMs);
    }
};

/**
 * Authentication request sent to the Presence WebSocket
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerPresenceAuthenticationRequest
{
    GENERATED_BODY()
    /**
     * The session token for authenticating the presence connection
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Token = "";
};

/**
 * Ping request for presence WebSocket
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerPresencePingRequest
{
    GENERATED_BODY()
    /**
     * The type of the message, should be "ping"
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Type = "ping";
};

/**
 * Status update request for presence WebSocket
 */
USTRUCT(BlueprintType, Category="LootLocker")
struct FLootLockerPresenceStatusRequest
{
    GENERATED_BODY()
    /**
     * The status to set for the player
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    FString Status = "";
    /**
     * Optional metadata key-value pairs to send with the status update
     */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    TMap<FString, FString> Metadata;
};

// ========================================================================
// DELEGATES
// ========================================================================

/**
 * Delegate for presence connection state changes
 */
DECLARE_DELEGATE_FourParams(FLootLockerPresenceConnectionDelegate, const FString&, ELootLockerPresenceConnectionState, ELootLockerPresenceConnectionState, const FString&); // (PlayerUlid, PreviousState, CurrentState, ErrorMessage)

/**
 * Delegate for handling presence connection process callbacks
 */
DECLARE_DELEGATE_TwoParams(FLootLockerPresenceCallbackDelegate, bool, const FString&); // (Success, ErrorMessage)


// ========================================================================
// PRESENCE CLIENT CLASS
// ========================================================================

/**
 * Internal class for managing WebSocket connection to LootLocker presence service
 * This class handles the low-level WebSocket operations for a single player
 */
UCLASS()
class LOOTLOCKERSDK_API ULootLockerPresenceClient : public UObject
{
    GENERATED_BODY()

    // ====================================================================
    // PUBLIC INTERFACE
    // ====================================================================

public:
    ULootLockerPresenceClient();

    /**
     * Initialize the presence client for a specific player
     * 
     * @param InPlayerUlid The player ULID to associate with this presence client
     * @param InSessionToken The session token for authenticating the presence connection
     * @param InConnectionDelegate Delegate to call when connection state changes
     */
    void Initialize(const FString InPlayerUlid, const FString InSessionToken, const FLootLockerPresenceConnectionDelegate& InConnectionDelegate);

    /**
     * Start the WebSocket connection
     * 
     * @param OnComplete Delegate to call when connection attempt completes
     */
    void Connect(const FLootLockerPresenceCallbackDelegate& OnComplete);

    /**
     * Close the WebSocket connection
     * 
     * @param OnComplete Delegate to call when disconnection completes
     */
    void Disconnect(const FLootLockerPresenceCallbackDelegate& OnComplete);

    /**
     * Update the session token used for authentication
     * 
     * @param NewToken The new session token
     */
    void UpdateSessionToken(const FString& NewToken, bool ShouldAutoReconnect, const FLootLockerPresenceCallbackDelegate& OnComplete);

    /**
     * Get the current session token
     */
    FString GetSessionToken() const { return SessionToken; }

    /**
     * Send a status update to the presence service
     * 
     * @param Status The new status string to set
     * @param Metadata Optional metadata key-value pairs to send with the status update
     * @param OnComplete Delegate to call when status update completes
     */
    void UpdateStatus(const FString& Status, TMap<FString, FString> Metadata, const FLootLockerPresenceCallbackDelegate& OnComplete);

    /**
     * Get current connection state
     */
    ELootLockerPresenceConnectionState GetConnectionState() const { return ConnectionState; }

    /**
     * Check if currently connected and authenticated
     */
    bool IsConnected() const { return ConnectionState == ELootLockerPresenceConnectionState::Active; }

    /**
     * Get the player ULID this client represents
     */
    FString GetPlayerUlid() const { return PlayerUlid; }

    /**
     * Get connection statistics including latency information
     */
    FLootLockerPresenceConnectionStats GetConnectionStats() const;

    // ====================================================================
    // UNREAL ENGINE LIFECYCLE
    // ====================================================================

protected:
    virtual void BeginDestroy() override;
    void Cleanup();

private:
    // ====================================================================
    // CORE CONNECTION DATA
    // ====================================================================

    /** Player ULID for this presence connection */
    FString PlayerUlid;

    /** Session token for authentication */
    FString SessionToken;

    /** Current connection state */
    ELootLockerPresenceConnectionState ConnectionState = ELootLockerPresenceConnectionState::Destroyed;

    /** WebSocket connection */
    TSharedPtr<IWebSocket> WebSocket;

    /** Connection statistics */
    FLootLockerPresenceConnectionStats ConnectionStats;

    // ====================================================================
    // CALLBACK MANAGEMENT
    // ====================================================================

    /** Delegate to call when connection state changes */
    FLootLockerPresenceConnectionDelegate ConnectionDelegate;

    /** Connection request callback */
    FLootLockerPresenceCallbackDelegate ConnectionRequestCallback;

    void HandleConnectionResult(bool bSuccess, const FString& ErrorMessage);

    // ====================================================================
    // STATUS MANAGEMENT
    // ====================================================================

    /** Metadata from last sent status (for resending on reconnect) */
    TMap<FString, FString> LastSentMetadata;

    /** Pending status update data */
    bool bHasPendingStatusUpdate;
    FString PendingStatus;
    TMap<FString, FString> PendingMetadata;
    FLootLockerPresenceCallbackDelegate PendingStatusCallback;

    void SendStatusUpdateMessage(const FString& Status, const TMap<FString, FString>& Metadata, const FLootLockerPresenceCallbackDelegate& OnComplete);
    void ProcessPendingStatusUpdate();
    void AutoResendLastStatus();

    // ====================================================================
    // CONNECTION STATE & MESSAGING
    // ====================================================================

    /** Track client-initiated disconnects to avoid unnecessary reconnection */
    bool bIsClientInitiatedDisconnect;

    void SetConnectionState(ELootLockerPresenceConnectionState NewState, const FString& ErrorMessage = TEXT(""));
    bool SendMessage(const FString& Message);
    FString BuildWebSocketUrl() const;

    // ====================================================================
    // WEBSOCKET EVENT HANDLERS
    // ====================================================================

    void OnConnected();
    void OnConnectionError(const FString& Error);
    void OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
    void OnMessage(const FString& Message);
    void OnRawMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining);

    // ====================================================================
    // MESSAGE PROCESSING
    // ====================================================================

    void SendAuthenticationMessage();
    void HandleAuthenticationResponse(const FString& Message);
    void HandleErrorMessage(const FString& Message);
    void HandlePingMessage(const FString& Message);
    void HandlePongMessage(const FString& Message);

    // ====================================================================
    // RECONNECTION SYSTEM
    // ====================================================================
    int32 ReconnectAttempts;
    static constexpr int32 MaxReconnectAttempts = 8;
    static constexpr float ReconnectDelaySeconds = 1.0f;
    static constexpr float ReconnectBackoffFactor = 2.0f;
    float ReconnectInSeconds = 0.0f;
    void ScheduleReconnect();
    void AttemptReconnect();

    // ====================================================================
    // PING & LATENCY TRACKING
    // ====================================================================

    /** Ping system */
    static constexpr float PingIntervalSeconds = 20.0f;
    float TimeSinceLastPing = 0.0f;
    bool ShouldPing = false;
    TQueue<double> PendingPingTimestamps;

    /** Latency calculation */
    TUniquePtr<TCircularQueue<float>> RecentLatencies;
    float RecentLatenciesSum;
    void SendPing();
    void UpdateLatencyStats(float LatencyMs);
    void InitializeConnectionStats();
    UWorld* _GetWorld();

    // ====================================================================
    // TICKING & ROUTINES
    // ====================================================================
private:
    bool ShouldTick = false;
    void CancelAsyncActions();
    void StartTicker();
    virtual bool Tick(float DeltaTime);
};
