// Copyright (c) 2021 LootLocker

#include "LootLockerHTTPExecutionQueue.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IPluginManager.h"
#include "JsonObjectConverter.h"
#include "LootLockerConfig.h"
#include "LootLockerHttpClient.h"
#include "LootLockerLogger.h"
#include "LootLockerPlayerData.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerResponse.h"
#include "LootLockerStateData.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"
#include "Runtime/Launch/Resources/Version.h"

// -------------------------------------------------------------------------
// Static member definitions
// -------------------------------------------------------------------------

TUniquePtr<FLootLockerHTTPExecutionQueue> FLootLockerHTTPExecutionQueue::Instance;

FString            FLootLockerHTTPExecutionQueue::SDKVersion            = TEXT("");
const FString      FLootLockerHTTPExecutionQueue::UserAgent             = FString::Format(TEXT("X-UnrealEngine-Agent/{0}"), { ENGINE_VERSION_STRING });
const FString      FLootLockerHTTPExecutionQueue::UserInstanceIdentifier = FGuid::NewGuid().ToString();

// -------------------------------------------------------------------------
// Singleton lifecycle
// -------------------------------------------------------------------------

FLootLockerHTTPExecutionQueue& FLootLockerHTTPExecutionQueue::Get()
{
    if (!Instance.IsValid())
    {
        Initialize();
    }
    return *Instance;
}

void FLootLockerHTTPExecutionQueue::Initialize()
{
    if (Instance.IsValid())
    {
        return;
    }
    Instance = MakeUnique<FLootLockerHTTPExecutionQueue>();
    Instance->RateLimiter = MakeUnique<FLootLockerRateLimiter>();
    Instance->bIsInitialized = true;
    Instance->StartTicker();
}

bool FLootLockerHTTPExecutionQueue::IsInitialized()
{
    return Instance.IsValid() && Instance->bIsInitialized;
}

void FLootLockerHTTPExecutionQueue::Shutdown()
{
    if (!Instance.IsValid())
    {
        return;
    }

    Instance->StopTicker();
    Instance->bIsInitialized = false;

    const FLootLockerResponse ShutdownError = LootLockerResponseFactory::Error<FLootLockerResponse>(
        TEXT("SDK is shutting down — request aborted"),
        LootLockerStaticRequestErrorStatusCodes::LL_UNDEFINED_BEHAVIOUR_ERROR);

    for (auto& Pair : Instance->ExecutionQueue)
    {
        FLootLockerHTTPExecutionQueueItem& Item = *Pair.Value;
        Item.AbortRequest();
        if (!Item.RequestData.HaveListenersBeenInvoked)
        {
            Item.RequestData.CallListenersWithResult(ShutdownError);
        }
    }

    Instance->ExecutionQueue.Empty();
    Instance->OngoingRequestIds.Empty();
    Instance->CompletedRequestIds.Empty();
    Instance->RefreshNeededIds.Empty();
    Instance.Reset();
}

// -------------------------------------------------------------------------
// Public API
// -------------------------------------------------------------------------

