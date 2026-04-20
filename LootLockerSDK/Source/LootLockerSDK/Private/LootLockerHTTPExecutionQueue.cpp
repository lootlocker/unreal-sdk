// Copyright (c) 2021 LootLocker

#include "LootLockerHTTPExecutionQueue.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IPluginManager.h"
#include "JsonObjectConverter.h"
#include "LootLockerConfig.h"
#include "LootLockerLogger.h"
#include "LootLockerPlayerData.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerResponse.h"
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
    check(Instance.IsValid());
    return *Instance;
}

void FLootLockerHTTPExecutionQueue::Initialize()
{
    if (Instance.IsValid())
    {
        return;
    }
    Instance = TUniquePtr<FLootLockerHTTPExecutionQueue>(new FLootLockerHTTPExecutionQueue());
    Instance->RateLimiter = MakeUnique<FLootLockerRateLimiter>();
    Instance->bIsInitialized = true;
}

void FLootLockerHTTPExecutionQueue::Shutdown()
{
    if (!Instance.IsValid())
    {
        return;
    }

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
        MutableRequest.CallListenersWithResult(
            LootLockerResponseFactory::Error<FLootLockerResponse>(
                ErrorMessage, 0, Request.ForPlayerUlid));
        return;
    }

    // Check for choke threshold
    const int32 PendingCount = ExecutionQueue.Num() - static_cast<int32>(OngoingRequestIds.Num());
    if (Configuration.DenyIncomingRequestsWhenBackedUp &&
        PendingCount > Configuration.ChokeWarningThreshold)
    {
        const FString ErrorMessage = FString::Printf(
            TEXT("Request was denied because there are currently too many requests in queue (%d queued, threshold: %d)"),
            PendingCount, Configuration.ChokeWarningThreshold);
#if WITH_EDITOR
        if (Configuration.LogQueueRejections)
        {
            FLootLockerLogger::LogWarning(FString::Printf(
                TEXT("HTTP queue backed up: %d requests queued"), PendingCount));
        }
#endif
        FLootLockerHTTPRequestData MutableRequest = Request;
        MutableRequest.CallListenersWithResult(
            LootLockerResponseFactory::Error<FLootLockerResponse>(
                ErrorMessage, 0, Request.ForPlayerUlid));
        return;
    }

    // Deduplicate: merge listeners into existing item if same RequestId
    if (TSharedPtr<FLootLockerHTTPExecutionQueueItem>* ExistingItem = ExecutionQueue.Find(Request.RequestId))
    {
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

void FLootLockerHTTPExecutionQueue::SetSessionRefreshDelegate(FSessionRefreshDelegate InDelegate)
{
    OnRefreshSession = MoveTemp(InDelegate);
}

// -------------------------------------------------------------------------
// FTickableGameObject interface
// -------------------------------------------------------------------------

TStatId FLootLockerHTTPExecutionQueue::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(FLootLockerHTTPExecutionQueue, STATGROUP_Tickables);
}

