// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"

/**
 * Client-side rate limiter for the LootLocker HTTP execution queue.
 *
 * Uses a dual-threshold sliding-window algorithm (ported from the Unity SDK) to
 * detect both sudden large bursts and sustained high-frequency request patterns
 * before they reach the server:
 *
 *  Tripwire  — hard cap: more than MaxRequestsPerTripWireTimeFrame (280) requests
 *              within any rolling TripWireTimeFrameSeconds (60 s) window.
 *
 *  Moving average — soft cap: the average requests-per-bucket across the full
 *              RateLimitMovingAverageBucketCount (36) buckets exceeds
 *              MaxRequestsPerBucketOnMovingAverage (18), i.e. sustained traffic
 *              at > 80 % of the tripwire rate over the past 3 minutes.
 *
 * Both thresholds are tracked via a circular array of int32 buckets, each
 * covering SecondsPerBucket (5) seconds. Time-advancement is virtual so unit
 * tests can drive the clock without real sleeps.
 *
 * Usage:
 *   FLootLockerRateLimiter Limiter;
 *   if (Limiter.AddRequestAndCheckIfRateLimitHit()) { ... deny or queue ... }
 */
class LOOTLOCKERSDK_API FLootLockerRateLimiter
{
public:
    // -------------------------------------------------------------------------
    // Algorithm constants (all match the Unity SDK values)
    // -------------------------------------------------------------------------

    /** Length of the tripwire measurement window in seconds. */
    static constexpr int32 TripWireTimeFrameSeconds = 60;

    /** Maximum requests allowed within a single TripWireTimeFrameSeconds window. */
    static constexpr int32 MaxRequestsPerTripWireTimeFrame = 280;

    /** Duration of each bucket in seconds. Must evenly divide TripWireTimeFrameSeconds. */
    static constexpr int32 SecondsPerBucket = 5;

    /**
     * Moving-average threshold expressed as a fraction of the tripwire maximum.
     * The per-bucket average across CountMovingAverageAcrossNTripWireTimeFrames
     * windows must stay at or below this percentage.
     */
    static constexpr float AllowXPercentOfTripWireMaxForMovingAverage = 0.8f;

    /** Number of tripwire time frames covered by the moving-average window. */
    static constexpr int32 CountMovingAverageAcrossNTripWireTimeFrames = 3;

    // -------------------------------------------------------------------------
    // Derived constants
    // -------------------------------------------------------------------------

    /** Number of buckets that span one tripwire time frame (= 60 / 5 = 12). */
    static constexpr int32 BucketsPerTimeFrame = TripWireTimeFrameSeconds / SecondsPerBucket;

    /** Total number of buckets in the circular array (= 3 * 12 = 36). */
    static constexpr int32 RateLimitMovingAverageBucketCount = CountMovingAverageAcrossNTripWireTimeFrames * BucketsPerTimeFrame;

    /**
     * Per-bucket average that triggers the moving-average rate limit.
     * = (280 * 0.8) / 12 = 18  (computed as (280 * 4) / (12 * 5) to avoid float constexpr).
     */
    static constexpr int32 MaxRequestsPerBucketOnMovingAverage =
        (MaxRequestsPerTripWireTimeFrame * 4) / (BucketsPerTimeFrame * 5);

    // -------------------------------------------------------------------------
    // Lifecycle
    // -------------------------------------------------------------------------

    FLootLockerRateLimiter();
    virtual ~FLootLockerRateLimiter() = default;

    /**
     * Resets all rate-limiting state to its initial values.
     * Call this when the SDK session is torn down, or for unit-test isolation.
     */
    void Reset();

    // -------------------------------------------------------------------------
    // Public API
    // -------------------------------------------------------------------------

    /**
     * Records one outgoing request and returns whether the rate limit is
     * currently active.
     *
     * @return true  if the caller should back off (rate limit is active).
     *         false if the request may proceed normally.
     */
    virtual bool AddRequestAndCheckIfRateLimitHit();

    /**
     * Returns the approximate number of seconds until the rate limit clears.
     * Returns 0 when no rate limit is active.
     */
    int32 GetSecondsLeftOfRateLimit() const;

protected:
    // -------------------------------------------------------------------------
    // Testability hook
    // -------------------------------------------------------------------------

    /**
     * Returns the current wall-clock time used for bucket advancement.
     * Override in test subclasses to control time deterministically.
     */
    virtual FDateTime GetTimeNow() const;

    // -------------------------------------------------------------------------
    // State (protected for test-subclass access)
    // -------------------------------------------------------------------------

    /** When false, AddRequestAndCheckIfRateLimitHit() always returns false. */
    bool bEnableRateLimiter = true;

    /**
     * Set to true once the first request has been processed.
     * Used to defer the production-environment check until the SDK is running.
     */
    bool bFirstRequestSent = false;

    /** Circular array of per-bucket request counts. */
    int32 Buckets[RateLimitMovingAverageBucketCount];

    /** Index of the most-recently-written bucket (-1 = not yet started). */
    int32 LastBucket = -1;

    /** Wall-clock time at which the current bucket became active. */
    FDateTime LastBucketChangeTime;

    /** Running total of all requests across every bucket in the array. */
    int32 TotalRequestsInBuckets = 0;

    /** Running total of requests in the buckets that fall within the current tripwire time frame. */
    int32 TotalRequestsInBucketsInTripWireTimeFrame = 0;

    /** True while requests are being rejected due to an active rate limit. */
    bool bIsRateLimited = false;

    /** Wall-clock time at which the current rate limit is expected to clear. */
    FDateTime RateLimitResolvesAt;

private:
    /**
     * Advances the bucket pointer to reflect elapsed time since the last call.
     * Buckets skipped over are zeroed and their counts removed from the running
     * totals. Returns the index of the current (now active) bucket.
     */
    int32 MoveCurrentBucket(const FDateTime& Now);
};
