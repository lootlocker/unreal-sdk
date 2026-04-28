// Copyright (c) 2021 LootLocker

#include "Runtime/Launch/Resources/Version.h"
#include "LootLockerRateLimiter.h"
#include "Misc/AutomationTest.h"

#if ENGINE_MAJOR_VERSION > 4

// ---------------------------------------------------------------------------
// Testable subclass — overrides GetTimeNow() so tests control the clock.
// ---------------------------------------------------------------------------
class FLootLockerTestRateLimiter : public FLootLockerRateLimiter
{
public:
    FLootLockerTestRateLimiter()
    {
        // Force the limiter into the enabled state for deterministic testing
        // (bypasses the first-request production-environment guard).
        bEnableRateLimiter = true;
        bFirstRequestSent  = true;
        CurrentTime        = FDateTime(2021, 1, 1);
    }

    void SetTime(const FDateTime& NewTime)          { CurrentTime = NewTime; }
    void AddSecondsToCurrentTime(int32 Seconds)     { CurrentTime += FTimespan::FromSeconds(Seconds); }

protected:
    virtual FDateTime GetTimeNow() const override   { return CurrentTime; }

private:
    FDateTime CurrentTime;
};

// ---------------------------------------------------------------------------
// Spec
// ---------------------------------------------------------------------------