void FLootLockerHTTPExecutionQueue::Tick(float DeltaTime)
{
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
            if (Item.RetryAfter.IsSet() && Item.RetryAfter.GetValue() > FDateTime::UtcNow())
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

    // Choke warning (logged once per tick when the queue is backed up)
    const int32 PendingCount = ExecutionQueue.Num() - static_cast<int32>(OngoingRequestIds.Num());
    if (PendingCount > Configuration.ChokeWarningThreshold)
    {
        FLootLockerLogger::LogWarning(FString::Printf(
            TEXT("HTTP Execution Queue is overloaded. Requests currently waiting for execution: '%d'"),
            PendingCount));
    }

    // ---- Phase 2: LateUpdate — invoke listeners and remove completed items ----

    for (const FString& CompletedId : CompletedRequestIds)
    {
        TSharedPtr<FLootLockerHTTPExecutionQueueItem>* ItemPtr = ExecutionQueue.Find(CompletedId);
        if (!ItemPtr || !(*ItemPtr).IsValid())
        {
            continue;
        }
        FLootLockerHTTPExecutionQueueItem& Item = **ItemPtr;
        if (!Item.bDone)
        {
            continue;
        }
        if (!Item.RequestData.HaveListenersBeenInvoked)
        {
            Item.RequestData.CallListenersWithResult(Item.Response);
        }
        ExecutionQueue.Remove(CompletedId);
        OngoingRequestIds.Remove(CompletedId);
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
        MarkItemDone(Item, LootLockerResponseFactory::Error<FLootLockerResponse>(
            RateLimitMsg, 429, Item.RequestData.ForPlayerUlid));
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
    Request->SetHeader(TEXT("Content-Type"),           TEXT("application/json"));
    Request->SetHeader(TEXT("Accept"),                 TEXT("application/json"));
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

    Request->SetContentAsString(Item.RequestData.Body);

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
        if ((FPlatformTime::Seconds() - Item.RequestStartTime) >= DefaultTimeoutSeconds)
        {
            Item.HttpRequest->CancelRequest();
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
    ErrorResponse.Context.RequestId     = Item.RequestData.RequestId;
    ErrorResponse.Context.RequestURL    = Item.RequestData.Endpoint;
    ErrorResponse.Context.RequestMethod = Item.RequestData.Verb;
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
            MarkItemDone(Item, Item.Response);
            break;
        }

        case ELootLockerHTTPExecutionQueueProcessingResult::Completed_TimedOut:
        {
            MarkItemDone(Item, LootLockerResponseFactory::Error<FLootLockerResponse>(
                TEXT("Request timed out"),
                LootLockerStaticRequestErrorStatusCodes::LL_UNDEFINED_BEHAVIOUR_ERROR,
                Item.RequestData.ForPlayerUlid));
            break;
        }

        case ELootLockerHTTPExecutionQueueProcessingResult::ShouldBeRetried:
        {
            if (Item.RequestData.TimesRetried >= Configuration.MaxRetries)
            {
                // Retries exhausted — deliver the stored failure response
                MarkItemDone(Item, Item.Response);
                break;
            }

            // Compute the retry-after delay using exponential back-off
            const int32 RetryAfterSeconds = Item.Response.ErrorData.Retry_after_seconds;
            int32 BackoffMs = Configuration.InitialRetryWaitTimeMs;
            for (int32 i = 0; i < Item.RequestData.TimesRetried; ++i)
            {
                BackoffMs *= Configuration.IncrementalBackoffFactor;
            }

            FDateTime RetryAt;
            if (RetryAfterSeconds > 0)
            {
                RetryAt = FDateTime::UtcNow() + FTimespan::FromSeconds(RetryAfterSeconds);
            }
            else
            {
                RetryAt = FDateTime::UtcNow() + FTimespan::FromMilliseconds(BackoffMs);
            }

            // Reset item for re-dispatch
            OngoingRequestIds.Remove(Item.RequestData.RequestId);
            Item.AbortRequest();
            Item.RequestData.TimesRetried++;
            Item.RetryAfter = RetryAt;
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

    if (!OnRefreshSession)
    {
        // No refresh delegate registered — fail immediately
        FLootLockerHTTPExecutionQueueItem& Item = **ItemPtr;
        Item.bIsWaitingForSessionRefresh = false;
        MarkItemDone(Item, LootLockerResponseFactory::Error<FLootLockerResponse>(
            TEXT("Session refresh is not configured"),
            LootLockerStaticRequestErrorStatusCodes::LL_UNDEFINED_BEHAVIOUR_ERROR,
            PlayerData.PlayerUlid));
        return;
    }

    OnRefreshSession(PlayerData, [this, RequestId](bool bRefreshSuccess)
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
            // The refresh updated session state — reset the retry-after delay so
            // Tick() picks this item up as an unsent request on the next frame.
            Item.RetryAfter.Reset();
        }
        else
        {
            // Refresh failed — deliver the stored failure response to listeners
            MarkItemDone(Item, Item.Response);
        }
    });
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
