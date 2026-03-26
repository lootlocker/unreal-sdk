// Copyright (c) 2021 LootLocker

#include "LootLockerPresenceClient.h"
#include "LootLockerConfig.h"
#include "LootLockerLogger.h"
#include "Utils/LootLockerUtilities.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Containers/Ticker.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"

// ========================================================================
// CONSTRUCTOR & LIFECYCLE
// ========================================================================

ULootLockerPresenceClient::ULootLockerPresenceClient()
    : ConnectionState(ELootLockerPresenceConnectionState::Disconnected)
    , WebSocket(nullptr)
    , bHasPendingStatusUpdate(false)
    , bIsClientInitiatedDisconnect(false)
    , ReconnectAttempts(0)
    , RecentLatencies(nullptr)
    , RecentLatenciesSum(0.0f)
{
    // Initialize the circular queue for latency tracking
    RecentLatencies = MakeUnique<TCircularQueue<float>>(10);
}

void ULootLockerPresenceClient::Initialize(const FString InPlayerUlid, const FString InSessionToken, const FLootLockerPresenceConnectionDelegate& InConnectionDelegate)
{
    PlayerUlid = InPlayerUlid;
    SessionToken = InSessionToken;
    ConnectionDelegate = InConnectionDelegate;
    ConnectionState = ELootLockerPresenceConnectionState::Initializing;
    InitializeConnectionStats();
    StartTicker();
}

void ULootLockerPresenceClient::BeginDestroy()
{
    Disconnect(FLootLockerPresenceCallbackDelegate());
    Cleanup();
    
    // Set Connection State to Destroyed
    SetConnectionState(ELootLockerPresenceConnectionState::Destroyed);
    Super::BeginDestroy();
}

void ULootLockerPresenceClient::Cleanup()
{    
    // Close WebSocket if valid
    if (WebSocket.IsValid())
    {
        if (WebSocket->IsConnected())
        {
            WebSocket->Close();
        }
        WebSocket.Reset();
    }
    
    CancelAsyncActions();
    
    // Reset reconnect attempts
    ReconnectAttempts = 0;

    InitializeConnectionStats();
    
    // Clear Callbacks
    if (ConnectionRequestCallback.IsBound())
    {
        ConnectionRequestCallback.Unbind();
        ConnectionRequestCallback = FLootLockerPresenceCallbackDelegate();
    }
    if (ConnectionDelegate.IsBound())
    {
        ConnectionDelegate.Unbind();
        ConnectionDelegate = FLootLockerPresenceConnectionDelegate();
    }
}

// ========================================================================
// PUBLIC INTERFACE - CONNECTION MANAGEMENT
// ========================================================================

void ULootLockerPresenceClient::HandleConnectionResult(bool bSuccess, const FString& ErrorMessage)
{
    if (ConnectionRequestCallback.IsBound())
    {
        ConnectionRequestCallback.Execute(bSuccess, ErrorMessage);
        ConnectionRequestCallback.Unbind();
        ConnectionRequestCallback = FLootLockerPresenceCallbackDelegate();
    }
}