BEGIN_DEFINE_SPEC(
    FLootLockerRateLimiterSpec,
    "LootLocker.RateLimiter",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

    TUniquePtr<FLootLockerTestRateLimiter> RateLimiter;

END_DEFINE_SPEC(FLootLockerRateLimiterSpec)

void FLootLockerRateLimiterSpec::Define()
{
    BeforeEach([this]()
    {
        RateLimiter = MakeUnique<FLootLockerTestRateLimiter>();
    });

    AfterEach([this]()
    {
        RateLimiter.Reset();
    });

    Describe("Rate limiter", [this]()
    {
        It("NormalAmountOfAverageRequests_DoesNotHitRateLimit", [this]()
        {
            // Given
            const int32 SecondsToRunTest  = 360;
            const int32 RequestsPerSecond = 3;
            bool bWasRateLimitHit = false;

            RateLimiter->AddRequestAndCheckIfRateLimitHit();

            // When
            for (int32 i = 0; i < SecondsToRunTest; i++)
            {
                for (int32 j = 0; j < RequestsPerSecond; j++)
                {
                    bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                }
                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestFalse("Rate limit should not have been hit at 3 req/s", bWasRateLimitHit);
        });

        It("UndulatingLowLevelOfRequests_DoesNotHitRateLimit", [this]()
        {
            // Given
            const int32 SecondsToRunTest    = 360;
            const int32 UndulatingModuloMax = 6; // average 3.5 req/s — well below threshold
            bool bWasRateLimitHit = false;

            // When
            for (int32 i = 0; i < SecondsToRunTest; i++)
            {
                const int32 RequestsThisSecond = (i % UndulatingModuloMax) + 1;
                for (int32 j = 0; j < RequestsThisSecond; j++)
                {
                    bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                }
                RateLimiter->AddSecondsToCurrentTime(1);

                if (bWasRateLimitHit) { break; }
            }

            // Then
            TestFalse("Rate limit should not have been hit with undulating low-level traffic", bWasRateLimitHit);
        });

        It("FrequentSmallBursts_DoesNotHitRateLimit", [this]()
        {
            // Given
            const int32 SecondsToRunTest       = 360;
            const int32 RequestsPerBurst        = 9;
            const int32 SendRequestsEveryXSeconds = 3;
            bool  bWasRateLimitHit             = false;
            int32 RateLimitHitAfterSeconds     = -1;

            RateLimiter->AddRequestAndCheckIfRateLimitHit();

            // When
            for (int32 i = 0; i < SecondsToRunTest; i++)
            {
                if (i % SendRequestsEveryXSeconds == 0)
                {
                    for (int32 j = 0; j < RequestsPerBurst; j++)
                    {
                        bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                    }
                }
                if (bWasRateLimitHit) { RateLimitHitAfterSeconds = i; break; }
                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestTrue("Rate limit hit time should be -1 (not hit)", RateLimitHitAfterSeconds < 0);
            TestFalse("Rate limit should not have been hit with 9-req bursts every 3 s", bWasRateLimitHit);
        });

        It("InfrequentLargeBursts_DoesNotHitRateLimit", [this]()
        {
            // Given
            const int32 SecondsToRunTest      = 360;
            const int32 SendBurstsEveryXSeconds = 10;
            const int32 RequestsPerBurst       = 35;
            bool  bWasRateLimitHit            = false;
            int32 RateLimitHitAfterSeconds    = -1;

            RateLimiter->AddRequestAndCheckIfRateLimitHit();

            // When
            for (int32 i = 0; i < SecondsToRunTest; i++)
            {
                if (i % SendBurstsEveryXSeconds == 0)
                {
                    for (int32 j = 0; j < RequestsPerBurst; j++)
                    {
                        bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                        if (bWasRateLimitHit) { break; }
                    }
                }
                if (bWasRateLimitHit) { RateLimitHitAfterSeconds = i; break; }
                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestFalse("Rate limit should not have been hit with 35-req bursts every 10 s", bWasRateLimitHit);
            TestTrue("Rate limit hit time should be -1 (not hit)", RateLimitHitAfterSeconds < 0);
        });

        It("ExcessiveQuickSuccessionRequests_HitsTripwireRateLimit", [this]()
        {
            // Given
            const int32 MaxSecondsToRunTest   = 90;
            const int32 RequestsPerSecond     = 6;
            bool  bWasRateLimitHit            = false;
            int32 RateLimitHitAfterSeconds    = -1;

            RateLimiter->AddRequestAndCheckIfRateLimitHit();

            // When
            for (int32 i = 0; i < MaxSecondsToRunTest; i++)
            {
                for (int32 j = 0; j < RequestsPerSecond; j++)
                {
                    bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                }
                if (bWasRateLimitHit) { RateLimitHitAfterSeconds = i; break; }
                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestTrue("Rate limit should have been hit at 6 req/s", bWasRateLimitHit);
            TestTrue(
                FString::Printf(TEXT("Rate limit hit after %d s, expected < 56 s"), RateLimitHitAfterSeconds),
                RateLimitHitAfterSeconds < 56);
        });

        It("LowLevelBackgroundRequestsWithIntermittentBursts_HitsRateLimit", [this]()
        {
            // Given
            const int32 MaxSecondsToRunTest    = 360;
            const int32 RequestsPerSecond      = 2;
            const int32 RequestsPerBurst       = 110;
            const int32 SendBurstsEveryXSeconds = 29;
            bool bWasRateLimitHit              = false;

            // When
            for (int32 i = 0; i < MaxSecondsToRunTest; i++)
            {
                for (int32 j = 0; j < RequestsPerSecond; j++)
                {
                    bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                }

                if (i % SendBurstsEveryXSeconds == 0)
                {
                    for (int32 j = 0; j < RequestsPerBurst; j++)
                    {
                        bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                        if (bWasRateLimitHit) { break; }
                    }
                }

                if (bWasRateLimitHit) { break; }
                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestTrue("Rate limit should have been hit with background traffic + large intermittent bursts", bWasRateLimitHit);
        });

        It("SuddenHugeBurstBelowLimit_DoesNotTriggerRateLimit", [this]()
        {
            // Given
            const int32 MaxSecondsToRunTest    = 90;
            const int32 RequestsPerBurst       = 275;
            const int32 SendBurstsEveryXSeconds = 80;
            bool bWasRateLimitHit              = false;

            RateLimiter->AddRequestAndCheckIfRateLimitHit();
            RateLimiter->AddSecondsToCurrentTime(1);

            // When
            for (int32 i = 1; i < MaxSecondsToRunTest; i++)
            {
                if (i % SendBurstsEveryXSeconds == 0)
                {
                    for (int32 j = 0; j < RequestsPerBurst; j++)
                    {
                        bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                        if (bWasRateLimitHit) { break; }
                    }
                }
                if (bWasRateLimitHit) { break; }
                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestFalse("Rate limit should not have been hit with a burst of 275 requests", bWasRateLimitHit);
        });

        It("SuddenHugeBurstAboveLimit_TriggersRateLimit", [this]()
        {
            // Given
            const int32 MaxSecondsToRunTest    = 90;
            const int32 RequestsPerBurst       = 300;
            const int32 SendBurstsEveryXSeconds = 80;
            bool bWasRateLimitHit              = false;

            RateLimiter->AddRequestAndCheckIfRateLimitHit();
            RateLimiter->AddSecondsToCurrentTime(1);

            // When
            for (int32 i = 1; i < MaxSecondsToRunTest; i++)
            {
                if (i % SendBurstsEveryXSeconds == 0)
                {
                    for (int32 j = 0; j < RequestsPerBurst; j++)
                    {
                        bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                        if (bWasRateLimitHit) { break; }
                    }
                }
                if (bWasRateLimitHit) { break; }
                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestTrue("Rate limit should have been hit with a burst of 300 requests", bWasRateLimitHit);
        });

        It("SuddenHugeBurstBelowLimitFollowedByAFewRequests_TriggersRateLimit", [this]()
        {
            // Given
            const int32 MaxSecondsToRunTest          = 120;
            const int32 RequestsPerBurst             = 260;
            const int32 RequestsPerSecondAfterBurst  = 2;
            const int32 SendBurstsEveryXSeconds      = 80;
            bool bWasRateLimitHit                    = false;

            RateLimiter->AddRequestAndCheckIfRateLimitHit();
            RateLimiter->AddSecondsToCurrentTime(1);

            // When
            for (int32 i = 1; i < MaxSecondsToRunTest; i++)
            {
                if (i % SendBurstsEveryXSeconds == 0)
                {
                    for (int32 j = 0; j < RequestsPerBurst; j++)
                    {
                        bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                        if (bWasRateLimitHit) { break; }
                    }
                }

                if (i > SendBurstsEveryXSeconds)
                {
                    for (int32 j = 0; j < RequestsPerSecondAfterBurst; j++)
                    {
                        bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                        if (bWasRateLimitHit) { break; }
                    }
                }

                if (bWasRateLimitHit) { break; }
                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestTrue("Rate limit should have been hit: burst-of-260 + sustained 2 req/s pushes over the moving-average limit", bWasRateLimitHit);
        });

        It("ConstantRequestsBelowTripWire_HitsMovingAverageRateLimit", [this]()
        {
            // Given
            const int32 MaxSecondsToRunTest = 360;
            const int32 RequestsPerSecond   = 4;
            bool bWasRateLimitHit           = false;

            RateLimiter->AddRequestAndCheckIfRateLimitHit();
            RateLimiter->AddSecondsToCurrentTime(1);

            // When
            for (int32 i = 0; i < MaxSecondsToRunTest; i++)
            {
                for (int32 j = 0; j < RequestsPerSecond; j++)
                {
                    bWasRateLimitHit |= RateLimiter->AddRequestAndCheckIfRateLimitHit();
                }
                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestTrue("Sustained 4 req/s should eventually hit the moving-average rate limit", bWasRateLimitHit);
        });

        It("RateLimiterHit_ResetsAfterApproximately3Minutes", [this]()
        {
            // Given
            const int32 MaxSecondsToRunTest        = 480;
            const int32 ExpectedMaxSecondsToReset  = 180;
            const int32 ExpectedMinSecondsToReset  = 120;
            int32 ActualSecondsRateLimited         = 0;
            const int32 RequestsPerSecond          = 20;
            bool bIsRateLimited                    = false;

            RateLimiter->AddRequestAndCheckIfRateLimitHit();

            // When — drive requests until rate-limited, then keep driving until it clears
            for (int32 i = 0; i < MaxSecondsToRunTest; i++)
            {
                const bool bWasRateLimited = bIsRateLimited;
                for (int32 j = 0; j < RequestsPerSecond; j++)
                {
                    bIsRateLimited = RateLimiter->AddRequestAndCheckIfRateLimitHit();
                }

                if (bIsRateLimited)
                {
                    ActualSecondsRateLimited++;
                }

                // Stop once the rate limit clears
                if (bWasRateLimited && !bIsRateLimited)
                {
                    break;
                }

                RateLimiter->AddSecondsToCurrentTime(1);
            }

            // Then
            TestFalse("Rate limit should have cleared within the allotted period", bIsRateLimited);
            TestTrue(
                FString::Printf(TEXT("Rate limit should reset in < %d s, took %d s"), ExpectedMaxSecondsToReset, ActualSecondsRateLimited),
                ActualSecondsRateLimited < ExpectedMaxSecondsToReset);
            TestTrue(
                FString::Printf(TEXT("Rate limit should reset in > %d s, took %d s"), ExpectedMinSecondsToReset, ActualSecondsRateLimited),
                ActualSecondsRateLimited > ExpectedMinSecondsToReset);
        });
    });
}

#endif // ENGINE_MAJOR_VERSION > 4
