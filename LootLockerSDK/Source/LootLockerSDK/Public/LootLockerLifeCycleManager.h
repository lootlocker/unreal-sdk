// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "LootLockerLifeCycleManager.generated.h"

// Forward declarations
class ULootLockerPresenceManager;

/**
 * Delegate types for lifecycle events
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLootLockerLifeCycleDelegate);

/**
 * Manages Unreal Engine application and engine lifecycle events
 * Provides centralized handling of application state changes for LootLocker systems
 */
UCLASS(BlueprintType)
class LOOTLOCKERSDK_API ULootLockerLifeCycleManager : public UObject
{
    GENERATED_BODY()

public:
    // ========================================================================
    // SINGLETON MANAGEMENT
    // ========================================================================
    
    /** Get the singleton instance of the LifeCycle Manager */
    UFUNCTION(Category="LootLocker")
    static ULootLockerLifeCycleManager* GetInstance();

    /** Manually initialize the lifecycle manager (called automatically on first GetInstance) */
    UFUNCTION(Category="LootLocker")
    static void Initialize();

    /** Shutdown and cleanup the lifecycle manager */
    UFUNCTION(Category="LootLocker")
    static void Shutdown();

    // ========================================================================
    // LIFECYCLE EVENT DELEGATES
    // ========================================================================

    /** Called when application is about to enter background */
    UPROPERTY(BlueprintAssignable, Category="LootLocker")
    FLootLockerLifeCycleDelegate OnApplicationBackground;

    /** Called when application has returned to foreground */
    UPROPERTY(BlueprintAssignable, Category="LootLocker")
    FLootLockerLifeCycleDelegate OnApplicationForeground;

    /** Called when application is about to terminate */
    UPROPERTY(BlueprintAssignable, Category="LootLocker")
    FLootLockerLifeCycleDelegate OnApplicationStart;

    /** Called when application is about to terminate */
    UPROPERTY(BlueprintAssignable, Category="LootLocker")
    FLootLockerLifeCycleDelegate OnApplicationShutdown;

protected:
    // ========================================================================
    // CONSTRUCTOR & LIFECYCLE
    // ========================================================================

    ULootLockerLifeCycleManager();
    virtual void BeginDestroy() override;

    // ========================================================================
    // INTERNAL EVENT HANDLERS
    // ========================================================================

    /** Internal handlers for engine delegates */
    void HandleApplicationWillEnterBackground();
    void HandleApplicationHasEnteredForeground();
    void HandleApplicationWillTerminate();
    void HandleEnginePreExit();

    /** Game instance lifecycle handlers */
    void HandleGameInstanceInit(UGameInstance* ignored);

#if WITH_EDITOR
    void HandleStartingPIE(bool bIsSimulating);
    void HandleEndingPIE(bool bIsSimulating);
    void HandlePIEPaused(bool bIsSimulating);
    void HandlePIEResumed(bool bIsSimulating);
#endif

private:
    // ========================================================================
    // STATIC MEMBERS & THREADING
    // ========================================================================

    static ULootLockerLifeCycleManager* Instance;
    static FCriticalSection InstanceLock;

    // ========================================================================
    // STATE TRACKING
    // ========================================================================

    /** Whether the lifecycle manager has been initialized */
    bool bIsInitialized;

    /** Whether we're currently shutting down */
    bool bIsShuttingDown;

    // ========================================================================
    // DELEGATE HANDLES
    // ========================================================================

    /** Handles to engine delegates for proper cleanup */
    FDelegateHandle ApplicationWillEnterBackgroundHandle;
    FDelegateHandle ApplicationHasEnteredForegroundHandle;
    FDelegateHandle ApplicationWillTerminateHandle;
    FDelegateHandle EnginePreExitHandle;

    /** Game instance delegate handles */
    FDelegateHandle GameInstanceInitHandle;

#if WITH_EDITOR
    /** Editor window activation delegate handle */
    FDelegateHandle StartPIEHandle;
    FDelegateHandle EndPIEHandle;
    FDelegateHandle PIEPausedHandle;
    FDelegateHandle PIEResumedHandle;
#endif

    // ========================================================================
    // INTERNAL METHODS
    // ========================================================================

    /** Bind to all engine lifecycle delegates */
    void BindLifeCycleDelegates();

    /** Unbind from all engine lifecycle delegates */
    void UnbindLifeCycleDelegates();
};