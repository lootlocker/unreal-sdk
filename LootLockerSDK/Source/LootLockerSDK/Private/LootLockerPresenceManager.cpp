// Copyright (c) 2021 LootLocker

#include "LootLockerPresenceManager.h"
#include "LootLockerPresenceClient.h"
#include "LootLockerLifeCycleManager.h"
#include "LootLockerLogger.h"
#include "LootLockerStateData.h"
#include "LootLockerConfig.h"
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
    // Initialize runtime configuration from config values
    Configuration.bIsEnabled = ULootLockerConfig::IsPresenceEnabled();
    Configuration.bAutoConnectEnabled = ULootLockerConfig::IsPresenceAutoConnectEnabled();
    Configuration.bAutoDisconnectOnFocusChange = ULootLockerConfig::IsPresenceAutoDisconnectOnFocusChangeEnabled();
    Configuration.bEnabledInEditor = ULootLockerConfig::IsPresenceEnabledInEditor();

    FScopeLock Lock(&InstanceLock);
    if (!Instance)
    {
        Instance = this;
    }
}

// ========================================================================
// LIFECYCLE EVENT HANDLERS
// ========================================================================

void ULootLockerPresenceManager::HandleStartup()
{
    if (Configuration.bIsEnabled && Configuration.bAutoConnectEnabled)
    {
        ConnectPresenceForAllActiveSessions(FLootLockerPresenceCallbackDelegate());
    }
}

void ULootLockerPresenceManager::HandleShutdown()
{
    DisconnectAll(FLootLockerPresenceCallbackDelegate());
}

void ULootLockerPresenceManager::HandleApplicationBackground()
{
    if (Configuration.bIsEnabled && Configuration.bAutoDisconnectOnFocusChange)
    {
        PauseAllConnections();
    }
}

void ULootLockerPresenceManager::HandleApplicationForeground()
{
    if (Configuration.bIsEnabled && Configuration.bAutoConnectEnabled)
    {
        ResumeAllConnections();
    }
}

// ========================================================================
// OTHER EVENT HANDLERS
// ========================================================================

void ULootLockerPresenceManager::HandleConfigurationUpdated(const FString& SettingName)
{
    if (SettingName.Equals(TEXT("bEnablePresence"), ESearchCase::IgnoreCase))
    {
        Configuration.bIsEnabled = ULootLockerConfig::IsPresenceEnabled();
    }
    else if (SettingName.Equals(TEXT("bEnablePresenceAutoConnect"), ESearchCase::IgnoreCase))
    {
        Configuration.bAutoConnectEnabled = ULootLockerConfig::IsPresenceAutoConnectEnabled();
    }
    else if (SettingName.Equals(TEXT("bEnablePresenceAutoDisconnectOnFocusChange"), ESearchCase::IgnoreCase))
    {
        Configuration.bAutoDisconnectOnFocusChange = ULootLockerConfig::IsPresenceAutoDisconnectOnFocusChangeEnabled();
    }
    else if (SettingName.Equals(TEXT("bEnablePresenceInEditor"), ESearchCase::IgnoreCase))
    {
        Configuration.bEnabledInEditor = ULootLockerConfig::IsPresenceEnabledInEditor();
    }
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
    }
    return Instance;
}

void ULootLockerPresenceManager::Initialize()
{
    ULootLockerPresenceManager* presenceManager = GetInstance();

    if (presenceManager)
    {
        presenceManager->AddToRoot();
        
        ULootLockerLifeCycleManager* LifeCycleManager = ULootLockerLifeCycleManager::GetInstance();
        if (LifeCycleManager)
        {
            LifeCycleManager->OnApplicationStart.AddDynamic(presenceManager, &ULootLockerPresenceManager::HandleStartup);
            LifeCycleManager->OnApplicationShutdown.AddDynamic(presenceManager, &ULootLockerPresenceManager::HandleShutdown);
            LifeCycleManager->OnApplicationBackground.AddDynamic(presenceManager, &ULootLockerPresenceManager::HandleApplicationBackground);
            LifeCycleManager->OnApplicationForeground.AddDynamic(presenceManager, &ULootLockerPresenceManager::HandleApplicationForeground);
        }
        ULootLockerConfig* Config = GetMutableDefault<ULootLockerConfig>();
        if(Config) {
            Config->OnConfigurationUpdated.AddDynamic(presenceManager, &ULootLockerPresenceManager::HandleConfigurationUpdated);
        }
    }
}

