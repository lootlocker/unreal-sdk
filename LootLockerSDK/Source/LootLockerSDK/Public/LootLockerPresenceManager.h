// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Engine.h"
#include "LootLockerPresenceClient.h"
#include "LootLockerPlayerData.h"
#include "LootLockerPresenceManager.generated.h"

// ========================================================================
// FORWARD DECLARATIONS & DELEGATES
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
// CONFIGURATION TYPES
// ========================================================================

/**
 * Configuration structure for presence manager behavior
 */
USTRUCT(BlueprintType)
struct LOOTLOCKERSDK_API FLootLockerPresenceManagerConfig
{
    GENERATED_BODY()

    /** Whether presence connections are enabled globally */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool bIsEnabled = true;

    /** Whether to auto-connect presence when sessions are established */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool bAutoConnectEnabled = true;

    /** Whether to pause connections when app goes to background */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool bAutoDisconnectOnFocusChange = true;

    /** Whether presence is enabled in editor */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    bool bEnabledInEditor = true;
};

// ========================================================================
// CACHED STATUS UPDATE STRUCTURE
// ========================================================================
USTRUCT()
struct FLootLockerCachedPresenceStatusUpdate
{
    GENERATED_BODY()

    /** Status string to set */
    FString Status;

    /** Optional metadata key-value pairs */
    TMap<FString, FString> Metadata;
};


// ========================================================================
// MAIN CLASS
// ========================================================================

/**
 * Manager for LootLocker presence functionality
 * Coordinates presence connections for multiple players/sessions
 * and provides lifecycle management through external event integration
 */
UCLASS(BlueprintType)
class LOOTLOCKERSDK_API ULootLockerPresenceManager : public UObject
{
    GENERATED_BODY()

public:
    ULootLockerPresenceManager();

    // ====================================================================
    // PUBLIC API - MANUAL PRESENCE CONTROL
    // ====================================================================

    /**
     * Manually connect presence for a specific player
     * @param PlayerUlid The player ULID to connect presence for
     * @param OnComplete Callback when connection attempt completes
     */
    void ConnectPresence(const FString& PlayerUlid, const FLootLockerPresenceCallbackDelegate& OnComplete);

    /**
     * Manually disconnect presence for a specific player
     * @param PlayerUlid The player ULID to disconnect presence for
     * @param OnComplete Callback when disconnection completes
     */
    void DisconnectPresence(const FString& PlayerUlid, const FLootLockerPresenceCallbackDelegate& OnComplete);

    /**
     * Update status for a player's presence connection
     * @param PlayerUlid The player ULID to update status for
     * @param Status The new status string (e.g., "online", "in_game", "away")
     * @param Metadata Optional metadata key-value pairs
     * @param OnComplete Callback when status update completes
     */
    void UpdateStatus(const FString& PlayerUlid, const FString& Status, const TMap<FString, FString>& Metadata, const FLootLockerPresenceCallbackDelegate& OnComplete);

    /**
     * Update session token for an existing presence connection
     * @param PlayerUlid The player ULID to update token for
     * @param NewToken The new session token
     */
    void UpdateSessionToken(const FString& PlayerUlid, const FString& NewToken);

    // ====================================================================
    // PUBLIC API - BULK OPERATIONS
    // ====================================================================

    /**
     * Connect presence for all currently authenticated players/sessions
     * @param OnComplete Callback when all connection attempts complete
     */
    void ConnectPresenceForAllActiveSessions(const FLootLockerPresenceCallbackDelegate& OnComplete);

    /**
     * Disconnect all active presence connections
     * @param OnComplete Callback when all disconnections complete
     */
    void DisconnectAll(const FLootLockerPresenceCallbackDelegate& OnComplete);

    /**
     * Pause all active presence connections (keeps connections alive but stops activity)
     * Called when app goes to background, network is lost, etc.
     */
    void PauseAllConnections();

    /**
     * Pause presence connection for a specific player
     * @param PlayerUlid The player ULID to pause presence for
     */
    void PauseConnection(const FString& PlayerUlid);

    /**
     * Resume all paused presence connections
     * Called when app returns to foreground, network is restored, etc.
     */
    void ResumeAllConnections();

    /**
     * Resume presence connection for a specific player
     * @param PlayerUlid The player ULID to resume presence for
     */
    void ResumeConnection(const FString& PlayerUlid);

    /**
     * Gracefully shutdown all presence connections
     * Called during application termination
     */
    void GracefullyShutdown();

    // ====================================================================
    // PUBLIC API - QUERY & STATUS
    // ====================================================================

    /**
     * Check if presence is active for a specific player
     * @param PlayerUlid The player ULID to check
     * @return True if presence is active and connected
     */
    bool IsPresenceActiveForPlayer(const FString& PlayerUlid) const;

    /**
     * Get connection state for a specific player
     * @param PlayerUlid The player ULID to check
     * @return Current connection state
     */
    ELootLockerPresenceConnectionState GetPresenceStateForPlayer(const FString& PlayerUlid) const;

    /**
     * Get connection statistics for a specific player
     * @param PlayerUlid The player ULID to get statistics for
     * @return Connection statistics structure
     */
    FLootLockerPresenceConnectionStats GetConnectionStatsForPlayer(const FString& PlayerUlid) const;

