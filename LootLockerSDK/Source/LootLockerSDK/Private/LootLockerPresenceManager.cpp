// Copyright (c) 2021 LootLocker

#include "LootLockerPresenceManager.h"
#include "LootLockerLogger.h"
#include "LootLockerStateData.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"

// ========================================================================
// STATIC MEMBERS
// ========================================================================

ULootLockerPresenceManager* ULootLockerPresenceManager::Instance = nullptr;
FCriticalSection ULootLockerPresenceManager::InstanceLock;

// ========================================================================
// CONSTRUCTOR & LIFECYCLE
// ========================================================================

ULootLockerPresenceManager::ULootLockerPresenceManager()
{
    FLootLockerLogger::LogVeryVerbose(TEXT("LootLocker Presence Manager created"));
}

// ========================================================================
// SINGLETON MANAGEMENT
// ========================================================================

ULootLockerPresenceManager* ULootLockerPresenceManager::GetInstance()
{
    FScopeLock Lock(&InstanceLock);
    if (!Instance)
    {
        Instance = NewObject<ULootLockerPresenceManager>();
        if (Instance)
        {
            Instance->AddToRoot(); // Prevent garbage collection
            FLootLockerLogger::LogVeryVerbose(TEXT("LootLocker Presence Manager singleton initialized"));
        }
    }
    return Instance;
}

// ========================================================================
// PUBLIC API - MANUAL PRESENCE CONTROL
// ========================================================================