void ULootLockerPresenceManager::Shutdown()
{
    FScopeLock Lock(&InstanceLock);
    if (Instance)
    {
        ULootLockerLifeCycleManager* LifeCycleManager = ULootLockerLifeCycleManager::GetInstance();
        if (LifeCycleManager)
        {
            LifeCycleManager->OnApplicationStart.RemoveDynamic(Instance, &ULootLockerPresenceManager::HandleStartup);
            LifeCycleManager->OnApplicationShutdown.RemoveDynamic(Instance, &ULootLockerPresenceManager::HandleShutdown);
            LifeCycleManager->OnApplicationBackground.RemoveDynamic(Instance, &ULootLockerPresenceManager::HandleApplicationBackground);
            LifeCycleManager->OnApplicationForeground.RemoveDynamic(Instance, &ULootLockerPresenceManager::HandleApplicationForeground);
        }
        ULootLockerConfig* Config = GetMutableDefault<ULootLockerConfig>();
        if(Config) {
            Config->OnConfigurationUpdated.RemoveDynamic(Instance, &ULootLockerPresenceManager::HandleConfigurationUpdated);
        }
        Instance->GracefullyShutdown();
        Instance->RemoveFromRoot();
        Instance = nullptr;
        FLootLockerLogger::LogVeryVerbose(TEXT("LootLocker Presence Manager singleton shutdown"));
    }
}

// ========================================================================
// PUBLIC API - MANUAL PRESENCE CONTROL
// ========================================================================

void ULootLockerPresenceManager::ConnectPresence(const FString& PlayerUlid, const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    if (!Configuration.bIsEnabled || (!Configuration.bEnabledInEditor && GIsEditor))
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
        if (*ExistingClient)
        {
            const TSharedPtr<FLootLockerPlayerData> PlayerData = ULootLockerStateData::GetStateForPlayerOrDefaultIfActive(PlayerUlid);
            if (PlayerData.IsValid() 
                && !PlayerData->PlayerUlid.IsEmpty() 
                && !PlayerData->Token.IsEmpty() 
                && !(*ExistingClient)->GetSessionToken().Equals(PlayerData->Token, ESearchCase::IgnoreCase))
            {
                if (Configuration.bAutoConnectEnabled)
                {
                    ConnectingClients.Add(PlayerUlid);
                }
                (*ExistingClient)->UpdateSessionToken(PlayerData->Token, Configuration.bAutoConnectEnabled, FLootLockerPresenceCallbackDelegate::CreateLambda([this, PlayerUlid, OnComplete](bool bSuccess, FString ErrorMessage)
                {
                    FScopeLock InnerLock(&ClientMapLock);
                    PausedClients.Remove(PlayerUlid);
                    ConnectingClients.Remove(PlayerUlid);
                    OnComplete.ExecuteIfBound(bSuccess, ErrorMessage);
                }));
                return;
            }
            else if ((*ExistingClient)->IsConnected())
            {
                FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence already active for player: %s"), *PlayerUlid));
                PausedClients.Remove(PlayerUlid);
                ConnectingClients.Remove(PlayerUlid);
                OnComplete.ExecuteIfBound(true, TEXT("Already connected"));
                return;
            }
            else if ((*ExistingClient)->GetConnectionState() == ELootLockerPresenceConnectionState::Disconnected) 
            {
                ConnectingClients.Add(PlayerUlid);
                (*ExistingClient)->Connect(FLootLockerPresenceCallbackDelegate::CreateLambda([this, PlayerUlid, OnComplete](bool bSuccess, FString ErrorMessage)
                {
                    FScopeLock InnerLock(&ClientMapLock);
                    PausedClients.Remove(PlayerUlid);
                    ConnectingClients.Remove(PlayerUlid);
                    OnComplete.ExecuteIfBound(bSuccess, ErrorMessage);
                }));
                return;
            }
            else 
            {
                // Client exists but is in a bad state, remove and continue with new client creation
                PresenceClients.Remove(PlayerUlid);
                (*ExistingClient)->RemoveFromRoot();
                #if ENGINE_MAJOR_VERSION >= 5
                    (*ExistingClient)->MarkAsGarbage();
                #else
                    (*ExistingClient)->MarkPendingKill();
                #endif
                PausedClients.Remove(PlayerUlid);
                ConnectingClients.Remove(PlayerUlid);
            }
        }
        else 
        {
            // Client was null, remove and continue with new client creation
            PresenceClients.Remove(PlayerUlid);
            PausedClients.Remove(PlayerUlid);
            ConnectingClients.Remove(PlayerUlid);
        }
    }

    // Get player data for this ULID
    const TSharedPtr<FLootLockerPlayerData> PlayerData = ULootLockerStateData::GetStateForPlayerOrDefaultIfActive(PlayerUlid);
    if (!PlayerData.IsValid() || PlayerData->PlayerUlid.IsEmpty() || PlayerData->Token.IsEmpty())
    {
        FString ErrorMessage = FString::Printf(TEXT("No valid session data found for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogWarning(ErrorMessage);
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }

    // Create and connect client
    ULootLockerPresenceClient* Client = CreatePresenceClient(PlayerData->PlayerUlid, PlayerData->Token);
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
            (*ClientPtr)->RemoveFromRoot();
            #if ENGINE_MAJOR_VERSION >= 5
                (*ClientPtr)->MarkAsGarbage();
            #else
                (*ClientPtr)->MarkPendingKill();
            #endif
        }
        PresenceClients.Remove(PlayerUlid);
        
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Removed presence client for player: %s"), *PlayerUlid));
    }
    OnComplete.ExecuteIfBound(true, TEXT("Disconnected successfully"));
}

