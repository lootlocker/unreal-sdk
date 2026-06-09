// Copyright (c) LootLocker. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

/**
 * Editor-only utility that checks GitHub Releases for a newer LootLocker SDK version
 * and shows a non-blocking notification window when one is available.
 *
 * Call Initialize() from StartupModule() and Shutdown() from ShutdownModule().
 * The automatic check fires once after a 180-second startup delay, then at most once
 * every 24 hours. Silence and skip preferences are persisted via GConfig.
 */
class FLootLockerUpdateChecker
{
public:
    /** Called from StartupModule — registers the delayed startup ticker. */
    static void Initialize();

    /** Called from ShutdownModule — removes the ticker handle. */
    static void Shutdown();

    /** Manual check triggered from the Tools menu. Bypasses throttle and silence settings. */
    static void ManualCheck();

    // Called by SLootLockerUpdateNotification button handlers
    static void SetNeverNotify(bool bValue);
    static void SetSkippedVersion(const FString& Version);
    static void SetRemindAfterTime(const FDateTime& Time);

private:
    static bool OnStartupTick(float DeltaTime);

    static void CheckForUpdate(bool bManual);

    /** Returns true if the automatic check should proceed (throttle + silence guards). */
    static bool ShouldCheck();

    /** Returns true if the notification window should be shown for LatestVersion. */
    static bool ShouldNotify(const FString& LatestVersion);

    static void FetchLatestRelease(bool bManual);

    static void OnResponseReceived(
        FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, bool bManual);

    static void ShowUpdateNotification(
        const FString& LatestVersion, const FString& ReleaseUrl);

    static void ShowUpToDateNotification();

    /** Numeric semver comparison — returns true if RemoteVersion is strictly newer than LocalVersion. */
    static bool IsVersionNewer(const FString& RemoteVersion, const FString& LocalVersion);

    /** Reads the current SDK version from the plugin descriptor. */
    static FString GetCurrentVersion();

    // --- Config helpers (GEditorPerProjectIni) ---
    static bool GetNeverNotify();
    static FString GetSkippedVersion();
    static FDateTime GetRemindAfterTime();
    static FDateTime GetLastCheckedTime();
    static void SaveLastCheckedTime(const FDateTime& Time);

    static FTSTicker::FDelegateHandle TickerHandle;

    static constexpr float StartupDelaySeconds = 180.0f;
    static constexpr double CheckIntervalHours = 24.0;
    static const TCHAR* ConfigSection;
    static const TCHAR* GitHubReleasesUrl;
};
