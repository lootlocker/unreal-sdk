// Copyright (c) 2021 LootLocker

#include "LootLockerLifeCycleManager.h"
#include "LootLockerLogger.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Misc/CoreDelegates.h"
#if WITH_EDITOR
#include "Editor.h"
#endif

// ========================================================================
// STATIC MEMBERS
// ========================================================================

ULootLockerLifeCycleManager* ULootLockerLifeCycleManager::Instance = nullptr;
FCriticalSection ULootLockerLifeCycleManager::InstanceLock;

// ========================================================================
// CONSTRUCTOR & LIFECYCLE
// ========================================================================

ULootLockerLifeCycleManager::ULootLockerLifeCycleManager()
    : bIsInitialized(false)
    , bIsShuttingDown(false)
{
    // If this is the first instance created, mark it as the singleton
    {
        FScopeLock Lock(&InstanceLock);
        if (!Instance)
        {
            Instance = this;
        }
    }
}

void ULootLockerLifeCycleManager::BeginDestroy()
{
    if (bIsInitialized && !bIsShuttingDown)
    {
        UnbindLifeCycleDelegates();

        FLootLockerLogger::LogVeryVerbose(TEXT("LifeCycle Manager is being destroyed, treating as shutdown"));
        
        // Broadcast to listeners
        OnApplicationShutdown.Broadcast();

        Shutdown();
    }

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
// SINGLETON MANAGEMENT
// ========================================================================

ULootLockerLifeCycleManager* ULootLockerLifeCycleManager::GetInstance()
{
    FScopeLock Lock(&InstanceLock);
    if (!Instance)
    {
        // Only create if no instance exists (shouldn't happen if constructor sets it)
        Instance = NewObject<ULootLockerLifeCycleManager>();
    }
    return Instance;
}

void ULootLockerLifeCycleManager::Initialize()
{
    ULootLockerLifeCycleManager* Manager = GetInstance();
    if (Manager && !Manager->bIsInitialized)
    {
        // Now it's safe to add to root - GC system is fully initialized
        Manager->AddToRoot();
        Manager->BindLifeCycleDelegates();
        Manager->bIsInitialized = true;
        FLootLockerLogger::LogVeryVerbose(TEXT("LootLocker LifeCycle Manager initialized successfully"));
    }
}

void ULootLockerLifeCycleManager::Shutdown()
{
    FScopeLock Lock(&InstanceLock);
    if (Instance)
    {
        Instance->bIsShuttingDown = true;
        Instance->UnbindLifeCycleDelegates();
        Instance->RemoveFromRoot();
        Instance = nullptr;
        FLootLockerLogger::LogVeryVerbose(TEXT("LootLocker LifeCycle Manager shutdown completed"));
    }
}

// ========================================================================
// INTERNAL DELEGATE BINDING
// ========================================================================

void ULootLockerLifeCycleManager::BindLifeCycleDelegates()
{
    if (!IsValid(this) || bIsShuttingDown)
    {
        return;
    }

    // Application lifecycle events
    ApplicationWillEnterBackgroundHandle = FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(
        this, &ULootLockerLifeCycleManager::HandleApplicationWillEnterBackground);

    ApplicationHasEnteredForegroundHandle = FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddUObject(
        this, &ULootLockerLifeCycleManager::HandleApplicationHasEnteredForeground);

    ApplicationWillTerminateHandle =
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
        FCoreDelegates::GetApplicationWillTerminateDelegate()
#else
        FCoreDelegates::ApplicationWillTerminateDelegate
#endif
        .AddUObject(this, &ULootLockerLifeCycleManager::HandleApplicationWillTerminate);

    // Engine lifecycle events
    EnginePreExitHandle = FCoreDelegates::OnEnginePreExit.AddUObject(
        this, &ULootLockerLifeCycleManager::HandleEnginePreExit);
    
    // Use world delegates for game instance events as they're more reliable for our use case
    GameInstanceInitHandle = FWorldDelegates::OnStartGameInstance.AddUObject(
        this, &ULootLockerLifeCycleManager::HandleGameInstanceInit);

#if WITH_EDITOR
    StartPIEHandle = FEditorDelegates::PostPIEStarted.AddUObject(
        this, &ULootLockerLifeCycleManager::HandleStartingPIE);

    EndPIEHandle = FEditorDelegates::PrePIEEnded.AddUObject(
        this, &ULootLockerLifeCycleManager::HandleEndingPIE);
        
    PIEPausedHandle = FEditorDelegates::PausePIE.AddUObject(
        this, &ULootLockerLifeCycleManager::HandlePIEPaused);

    PIEResumedHandle = FEditorDelegates::ResumePIE.AddUObject(
        this, &ULootLockerLifeCycleManager::HandlePIEResumed);
#endif

    FLootLockerLogger::LogVeryVerbose(TEXT("LifeCycle delegates bound successfully"));
}

void ULootLockerLifeCycleManager::UnbindLifeCycleDelegates()
{
    if (bIsShuttingDown)
    {
        return;
    }

    // Remove application lifecycle delegates
    if (ApplicationWillEnterBackgroundHandle.IsValid())
    {
        FCoreDelegates::ApplicationWillEnterBackgroundDelegate.Remove(ApplicationWillEnterBackgroundHandle);
        ApplicationWillEnterBackgroundHandle.Reset();
    }

    if (ApplicationHasEnteredForegroundHandle.IsValid())
    {
        FCoreDelegates::ApplicationHasEnteredForegroundDelegate.Remove(ApplicationHasEnteredForegroundHandle);
        ApplicationHasEnteredForegroundHandle.Reset();
    }

    if (ApplicationWillTerminateHandle.IsValid())
    {

#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
        FCoreDelegates::GetApplicationWillTerminateDelegate().Remove(ApplicationWillTerminateHandle);
#else
        FCoreDelegates::ApplicationWillTerminateDelegate.Remove(ApplicationWillTerminateHandle);
#endif
        ApplicationWillTerminateHandle.Reset();
    }

    // Remove engine lifecycle delegates
    if (EnginePreExitHandle.IsValid())
    {
        FCoreDelegates::OnEnginePreExit.Remove(EnginePreExitHandle);
        EnginePreExitHandle.Reset();
    }

    if (GameInstanceInitHandle.IsValid())
    {
        FWorldDelegates::OnStartGameInstance.Remove(GameInstanceInitHandle);
        GameInstanceInitHandle.Reset();
    }

#if WITH_EDITOR
    if (StartPIEHandle.IsValid())
    {
        FEditorDelegates::PostPIEStarted.Remove(StartPIEHandle);
        StartPIEHandle.Reset();
    }

    if (EndPIEHandle.IsValid())
    {
        FEditorDelegates::PrePIEEnded.Remove(EndPIEHandle);
        EndPIEHandle.Reset();
    }
    
    if (PIEPausedHandle.IsValid())
    {
        FEditorDelegates::PausePIE.Remove(PIEPausedHandle);
        PIEPausedHandle.Reset();
    }

    if (PIEResumedHandle.IsValid())
    {
        FEditorDelegates::ResumePIE.Remove(PIEResumedHandle);
        PIEResumedHandle.Reset();
    }
#endif

    FLootLockerLogger::LogVeryVerbose(TEXT("LifeCycle delegates unbound successfully"));
}

// ========================================================================
// APPLICATION LIFECYCLE EVENT HANDLERS
// ========================================================================

void ULootLockerLifeCycleManager::HandleApplicationWillEnterBackground()
{
    if (bIsShuttingDown) return;
    
    FLootLockerLogger::LogVeryVerbose(TEXT("Application will enter background"));

    // Broadcast to listeners
    OnApplicationBackground.Broadcast();
}

void ULootLockerLifeCycleManager::HandleApplicationHasEnteredForeground()
{
    if (bIsShuttingDown) return;

    FLootLockerLogger::LogVeryVerbose(TEXT("Application has entered foreground"));
    
    // Broadcast to listeners
    OnApplicationForeground.Broadcast();
}

void ULootLockerLifeCycleManager::HandleApplicationWillTerminate()
{
    if (bIsShuttingDown) return;

    FLootLockerLogger::LogVeryVerbose(TEXT("Application will terminate"));
    
    // Broadcast to listeners
    OnApplicationShutdown.Broadcast();

    Shutdown();
}

void ULootLockerLifeCycleManager::HandleEnginePreExit()
{
    if (bIsShuttingDown) return;

    FLootLockerLogger::LogVeryVerbose(TEXT("Engine pre-exit"));
    
    // Broadcast to listeners
    OnApplicationShutdown.Broadcast();
    
    // Final cleanup
    Shutdown();
}

// ========================================================================
// GAME INSTANCE LIFECYCLE HANDLERS
// ========================================================================

void ULootLockerLifeCycleManager::HandleGameInstanceInit(UGameInstance* ignored)
{
    if (bIsShuttingDown) return;

    FLootLockerLogger::LogInfo(TEXT("Game instance initialized - Game session starting"));
    
    // Broadcast to listeners
    OnApplicationStart.Broadcast();
}

#if WITH_EDITOR
void ULootLockerLifeCycleManager::HandleStartingPIE(bool bIsSimulating)
{
    if (bIsShuttingDown) return;

    FLootLockerLogger::LogVeryVerbose(TEXT("Entering PIE"));
    
    // Simulate application foreground event
    HandleGameInstanceInit(nullptr);
}

void ULootLockerLifeCycleManager::HandleEndingPIE(bool bIsSimulating)
{
    if (bIsShuttingDown) return;

    FLootLockerLogger::LogVeryVerbose(TEXT("Ending PIE"));
    
    // Broadcast to listeners but don't shut down the manager
    OnApplicationShutdown.Broadcast();
}

void ULootLockerLifeCycleManager::HandlePIEPaused(bool bIsSimulating)
{
    if (bIsShuttingDown) return;

    FLootLockerLogger::LogVeryVerbose(TEXT("PIE Paused"));
    
    // Simulate application background event
    HandleApplicationWillEnterBackground();
}

void ULootLockerLifeCycleManager::HandlePIEResumed(bool bIsSimulating)
{
    if (bIsShuttingDown) return;

    FLootLockerLogger::LogVeryVerbose(TEXT("PIE Resumed"));
    
    // Simulate application foreground event
    HandleApplicationHasEnteredForeground();
}
#endif