void ULootLockerPresenceManager::UpdateStatus(const FString& PlayerUlid, const FString& Status, const TMap<FString, FString>& Metadata, const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    if (!Configuration.bIsEnabled || (!Configuration.bEnabledInEditor && GIsEditor))
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
        else 
        {
            // Cache status update for later
            FLootLockerCachedPresenceStatusUpdate& CachedUpdate = CachedStatusUpdate.FindOrAdd(PlayerUlid);
            CachedUpdate.Status = Status;
            CachedUpdate.Metadata = Metadata;
        }
    }
    else 
    {
        // Cache status update for later
        FLootLockerCachedPresenceStatusUpdate& CachedUpdate = CachedStatusUpdate.FindOrAdd(PlayerUlid);
        CachedUpdate.Status = Status;
        CachedUpdate.Metadata = Metadata;
    }

    FString ErrorMessage = FString::Printf(TEXT("No active presence connection found for player: %s. Status has been cached and will be sent when connection is established"), *PlayerUlid);
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
            (*ClientPtr)->UpdateSessionToken(NewToken, Configuration.bAutoConnectEnabled, FLootLockerPresenceCallbackDelegate());
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
    if (!Configuration.bIsEnabled || (!Configuration.bEnabledInEditor && GIsEditor))
    {
        FString ErrorMessage = TEXT("Presence manager is disabled");
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }
    
    FScopeLock Lock(&ClientMapLock);
    
    TArray<FString> PlayersToConnect;
    for (const FString& ActivePlayerUlid : ULootLockerStateData::GetActivePlayerUlids())
    {
        if (!ConnectingClients.Contains(ActivePlayerUlid) && (!PresenceClients.Contains(ActivePlayerUlid) || !(*PresenceClients.Find(ActivePlayerUlid))->IsConnected()))
        {
            PlayersToConnect.Add(ActivePlayerUlid);
        }
    }

    if (PlayersToConnect.Num() == 0)
    {
        OnComplete.ExecuteIfBound(true, TEXT("No additional sessions to connect"));
        return;
    }

    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Connecting presence for %d active sessions"), PlayersToConnect.Num()));
    
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
    if (!Configuration.bAutoDisconnectOnFocusChange)
    {
        FLootLockerLogger::LogVeryVerbose(TEXT("Pause on background is disabled, skipping pause"));
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
    TArray<FString> PlayerUlidsToResume = PausedClients.Array();
    
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

void ULootLockerPresenceManager::GracefullyShutdown()
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
    return Manager ? Manager->Configuration.bIsEnabled : ULootLockerConfig::IsPresenceEnabled();
}

