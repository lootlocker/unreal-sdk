// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"

/**
 * Configuration for the LootLocker HTTP execution queue and retry logic.
 *
 * Construct an instance with custom values and pass it to
 * ULootLockerHttpClient::OverrideConfiguration() to tune the SDK's HTTP behaviour
 * at runtime.
 */
struct LOOTLOCKERSDK_API FLootLockerHTTPClientConfiguration
{
    /**
     * Maximum number of times a failed request will be retried before the error is
     * returned to the caller.
     */
    int32 MaxRetries = 5;

    /**
     * Multiplicative factor applied to the wait time between each successive retry
     * attempt (exponential back-off).
     *
     * Example: with InitialRetryWaitTimeMs=50 and IncrementalBackoffFactor=2 the
     * delays are 50 ms → 100 ms → 200 ms → 400 ms → …
     */
    int32 IncrementalBackoffFactor = 2;

    /**
     * Base wait time in milliseconds before the first retry attempt.
     * See IncrementalBackoffFactor for how subsequent delays are computed.
     */
    int32 InitialRetryWaitTimeMs = 50;

    /**
     * Maximum number of HTTP requests that may be in-flight (awaiting a server
     * response) at the same time.  Requests beyond this limit are held in the
     * pending queue.
     */
    int32 MaxOngoingRequests = 50;

    /**
     * Maximum number of requests allowed to sit in the pending queue.
     * New requests submitted while the queue is at capacity are rejected immediately
     * when DenyIncomingRequestsWhenBackedUp is true.
     */
    int32 MaxQueueSize = 5000;

    /**
     * Pending-queue depth at which a warning is emitted to alert that the HTTP
     * client is approaching capacity.
     */
    int32 ChokeWarningThreshold = 500;

    /**
     * Client-side request timeout in seconds. If the server has not responded within
     * this time, the request is cancelled and reported as timed out.
     */
    int32 RequestTimeoutSeconds = 300;

    /**
     * When true, incoming requests are immediately rejected (with a synthetic error
     * response) while the pending queue is at or above MaxQueueSize.
     * When false, new requests continue to be accepted regardless of queue depth.
     */
    bool DenyIncomingRequestsWhenBackedUp = true;

    /**
     * When true, rejections caused by queue-capacity limits are written to the log.
     * Defaults to true in editor builds, false otherwise to reduce log noise in
     * shipping.
     */
    bool LogQueueRejections =
#if WITH_EDITOR
        true;
#else
        false;
#endif

    /**
     * Minimum interval in seconds between consecutive choke-warning log entries.
     * Prevents the log from being flooded when the queue is consistently backed up
     * over many ticks. Only applies in editor builds (where LogQueueRejections is
     * checked).
     */
    float ChokeWarningLogIntervalSeconds = 2.0f;

    /**
     * Wall-clock threshold in milliseconds above which a warning is emitted if a
     * single response listener takes too long to execute.
     *
     * Listeners run on the game thread inside Tick(). Heavy work inside a callback
     * (asset loading, synchronous I/O, complex computation) will stall the game
     * thread for every frame it occupies. This threshold gives developers an early
     * warning when that happens.
     *
     * Set to 0 to disable the check. Defaults to 16 ms (one frame at 60 fps).
     */
    float SlowListenerWarningThresholdMs = 16.0f;

    FLootLockerHTTPClientConfiguration() = default;
};