void FLootLockerHTTPExecutionQueue::ScheduleRequest(const FLootLockerHTTPRequestData& Request)
{
    // Check for queue capacity
    if (Configuration.DenyIncomingRequestsWhenBackedUp &&
        ExecutionQueue.Num() >= Configuration.MaxQueueSize)
    {
        const FString ErrorMessage = FString::Printf(
            TEXT("Request was denied because the queue has reached its maximum size (%d)"),
            Configuration.MaxQueueSize);
#if WITH_EDITOR
        if (Configuration.LogQueueRejections)
        {
            FLootLockerLogger::LogWarning(FString::Printf(
                TEXT("HTTP queue full: %d/%d requests queued"),
                ExecutionQueue.Num(), Configuration.MaxQueueSize));
        }
#endif
        FLootLockerHTTPRequestData MutableRequest = Request;
        FLootLockerResponse QueueFullResponse = LootLockerResponseFactory::Error<FLootLockerResponse>(
            ErrorMessage, 0, Request.ForPlayerUlid);
        QueueFullResponse.Context.RequestId                   = Request.RequestId;
        QueueFullResponse.Context.RequestURL                  = Request.Endpoint;
        QueueFullResponse.Context.RequestMethod               = Request.Verb;
        QueueFullResponse.Context.RequestParametersJsonString = Request.Body;
        QueueFullResponse.Context.RequestTime                 = Request.RequestStartDateTime.ToString();
        FLootLockerLogger::LogHttpRequest(QueueFullResponse, TEXT("N/A"));
        MutableRequest.CallListenersWithResult(QueueFullResponse);
        return;
    }

    // Check for choke threshold
    const int32 PendingCount = ExecutionQueue.Num() - static_cast<int32>(OngoingRequestIds.Num());
    if (Configuration.DenyIncomingRequestsWhenBackedUp &&
        PendingCount > Configuration.ChokeWarningThreshold)
    {
        const FString ErrorMessage = FString::Printf(
            TEXT("Request was denied because there are currently too many unsent requests in queue (%d queued, threshold: %d)"),
            PendingCount, Configuration.ChokeWarningThreshold);
#if WITH_EDITOR
        if (Configuration.LogQueueRejections)
        {
            FLootLockerLogger::LogWarning(FString::Printf(
                TEXT("HTTP queue backed up: %d requests queued"), PendingCount));
        }
#endif
        FLootLockerHTTPRequestData MutableRequest = Request;
        FLootLockerResponse ChokeResponse = LootLockerResponseFactory::Error<FLootLockerResponse>(
            ErrorMessage, 0, Request.ForPlayerUlid);
        ChokeResponse.Context.RequestId                   = Request.RequestId;
        ChokeResponse.Context.RequestURL                  = Request.Endpoint;
        ChokeResponse.Context.RequestMethod               = Request.Verb;
        ChokeResponse.Context.RequestParametersJsonString = Request.Body;
        ChokeResponse.Context.RequestTime                 = Request.RequestStartDateTime.ToString();
        FLootLockerLogger::LogHttpRequest(ChokeResponse, TEXT("N/A"));
        MutableRequest.CallListenersWithResult(ChokeResponse);
        return;
    }

    // Deduplicate: merge listeners into existing item if same RequestId
    if (TSharedPtr<FLootLockerHTTPExecutionQueueItem>* ExistingItem = ExecutionQueue.Find(Request.RequestId))
    {
        // Guard: if the existing item has already delivered its response, its
        // listeners are stale — replace the item so the new request gets a fresh dispatch.
        if ((*ExistingItem)->RequestData.HaveListenersBeenInvoked)
        {
            TSharedPtr<FLootLockerHTTPExecutionQueueItem> NewItem = MakeShared<FLootLockerHTTPExecutionQueueItem>();
            NewItem->RequestData = Request;
            ExecutionQueue[Request.RequestId] = NewItem;
            return;
        }
        for (const FResponseCallback& Listener : Request.Listeners)
        {
            (*ExistingItem)->RequestData.Listeners.Add(Listener);
        }
        return;
    }

    // Enqueue new item
    TSharedPtr<FLootLockerHTTPExecutionQueueItem> NewItem = MakeShared<FLootLockerHTTPExecutionQueueItem>();
    NewItem->RequestData = Request;
    ExecutionQueue.Add(Request.RequestId, NewItem);
}

void FLootLockerHTTPExecutionQueue::OverrideConfiguration(
    const FLootLockerHTTPClientConfiguration& NewConfig)
{
    Configuration = NewConfig;
}

// -------------------------------------------------------------------------
// Ticker
// -------------------------------------------------------------------------

void FLootLockerHTTPExecutionQueue::StartTicker()
{
    TickerHandle =
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
        FTSTicker::GetCoreTicker()
#else
        FTicker::GetCoreTicker()
#endif
        .AddTicker(FTickerDelegate::CreateRaw(this, &FLootLockerHTTPExecutionQueue::Tick));
}

void FLootLockerHTTPExecutionQueue::StopTicker()
{
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3)
    FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
#else
    FTicker::GetCoreTicker().RemoveTicker(TickerHandle);
#endif
    TickerHandle.Reset();
}