void ULootLockerPresenceManager::ConnectPresence(const FString& PlayerUlid, const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    if (!Configuration.bIsEnabled)
    {
        FString ErrorMessage = TEXT("Presence manager is disabled");
        FLootLockerLogger::LogWarning(ErrorMessage);
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }

    if (PlayerUlid.IsEmpty())
    {
        FString ErrorMessage = TEXT("Invalid player ULID provided");
        FLootLockerLogger::LogWarning(ErrorMessage);
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }

    FScopeLock Lock(&ClientMapLock);
    
    // Check if already connecting
    if (ConnectingClients.Contains(PlayerUlid))
    {
        FString ErrorMessage = FString::Printf(TEXT("Presence connection already in progress for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogVeryVerbose(ErrorMessage);
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }

    // Check if already connected
    if (ULootLockerPresenceClient** ExistingClient = PresenceClients.Find(PlayerUlid))
    {
        if (*ExistingClient && (*ExistingClient)->IsConnected())
        {
            FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence already active for player: %s"), *PlayerUlid));
            OnComplete.ExecuteIfBound(true, TEXT("Already connected"));
            return;
        }
    }

    // Check if we have a paused client that can be resumed instead of creating a new one
    if (PausedClients.Contains(PlayerUlid))
    {
        if (ULootLockerPresenceClient** ExistingClient = PresenceClients.Find(PlayerUlid))
        {
            if (*ExistingClient)
            {                
                // Update session token in case it has changed
                FLootLockerPlayerData PlayerData = ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer(PlayerUlid);
                if (!PlayerData.PlayerUlid.IsEmpty() && !PlayerData.Token.IsEmpty())
                {
                    (*ExistingClient)->UpdateSessionToken(PlayerData.Token);
                }
                
                // Remove from paused set and add to connecting
                PausedClients.Remove(PlayerUlid);
                ConnectingClients.Add(PlayerUlid);
                
                // Connect the existing client
                (*ExistingClient)->Connect(FLootLockerPresenceCallbackDelegate::CreateLambda([this, PlayerUlid, OnComplete](bool bSuccess, FString ErrorMessage)
                {
                    FScopeLock InnerLock(&ClientMapLock);
                    ConnectingClients.Remove(PlayerUlid);
                    OnComplete.ExecuteIfBound(bSuccess, ErrorMessage);
                }));
                return;
            }
            else
            {
                // Client was null, remove from paused set and continue with new client creation
                PausedClients.Remove(PlayerUlid);
            }
        }
        else
        {
            // Client not found in map, remove from paused set and continue with new client creation
            PausedClients.Remove(PlayerUlid);
        }
    }

    // Get player data for this ULID
    FLootLockerPlayerData PlayerData = ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer(PlayerUlid);
    if (PlayerData.PlayerUlid.IsEmpty() || PlayerData.Token.IsEmpty())
    {
        FString ErrorMessage = FString::Printf(TEXT("No valid session data found for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogWarning(ErrorMessage);
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }

    // Create and connect client
    ULootLockerPresenceClient* Client = CreatePresenceClient(PlayerData.PlayerUlid, PlayerData.Token);
    if (!Client)
    {
        FString ErrorMessage = FString::Printf(TEXT("Failed to create presence client for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogError(ErrorMessage);
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }

    ConnectingClients.Add(PlayerUlid);
    Client->Connect(FLootLockerPresenceCallbackDelegate::CreateLambda([this, PlayerUlid, OnComplete](bool bSuccess, FString ErrorMessage)
    {
        FScopeLock InnerLock(&ClientMapLock);
        ConnectingClients.Remove(PlayerUlid);
        OnComplete.ExecuteIfBound(bSuccess, ErrorMessage);
    }));
}

void ULootLockerPresenceManager::DisconnectPresence(const FString& PlayerUlid, const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    if (PlayerUlid.IsEmpty())
    {
        FString ErrorMessage = TEXT("Invalid player ULID provided");
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }

    FScopeLock Lock(&ClientMapLock);
    
    // Remove from tracking sets
    ConnectingClients.Remove(PlayerUlid);
    PausedClients.Remove(PlayerUlid);
    
    // Find and disconnect client
    if (ULootLockerPresenceClient** ClientPtr = PresenceClients.Find(PlayerUlid))
    {
        if (*ClientPtr)
        {
            (*ClientPtr)->Disconnect(FLootLockerPresenceCallbackDelegate());
            (*ClientPtr)->ConditionalBeginDestroy();
        }
        PresenceClients.Remove(PlayerUlid);
        
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Removed presence client for player: %s"), *PlayerUlid));
    }
    OnComplete.ExecuteIfBound(true, TEXT("Disconnected successfully"));
}

void ULootLockerPresenceManager::UpdateStatus(const FString& PlayerUlid, const FString& Status, const TMap<FString, FString>& Metadata, const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    if (!Configuration.bIsEnabled)
    {
        FString ErrorMessage = TEXT("Presence manager is disabled");
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }

    if (PlayerUlid.IsEmpty())
    {
        FString ErrorMessage = TEXT("Invalid player ULID provided");
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }

    FScopeLock Lock(&ClientMapLock);
    if (ULootLockerPresenceClient** ClientPtr = PresenceClients.Find(PlayerUlid))
    {
        if (*ClientPtr && (*ClientPtr)->IsConnected())
        {
            (*ClientPtr)->UpdateStatus(Status, Metadata, OnComplete);
            return;
        }
    }

    FString ErrorMessage = FString::Printf(TEXT("No active presence connection found for player: %s"), *PlayerUlid);
    FLootLockerLogger::LogWarning(ErrorMessage);
    OnComplete.ExecuteIfBound(false, ErrorMessage);
}

void ULootLockerPresenceManager::UpdateSessionToken(const FString& PlayerUlid, const FString& NewToken)
{
    if (PlayerUlid.IsEmpty() || NewToken.IsEmpty())
    {
        FLootLockerLogger::LogWarning(TEXT("Invalid parameters for session token update"));
        return;
    }

    FScopeLock Lock(&ClientMapLock);

    if (ULootLockerPresenceClient** ClientPtr = PresenceClients.Find(PlayerUlid))
    {
        if (*ClientPtr)
        {
            (*ClientPtr)->UpdateSessionToken(NewToken);
        }
    } 
    else 
    {
        if (Configuration.bAutoConnectEnabled) 
        {
            ConnectPresence(PlayerUlid, FLootLockerPresenceCallbackDelegate());
        }
    }

    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Session token updated for player: %s"), *PlayerUlid));
}

// ========================================================================
// PUBLIC API - BULK OPERATIONS
// ========================================================================

void ULootLockerPresenceManager::ConnectPresenceForAllActiveSessions(const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    if (!Configuration.bIsEnabled)
    {
        FString ErrorMessage = TEXT("Presence manager is disabled");
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }
    
    FScopeLock Lock(&ClientMapLock);
    
    TArray<FString> PlayersToConnect;
    for (const FString& ActivePlayerUlid : ULootLockerStateData::GetActivePlayerUlids())
    {

        if (!PresenceClients.Contains(ActivePlayerUlid) && !ConnectingClients.Contains(ActivePlayerUlid))
        {
            PlayersToConnect.Add(ActivePlayerUlid);
        }
    }

    if (PlayersToConnect.Num() == 0)
    {
        OnComplete.ExecuteIfBound(true, TEXT("No additional sessions to connect"));
        return;
    }

    FLootLockerLogger::LogInfo(FString::Printf(TEXT("Connecting presence for %d active sessions"), PlayersToConnect.Num()));
    
    // For simplicity, connect them sequentially. Could be optimized to connect in parallel.
    for (const FString& PlayerUlid : PlayersToConnect)
    {
        ConnectPresence(PlayerUlid, FLootLockerPresenceCallbackDelegate());
    }
    
    OnComplete.ExecuteIfBound(true, FString::Printf(TEXT("Started connections for %d sessions"), PlayersToConnect.Num()));
}

void ULootLockerPresenceManager::DisconnectAll(const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    FScopeLock Lock(&ClientMapLock);
    ConnectingClients.Empty();
    PausedClients.Empty();
    
    int32 DisconnectedCount = 0;

    TArray<FString> PlayerUlidsToDisconnect;
    PresenceClients.GenerateKeyArray(PlayerUlidsToDisconnect);

    for (const FString& PlayerUlid : PlayerUlidsToDisconnect)
    {
        DisconnectPresence(PlayerUlid, FLootLockerPresenceCallbackDelegate());
        DisconnectedCount++;
    }

    PresenceClients.Empty();
    
    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Disconnected %d presence connections"), DisconnectedCount));
    OnComplete.ExecuteIfBound(true, FString::Printf(TEXT("Disconnected %d connections"), DisconnectedCount));
}

void ULootLockerPresenceManager::PauseAllConnections()
{
    if (!Configuration.bPauseOnBackground)
    {
        FLootLockerLogger::LogVerbose(TEXT("Pause on background is disabled, skipping pause"));
        return;
    }

    TArray<FString> PlayerUlidsToDisconnect;
    PresenceClients.GenerateKeyArray(PlayerUlidsToDisconnect);
    
    for (const FString& PlayerUlid : PlayerUlidsToDisconnect)
    {
        if (!PlayerUlid.IsEmpty())
        {
            PauseConnection(PlayerUlid);
        }
    }
}

void ULootLockerPresenceManager::PauseConnection(const FString& PlayerUlid)
{
    FScopeLock Lock(&ClientMapLock);
    
    if (ULootLockerPresenceClient** ClientPtr = PresenceClients.Find(PlayerUlid))
    {
        if (*ClientPtr && (*ClientPtr)->IsConnected())
        {
            (*ClientPtr)->Disconnect(FLootLockerPresenceCallbackDelegate());
            PausedClients.Add(PlayerUlid);
        }
    }
}


void ULootLockerPresenceManager::ResumeAllConnections()
{
    TArray<FString> PlayerUlidsToResume;
    PresenceClients.GenerateKeyArray(PlayerUlidsToResume);
    
    for (const FString& PlayerUlid : PlayerUlidsToResume)
    {
        if (!PlayerUlid.IsEmpty())
        {
            ResumeConnection(PlayerUlid);
        }
    }
}

void ULootLockerPresenceManager::ResumeConnection(const FString& PlayerUlid)
{
    FScopeLock Lock(&ClientMapLock);
    
    if (PausedClients.Contains(PlayerUlid))
    {
        ConnectPresence(PlayerUlid, FLootLockerPresenceCallbackDelegate());
        PausedClients.Remove(PlayerUlid);
    }
}

void ULootLockerPresenceManager::Shutdown()
{
    DisconnectAll(FLootLockerPresenceCallbackDelegate());
}

// ========================================================================
// PUBLIC API - QUERY & STATUS
// ========================================================================

bool ULootLockerPresenceManager::IsPresenceActiveForPlayer(const FString& PlayerUlid) const
{
    FScopeLock Lock(&ClientMapLock);
    if (const ULootLockerPresenceClient* const* Client = PresenceClients.Find(PlayerUlid))
    {
        return *Client && (*Client)->IsConnected();
    }
    return false;
}

ELootLockerPresenceConnectionState ULootLockerPresenceManager::GetPresenceStateForPlayer(const FString& PlayerUlid) const
{
    FScopeLock Lock(&ClientMapLock);
    if (const ULootLockerPresenceClient* const* Client = PresenceClients.Find(PlayerUlid))
    {
        return *Client ? (*Client)->GetConnectionState() : ELootLockerPresenceConnectionState::Disconnected;
    }
    return ELootLockerPresenceConnectionState::Disconnected;
}

FLootLockerPresenceConnectionStats ULootLockerPresenceManager::GetConnectionStatsForPlayer(const FString& PlayerUlid) const
{
    FScopeLock Lock(&ClientMapLock);
    if (const ULootLockerPresenceClient* const* Client = PresenceClients.Find(PlayerUlid))
    {
        return *Client ? (*Client)->GetConnectionStats() : FLootLockerPresenceConnectionStats();
    }
    return FLootLockerPresenceConnectionStats();
}

TArray<FString> ULootLockerPresenceManager::GetConnectedPlayerUlids() const
{
    FScopeLock Lock(&ClientMapLock);
    TArray<FString> ConnectedUlids;
    
    for (const auto& ClientPair : PresenceClients)
    {
        if (ClientPair.Value && ClientPair.Value->IsConnected())
        {
            ConnectedUlids.Add(ClientPair.Key);
        }
    }
    
    return ConnectedUlids;
}

int32 ULootLockerPresenceManager::GetActiveConnectionCount() const
{
    FScopeLock Lock(&ClientMapLock);
    int32 ActiveCount = 0;
    
    for (const auto& ClientPair : PresenceClients)
    {
        if (ClientPair.Value && ClientPair.Value->IsConnected())
        {
            ActiveCount++;
        }
    }
    
    return ActiveCount;
}

// ========================================================================
// PUBLIC API - CONFIGURATION
// ========================================================================

bool ULootLockerPresenceManager::IsEnabled()
{
    ULootLockerPresenceManager* Manager = GetInstance();
    return Manager ? Manager->Configuration.bIsEnabled : false;
}

void ULootLockerPresenceManager::SetEnabled(bool bEnabled)
{
    ULootLockerPresenceManager* Manager = GetInstance();
    if (Manager)
    {
        Manager->Configuration.bIsEnabled = bEnabled;
        FLootLockerLogger::LogInfo(FString::Printf(TEXT("Presence manager %s"), bEnabled ? TEXT("enabled") : TEXT("disabled")));
        
        if (!bEnabled)
        {
            Manager->DisconnectAll(FLootLockerPresenceCallbackDelegate());
        }
    }
}

bool ULootLockerPresenceManager::IsAutoConnectEnabled()
{
    ULootLockerPresenceManager* Manager = GetInstance();
    return Manager ? Manager->Configuration.bAutoConnectEnabled : false;
}

void ULootLockerPresenceManager::SetAutoConnectEnabled(bool bEnabled)
{
    ULootLockerPresenceManager* Manager = GetInstance();
    if (Manager)
    {
        Manager->Configuration.bAutoConnectEnabled = bEnabled;
        FLootLockerLogger::LogInfo(FString::Printf(TEXT("Presence auto-connect %s"), bEnabled ? TEXT("enabled") : TEXT("disabled")));
    }
}

bool ULootLockerPresenceManager::IsPauseOnBackgroundEnabled()
{
    ULootLockerPresenceManager* Manager = GetInstance();
    return Manager ? Manager->Configuration.bPauseOnBackground : false;
}

void ULootLockerPresenceManager::SetPauseOnBackgroundEnabled(bool bEnabled)
{
    ULootLockerPresenceManager* Manager = GetInstance();
    if (Manager)
    {
        Manager->Configuration.bPauseOnBackground = bEnabled;
        FLootLockerLogger::LogInfo(FString::Printf(TEXT("Presence pause-on-background %s"), bEnabled ? TEXT("enabled") : TEXT("disabled")));
    }
}

void ULootLockerPresenceManager::BeginDestroy()
{
    Shutdown();

    {
        FScopeLock Lock(&InstanceLock);
        if (Instance == this)
        {
            Instance = nullptr;
        }
    }

    Super::BeginDestroy();
}

// ========================================================================
// PRIVATE METHODS - CLIENT LIFECYCLE
// ========================================================================

ULootLockerPresenceClient* ULootLockerPresenceManager::CreatePresenceClient(const FString& PlayerUlid, const FString& SessionToken)
{
    ULootLockerPresenceClient* Client = NewObject<ULootLockerPresenceClient>(this);
    if (!Client)
    {
        FLootLockerLogger::LogError(FString::Printf(TEXT("Failed to create presence client for player: %s"), *PlayerUlid));
        return nullptr;
    }

    // Create connection state change delegate
    FLootLockerPresenceConnectionDelegate ConnectionDelegate;
    ConnectionDelegate.BindUObject(this, &ULootLockerPresenceManager::HandleClientConnectionStateChange);

    // Initialize client
    Client->Initialize(PlayerUlid, SessionToken, ConnectionDelegate);
    
    // Store in map
    PresenceClients.Add(PlayerUlid, Client);
    
    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Created presence client for player: %s"), *PlayerUlid));
    return Client;
}

void ULootLockerPresenceManager::HandleClientConnectionStateChange(const FString& PlayerUlid, ELootLockerPresenceConnectionState OldState, ELootLockerPresenceConnectionState NewState, const FString& ErrorMessage)
{
    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence connection state changed for player %s: %s -> %s"), 
           *PlayerUlid, 
           *UEnum::GetValueAsString(OldState),
           *UEnum::GetValueAsString(NewState)));

    // Handle connection failures
    if (NewState == ELootLockerPresenceConnectionState::Failed)
    {
        FLootLockerLogger::LogError(FString::Printf(TEXT("Presence connection failed for player %s: %s"), 
               *PlayerUlid, *ErrorMessage));
        
        // Optionally implement reconnection logic here
    }
    
    // Handle successful connections
    if (NewState == ELootLockerPresenceConnectionState::Active)
    {
        FLootLockerLogger::LogInfo(FString::Printf(TEXT("Presence connection established for player: %s"), *PlayerUlid));
    }
}