void ULootLockerPresenceClient::Connect(const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    
    if (ConnectionState != ELootLockerPresenceConnectionState::Disconnected 
        && ConnectionState != ELootLockerPresenceConnectionState::Initializing
        && ConnectionState != ELootLockerPresenceConnectionState::Reconnecting
        && ConnectionState != ELootLockerPresenceConnectionState::Failed)
    {
        FString Message = FString::Printf(TEXT("Presence client is not in a proper state to connect for player ulid %s, current state is %d"), *PlayerUlid, static_cast<uint8>(ConnectionState));
        FLootLockerLogger::LogWarning(Message);
        ConnectionRequestCallback = OnComplete;
        HandleConnectionResult(false, *Message);
        return;
    }

    // Check if we have valid session data
    if (SessionToken.IsEmpty())
    {
        FString ErrorMessage = FString::Printf(TEXT("Cannot connect presence - missing session data for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogWarning(ErrorMessage);
        ConnectionRequestCallback = OnComplete;
        HandleConnectionResult(false, *ErrorMessage);
        SetConnectionState(ELootLockerPresenceConnectionState::Failed, ErrorMessage);
        return;
    }
    
    if (WebSocket == nullptr && !FModuleManager::Get().IsModuleLoaded("WebSockets"))
    {
        if(FModuleManager::Get().LoadModule("WebSockets") == nullptr) 
        {
            FString ErrorMessage = TEXT("Failed to load WebSockets module. Presence connection cannot proceed.");
            FLootLockerLogger::LogError(ErrorMessage);
            ConnectionRequestCallback = OnComplete;
            HandleConnectionResult(false, *ErrorMessage);
            SetConnectionState(ELootLockerPresenceConnectionState::Failed, ErrorMessage);
            return;
        }
    }

    Cleanup();

    ConnectionRequestCallback = OnComplete;

    StartTicker();

    SetConnectionState(ELootLockerPresenceConnectionState::Connecting);

    // Create WebSocket connection
    const FString WebSocketUrl = BuildWebSocketUrl();
    FLootLockerLogger::LogInfo(FString::Printf(TEXT("Connecting presence WebSocket for player %s"), *PlayerUlid));

    WebSocket = FWebSocketsModule::Get().CreateWebSocket(WebSocketUrl);

    if (!WebSocket.IsValid())
    {
        FString ErrorMessage = FString::Printf(TEXT("Failed to create presence WebSocket for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogError(ErrorMessage);
        HandleConnectionResult(false, *ErrorMessage);
        SetConnectionState(ELootLockerPresenceConnectionState::Failed, ErrorMessage);
        return;
    }

    // Bind WebSocket events
    WebSocket->OnConnected().AddUObject(this, &ULootLockerPresenceClient::OnConnected);
    WebSocket->OnConnectionError().AddUObject(this, &ULootLockerPresenceClient::OnConnectionError);
    WebSocket->OnClosed().AddUObject(this, &ULootLockerPresenceClient::OnClosed);
    WebSocket->OnMessage().AddUObject(this, &ULootLockerPresenceClient::OnMessage);
    WebSocket->OnRawMessage().AddUObject(this, &ULootLockerPresenceClient::OnRawMessage);

    // Attempt connection
    WebSocket->Connect();
}

void ULootLockerPresenceClient::Disconnect(const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    bIsClientInitiatedDisconnect = true;
    
    CancelAsyncActions();

    if (ConnectionState == ELootLockerPresenceConnectionState::Disconnected ||
        ConnectionState == ELootLockerPresenceConnectionState::Failed ||
        ConnectionState == ELootLockerPresenceConnectionState::Destroyed)
    {
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence client already disconnected for player: %s"), *PlayerUlid));
        OnComplete.ExecuteIfBound(true, TEXT("Already disconnected"));
        return;
    }

    if (WebSocket.IsValid())
    {
        if (WebSocket->IsConnected())
        {
            FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Disconnecting presence WebSocket for player: %s"), *PlayerUlid));
            WebSocket->Close();
        }
        WebSocket.Reset();
    }

    SetConnectionState(ELootLockerPresenceConnectionState::Disconnected);

    OnComplete.ExecuteIfBound(true, TEXT("Disconnected successfully"));

    ReconnectAttempts = 0;
    bIsClientInitiatedDisconnect = false;
}

void ULootLockerPresenceClient::UpdateSessionToken(const FString& NewToken, bool ShouldAutoReconnect, const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    if (NewToken.IsEmpty())
    {
        OnComplete.ExecuteIfBound(false, TEXT("New session token is empty"));
        FLootLockerLogger::LogWarning(FString::Printf(TEXT("Cannot update session token for player %s - new token is empty"), *PlayerUlid));
        return;
    }

    if (SessionToken.Equals(NewToken, ESearchCase::IgnoreCase)) 
    {
        OnComplete.ExecuteIfBound(true, TEXT("Session token is the same as the current token; no update needed"));
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Tried updating presence client with the same session token as previous token. Ignoring update.")));
        return;
    }
    
    // Store the new token
    SessionToken = NewToken;
    
    // If we're currently connected, disconnect and reconnect with the new token
    if (IsConnected())
    {
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Reconnecting player %s with new session token"), *PlayerUlid));
        
        // Disconnect gracefully, then reconnect
        Disconnect(FLootLockerPresenceCallbackDelegate::CreateLambda([this, OnComplete, ShouldAutoReconnect](bool bDisconnectSuccess, const FString& DisconnectError)
        {
            if (bDisconnectSuccess && ShouldAutoReconnect)
            {
                // Reconnect with new token after disconnect completes
                Connect(FLootLockerPresenceCallbackDelegate::CreateLambda([this, OnComplete](bool bReconnectSuccess, const FString& ReconnectError)
                {
                    if (bReconnectSuccess)
                    {
                        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Successfully reconnected player %s with new session token"), *PlayerUlid));
                        
                        // Re-send last status if we had one
                        AutoResendLastStatus();
                    }
                    else
                    {
                        FLootLockerLogger::LogWarning(FString::Printf(TEXT("Failed to reconnect player %s with new session token: %s"), *PlayerUlid, *ReconnectError));
                    }
                    OnComplete.ExecuteIfBound(bReconnectSuccess, ReconnectError);
                }));
            }
            else
            {
                OnComplete.ExecuteIfBound(false, DisconnectError);
                FLootLockerLogger::LogWarning(FString::Printf(TEXT("Failed to disconnect player %s for token update: %s"), *PlayerUlid, *DisconnectError));
            }
        }));
    }
    else if(ShouldAutoReconnect)
    {
        Connect(FLootLockerPresenceCallbackDelegate::CreateLambda([this, OnComplete](bool bReconnectSuccess, const FString& ReconnectError)
        {
            if (bReconnectSuccess)
            {
                FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Successfully reconnected player %s with new session token"), *PlayerUlid));
                
                // Re-send last status if we had one
                AutoResendLastStatus();
            }
            else
            {
                FLootLockerLogger::LogWarning(FString::Printf(TEXT("Failed to reconnect player %s with new session token: %s"), *PlayerUlid, *ReconnectError));
            }
            OnComplete.ExecuteIfBound(bReconnectSuccess, ReconnectError);
        }));

    }
    else
    {
        FString Message = FString::Printf(TEXT("Session token updated for player %s (not currently connected and auto reconnect is disabled)"), *PlayerUlid);
        FLootLockerLogger::LogVeryVerbose(Message);
        OnComplete.ExecuteIfBound(true, Message);
    }
}

// ========================================================================
// PUBLIC INTERFACE - STATUS MANAGEMENT
// ========================================================================

void ULootLockerPresenceClient::UpdateStatus(const FString& Status, TMap<FString, FString> Metadata, const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    if (!IsConnected())
    {
        // Queue the status update for when we're connected
        PendingStatus = Status;
        PendingMetadata = Metadata;
        PendingStatusCallback = OnComplete;
        bHasPendingStatusUpdate = true;
        
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Queuing status update for player %s: %s (not connected)"), *PlayerUlid, *Status));
        return;
    }
    
    SendStatusUpdateMessage(Status, Metadata, OnComplete);
}

// ========================================================================
// PUBLIC INTERFACE - STATISTICS
// ========================================================================

FLootLockerPresenceConnectionStats ULootLockerPresenceClient::GetConnectionStats() const
{
    // Update connection duration in real-time
    FLootLockerPresenceConnectionStats CurrentStats = ConnectionStats;
    if (ConnectionStats.ConnectionStartTime != FDateTime::MinValue())
    {
        if (ConnectionStats.ConnectionEndTime != FDateTime::MinValue())
        {
            // Connection has ended, use start->end duration
            CurrentStats.ConnectionDuration = ConnectionStats.ConnectionEndTime - ConnectionStats.ConnectionStartTime;
        }
        else
        {
            // Connection is still active, use start->now duration
            CurrentStats.ConnectionDuration = FDateTime::UtcNow() - ConnectionStats.ConnectionStartTime;
        }
    }
    return CurrentStats;
}

// ========================================================================
// INTERNAL - CONNECTION STATE & MESSAGING
// ========================================================================

bool ULootLockerPresenceClient::SendMessage(const FString& Message)
{
    if (!WebSocket.IsValid() || !WebSocket->IsConnected())
    {
        FLootLockerLogger::LogWarning(FString::Printf(TEXT("Cannot send presence message - not connected for player: %s"), *PlayerUlid));
        return false;
    }

    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Sending presence message for player %s: %s"), *PlayerUlid, *Message));
    WebSocket->Send(Message);
    return true;
}

void ULootLockerPresenceClient::ProcessPendingStatusUpdate()
{
    if (bHasPendingStatusUpdate && IsConnected())
    {
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Processing pending status update for player %s: %s"), *PlayerUlid, *PendingStatus));
        SendStatusUpdateMessage(PendingStatus, PendingMetadata, PendingStatusCallback);
        
        // Clear pending status
        bHasPendingStatusUpdate = false;
        PendingStatus.Empty();
        PendingMetadata.Empty();
        PendingStatusCallback.Unbind();
    }
}

void ULootLockerPresenceClient::AutoResendLastStatus()
{
    // Send last status if we have one and are connected
    if (!ConnectionStats.LastSentStatus.IsEmpty() && IsConnected())
    {
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Auto-resending last status for player %s: %s"), *PlayerUlid, *ConnectionStats.LastSentStatus));
        SendStatusUpdateMessage(ConnectionStats.LastSentStatus, LastSentMetadata, FLootLockerPresenceCallbackDelegate());
    }
}

void ULootLockerPresenceClient::SendStatusUpdateMessage(const FString& Status, const TMap<FString, FString>& Metadata, const FLootLockerPresenceCallbackDelegate& OnComplete)
{
    if (!WebSocket.IsValid() || !WebSocket->IsConnected())
    {
        FString ErrorMessage = FString::Printf(TEXT("Cannot send status update - WebSocket not connected for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogWarning(ErrorMessage);
        OnComplete.ExecuteIfBound(false, ErrorMessage);
        return;
    }
    
    FLootLockerPresenceStatusRequest StatusRequest {
        Status,
        Metadata
    };
    
    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Sending status update for player %s: %s"), *PlayerUlid, *Status));
    
    if (SendMessage(LootLockerUtilities::UStructToJsonString(StatusRequest)))
    {
        // Store as last sent status and metadata
        ConnectionStats.LastSentStatus = Status;
        LastSentMetadata = Metadata;
        
        OnComplete.ExecuteIfBound(true, TEXT(""));
    }
    else
    {
        FString ErrorMessage = FString::Printf(TEXT("Failed to send status update for player: %s"), *PlayerUlid);
        OnComplete.ExecuteIfBound(false, ErrorMessage);
    }
}

// ========================================================================
// WEBSOCKET EVENT HANDLERS
// ========================================================================

void ULootLockerPresenceClient::OnConnected()
{
    ReconnectAttempts = 0;
    
    // Set authenticating state and send authentication message
    SetConnectionState(ELootLockerPresenceConnectionState::Authenticating);
    SendAuthenticationMessage();
}

void ULootLockerPresenceClient::OnConnectionError(const FString& Error)
{
    switch (ConnectionState)
    {
        case ELootLockerPresenceConnectionState::Reconnecting:
        case ELootLockerPresenceConnectionState::Active:
        {
            // Only attempt to reconnect if this wasn't a client-initiated disconnect
            if (!bIsClientInitiatedDisconnect)
            {
                FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Unexpected presence websocket error for player %s - Message: %s"), *PlayerUlid, *Error));
                SetConnectionState(ELootLockerPresenceConnectionState::Reconnecting);
                ScheduleReconnect();
            }
            else
            {
                FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Client-initiated disconnect for player %s - Message: %s"), *PlayerUlid, *Error));
            }
            break;
        }
        case ELootLockerPresenceConnectionState::Disconnected:
        case ELootLockerPresenceConnectionState::Failed:
        case ELootLockerPresenceConnectionState::Destroyed:
        {
            // Already disconnected or in a terminal state, log but do nothing
            FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Unexpected websocket error for player %s while shut down - Message: %s"), *PlayerUlid, *Error));
            break;
        }
        case ELootLockerPresenceConnectionState::Initializing:
        case ELootLockerPresenceConnectionState::Connecting:
        case ELootLockerPresenceConnectionState::Connected:
        case ELootLockerPresenceConnectionState::Authenticating:
        default:
        {
            // Connection closed while being established, notify caller of failure
            FString ErrorMessage = FString::Printf(TEXT("Presence WebSocket connection error during connection for player %s: %s"), *PlayerUlid, *Error);
            FLootLockerLogger::LogWarning(ErrorMessage);
            HandleConnectionResult(false, *ErrorMessage);
            SetConnectionState(ELootLockerPresenceConnectionState::Failed, ErrorMessage);
            break;
        }
    }
}

void ULootLockerPresenceClient::OnClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
    switch (ConnectionState)
    {
        case ELootLockerPresenceConnectionState::Reconnecting:
        case ELootLockerPresenceConnectionState::Active:
        {
            // Only attempt to reconnect if this wasn't a client-initiated disconnect
            if (!bIsClientInitiatedDisconnect)
            {
                FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence WebSocket closed unexpectedly for player %s - Code: %d, Reason: %s, Clean: %s"), 
                    *PlayerUlid, StatusCode, *Reason, bWasClean ? TEXT("true") : TEXT("false")));
                SetConnectionState(ELootLockerPresenceConnectionState::Reconnecting);
                ScheduleReconnect();
            }
            else
            {
                FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Client-initiated disconnect for player %s - Code: %d, Reason: %s, Clean: %s"), 
                    *PlayerUlid, StatusCode, *Reason, bWasClean ? TEXT("true") : TEXT("false")));
            }
            break;
        }
        case ELootLockerPresenceConnectionState::Disconnected:
        case ELootLockerPresenceConnectionState::Failed:
        case ELootLockerPresenceConnectionState::Destroyed:
        {
            // Already disconnected or in a terminal state, log but do nothing
            FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence WebSocket closed for player %s - Code: %d, Reason: %s, Clean: %s"), 
                *PlayerUlid, StatusCode, *Reason, bWasClean ? TEXT("true") : TEXT("false")));
            break;
        }
        case ELootLockerPresenceConnectionState::Initializing:
        case ELootLockerPresenceConnectionState::Connecting:
        case ELootLockerPresenceConnectionState::Connected:
        case ELootLockerPresenceConnectionState::Authenticating:
        default:
        {
            // Connection closed while being established, notify caller of failure
            FString ErrorMessage = FString::Printf(TEXT("Presence WebSocket closed during connection for player %s - Code: %d, Reason: %s, Clean: %s"), 
                *PlayerUlid, StatusCode, *Reason, bWasClean ? TEXT("true") : TEXT("false"));
            FLootLockerLogger::LogWarning(ErrorMessage);
            HandleConnectionResult(false, *ErrorMessage);
            SetConnectionState(ELootLockerPresenceConnectionState::Failed, ErrorMessage);
            break;
        }
    }
}