bool FLootLockerHTTPExecutionQueue::Tick(float DeltaTime)
{
    if (!bIsInitialized)
    {
        return false;
    }

    // ---- Phase 1: Update — process each item in the queue ----

    for (auto& Pair : ExecutionQueue)
    {
        FLootLockerHTTPExecutionQueueItem& Item = *Pair.Value;

        if (Item.bDone)
        {
            if (!CompletedRequestIds.Contains(Item.RequestData.RequestId))
            {
                CompletedRequestIds.Add(Item.RequestData.RequestId);
            }
            continue;
        }

        if (Item.bIsWaitingForSessionRefresh)
        {
            continue;
        }

        if (!Item.HttpRequest.IsValid())
        {
            // Not yet dispatched — check if we should send now
            if (Item.RetryAfter != FDateTime(0) && Item.RetryAfter > FDateTime::UtcNow())
            {
                // Still waiting for the retry-after delay
                continue;
            }
            if (static_cast<int32>(OngoingRequestIds.Num()) >= Configuration.MaxOngoingRequests)
            {
                // Too many in-flight requests; hold until one completes
                continue;
            }
            CreateAndSendRequest(Item);
            continue;
        }

        // In-flight: poll for completion
        const ELootLockerHTTPExecutionQueueProcessingResult Result = ProcessOngoingRequest(Item);

        if (Result == ELootLockerHTTPExecutionQueueProcessingResult::NeedsSessionRefresh)
        {
            RefreshNeededIds.AddUnique(Item.RequestData.RequestId);
            continue;
        }
        if (Result == ELootLockerHTTPExecutionQueueProcessingResult::WaitForNextTick ||
            Result == ELootLockerHTTPExecutionQueueProcessingResult::None)
        {
            continue;
        }

        HandleRequestResult(Item, Result);
    }

    // Bulk session refresh
    for (const FString& RequestId : RefreshNeededIds)
    {
        TSharedPtr<FLootLockerHTTPExecutionQueueItem>* ItemPtr = ExecutionQueue.Find(RequestId);
        if (!ItemPtr || !(*ItemPtr).IsValid())
        {
            continue;
        }
        FLootLockerHTTPExecutionQueueItem& Item = **ItemPtr;
        if (Item.bIsWaitingForSessionRefresh)
        {
            continue;
        }
        OngoingRequestIds.Remove(RequestId);
        Item.bIsWaitingForSessionRefresh = true;
        Item.RequestData.TimesRetried++;
        Item.AbortRequest();
        DispatchSessionRefreshForItem(RequestId);
    }
    RefreshNeededIds.Empty();

    // Choke warning (throttled to avoid flooding the log)
    const int32 PendingCount = ExecutionQueue.Num() - static_cast<int32>(OngoingRequestIds.Num());
#if WITH_EDITOR
    if (PendingCount > Configuration.ChokeWarningThreshold && Configuration.LogQueueRejections)
    {
        const double Now = FPlatformTime::Seconds();
        if ((Now - LastChokeWarningLogTime) >= Configuration.ChokeWarningLogIntervalSeconds)
        {
            FLootLockerLogger::LogWarning(FString::Printf(
                TEXT("HTTP Execution Queue is overloaded. Requests currently waiting for execution: '%d'"),
                PendingCount));
            LastChokeWarningLogTime = Now;
        }
    }
#endif

    // ---- Phase 2: LateUpdate — invoke listeners and remove completed items ----

    for (const FString& CompletedId : CompletedRequestIds)
    {
        TSharedPtr<FLootLockerHTTPExecutionQueueItem>* ItemPtr = ExecutionQueue.Find(CompletedId);
        if (!ItemPtr || !(*ItemPtr).IsValid())
        {
            continue;
        }
        // Keep a local TSharedPtr so the item stays alive after ExecutionQueue.Remove().
        TSharedPtr<FLootLockerHTTPExecutionQueueItem> LiveItem = *ItemPtr;
        FLootLockerHTTPExecutionQueueItem& Item = *LiveItem;
        if (!Item.bDone)
        {
            continue;
        }
        Item.AbortRequest();
        ExecutionQueue.Remove(CompletedId);
        OngoingRequestIds.Remove(CompletedId);
        if (!Item.RequestData.HaveListenersBeenInvoked)
        {
            if (Configuration.SlowListenerWarningThresholdMs > 0.0f)
            {
                const double ListenerStartTime = FPlatformTime::Seconds();
                Item.RequestData.CallListenersWithResult(Item.Response);
                const double ElapsedMs = (FPlatformTime::Seconds() - ListenerStartTime) * 1000.0;
                if (ElapsedMs > static_cast<double>(Configuration.SlowListenerWarningThresholdMs))
                {
                    FLootLockerLogger::LogWarning(FString::Printf(
                        TEXT("Response listener for request %s took %.1f ms on the game thread "
                             "(threshold: %.0f ms). Avoid heavy work inside SDK callbacks — "
                             "consider dispatching to a background task instead."),
                        *CompletedId, ElapsedMs,
                        static_cast<double>(Configuration.SlowListenerWarningThresholdMs)));
                }
            }
            else
            {
                Item.RequestData.CallListenersWithResult(Item.Response);
            }
        }
    }
    CompletedRequestIds.Empty();

    // Collect stragglers — done items not yet tracked in CompletedRequestIds
    for (auto& Pair : ExecutionQueue)
    {
        if (Pair.Value->bDone)
        {
            CompletedRequestIds.AddUnique(Pair.Key);
        }
    }

    // Clean up OngoingRequestIds entries whose queue items have already been removed
    TArray<FString> StaleOngoing;
    for (const FString& OngoingId : OngoingRequestIds)
    {
        if (!ExecutionQueue.Contains(OngoingId))
        {
            StaleOngoing.Add(OngoingId);
        }
    }
    for (const FString& StaleId : StaleOngoing)
    {
        OngoingRequestIds.Remove(StaleId);
    }

    return true;
}