void ULootLockerPresenceManager::SetEnabled(bool bEnabled)
{
    ULootLockerPresenceManager* Manager = GetInstance();
    if (Manager)
    {
        Manager->Configuration.bIsEnabled = bEnabled;
        
        if (!bEnabled)
        {
            Manager->DisconnectAll(FLootLockerPresenceCallbackDelegate());
        }
        else if (Manager->Configuration.bAutoConnectEnabled)
        {
            Manager->ConnectPresenceForAllActiveSessions(FLootLockerPresenceCallbackDelegate());
        }
    }
}

bool ULootLockerPresenceManager::IsAutoConnectEnabled()
{
    ULootLockerPresenceManager* Manager = GetInstance();
    return Manager ? Manager->Configuration.bAutoConnectEnabled : ULootLockerConfig::IsPresenceAutoConnectEnabled();
}

void ULootLockerPresenceManager::SetAutoConnectEnabled(bool bEnabled)
{
    ULootLockerPresenceManager* Manager = GetInstance();
    if (Manager)
    {
        Manager->Configuration.bAutoConnectEnabled = bEnabled;
        if(bEnabled && Manager->Configuration.bIsEnabled)
        {
            Manager->ConnectPresenceForAllActiveSessions(FLootLockerPresenceCallbackDelegate());
        }
        else 
        {
            Manager->DisconnectAll(FLootLockerPresenceCallbackDelegate());
        }
    }
}

bool ULootLockerPresenceManager::IsPauseOnBackgroundEnabled()
{
    ULootLockerPresenceManager* Manager = GetInstance();
    return Manager ? Manager->Configuration.bAutoDisconnectOnFocusChange : ULootLockerConfig::IsPresenceAutoDisconnectOnFocusChangeEnabled();
}

void ULootLockerPresenceManager::SetPauseOnBackgroundEnabled(bool bEnabled)
{
    ULootLockerPresenceManager* Manager = GetInstance();
    if (Manager)
    {
        Manager->Configuration.bAutoDisconnectOnFocusChange = bEnabled;
    }
}

bool ULootLockerPresenceManager::IsEnabledInEditor()
{
    ULootLockerPresenceManager* Manager = GetInstance();
    return Manager ? Manager->Configuration.bEnabledInEditor : ULootLockerConfig::IsPresenceEnabledInEditor();
}

void ULootLockerPresenceManager::SetEnabledInEditor(bool bEnabled)
{
    ULootLockerPresenceManager* Manager = GetInstance();
    if (Manager)
    {
        Manager->Configuration.bEnabledInEditor = bEnabled;
    }
}

void ULootLockerPresenceManager::BeginDestroy()
{
    GracefullyShutdown();

    {
        FScopeLock Lock(&InstanceLock);
        if (Instance == this)
        {
            Instance->RemoveFromRoot();
            Instance = nullptr;
        }
    }

    Super::BeginDestroy();
}

// ====================================================================
// PUBLIC API - EVENTS
// ====================================================================
void ULootLockerPresenceManager::NotifyPlayerActivated(const FString& PlayerUlid)
{
    ULootLockerPresenceManager* Manager = GetInstance();
    if (Manager && Manager->Configuration.bIsEnabled && (!GIsEditor || Manager->Configuration.bEnabledInEditor) && Manager->Configuration.bAutoConnectEnabled)
    {
        Manager->ConnectPresence(PlayerUlid, FLootLockerPresenceCallbackDelegate());
    }
}

void ULootLockerPresenceManager::NotifyPlayerDeactivated(const FString& PlayerUlid)
{
    ULootLockerPresenceManager* Manager = GetInstance();
    if (Manager)
    {
        Manager->DisconnectPresence(PlayerUlid, FLootLockerPresenceCallbackDelegate());
    }
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
    Client->AddToRoot(); // Prevent GC while managed by Presence Manager

    if (CachedStatusUpdate.Contains(PlayerUlid)) 
    {
        FLootLockerCachedPresenceStatusUpdate* CachedUpdate = CachedStatusUpdate.Find(PlayerUlid);
        Client->UpdateStatus(CachedUpdate->Status, CachedUpdate->Metadata, FLootLockerPresenceCallbackDelegate());
        CachedStatusUpdate.Remove(PlayerUlid);

    }
    
    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Created presence client for player: %s"), *PlayerUlid));
    return Client;
}