    /**
     * Get list of all currently connected player ULIDs
     * @return Array of player ULIDs with active presence connections
     */
    TArray<FString> GetConnectedPlayerUlids() const;

    /**
     * Get count of currently active presence connections
     * @return Number of active connections
     */
    int32 GetActiveConnectionCount() const;

    // ====================================================================
    // PUBLIC API - CONFIGURATION
    // ====================================================================

    /**
     * Check if presence manager is globally enabled
     * @return True if presence connections are enabled
     */
    static bool IsEnabled();

    /**
     * Enable or disable presence manager globally
     * @param bEnabled Whether to enable presence connections
     */
    static void SetEnabled(bool bEnabled);

    /**
     * Check if auto-connect is enabled
     * @return True if auto-connect is enabled
     */
    static bool IsAutoConnectEnabled();

    /**
     * Enable or disable auto-connect behavior
     * @param bEnabled Whether to enable auto-connect
     */
    static void SetAutoConnectEnabled(bool bEnabled);

    /**
     * Check if pause-on-background is enabled
     * @return True if pause-on-background is enabled
     */
    static bool IsPauseOnBackgroundEnabled();

    /**
     * Enable or disable pause-on-background behavior
     * @param bEnabled Whether to enable pause-on-background
     */
    static void SetPauseOnBackgroundEnabled(bool bEnabled);

    /**
     * Check if presence is enabled in editor
     * @return True if presence is enabled in editor
     */
    static bool IsEnabledInEditor();

    /**
     * Enable or disable presence in editor
     * @param bEnabled Whether to enable presence in editor
     */
    static void SetEnabledInEditor(bool bEnabled);

protected:
    virtual void BeginDestroy() override;

private:
    // ====================================================================
    // PRIVATE MEMBERS - CLIENT MANAGEMENT
    // ====================================================================

    /** Map of active presence clients by player ULID */
    UPROPERTY()
    TMap<FString, ULootLockerPresenceClient*> PresenceClients;

    /** Set of clients currently in the process of connecting */
    TSet<FString> ConnectingClients;

    /** Set of clients that are paused (due to background, etc.) */
    TSet<FString> PausedClients;

    /** Thread safety for client operations */
    mutable FCriticalSection ClientMapLock;

    // ====================================================================
    // PRIVATE MEMBERS - CONFIGURATION & STATE
    // ====================================================================

    /** Current manager configuration */
    FLootLockerPresenceManagerConfig Configuration;

    TMap<FString /*Player Ulid*/, FLootLockerCachedPresenceStatusUpdate> CachedStatusUpdate;

    // ====================================================================
    // PRIVATE METHODS - CLIENT LIFECYCLE
    // ====================================================================

    /**
     * Create and initialize a new presence client
     * @param PlayerData Player data for the new client
     * @return Newly created client or nullptr on failure
     */
    ULootLockerPresenceClient* CreatePresenceClient(const FString& PlayerUlid, const FString& SessionToken);

    /**
     * Handle connection state changes from clients
     * @param PlayerUlid The player ULID whose state changed
     * @param OldState Previous connection state
     * @param NewState New connection state  
     * @param ErrorMessage Error message if applicable
     */
    void HandleClientConnectionStateChange(const FString& PlayerUlid, ELootLockerPresenceConnectionState OldState, ELootLockerPresenceConnectionState NewState, const FString& ErrorMessage);

    // ====================================================================
    // LIFECYCLE EVENT HANDLERS
    // ====================================================================

    /** Handle application startup event */
    UFUNCTION(Category="LootLocker")
    void HandleStartup();

    /** Handle application shutdown event */
    UFUNCTION(Category="LootLocker")
    void HandleShutdown();

    /** Handle application backgrounding event */
    UFUNCTION(Category="LootLocker")
    void HandleApplicationBackground();

    /** Handle application foregrounding event */
    UFUNCTION(Category="LootLocker")
    void HandleApplicationForeground();

    // ====================================================================
    // OTHER EVENT HANDLERS
    // ====================================================================

    /** Handle LootLocker config changes */
    UFUNCTION(Category="LootLocker")
    void HandleConfigurationUpdated(const FString& SettingName);

    // ====================================================================
    // SINGLETON MANAGEMENT
    // ====================================================================
public:
    /**
     * Get the singleton instance of the presence manager
     */
    static ULootLockerPresenceManager* GetInstance();

    /**
     * Initialize the presence manager subsystem
     */
    static void Initialize();
    /**
     * Shutdown and cleanup the presence manager subsystem
     */
    static void Shutdown();

    // ====================================================================
    // PUBLIC API - EVENTS
    // ====================================================================

    /**
     * Notify manager that a player has been activated (e.g., logged in)
     * 
     * @param PlayerUlid The player ULID that was activated
     * @param SessionToken The session token for the activated player
     */
    static void NotifyPlayerActivated(const FString& PlayerUlid);

    /**
     * Notify manager that a player has been activated (e.g., logged in)
     * 
     * @param PlayerUlid The player ULID that was activated
     * @param SessionToken The session token for the activated player
     */
    static void NotifyPlayerDeactivated(const FString& PlayerUlid);
private:
    /** Singleton instance */
    static ULootLockerPresenceManager* Instance;

    /** Critical section for singleton creation */
    static FCriticalSection InstanceLock;
};