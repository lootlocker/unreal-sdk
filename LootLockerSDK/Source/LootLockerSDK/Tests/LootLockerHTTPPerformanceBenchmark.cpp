// Copyright (c) 2021 LootLocker

// Phase 0 — HTTP Performance Baseline Benchmark
// Measures the raw throughput of ULootLockerHttpClient BEFORE the queue refactor.
// Re-run (without modification) after Phase 4 to compare post-queue numbers.
//
// Uses FHttpModule NullHttp mode — no backend connection required.
// Tagged EngineFilter so it is excluded from the default smoke pass.
//
// Run manually:
//   UnrealEditor.exe "YourProject.uproject" -run=automation
//     -ExecCmds="automation RunTests LootLocker.HTTP.PerformanceBenchmark"
//     -unattended -nullrhi -nosound -stdout

#include <atomic>

#include "LootLockerHttpClient.h"
#include "LootLockerPlayerData.h"
#include "LootLockerResponse.h"
#include "HttpModule.h"
#include "Misc/AutomationTest.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformTime.h"
#include "HAL/PlatformProcess.h"

#if ENGINE_MAJOR_VERSION > 4

BEGIN_DEFINE_SPEC(
    FLootLockerHTTPPerformanceBenchmark,
    "LootLocker.HTTP.PerformanceBenchmark",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

    // Runs one benchmark scenario and logs + appends a CSV row.
    // NumRequests  — how many concurrent SendApi() calls to submit
    // Label        — identifier written to the CSV (e.g. "Baseline_100")
    void RunBenchmark(int32 NumRequests, const FString& Label);

    // Path to the shared CSV file for this test session.
    // Populated lazily on the first RunBenchmark() call so the timestamp
    // reflects actual test execution time rather than spec-registration time.
    FString CSVFilePath;

END_DEFINE_SPEC(FLootLockerHTTPPerformanceBenchmark)

// ---------------------------------------------------------------------------

void FLootLockerHTTPPerformanceBenchmark::RunBenchmark(int32 NumRequests, const FString& Label)
{
    // Lazy CSV initialisation — all three scenarios share one file per session.
    if (CSVFilePath.IsEmpty())
    {
        CSVFilePath = FPaths::ProjectSavedDir() /
            FString::Printf(TEXT("LootLockerHTTPBenchmark_%s.csv"),
                *FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S")));

        FFileHelper::SaveStringToFile(
            FString(TEXT("Label,NumRequests,Completed,PeakInFlight,DurationSeconds")) + LINE_TERMINATOR,
            *CSVFilePath);

        UE_LOG(LogTemp, Log,
            TEXT("[LootLocker Benchmark] Results will be written to: %s"), *CSVFilePath);
    }

    // Redirect all HTTP traffic through the null handler — no backend needed.
    FHttpModule::Get().ToggleNullHttp(true);

    // Thread-safe counters shared between the submission loop and callbacks.
    // RunBenchmark() blocks until all callbacks have fired, so capturing these
    // by reference inside the delegate lambdas is safe.
    std::atomic<int32> CompletedCount(0);
    std::atomic<int32> CurrentInFlight(0);
    std::atomic<int32> PeakInFlight(0);

    // Empty player data — no session token, so no session-refresh paths fire.
    FLootLockerPlayerData EmptyPlayerData;
    const FString FakeEndpoint = TEXT("http://localhost/api/benchmark");

    const double StartTime = FPlatformTime::Seconds();

    for (int32 i = 0; i < NumRequests; i++)
    {
        // Increment before the request is dispatched so we see the peak
        // in-flight value even when NullHttp fires callbacks synchronously.
        const int32 InFlight = ++CurrentInFlight;

        // Non-locking CAS loop to track the running maximum.
        int32 CurrentPeak = PeakInFlight.load(std::memory_order_relaxed);
        while (InFlight > CurrentPeak &&
               !PeakInFlight.compare_exchange_weak(
                   CurrentPeak, InFlight, std::memory_order_relaxed))
        {
        }

        ULootLockerHttpClient::SendApi(
            FakeEndpoint,
            TEXT("GET"),
            TEXT("{}"),
            FResponseCallback::CreateLambda(
                [&CompletedCount, &CurrentInFlight](const FLootLockerResponse& /*Response*/)
                {
                    --CurrentInFlight;
                    ++CompletedCount;
                }),
            EmptyPlayerData);
    }

    // Poll until all callbacks have fired, with a generous timeout to handle
    // slow CI machines. 30 s is far more than NullHttp needs in practice.
    constexpr double TimeoutSeconds = 30.0;
    const double     WaitStart      = FPlatformTime::Seconds();
    while (CompletedCount.load() < NumRequests)
    {
        if ((FPlatformTime::Seconds() - WaitStart) > TimeoutSeconds)
        {
            UE_LOG(LogTemp, Warning,
                TEXT("[LootLocker Benchmark] %s timed out: %d/%d callbacks received"),
                *Label, CompletedCount.load(), NumRequests);
            break;
        }
        FPlatformProcess::Sleep(0.001f);
    }

    const double DurationSeconds = FPlatformTime::Seconds() - StartTime;
    const int32  Completed       = CompletedCount.load();
    const int32  Peak            = PeakInFlight.load();

    UE_LOG(LogTemp, Log,
        TEXT("[LootLocker Benchmark] %s | requests=%d  completed=%d  peak_in_flight=%d  duration=%.4fs"),
        *Label, NumRequests, Completed, Peak, DurationSeconds);

    // Append one CSV row (FILEWRITE_Append | FILEWRITE_AllowRead).
    FFileHelper::SaveStringToFile(
        FString::Printf(TEXT("%s,%d,%d,%d,%.6f"), *Label, NumRequests, Completed, Peak, DurationSeconds)
            + LINE_TERMINATOR,
        *CSVFilePath,
        FFileHelper::EEncodingOptions::AutoDetect,
        &IFileManager::Get(),
        FILEWRITE_Append | FILEWRITE_AllowRead);

    // Restore real HTTP transport before asserting so a test failure here
    // does not leave the module in NullHttp mode for subsequent tests.
    FHttpModule::Get().ToggleNullHttp(false);

    TestEqual(
        FString::Printf(TEXT("%s: all %d requests completed"), *Label, NumRequests),
        Completed, NumRequests);
}

// ---------------------------------------------------------------------------

void FLootLockerHTTPPerformanceBenchmark::Define()
{
    Describe("HTTP Performance Benchmark (NullHttp — no backend required)", [this]()
    {
        LatentIt("Baseline: 100 concurrent submissions", EAsyncExecution::ThreadPool,
            [this](const FDoneDelegate TestDone)
            {
                RunBenchmark(100, TEXT("Baseline_100"));
                TestDone.Execute();
            });

        LatentIt("Baseline: 500 concurrent submissions", EAsyncExecution::ThreadPool,
            [this](const FDoneDelegate TestDone)
            {
                RunBenchmark(500, TEXT("Baseline_500"));
                TestDone.Execute();
            });

        LatentIt("Baseline: 1000 concurrent submissions", EAsyncExecution::ThreadPool,
            [this](const FDoneDelegate TestDone)
            {
                RunBenchmark(1000, TEXT("Baseline_1000"));
                TestDone.Execute();
            });
    });
}

#endif // ENGINE_MAJOR_VERSION > 4
