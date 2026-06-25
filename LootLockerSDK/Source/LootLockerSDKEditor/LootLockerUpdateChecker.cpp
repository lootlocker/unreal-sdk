// Copyright (c) LootLocker. All Rights Reserved.
#include "LootLockerUpdateChecker.h"
#include "SLootLockerUpdateNotification.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/DateTime.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/App.h"
#include "Containers/Ticker.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "HAL/PlatformProcess.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogLootLockerSDKEditor, Log, All);

// --- Static member definitions ---
FTSTicker::FDelegateHandle FLootLockerUpdateChecker::TickerHandle;
const TCHAR* FLootLockerUpdateChecker::ConfigSection = TEXT("/Script/LootLockerSDKEditor.UpdateChecker");
const TCHAR* FLootLockerUpdateChecker::GitHubReleasesUrl =
    TEXT("https://api.github.com/repos/lootlocker/unreal-sdk/releases/latest");

// ---------------------------------------------------------------------------

void FLootLockerUpdateChecker::Initialize()
{
    // Fire once after StartupDelaySeconds — return false in the callback to auto-unregister.
    TickerHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateStatic(&FLootLockerUpdateChecker::OnStartupTick),
        StartupDelaySeconds
    );
}

void FLootLockerUpdateChecker::Shutdown()
{
    if (TickerHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
        TickerHandle.Reset();
    }
}

void FLootLockerUpdateChecker::ManualCheck()
{
    CheckForUpdate(/*bManual=*/true);
}

bool FLootLockerUpdateChecker::OnStartupTick(float DeltaTime)
{
    CheckForUpdate(/*bManual=*/false);
    return false;  // one-shot — unregister immediately
}

void FLootLockerUpdateChecker::CheckForUpdate(bool bManual)
{
    if (!bManual && !ShouldCheck())
    {
        return;
    }
    FetchLatestRelease(bManual);
}

bool FLootLockerUpdateChecker::ShouldCheck()
{
    if (GetNeverNotify())
    {
        return false;
    }

    const FDateTime RemindAfter = GetRemindAfterTime();
    if (FDateTime::UtcNow() < RemindAfter)
    {
        return false;
    }

    const FDateTime LastChecked = GetLastCheckedTime();
    const FTimespan TimeSinceLastCheck = FDateTime::UtcNow() - LastChecked;
    if (TimeSinceLastCheck.GetTotalHours() < CheckIntervalHours)
    {
        return false;
    }

    return true;
}

bool FLootLockerUpdateChecker::ShouldNotify(const FString& LatestVersion)
{
    return GetSkippedVersion() != LatestVersion;
}

void FLootLockerUpdateChecker::FetchLatestRelease(bool bManual)
{
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(GitHubReleasesUrl);
    Request->SetVerb(TEXT("GET"));
    Request->SetHeader(TEXT("Accept"), TEXT("application/vnd.github.v3+json"));
    Request->SetHeader(TEXT("User-Agent"), TEXT("LootLockerSDK-UnrealEditor"));

    // Capture bManual by value in the lambda binding
    Request->OnProcessRequestComplete().BindLambda(
        [bManual](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bWasSuccessful)
        {
            FLootLockerUpdateChecker::OnResponseReceived(Req, Resp, bWasSuccessful, bManual);
        }
    );

    Request->ProcessRequest();
}

void FLootLockerUpdateChecker::OnResponseReceived(
    FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, bool bManual)
{
    if (!bWasSuccessful || !Response.IsValid() || Response->GetResponseCode() != 200)
    {
        if (bManual)
        {
            FNotificationInfo Info(FText::FromString(
                TEXT("LootLocker: Could not reach GitHub to check for updates.")));
            Info.ExpireDuration = 5.0f;
            Info.bFireAndForget = true;
            FSlateNotificationManager::Get().AddNotification(Info);
        }
        return;
    }

    TSharedPtr<FJsonObject> JsonObject;
    const TSharedRef<TJsonReader<>> Reader =
        TJsonReaderFactory<>::Create(Response->GetContentAsString());

    if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
    {
        UE_LOG(LogLootLockerSDKEditor, Warning, TEXT("LootLocker update check: failed to parse GitHub response."));
        return;
    }

    FString TagName;
    FString HtmlUrl;
    if (!JsonObject->TryGetStringField(TEXT("tag_name"), TagName) ||
        !JsonObject->TryGetStringField(TEXT("html_url"), HtmlUrl))
    {
        UE_LOG(LogLootLockerSDKEditor, Warning,
            TEXT("LootLocker update check: GitHub response is missing expected fields."));
        return;
    }

    // Strip leading 'v' or 'V'
    if (TagName.StartsWith(TEXT("v")) || TagName.StartsWith(TEXT("V")))
    {
        TagName.RightChopInline(1);
    }

    // Strip any pre-release suffix (e.g. "10.5.0-beta.1" → "10.5.0")
    int32 DashIndex;
    if (TagName.FindChar(TEXT('-'), DashIndex))
    {
        TagName = TagName.Left(DashIndex);
    }
    int32 PlusIndex;
    if (TagName.FindChar(TEXT('+'), PlusIndex))
    {
        TagName = TagName.Left(PlusIndex);
    }

    SaveLastCheckedTime(FDateTime::UtcNow());

    if (IsVersionNewer(TagName, GetCurrentVersion()))
    {
        if (bManual || ShouldNotify(TagName))
        {
            ShowUpdateNotification(TagName, HtmlUrl);
        }
    }
    else if (bManual)
    {
        ShowUpToDateNotification();
    }
}