void ULootLockerPresenceManager::HandleClientConnectionStateChange(const FString& PlayerUlid, ELootLockerPresenceConnectionState OldState, ELootLockerPresenceConnectionState NewState, const FString& ErrorMessage)
{
    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence connection state changed for player %s: %s -> %s"), 
           *PlayerUlid, 
           *UEnum::GetValueAsString(OldState),
           *UEnum::GetValueAsString(NewState)));

    if (NewState == ELootLockerPresenceConnectionState::Destroyed)
    {
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Auto-cleaning up presence client for %s due to state change: %s"), *PlayerUlid, *UEnum::GetValueAsString(NewState)));
        
        // Clean up the client from our tracking
        ULootLockerPresenceClient* ClientToCleanup = nullptr;
        {
            FScopeLock Lock(&ClientMapLock);
            if (ULootLockerPresenceClient** ClientPtr = PresenceClients.Find(PlayerUlid))
            {
                ClientToCleanup = *ClientPtr;
                PresenceClients.Remove(PlayerUlid);

            }
            
            // Also remove from tracking sets
            ConnectingClients.Remove(PlayerUlid);
            PausedClients.Remove(PlayerUlid);
        }
        
        // Mark for garbage collection (Unreal's equivalent to Destroy)
        if (ClientToCleanup)
        {
            ClientToCleanup->RemoveFromRoot();
            #if ENGINE_MAJOR_VERSION >= 5
                ClientToCleanup->MarkAsGarbage();
            #else
                ClientToCleanup->MarkPendingKill();
            #endif
        }
    }
    else if (NewState == ELootLockerPresenceConnectionState::Disconnected)
    {
        FScopeLock Lock(&ClientMapLock);
        
        // Remove from connecting state if applicable
        ConnectingClients.Remove(PlayerUlid);
    }
    else if (NewState == ELootLockerPresenceConnectionState::Failed)
    {
        FScopeLock Lock(&ClientMapLock);
        
        // Remove from connecting state
        ConnectingClients.Remove(PlayerUlid);
        PausedClients.Remove(PlayerUlid);
        
        ULootLockerPresenceClient* ClientToHandle = nullptr;
        if (ULootLockerPresenceClient** ClientPtr = PresenceClients.Find(PlayerUlid))
        {
            ClientToHandle = *ClientPtr;
        }

        if (ClientToHandle)
        {
            // If the error indicates authentication failure, remove and destroy the client
            // Otherwise, keep in disconnected state for potential reconnection
            if (!ErrorMessage.IsEmpty() && 
                (ErrorMessage.Contains(TEXT("authentication")) || 
                 ErrorMessage.Contains(TEXT("unauthorized")) || 
                 ErrorMessage.Contains(TEXT("invalid token"))))
            {
                FLootLockerLogger::LogWarning(FString::Printf(TEXT("Removing presence client for %s due to authentication failure: %s"), 
                       *PlayerUlid, *ErrorMessage));
                PresenceClients.Remove(PlayerUlid);
                ClientToHandle->RemoveFromRoot();
                #if ENGINE_MAJOR_VERSION >= 5
                    ClientToHandle->MarkAsGarbage();
                #else
                    ClientToHandle->MarkPendingKill();
                #endif
            }
            else
            {
                // Network or other failure - keep client for potential reconnection
                FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence client for %s failed, keeping for potential reconnection: %s"), 
                       *PlayerUlid, *ErrorMessage));
            }
        }
    }
    else if (NewState == ELootLockerPresenceConnectionState::Active)
    {
        FScopeLock Lock(&ClientMapLock);
        
        // Remove from connecting and paused states
        ConnectingClients.Remove(PlayerUlid);
        PausedClients.Remove(PlayerUlid);
    }
}