void ULootLockerPresenceClient::OnMessage(const FString& Message)
{    
    if (Message.IsEmpty())
    {
        FLootLockerLogger::LogWarning(FString::Printf(TEXT("Received empty presence message for player: %s"), *PlayerUlid));
        return;
    }

    if (ConnectionState == ELootLockerPresenceConnectionState::Disconnected ||
        ConnectionState == ELootLockerPresenceConnectionState::Failed ||
        ConnectionState == ELootLockerPresenceConnectionState::Destroyed)
    {
        FLootLockerLogger::LogWarning(FString::Printf(TEXT("Received presence message while disconnected for player: %s"), *PlayerUlid));
        return;
    }

    if (!WebSocket.IsValid() || !WebSocket->IsConnected())
    {
        FLootLockerLogger::LogWarning(FString::Printf(TEXT("Received presence message but WebSocket not connected for player: %s"), *PlayerUlid));
        return;
    }

    if (Message.Contains(TEXT("authenticated")))
    {
        HandleAuthenticationResponse(Message);
        return;
    } 
    else if (Message.Contains(TEXT("pong")))
    {
        HandlePongMessage(Message);
        return;
    }
    else if (Message.Contains(TEXT("error")))
    {
        HandleErrorMessage(Message);
        return;
    }
    else if (Message.Contains(TEXT("presence is not enabled")))
    {
        FString ErrorMessage = FString::Printf(TEXT("Presence is not enabled for this game. Please enable it in the LootLocker console to use this feature."), *PlayerUlid);
        FLootLockerLogger::LogWarning(ErrorMessage);
        Disconnect(FLootLockerPresenceCallbackDelegate::CreateLambda([this, ErrorMessage](bool bSuccess, const FString& Message)
        {
            SetConnectionState(ELootLockerPresenceConnectionState::Failed, ErrorMessage);
            HandleConnectionResult(false, ErrorMessage);
        }));
        return;
    }
    else
    {
        FLootLockerLogger::LogWarning(FString::Printf(TEXT("Received unrecognized presence message for player %s: %s"), *PlayerUlid, *Message));
    }
}