// -------------------------------------------------------------------------
// Private helpers
// -------------------------------------------------------------------------

bool FLootLockerHTTPExecutionQueue::CreateAndSendRequest(FLootLockerHTTPExecutionQueueItem& Item)
{
    // Rate limiting (optional — if no limiter is set, requests proceed freely)
    if (RateLimiter.IsValid() && RateLimiter->AddRequestAndCheckIfRateLimitHit())
    {
        const FString RateLimitMsg = FString::Printf(
            TEXT("Request to %s was rate limited. Try again in %d seconds."),
            *Item.RequestData.Endpoint,
            RateLimiter->GetSecondsLeftOfRateLimit());
        FLootLockerResponse RateLimitedResponse = LootLockerResponseFactory::Error<FLootLockerResponse>(
            RateLimitMsg, 429, Item.RequestData.ForPlayerUlid);
        RateLimitedResponse.Context.RequestId                   = Item.RequestData.RequestId;
        RateLimitedResponse.Context.RequestURL                  = Item.RequestData.Endpoint;
        RateLimitedResponse.Context.RequestMethod               = Item.RequestData.Verb;
        RateLimitedResponse.Context.RequestParametersJsonString = Item.RequestData.Body;
        RateLimitedResponse.Context.RequestTime                 = Item.RequestData.RequestStartDateTime.ToString();
        FLootLockerLogger::LogHttpRequest(RateLimitedResponse, TEXT("N/A"));
        MarkItemDone(Item, RateLimitedResponse);
        return false;
    }

    // Resolve SDK version lazily (mirrors ULootLockerHttpClient::SendApi)
    if (SDKVersion.IsEmpty())
    {
        const TSharedPtr<IPlugin> Ptr = IPluginManager::Get().FindPlugin(TEXT("LootLockerSDK"));
        if (Ptr.IsValid())
        {
            SDKVersion = Ptr->GetDescriptor().VersionName;
        }
    }

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
        FHttpModule::Get().CreateRequest();
    Request->SetURL(Item.RequestData.Endpoint);
    Request->SetVerb(Item.RequestData.Verb);

    // Standard SDK headers
    if (!Item.RequestData.PlayerData.Token.IsEmpty())
    {
        Request->SetHeader(TEXT("x-session-token"), Item.RequestData.PlayerData.Token);
    }
    Request->SetHeader(TEXT("User-Agent"),              UserAgent);
    Request->SetHeader(TEXT("LL-Instance-Identifier"), UserInstanceIdentifier);
    Request->SetHeader(TEXT("LL-SDK-Version"),         SDKVersion);
    Request->SetHeader(TEXT("LL-Request-Id"),          Item.RequestData.RequestId);

    if (Item.RequestData.TimesRetried > 0)
    {
        Request->SetHeader(TEXT("LL-Retry-Attempt"),
            FString::FromInt(Item.RequestData.TimesRetried));
    }

    // Per-request extra headers
    for (const TTuple<FString, FString>& Header : Item.RequestData.ExtraHeaders)
    {
        Request->SetHeader(Header.Key, Header.Value);
    }

    if (!Item.RequestData.bIsFileUpload)
    {
        Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
        Request->SetHeader(TEXT("Accept"),       TEXT("application/json"));
        Request->SetContentAsString(Item.RequestData.Body);
    }
    else
    {
        const FString Boundary = TEXT("lootlockerboundary");
        Request->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=") + Boundary);

        // Resolve the filename before allocating any body buffers
        int32 LastSlash = INDEX_NONE;
        if (!Item.RequestData.FilePath.FindLastChar('/', LastSlash))
        {
            Item.RequestData.FilePath.FindLastChar('\\', LastSlash);
        }
        const FString FileName = Item.RequestData.FilePath.RightChop(LastSlash + 1);

        // Load the file early so we can bail out before allocating the rest of the body
        TArray<uint8> FileData;
        if (!FFileHelper::LoadFileToArray(FileData, *Item.RequestData.FilePath))
        {
            FLootLockerResponse FileReadError = LootLockerResponseFactory::Error<FLootLockerResponse>(
                FString::Printf(TEXT("Failed to read file for upload: %s"), *Item.RequestData.FilePath),
                LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_HTTP,
                Item.RequestData.ForPlayerUlid);
            FileReadError.Context.RequestId     = Item.RequestData.RequestId;
            FileReadError.Context.RequestURL    = Item.RequestData.Endpoint;
            FileReadError.Context.RequestMethod = Item.RequestData.Verb;
            FileReadError.Context.RequestTime   = Item.RequestData.RequestStartDateTime.ToString();
            FLootLockerLogger::LogHttpRequest(FileReadError, TEXT("N/A"));
            MarkItemDone(Item, FileReadError);
            return false;
        }

        TArray<uint8> BodyData;
        const FString BeginBoundary = TEXT("\r\n--") + Boundary + TEXT("\r\n");
        const FString EndBoundary   = TEXT("\r\n--") + Boundary + TEXT("--\r\n");

        for (const auto& KV : Item.RequestData.AdditionalFields)
        {
            const auto BeginBoundaryAnsi = StringCast<ANSICHAR>(*BeginBoundary);
            BodyData.Append(reinterpret_cast<const uint8*>(BeginBoundaryAnsi.Get()), BeginBoundaryAnsi.Length());
            FString ParameterEntry = TEXT("Content-Type: text/plain; charset=\"utf-8\"\r\n");
            ParameterEntry        += TEXT("Content-Disposition: form-data; name=\"") + KV.Key + TEXT("\"\r\n\r\n") + KV.Value;
            const auto ParameterEntryAnsi = StringCast<ANSICHAR>(*ParameterEntry);
            BodyData.Append(reinterpret_cast<const uint8*>(ParameterEntryAnsi.Get()), ParameterEntryAnsi.Length());
        }

        const auto BeginBoundaryAnsi = StringCast<ANSICHAR>(*BeginBoundary);
        BodyData.Append(reinterpret_cast<const uint8*>(BeginBoundaryAnsi.Get()), BeginBoundaryAnsi.Length());

        FString FileHeader  = TEXT("Content-Type: application/octet-stream\r\n");
        FileHeader         += TEXT("Content-disposition: form-data; name=\"file\"; filename=\"") + FileName + TEXT("\"\r\n\r\n");
        const auto FileHeaderAnsi = StringCast<ANSICHAR>(*FileHeader);
        BodyData.Append(reinterpret_cast<const uint8*>(FileHeaderAnsi.Get()), FileHeaderAnsi.Length());

        BodyData.Append(FileData);

        const auto EndBoundaryAnsi = StringCast<ANSICHAR>(*EndBoundary);
        BodyData.Append(reinterpret_cast<const uint8*>(EndBoundaryAnsi.Get()), EndBoundaryAnsi.Length());

        Request->SetContent(BodyData);
    }

    Item.RequestStartTime = FPlatformTime::Seconds();
    Item.HttpRequest = Request;
    OngoingRequestIds.Add(Item.RequestData.RequestId);

    Request->ProcessRequest();
    return true;
}

