// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "LootLockerHTTPRequestData.h"
#include "LootLockerResponse.h"

/**
 * Outcome codes returned by the HTTP execution queue's per-tick processing loop.
 * Each in-flight item produces one of these on every Tick() pass.
 */
enum class ELootLockerHTTPExecutionQueueProcessingResult : uint8
{
    /** No determination made (initial / sentinel value). */
    None = 0,

    /** The item is still in-flight; check again next tick. */
    WaitForNextTick = 1,

    /** The HTTP exchange completed and returned a success response. */
    Completed_Success = 2,

    /** The HTTP exchange completed and returned a failure response. */
    Completed_Failed = 3,

    /**
     * The request timed out waiting for a server response or for a session-refresh
     * handshake to complete.
     */
    Completed_TimedOut = 4,

    /**
     * The request failed with a retryable error (e.g. 5xx, network glitch).
     * The queue will re-enqueue it after the appropriate back-off delay.
     */
    ShouldBeRetried = 5,

    /**
     * The server returned a 401/403 that can potentially be resolved by refreshing
     * the player session.  The queue suspends the item until the refresh completes.
     */
    NeedsSessionRefresh = 6,
};

/**
 * Pairs a pending FLootLockerHTTPRequestData with its active IHttpRequest handle.
 *
 * Instances are created by FLootLockerHTTPExecutionQueue when a queued request is
 * promoted to in-flight status, and destroyed when the request reaches a terminal
 * state (Completed_* or after all retries are exhausted).
 */
struct LOOTLOCKERSDK_API FLootLockerHTTPExecutionQueueItem
{
    /** The logical request (endpoint, verb, body, listeners, retry count, …). */
    FLootLockerHTTPRequestData RequestData;

    /**
     * The underlying Unreal HTTP request object.
     * Valid while the request is in-flight; reset to nullptr once the response
     * arrives or the request is aborted.
     */
    TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest;

    /**
     * Wall-clock time (FPlatformTime::Seconds()) at which the HTTP request was
     * most recently dispatched via ProcessRequest().  Reset on each retry.
     */
    double RequestStartTime = 0.0;

    /**
     * When set, the request must not be retried until after this point in time
     * (honouring a Retry-After header returned by the server).
     */
    TOptional<FDateTime> RetryAfter;

    /**
     * True while the queue is waiting for a session-refresh handshake to complete
     * before re-issuing this request.
     */
    bool bIsWaitingForSessionRefresh = false;

    /**
     * True once the item has reached a terminal state (success, failure, or
     * exhausted retries).  The queue removes Done items at the start of each tick.
     */
    bool bDone = false;

    /** The final response.  Meaningful only when bDone == true. */
    FLootLockerResponse Response;

    /**
     * Cancels the in-flight IHttpRequest and releases the shared pointer.
     * Safe to call on an item whose HttpRequest has already been reset.
     */
    void AbortRequest()
    {
        if (HttpRequest.IsValid())
        {
            HttpRequest->CancelRequest();
            HttpRequest.Reset();
        }
    }
};
