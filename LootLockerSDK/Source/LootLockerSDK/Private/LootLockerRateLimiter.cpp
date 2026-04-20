// Copyright (c) 2021 LootLocker

#include "LootLockerRateLimiter.h"
#include "LootLockerLogger.h"

FLootLockerRateLimiter::FLootLockerRateLimiter()
    : LastBucketChangeTime(0)   // FDateTime(0) == January 1, AD 1 — used as "not set" sentinel
    , RateLimitResolvesAt(0)
{
    FMemory::Memset(Buckets, 0, sizeof(Buckets));
}

void FLootLockerRateLimiter::Reset()
{
    FMemory::Memset(Buckets, 0, sizeof(Buckets));
    LastBucket = -1;
    LastBucketChangeTime = FDateTime(0);
    TotalRequestsInBuckets = 0;
    TotalRequestsInBucketsInTripWireTimeFrame = 0;
    bIsRateLimited = false;
    RateLimitResolvesAt = FDateTime(0);
    bFirstRequestSent = false;
}

FDateTime FLootLockerRateLimiter::GetTimeNow() const
{
    return FDateTime::UtcNow();
}

int32 FLootLockerRateLimiter::GetSecondsLeftOfRateLimit() const
{
    if (!bIsRateLimited)
    {
        return 0;
    }
    return FMath::CeilToInt(static_cast<float>((RateLimitResolvesAt - GetTimeNow()).GetTotalSeconds()));
}

int32 FLootLockerRateLimiter::MoveCurrentBucket(const FDateTime& Now)
{
    // On the very first call LastBucketChangeTime is the zero sentinel — always
    // advance by exactly one bucket to initialise bucket 0.
    const int32 MoveOverXBuckets = (LastBucketChangeTime == FDateTime(0))
        ? 1
        : FMath::FloorToInt(static_cast<float>((Now - LastBucketChangeTime).GetTotalSeconds()) / SecondsPerBucket);

    if (MoveOverXBuckets == 0)
    {
        return LastBucket;
    }

    for (int32 StepIndex = 1; StepIndex <= MoveOverXBuckets; StepIndex++)
    {
        const int32 BucketIndex = (LastBucket + StepIndex) % RateLimitMovingAverageBucketCount;

        // Guard against wrapping all the way around back to the same bucket
        if (BucketIndex == LastBucket)
        {
            continue;
        }

        // The bucket exactly one tripwire-time-frame behind BucketIndex is
        // sliding out of the tripwire window — remove its count.
        const int32 BucketMovingOutOfTripWireTimeFrame =
            (BucketIndex - BucketsPerTimeFrame) < 0
                ? RateLimitMovingAverageBucketCount + (BucketIndex - BucketsPerTimeFrame)
                : BucketIndex - BucketsPerTimeFrame;

        TotalRequestsInBucketsInTripWireTimeFrame -= Buckets[BucketMovingOutOfTripWireTimeFrame];
        TotalRequestsInBuckets                   -= Buckets[BucketIndex]; // subtract before zeroing
        Buckets[BucketIndex] = 0;
    }

    return (LastBucket + MoveOverXBuckets) % RateLimitMovingAverageBucketCount;
}

bool FLootLockerRateLimiter::AddRequestAndCheckIfRateLimitHit()
{
    if (!bFirstRequestSent)
    {
        // TODO (Phase 4): enable only when targeting the production environment,
        //   matching the Unity SDK's LootLockerConfig.IsTargetingProductionEnvironment() check.
        bEnableRateLimiter = true;
        bFirstRequestSent = true;
    }

    if (!bEnableRateLimiter)
    {
        return false;
    }

    const FDateTime Now = GetTimeNow();
    const int32 CurrentBucket = MoveCurrentBucket(Now);

    if (bIsRateLimited)
    {
        // Lift the rate limit once all tracked requests have aged out of the window.
        if (TotalRequestsInBuckets <= 0)
        {
            bIsRateLimited = false;
            RateLimitResolvesAt = FDateTime(0);
        }
    }
    else
    {
        // Count this request in the current bucket and running totals.
        Buckets[CurrentBucket]++;
        TotalRequestsInBuckets++;
        TotalRequestsInBucketsInTripWireTimeFrame++;

        // Tripwire check: too many requests in the last 60 seconds.
        const bool bHitTripwire = TotalRequestsInBucketsInTripWireTimeFrame >= MaxRequestsPerTripWireTimeFrame;

        // Moving-average check: sustained high rate over the last 3 minutes.
        const bool bHitMovingAverage = (TotalRequestsInBuckets / RateLimitMovingAverageBucketCount) > MaxRequestsPerBucketOnMovingAverage;

        if (bHitTripwire || bHitMovingAverage)
        {
            bIsRateLimited = true;

#if WITH_EDITOR
            if (bHitTripwire)
            {
                FLootLockerLogger::LogWarning(FString::Printf(
                    TEXT("LootLocker rate limit hit (tripwire): %d requests in the last %d s, limit is %d."),
                    TotalRequestsInBucketsInTripWireTimeFrame, TripWireTimeFrameSeconds, MaxRequestsPerTripWireTimeFrame));
            }
            if (bHitMovingAverage)
            {
                FLootLockerLogger::LogWarning(FString::Printf(
                    TEXT("LootLocker rate limit hit (moving average): avg %.1f req/bucket over %d buckets, limit is %d."),
                    static_cast<float>(TotalRequestsInBuckets) / RateLimitMovingAverageBucketCount,
                    RateLimitMovingAverageBucketCount,
                    MaxRequestsPerBucketOnMovingAverage));
            }
#endif

            // Rate limit clears once all current requests age out of the moving-average
            // window: round down to the start of the current bucket, then add the full
            // window duration (36 buckets × 5 s = 180 s).
            const int32 SecondsIntoCurrentBucket = Now.GetSecond() % SecondsPerBucket;
            RateLimitResolvesAt =
                (Now - FTimespan::FromSeconds(SecondsIntoCurrentBucket))
                + FTimespan::FromSeconds(static_cast<double>(RateLimitMovingAverageBucketCount * SecondsPerBucket));
        }
    }

    // Advance the bucket pointer if time moved forward.
    if (CurrentBucket != LastBucket)
    {
        LastBucketChangeTime = Now;
        LastBucket = CurrentBucket;
    }

    return bIsRateLimited;
}