ELootLockerHTTPExecutionQueueProcessingResult
FLootLockerHTTPExecutionQueue::ProcessOngoingRequest(FLootLockerHTTPExecutionQueueItem& Item)
{
    if (!Item.HttpRequest.IsValid())
    {
        return ELootLockerHTTPExecutionQueueProcessingResult::WaitForNextTick;
    }

    const EHttpRequestStatus::Type Status = Item.HttpRequest->GetStatus();

    if (Status == EHttpRequestStatus::Processing ||
        Status == EHttpRequestStatus::NotStarted)
    {
        // Check for client-side timeout
        constexpr double DefaultTimeoutSeconds = 300.0;
        const double TimeoutSeconds = (Configuration.RequestTimeoutSeconds > 0)
            ? static_cast<double>(Configuration.RequestTimeoutSeconds)
            : DefaultTimeoutSeconds;
        if ((FPlatformTime::Seconds() - Item.RequestStartTime) >= TimeoutSeconds)
        {
            return ELootLockerHTTPExecutionQueueProcessingResult::Completed_TimedOut;
        }
        return ELootLockerHTTPExecutionQueueProcessingResult::WaitForNextTick;
    }

    // Request has finished (Succeeded, Failed, or Failed_ConnectionError)
    const FHttpResponsePtr Response = Item.HttpRequest->GetResponse();

    if (Status == EHttpRequestStatus::Succeeded && Response.IsValid())
    {
        const int32 StatusCode = Response->GetResponseCode();

        FLootLockerResponse LLResponse;
        LLResponse.StatusCode                        = StatusCode;
        LLResponse.FullTextFromServer                = Response->GetContentAsString();
        LLResponse.Context.PlayerUlid               = Item.RequestData.ForPlayerUlid;
        LLResponse.Context.RequestId                = Item.RequestData.RequestId;
        LLResponse.Context.RequestURL               = Item.RequestData.Endpoint;
        LLResponse.Context.RequestMethod            = Item.RequestData.Verb;
        LLResponse.Context.RequestParametersJsonString = Item.RequestData.Body;
        LLResponse.Context.RequestTime              = Item.RequestData.RequestStartDateTime.ToString();

        if (EHttpResponseCodes::IsOk(StatusCode))
        {
            LLResponse.success = true;
            Item.Response = LLResponse;
            return ELootLockerHTTPExecutionQueueProcessingResult::Completed_Success;
        }

        // Failure path
        LLResponse.success = false;
        FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerErrorData>(
            LLResponse.FullTextFromServer, &LLResponse.ErrorData, 0, 0);
        const FString RetryAfterHeader = Response->GetHeader(TEXT("retry-after"));
        if (!RetryAfterHeader.IsEmpty())
        {
            LLResponse.ErrorData.Retry_after_seconds = FCString::Atoi(*RetryAfterHeader);
        }
        Item.Response = LLResponse;

        if (ShouldRefreshSession(StatusCode, Item.RequestData.PlayerData,
                                 Item.RequestData.TimesRetried))
        {
            return ELootLockerHTTPExecutionQueueProcessingResult::NeedsSessionRefresh;
        }
        if (ShouldRetryRequest(StatusCode, Item.RequestData.TimesRetried))
        {
            return ELootLockerHTTPExecutionQueueProcessingResult::ShouldBeRetried;
        }
        return ELootLockerHTTPExecutionQueueProcessingResult::Completed_Failed;
    }

    // Connection error or invalid response
    FLootLockerResponse ErrorResponse = LootLockerResponseFactory::Error<FLootLockerResponse>(
        TEXT("HTTP request failed — connection error"),
        LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_HTTP,
        Item.RequestData.ForPlayerUlid);
    ErrorResponse.Context.RequestId                    = Item.RequestData.RequestId;
    ErrorResponse.Context.RequestURL                   = Item.RequestData.Endpoint;
    ErrorResponse.Context.RequestMethod                = Item.RequestData.Verb;
    ErrorResponse.Context.RequestParametersJsonString  = Item.RequestData.Body;
    ErrorResponse.Context.RequestTime                  = Item.RequestData.RequestStartDateTime.ToString();
    Item.Response = ErrorResponse;

    if (ShouldRetryRequest(0, Item.RequestData.TimesRetried))
    {
        return ELootLockerHTTPExecutionQueueProcessingResult::ShouldBeRetried;
    }
    return ELootLockerHTTPExecutionQueueProcessingResult::Completed_Failed;
}


