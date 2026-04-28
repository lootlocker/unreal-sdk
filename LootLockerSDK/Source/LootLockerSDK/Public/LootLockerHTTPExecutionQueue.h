// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "LootLockerHTTPClientConfiguration.h"
#include "LootLockerHTTPExecutionQueueItem.h"
#include "LootLockerRateLimiter.h"

struct FLootLockerPlayerData;

/**
 * Manages the LootLocker HTTP request queue as a tickable singleton.
 *
 * Maintains a two-phase per-frame loop that:
 *  1. Promotes pending requests to in-flight status (respecting MaxOngoingRequests
 *     and Retry-After delays).
 *  2. Polls in-flight requests for completion, handles retries, session refresh,
 *     and rate limiting.
 *  3. Cleans up completed items and invokes response listeners.
 *
 * Access the singleton via Get(). Call Initialize() once on startup (done
 * automatically by FLootLockerSDKModule::StartupModule()) and Shutdown() on
 * teardown.
 */
class LOOTLOCKERSDK_API FLootLockerHTTPExecutionQueue : public FTickableGameObject
{
public:
    // -------------------------------------------------------------------------
    // Singleton lifecycle
    // -------------------------------------------------------------------------

    /** Returns the singleton instance.  Lazy-initializes if not already initialized. */
    static FLootLockerHTTPExecutionQueue& Get();

    /** Creates and starts ticking the singleton.  Safe to call multiple times. */
    static void Initialize();

    /** Returns true if Initialize() has been called and Shutdown() has not yet been called. */
    static bool IsInitialized();

    /**
     * Aborts all in-flight requests, drains the queue with error callbacks, and
     * destroys the singleton.
     */
    static void Shutdown();

    // -------------------------------------------------------------------------
    // Public API
    // -------------------------------------------------------------------------

    /**
     * Enqueues a request for dispatch on the next available tick.
     *
     * If the queue is full and DenyIncomingRequestsWhenBackedUp is true the
     * request is immediately failed via its listeners.  If a request with the
     * same RequestId is already queued the new listeners are merged into the
     * existing entry.
     */
    void ScheduleRequest(const FLootLockerHTTPRequestData& Request);

    /** Replaces the active configuration.  Takes effect from the next Tick(). */
    void OverrideConfiguration(const FLootLockerHTTPClientConfiguration& NewConfig);

    // -------------------------------------------------------------------------
    // FTickableGameObject interface
    // -------------------------------------------------------------------------

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override { return bIsInitialized; }
    virtual TStatId GetStatId() const override;
    
    /** Do not construct directly — use Get() or Initialize() instead. */
    FLootLockerHTTPExecutionQueue() = default;

private:
    static TUniquePtr<FLootLockerHTTPExecutionQueue> Instance;

    bool bIsInitialized = false;
    FLootLockerHTTPClientConfiguration Configuration;
    TUniquePtr<FLootLockerRateLimiter> RateLimiter;

    /** Pending + in-flight queue, keyed by RequestId. */
    TMap<FString, TSharedPtr<FLootLockerHTTPExecutionQueueItem>> ExecutionQueue;

    /** Set of RequestIds currently dispatched as HTTP requests. */
    TSet<FString> OngoingRequestIds;

    /**
     * RequestIds confirmed done in this tick's first phase.
     * Listeners are invoked and entries are removed in the second phase.
     */
    TArray<FString> CompletedRequestIds;

    /** RequestIds batched for bulk session refresh at the end of the first phase. */
    TArray<FString> RefreshNeededIds;

    // --- SDK identity headers (mirrors ULootLockerHttpClient statics) ---
    static FString SDKVersion;
    static const FString UserAgent;
    static const FString UserInstanceIdentifier;

    // --- Per-tick helpers ---

    /**
     * Dispatches Item as an Unreal HTTP request.
     * Returns false if the rate limiter denied the request (listeners already
     * invoked in that case).
     */
    bool CreateAndSendRequest(FLootLockerHTTPExecutionQueueItem& Item);

    /**
     * Polls the status of Item's in-flight HTTP request.
     * Returns the appropriate processing result for this tick.
     */
    ELootLockerHTTPExecutionQueueProcessingResult ProcessOngoingRequest(
        FLootLockerHTTPExecutionQueueItem& Item);

    /**
     * Applies the given processing result to Item (sets done, schedules retry, or
     * initiates session refresh as appropriate).
     */
    void HandleRequestResult(
        FLootLockerHTTPExecutionQueueItem& Item,
        ELootLockerHTTPExecutionQueueProcessingResult Result);

    /**
     * Begins an async session-refresh for the item identified by RequestId and
     * marks it as waiting.  On completion the item is either re-queued for dispatch
     * or marked done with the stored failure response.
     */
    void DispatchSessionRefreshForItem(const FString& RequestId);

    /**
     * Called when a session refresh completes.  Resumes the request if the refresh
     * succeeded, or marks it done with the stored failure response if not.
     *
     * Invoked from the session-refresh callback lambda instead of capturing `this`
     * directly, so the callback is safe to call even if Shutdown() has run
     * (IsInitialized() is checked before entering this method).
     */
    void OnSessionRefreshCompleted(const FString& RequestId, bool bRefreshSuccess);

    /**
     * Stores Response on Item, marks it done, removes it from OngoingRequestIds,
     * and adds it to CompletedRequestIds so the cleanup phase will invoke its
     * listeners.
     */
    void MarkItemDone(FLootLockerHTTPExecutionQueueItem& Item, const FLootLockerResponse& Response);

    /**
     * Centralised terminal-completion path for all real HTTP outcomes (success,
     * failure, timeout, and session-refresh failure).
     *
     * In order:
     *  1. Captures request headers from the live HttpRequest (before MarkItemDone
     *     resets the pointer).
     *  2. On success: calls ULootLockerStateData::MakePlayerActive.
     *     On failure: calls ULootLockerHttpClient::StoreFailedRequestReport.
     *  3. Calls FLootLockerLogger::LogHttpRequest to write to console/file and
     *     broadcast to the editor Log Viewer.
     *  4. Calls MarkItemDone to hand the item to the cleanup phase.
     *
     * Do NOT call this for synthetic pre-queue rejections (queue-full, choke,
     * rate-limit) — those have no real HTTP request and call MarkItemDone directly.
     */
    void CompleteItem(FLootLockerHTTPExecutionQueueItem& Item, const FLootLockerResponse& Response);

    /**
     * Returns true when the HTTP status code and retry count indicate the request
     * should be retried (5xx, network errors, and 429).
     */
    bool ShouldRetryRequest(int32 StatusCode, int32 TimesRetried) const;

    /**
     * Returns true when a 401/403 response might be resolved by refreshing the
     * player session (checks platform, token availability, and SDK config).
     */
    bool ShouldRefreshSession(int32 StatusCode, const FLootLockerPlayerData& PlayerData,
                              int32 TimesRetried) const;

    /** Timestamp (FPlatformTime::Seconds()) of the last choke-warning log entry.
     *  Used to throttle the per-tick warning to at most once per ChokeWarningLogIntervalSeconds. */
    double LastChokeWarningLogTime = 0.0;
};