void ULootLockerPresenceClient::OnRawMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining)
{
    // Currently not implemented for presence - only text messages are used
}

// ========================================================================
// INTERNAL - CONNECTION STATE MANAGEMENT
// ========================================================================

void ULootLockerPresenceClient::SetConnectionState(ELootLockerPresenceConnectionState NewState, const FString& ErrorMessage)
{
    if (ConnectionState != NewState)
    {
        const ELootLockerPresenceConnectionState OldState = ConnectionState;
        ConnectionState = NewState;
        
        // Update connection stats with new state
        ConnectionStats.ConnectionState = NewState;
        
        // Set end time when transitioning to a disconnected state
        if (NewState == ELootLockerPresenceConnectionState::Disconnected ||
            NewState == ELootLockerPresenceConnectionState::Failed ||
            NewState == ELootLockerPresenceConnectionState::Destroyed)
        {
            if (ConnectionStats.ConnectionStartTime != FDateTime::MinValue() &&
                ConnectionStats.ConnectionEndTime == FDateTime::MinValue())
            {
                ConnectionStats.ConnectionEndTime = FDateTime::UtcNow();
            }
        }
        
        FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence connection state changed for player %s: %s -> %s"), 
               *PlayerUlid,
               *UEnum::GetValueAsString(OldState),
               *UEnum::GetValueAsString(NewState)));

        if (ConnectionDelegate.IsBound())
        {
            ConnectionDelegate.ExecuteIfBound(PlayerUlid, OldState, NewState, ErrorMessage);
        }
    }
}