void FLootLockerHTTPExecutionQueue::HandleRequestResult(
    FLootLockerHTTPExecutionQueueItem& Item,
    ELootLockerHTTPExecutionQueueProcessingResult Result)
{
    switch (Result)
    {
        case ELootLockerHTTPExecutionQueueProcessingResult::None:
        case ELootLockerHTTPExecutionQueueProcessingResult::WaitForNextTick:
        case ELootLockerHTTPExecutionQueueProcessingResult::NeedsSessionRefresh:
        default:
            return;

        case ELootLockerHTTPExecutionQueueProcessingResult::Completed_Success:
        case ELootLockerHTTPExecutionQueueProcessingResult::Completed_Failed:
        {
            CompleteItem(Item, Item.Response);
            break;
        }

        case ELootLockerHTTPExecutionQueueProcessingResult::Completed_TimedOut:
        {
            FLootLockerResponse TimeoutResponse = LootLockerResponseFactory::Error<FLootLockerResponse>(
                TEXT("Request timed out"),
                LootLockerStaticRequestErrorStatusCodes::LL_ERROR_REQUEST_TIMED_OUT,
                Item.RequestData.ForPlayerUlid);
            TimeoutResponse.Context.RequestId                   = Item.RequestData.RequestId;
            TimeoutResponse.Context.RequestURL                  = Item.RequestData.Endpoint;
            TimeoutResponse.Context.RequestMethod               = Item.RequestData.Verb;
            TimeoutResponse.Context.RequestParametersJsonString = Item.RequestData.Body;
            TimeoutResponse.Context.RequestTime                 = Item.RequestData.RequestStartDateTime.ToString();
            CompleteItem(Item, TimeoutResponse);
            break;
        }

        case ELootLockerHTTPExecutionQueueProcessingResult::ShouldBeRetried:
        {
            // Compute the retry-after delay using exponential back-off
            const int32 RetryAfterSeconds = Item.Response.ErrorData.Retry_after_seconds;
            const int32 BackoffMs = Configuration.InitialRetryWaitTimeMs *
                FMath::RoundToInt(FMath::Pow(
                    static_cast<float>(Configuration.IncrementalBackoffFactor),
                    static_cast<float>(Item.RequestData.TimesRetried)));

            if (RetryAfterSeconds > 0)
            {
                Item.RetryAfter = FDateTime::UtcNow() + FTimespan::FromSeconds(RetryAfterSeconds);
            }
            else
            {
                Item.RetryAfter = FDateTime::UtcNow() + FTimespan::FromMilliseconds(BackoffMs);
            }

            // Reset item for re-dispatch
            OngoingRequestIds.Remove(Item.RequestData.RequestId);
            Item.AbortRequest();
            Item.RequestData.TimesRetried++;
            break;
        }
    }
}