void FLootLockerUpdateChecker::ShowUpdateNotification(
    const FString& LatestVersion, const FString& ReleaseUrl)
{
    if (!FSlateApplication::IsInitialized())
    {
        return;
    }

    const TSharedRef<SWindow> Window = SNew(SWindow)
        .Title(FText::FromString(TEXT("LootLocker SDK Update Available")))
        .ClientSize(FVector2D(560.0f, 210.0f))
        .SupportsMinimize(false)
        .SupportsMaximize(false)
        .IsTopmostWindow(false)
        .SizingRule(ESizingRule::FixedSize);

    Window->SetContent(
        SNew(SLootLockerUpdateNotification)
            .CurrentVersion(GetCurrentVersion())
            .LatestVersion(LatestVersion)
            .ReleaseUrl(ReleaseUrl)
            .ParentWindow(Window)
    );

    FSlateApplication::Get().AddWindow(Window);
}

void FLootLockerUpdateChecker::ShowUpToDateNotification()
{
    FNotificationInfo Info(FText::FromString(
        TEXT("LootLocker SDK is up to date!")));
    Info.ExpireDuration = 5.0f;
    Info.bFireAndForget = true;
    FSlateNotificationManager::Get().AddNotification(Info);
}

bool FLootLockerUpdateChecker::IsVersionNewer(const FString& RemoteVersion, const FString& LocalVersion)
{
    TArray<FString> RemoteParts, LocalParts;
    RemoteVersion.ParseIntoArray(RemoteParts, TEXT("."));
    LocalVersion.ParseIntoArray(LocalParts, TEXT("."));

    const int32 MaxParts = FMath::Max(RemoteParts.Num(), LocalParts.Num());
    for (int32 i = 0; i < MaxParts; ++i)
    {
        const int32 Remote = (i < RemoteParts.Num()) ? FCString::Atoi(*RemoteParts[i]) : 0;
        const int32 Local  = (i < LocalParts.Num())  ? FCString::Atoi(*LocalParts[i])  : 0;
        if (Remote > Local) return true;
        if (Remote < Local) return false;
    }
    return false;  // equal
}

FString FLootLockerUpdateChecker::GetCurrentVersion()
{
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("LootLockerSDK"));
    if (Plugin.IsValid())
    {
        return Plugin->GetDescriptor().VersionName;
    }
    return TEXT("0.0.0");
}

// --- Config helpers ---

bool FLootLockerUpdateChecker::GetNeverNotify()
{
    bool bValue = false;
    GConfig->GetBool(ConfigSection, TEXT("NeverNotify"), bValue, GEditorPerProjectIni);
    return bValue;
}

void FLootLockerUpdateChecker::SetNeverNotify(bool bValue)
{
    GConfig->SetBool(ConfigSection, TEXT("NeverNotify"), bValue, GEditorPerProjectIni);
    GConfig->Flush(false, GEditorPerProjectIni);
}

FString FLootLockerUpdateChecker::GetSkippedVersion()
{
    FString Value;
    GConfig->GetString(ConfigSection, TEXT("SkippedVersion"), Value, GEditorPerProjectIni);
    return Value;
}

void FLootLockerUpdateChecker::SetSkippedVersion(const FString& Version)
{
    GConfig->SetString(ConfigSection, TEXT("SkippedVersion"), *Version, GEditorPerProjectIni);
    GConfig->Flush(false, GEditorPerProjectIni);
}

FDateTime FLootLockerUpdateChecker::GetRemindAfterTime()
{
    FString Value;
    GConfig->GetString(ConfigSection, TEXT("RemindAfterUtc"), Value, GEditorPerProjectIni);
    FDateTime Result;
    if (FDateTime::ParseIso8601(*Value, Result))
    {
        return Result;
    }
    return FDateTime::MinValue();
}

void FLootLockerUpdateChecker::SetRemindAfterTime(const FDateTime& Time)
{
    GConfig->SetString(ConfigSection, TEXT("RemindAfterUtc"), *Time.ToIso8601(), GEditorPerProjectIni);
    GConfig->Flush(false, GEditorPerProjectIni);
}

FDateTime FLootLockerUpdateChecker::GetLastCheckedTime()
{
    FString Value;
    GConfig->GetString(ConfigSection, TEXT("LastCheckedUtc"), Value, GEditorPerProjectIni);
    FDateTime Result;
    if (FDateTime::ParseIso8601(*Value, Result))
    {
        return Result;
    }
    return FDateTime::MinValue();
}

void FLootLockerUpdateChecker::SaveLastCheckedTime(const FDateTime& Time)
{
    GConfig->SetString(ConfigSection, TEXT("LastCheckedUtc"), *Time.ToIso8601(), GEditorPerProjectIni);
    GConfig->Flush(false, GEditorPerProjectIni);
}