FString ULootLockerPresenceClient::BuildWebSocketUrl() const
{
    // Use the dedicated WebSocket endpoint with proper domain key substitution
    FString WebSocketUrl = ULootLockerGameEndpoints::PresenceWebSocketEndpoint.endpoint;
    
    // Add domain key substitution
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    FString DomainKey = (Config && !Config->DomainKey.IsEmpty()) ? Config->DomainKey + "." : "";
    WebSocketUrl = WebSocketUrl.Replace(TEXT("{domainKey}"), *DomainKey);
    
    return WebSocketUrl;
}

// ========================================================================
// RECONNECTION SYSTEM
// ========================================================================

void ULootLockerPresenceClient::AttemptReconnect()
{
    if (ReconnectAttempts >= MaxReconnectAttempts)
    {
        FString ErrorMessage = FString::Printf(TEXT("Max presence reconnect attempts reached for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogWarning(ErrorMessage);
        SetConnectionState(ELootLockerPresenceConnectionState::Failed, ErrorMessage);
        return;
    }

    ReconnectAttempts++;
    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Attempting reconnect for player %s (attempt %d/%d)"), 
           *PlayerUlid, ReconnectAttempts, MaxReconnectAttempts));
    Connect(FLootLockerPresenceCallbackDelegate::CreateLambda([this](bool bSuccess, const FString& ErrorMessage)
    {
        if (!bSuccess)
        {
            FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Presence reconnect attempt failed: %s"), *ErrorMessage));
            ScheduleReconnect();
        }
    }));
}