void FLootLockerHTTPExecutionQueue::DispatchSessionRefreshForItem(const FString& RequestId)
{
    TSharedPtr<FLootLockerHTTPExecutionQueueItem>* ItemPtr = ExecutionQueue.Find(RequestId);
    if (!ItemPtr || !(*ItemPtr).IsValid())
    {
        return;
    }

    const FLootLockerPlayerData PlayerData = (*ItemPtr)->RequestData.PlayerData;

    ULootLockerHttpClient::RefreshSessionForPlatform(PlayerData, [RequestId](bool bRefreshSuccess)
    {
        if (!FLootLockerHTTPExecutionQueue::IsInitialized())
        {
            return;
        }
        FLootLockerHTTPExecutionQueue::Get().OnSessionRefreshCompleted(RequestId, bRefreshSuccess);
    });
}

void FLootLockerHTTPExecutionQueue::OnSessionRefreshCompleted(const FString& RequestId, bool bRefreshSuccess)
{
    TSharedPtr<FLootLockerHTTPExecutionQueueItem>* FoundItemPtr = ExecutionQueue.Find(RequestId);
    if (!FoundItemPtr || !(*FoundItemPtr).IsValid())
    {
        return;
    }
    FLootLockerHTTPExecutionQueueItem& Item = **FoundItemPtr;
    Item.bIsWaitingForSessionRefresh = false;

    if (bRefreshSuccess)
    {
        // Pull the freshly-issued token from state so the re-dispatched request
        // sends the new session token rather than the stale one captured at
        // enqueue time.
        Item.RequestData.PlayerData =
            ULootLockerStateData::GetAndActivateSavedStateOrDefaultOrEmptyForPlayer(
                Item.RequestData.ForPlayerUlid);
        // Reset the retry-after delay so Tick() picks this item up as an
        // unsent request on the next frame.
        Item.RetryAfter = FDateTime(0);
    }
    else
    {
        // Refresh failed — call side-effects then deliver the stored failure response
        CompleteItem(Item, Item.Response);
    }
}

