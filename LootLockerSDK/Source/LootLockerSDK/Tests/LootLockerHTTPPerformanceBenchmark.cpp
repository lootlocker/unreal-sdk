// Copyright (c) 2021 LootLocker

// Phase 0 — HTTP Submission Throughput Baseline Benchmark
// Measures dispatch overhead of ULootLockerHttpClient BEFORE the queue refactor.
// Re-run (without modification) after Phase 4 to compare post-queue numbers.
//
// What is measured: the wall-clock time to submit N ULootLockerHttpClient::SendApi()
// calls, i.e., the pure scheduling/dispatch overhead per request. Callback completion
// is NOT measured here because UE's FNullHttpRequest never fires completion delegates.
// After Phase 4, the same test will measure FLootLockerHTTPExecutionQueue::ScheduleRequest()
// overhead, giving a direct apples-to-apples comparison.
//
// No backend required — requests target http://localhost/api/benchmark which will
// be refused, but the benchmark completes before callbacks would ever arrive.
//
// Tagged EngineFilter so it is excluded from the default smoke pass.
//
// Run manually:
//   UnrealEditor.exe "YourProject.uproject" -run=automation
//     -ExecCmds="automation RunTests LootLocker.HTTP.PerformanceBenchmark"
//     -unattended -nullrhi -nosound -stdout

#include "Runtime/Launch/Resources/Version.h"
#include "LootLockerHttpClient.h"
#include "LootLockerPlayerData.h"
#include "LootLockerResponse.h"
#include "Misc/AutomationTest.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformTime.h"

#if ENGINE_MAJOR_VERSION > 4

BEGIN_DEFINE_SPEC(
    FLootLockerHTTPPerformanceBenchmark,
    "LootLocker.HTTP.PerformanceBenchmark",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

    // Submits NumRequests SendApi() calls and records the wall-clock submission
    // time to a shared CSV file. Always passes — this is an informational benchmark.
    void RunBenchmark(int32 NumRequests, const FString& Label);

    // Shared CSV file path for the session (lazily initialised on first call).
    FString CSVFilePath;

END_DEFINE_SPEC(FLootLockerHTTPPerformanceBenchmark)

// ---------------------------------------------------------------------------

void FLootLockerHTTPPerformanceBenchmark::RunBenchmark(int32 NumRequests, const FString& Label)
{
    // Lazy CSV initialisation — all scenarios share one file per session.
    if (CSVFilePath.IsEmpty())
    {
        CSVFilePath = FPaths::ProjectSavedDir() /
            FString::Printf(TEXT("LootLockerHTTPBenchmark_%s.csv"),
                *FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S")));

        FFileHelper::SaveStringToFile(
            FString(TEXT("Label,NumRequests,SubmissionMs,PerRequestUs")) + LINE_TERMINATOR,
            *CSVFilePath);

        UE_LOG(LogTemp, Log,
            TEXT("[LootLocker Benchmark] Results will be written to: %s"), *CSVFilePath);
    }

    // Empty player data — no session token, so no session-refresh paths fire.
    FLootLockerPlayerData EmptyPlayerData;
    const FString FakeEndpoint = TEXT("http://localhost/api/benchmark");

    // Measure only the submission loop — how long does it take to dispatch N requests.
    // Callbacks are intentionally ignored; the metric is scheduling overhead per call.
    const double StartTime = FPlatformTime::Seconds();

    for (int32 i = 0; i < NumRequests; i++)
    {
        ULootLockerHttpClient::SendApi(
            FakeEndpoint,
            TEXT("GET"),
            TEXT("{}"),
            FResponseCallback::CreateLambda([](const FLootLockerResponse& /*Response*/) {}),
            EmptyPlayerData);
    }

    const double SubmissionMs    = (FPlatformTime::Seconds() - StartTime) * 1000.0;
    const double PerRequestUs    = (SubmissionMs * 1000.0) / NumRequests;

    UE_LOG(LogTemp, Log,
        TEXT("[LootLocker Benchmark] %s | requests=%d  submission=%.3fms  per_request=%.2f\u03bcs"),
        *Label, NumRequests, SubmissionMs, PerRequestUs);

    // Append one CSV row.
    FFileHelper::SaveStringToFile(
        FString::Printf(TEXT("%s,%d,%.3f,%.2f"), *Label, NumRequests, SubmissionMs, PerRequestUs)
            + LINE_TERMINATOR,
        *CSVFilePath,
        FFileHelper::EEncodingOptions::AutoDetect,
        &IFileManager::Get(),
        FILEWRITE_Append | FILEWRITE_AllowRead);

    // Surface results in the automation report (informational, always passes).
    AddInfo(FString::Printf(
        TEXT("%s: submitted %d requests in %.3f ms (%.2f \u03bcs/req)"),
        *Label, NumRequests, SubmissionMs, PerRequestUs));
}

// ---------------------------------------------------------------------------

void FLootLockerHTTPPerformanceBenchmark::Define()
{
    Describe("HTTP Submission Throughput Benchmark (no backend required)", [this]()
    {
        It("Baseline: 100 concurrent submissions", [this]()
        {
            RunBenchmark(100, TEXT("Baseline_100"));
        });

        It("Baseline: 500 concurrent submissions", [this]()
        {
            RunBenchmark(500, TEXT("Baseline_500"));
        });

        It("Baseline: 1000 concurrent submissions", [this]()
        {
            RunBenchmark(1000, TEXT("Baseline_1000"));
        });
    });
}

#endif // ENGINE_MAJOR_VERSION > 4