void ULootLockerPresenceClient::ScheduleReconnect()
{
    // Don't schedule if already scheduled or if we've hit max attempts
    if (ReconnectAttempts >= MaxReconnectAttempts)
    {
        return;
    }

    if (!ShouldTick) 
    {
        StartTicker();
    }
    
    ReconnectInSeconds = ReconnectDelaySeconds * FMath::Pow(ReconnectBackoffFactor, ReconnectAttempts - 1); // Exponential backoff

    FLootLockerLogger::LogVeryVerbose(FString::Printf(TEXT("Scheduling reconnect for player %s in %f seconds"), *PlayerUlid, ReconnectInSeconds));

}

// ========================================================================
// AUTHENTICATION & MESSAGE PROCESSING
// ========================================================================

void ULootLockerPresenceClient::SendAuthenticationMessage()
{
    if (SessionToken.IsEmpty())
    {
        FString ErrorMessage = FString::Printf(TEXT("Cannot send authentication message - missing session token for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogError(ErrorMessage);
        SetConnectionState(ELootLockerPresenceConnectionState::Failed, ErrorMessage);
        HandleConnectionResult(false, ErrorMessage);
        return;
    }

    if (!WebSocket.IsValid() || !WebSocket->IsConnected())
    {
        FString ErrorMessage = FString::Printf(TEXT("Cannot send authentication message - WebSocket not connected for player: %s"), *PlayerUlid);
        FLootLockerLogger::LogError(ErrorMessage);
        SetConnectionState(ELootLockerPresenceConnectionState::Failed, ErrorMessage);
        HandleConnectionResult(false, ErrorMessage);
        return;
    }

    FLootLockerPresenceAuthenticationRequest AuthRequest {
        SessionToken
    };
    FString AuthRequestJson = LootLockerUtilities::UStructToJsonString(FLootLockerPresenceAuthenticationRequest { SessionToken });
    WebSocket->Send(AuthRequestJson);
}

void ULootLockerPresenceClient::HandleAuthenticationResponse(const FString& Message)
{
        FLootLockerLogger::LogInfo(FString::Printf(TEXT("Presence authentication successful for player: %s. Presence is now connected."), *PlayerUlid));
        SetConnectionState(ELootLockerPresenceConnectionState::Active);
        
        // Initialize connection statistics
        InitializeConnectionStats();
        
        ShouldPing = true;
        
        if(bHasPendingStatusUpdate) 
        {
            ProcessPendingStatusUpdate();
        }
        else 
        {
            AutoResendLastStatus();
        }

        HandleConnectionResult(true, TEXT(""));
}

void ULootLockerPresenceClient::HandleErrorMessage(const FString& Message)
{
    FLootLockerLogger::LogWarning(FString::Printf(TEXT("Received presence error message for player %s: %s"), *PlayerUlid, *Message));
}

// ========================================================================
// PING & LATENCY MANAGEMENT
// ========================================================================

void ULootLockerPresenceClient::SendPing()
{
    if (!WebSocket.IsValid() || !WebSocket->IsConnected())
    {
        FLootLockerLogger::LogWarning(FString::Printf(TEXT("Cannot send heartbeat - WebSocket not connected for player: %s"), *PlayerUlid));
        ShouldPing = false;
        return;
    }

    // Store the current local timestamp for round-trip time calculation
    double CurrentTime = FPlatformTime::Seconds();
    PendingPingTimestamps.Enqueue(CurrentTime);
    TimeSinceLastPing = 0.0f;
    // Increment ping counter
    ConnectionStats.TotalPingsSent++;

    FString PingRequestJson = LootLockerUtilities::UStructToJsonString(FLootLockerPresencePingRequest {});
    WebSocket->Send(PingRequestJson);
}

void ULootLockerPresenceClient::HandlePongMessage(const FString& Message)
{
    // Calculate round-trip time using local timestamps
    if (!PendingPingTimestamps.IsEmpty())
    {
        double CurrentTime = FPlatformTime::Seconds();
        double SentTime;
        PendingPingTimestamps.Dequeue(SentTime);
        
        double RoundTripTimeSeconds = CurrentTime - SentTime;
        
        if (RoundTripTimeSeconds >= 0 && RoundTripTimeSeconds < 30.0) // Sanity check for reasonable RTT (< 30 seconds)
        {
            // Convert to milliseconds and divide by 2 to get one-way latency
            float OneWayLatencyMs = static_cast<float>(RoundTripTimeSeconds * 1000.0 / 2.0);
            
            // Update latency statistics
            UpdateLatencyStats(OneWayLatencyMs);
            ConnectionStats.TotalPongsReceived++;
        }
    }
    else
    {
        // Received a pong without a corresponding ping - just increment counter
        ConnectionStats.TotalPongsReceived++;
    }
}

void ULootLockerPresenceClient::UpdateLatencyStats(float LatencyMs)
{
    // Update current latency
    ConnectionStats.CurrentLatencyMs = LatencyMs;
    
    // Update min/max
    if (LatencyMs < ConnectionStats.MinLatencyMs)
    {
        ConnectionStats.MinLatencyMs = LatencyMs;
    }
    if (LatencyMs > ConnectionStats.MaxLatencyMs)
    {
        ConnectionStats.MaxLatencyMs = LatencyMs;
    }
    
    // Check if buffer is full and we need to subtract the oldest value
    if (RecentLatencies->Count() >= 10)
    {
        const float* OldestSamplePtr = RecentLatencies->Peek();
        RecentLatenciesSum -= OldestSamplePtr ? *OldestSamplePtr : 0.0f;
    }
    
    // Add new sample (will automatically overwrite oldest if full)
    RecentLatencies->Enqueue(LatencyMs);
    RecentLatenciesSum += LatencyMs;
    
    // Calculate average from running sum
    ConnectionStats.AverageLatencyMs = RecentLatencies->Count() > 0 ? RecentLatenciesSum / RecentLatencies->Count() : 0.0f;
}

void ULootLockerPresenceClient::InitializeConnectionStats()
{    
    ConnectionStats.PlayerUlid = PlayerUlid;
    ConnectionStats.ConnectionState = ConnectionState;
    //ConnectionStats.LastSentStatus = ""; // We do not want to reset status
    ConnectionStats.ConnectionStartTime = FDateTime::UtcNow();
    ConnectionStats.ConnectionEndTime = FDateTime::MinValue(); // Clear end time on reconnect
    ConnectionStats.TotalPingsSent = 0;
    ConnectionStats.TotalPongsReceived = 0;
    ConnectionStats.CurrentLatencyMs = 0.0f;
    ConnectionStats.AverageLatencyMs = 0.0f;
    ConnectionStats.MinLatencyMs = FLT_MAX;
    ConnectionStats.MaxLatencyMs = 0.0f;

    if (RecentLatencies != nullptr) {
        RecentLatencies->Empty();    
    }
    RecentLatenciesSum = 0.0f;
}

// ========================================================================
// TICKING & ROUTINES
// ========================================================================

void ULootLockerPresenceClient::StartTicker()
{
    if (!ShouldTick)
    {
        ShouldTick = true;
        TWeakObjectPtr<ULootLockerPresenceClient> WeakThis = MakeWeakObjectPtr(this);
#if ENGINE_MAJOR_VERSION >= 5
        FTSTicker::GetCoreTicker()
#else
        FTicker::GetCoreTicker()
#endif
            .AddTicker(FTickerDelegate::CreateLambda([WeakThis](float DeltaTime) {
            if (WeakThis.IsValid() && WeakThis->ShouldTick)
            {
                return WeakThis->Tick(DeltaTime);
            }
            return false;
        }));
    }
}

bool ULootLockerPresenceClient::Tick(float DeltaTime)
{
    if (ReconnectInSeconds > 0.0f)
    {
        ReconnectInSeconds -= DeltaTime;
        if (ReconnectInSeconds <= 0.0f)
        {
            ReconnectInSeconds = 0.0f;
            AttemptReconnect();
        }
    }
    
    if(ShouldPing && IsConnected())
    {
        TimeSinceLastPing += DeltaTime;
        if(TimeSinceLastPing >= PingIntervalSeconds)
        {
            SendPing();
            TimeSinceLastPing = 0.0f;
        }
    }
    
    return true; // Continue ticking
}

// ========================================================================
// UTILITY METHODS
// ========================================================================

void ULootLockerPresenceClient::CancelAsyncActions()
{
    ShouldPing = false;
    ReconnectInSeconds = 0.0f;
    ShouldTick = false;
}