void FLootLockerHTTPExecutionQueue::CompleteItem(
    FLootLockerHTTPExecutionQueueItem& Item,
    const FLootLockerResponse& Response)
{
    // Capture headers before MarkItemDone resets the HttpRequest pointer
    FString DelimitedHeaders = TEXT("N/A");
    TArray<FString> AllHeaders;
    FHttpResponsePtr HttpResponse = nullptr;
    if (Item.HttpRequest.IsValid())
    {
        AllHeaders   = Item.HttpRequest->GetAllHeaders();
        HttpResponse = Item.HttpRequest->GetResponse();
        DelimitedHeaders = TEXT("");
        for (const FString& Header : AllHeaders)
        {
            DelimitedHeaders += TEXT("    ") + Header + TEXT("\n");
        }
    }

    if (Response.success)
    {
        if (!Item.RequestData.ForPlayerUlid.IsEmpty())
        {
            ULootLockerStateData::MakePlayerActive(Item.RequestData.ForPlayerUlid);
        }
    }
    else
    {
        ULootLockerHttpClient::StoreFailedRequestReport(
            Response, Item.RequestData.Body, AllHeaders, HttpResponse,
            Item.RequestData.TimesRetried, Item.RequestData.RequestStartDateTime);
    }

    FLootLockerLogger::LogHttpRequest(Response, DelimitedHeaders);
    MarkItemDone(Item, Response);
}

void FLootLockerHTTPExecutionQueue::MarkItemDone(
    FLootLockerHTTPExecutionQueueItem& Item,
    const FLootLockerResponse& Response)
{
    Item.AbortRequest();
    OngoingRequestIds.Remove(Item.RequestData.RequestId);
    Item.Response = Response;
    Item.bDone    = true;
    if (!CompletedRequestIds.Contains(Item.RequestData.RequestId))
    {
        CompletedRequestIds.Add(Item.RequestData.RequestId);
    }
}

bool FLootLockerHTTPExecutionQueue::ShouldRetryRequest(int32 StatusCode, int32 TimesRetried) const
{
    if (TimesRetried >= Configuration.MaxRetries)
    {
        return false;
    }
    // Retry on network/connection errors (StatusCode == 0) and 5xx server errors
    if (StatusCode == 0 || (StatusCode >= 500 && StatusCode < 600))
    {
        return true;
    }
    // Retry on 429 Too Many Requests (respecting Retry-After if present)
    if (StatusCode == 429)
    {
        return true;
    }
    return false;
}

bool FLootLockerHTTPExecutionQueue::ShouldRefreshSession(
    int32 StatusCode, const FLootLockerPlayerData& PlayerData, int32 TimesRetried) const
{
    // Do not attempt a refresh if this is already a retry attempt
    if (TimesRetried > 0)
    {
        return false;
    }
    if (PlayerData.PlayerUlid.IsEmpty())
    {
        return false;
    }
    if (StatusCode != 401 && StatusCode != 403)
    {
        return false;
    }
    const ULootLockerConfig* Config = GetDefault<ULootLockerConfig>();
    if (!Config || !Config->AllowTokenRefresh)
    {
        return false;
    }

    // Platforms that support refresh via stored tokens
    const ELootLockerPlatform Platform = PlayerData.CurrentPlatform.Platform;
    static const TArray<ELootLockerPlatform> RefreshTokenPlatforms = {
        ELootLockerPlatform::Google,
        ELootLockerPlatform::Epic,
        ELootLockerPlatform::AppleSignIn,
        ELootLockerPlatform::AppleGameCenter,
        ELootLockerPlatform::Meta,
        ELootLockerPlatform::Discord,
        ELootLockerPlatform::GooglePlayGames,
        ELootLockerPlatform::Remote,
    };
    if (RefreshTokenPlatforms.Contains(Platform) && !PlayerData.RefreshToken.IsEmpty())
    {
        return true;
    }

    // Guest and WhiteLabel can be refreshed using cached auth data
    if (Platform == ELootLockerPlatform::Guest && !PlayerData.PlayerIdentifier.IsEmpty())
    {
        return true;
    }
    if (Platform == ELootLockerPlatform::WhiteLabel &&
        !PlayerData.WhiteLabelEmail.IsEmpty() && !PlayerData.WhiteLabelToken.IsEmpty())
    {
        return true;
    }

    return false;
}
