// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "LootLockerPlayerData.h"
#include "LootLockerResponse.h"

/**
 * Captures everything needed to dispatch — and later retry — a single SDK HTTP
 * request.  Instances are created by ULootLockerHttpClient::SendApi() /
 * UploadFile() and enqueued into FLootLockerHTTPExecutionQueue.
 */
struct LOOTLOCKERSDK_API FLootLockerHTTPRequestData
{
    /** Unique identifier for this request. Assigned as a GUID at request creation
     *  time; used for queue lookup, deduplication, and correlation in logs.
     */
    FString RequestId = TEXT("");

    /**
     * ULID of the player this request is being made on behalf of.
     * Used to look up the player's session state for auth-token injection and
     * session-refresh decisions.
     */
    FString ForPlayerUlid = TEXT("");

    /** Fully-formed URL endpoint (before any run-time query-param appending). */
    FString Endpoint = TEXT("");

    /** HTTP verb ("GET", "POST", "PUT", "PATCH", "DELETE", …). */
    FString Verb = TEXT("");

    /** JSON body string. Empty for GET/HEAD/OPTIONS requests and file uploads. */
    FString Body = TEXT("");

    /** Additional headers to merge on top of the SDK defaults for this request. */
    TMap<FString, FString> ExtraHeaders;

    /**
     * Player session data used for auth-token injection and session-refresh
     * decisions.  Copied at enqueue time so the request carries a stable snapshot.
     */
    FLootLockerPlayerData PlayerData;

    /**
     * Registered completion callbacks.  All are invoked (in registration order)
     * when the request finishes — whether successfully or not.
     * Use CallListenersWithResult() to invoke them safely.
     */
    TArray<FResponseCallback> Listeners;

    /** Number of retry attempts made for this request so far. */
    int32 TimesRetried = 0;

    /**
     * Wall-clock time (FPlatformTime::Seconds()) when the request was first
     * submitted to the queue.
     */
    double RequestStartTime = 0.0;

    /**
     * True once all Listeners have been invoked via CallListenersWithResult().
     * Prevents double-delivery if a retry path calls the method more than once.
     */
    bool HaveListenersBeenInvoked = false;

    // --- File-upload fields (only meaningful when bIsFileUpload == true) ---

    /** True when this request represents a file upload rather than a JSON call. */
    bool bIsFileUpload = false;

    /** Absolute path to the file to upload (only used when bIsFileUpload is true). */
    FString FilePath = TEXT("");

    /** Additional form-data fields to include alongside the file (only used when bIsFileUpload is true). */
    TMap<FString, FString> AdditionalFields;

    // --- Helpers ---

    /**
     * Invokes every registered Listener with the supplied Response.
     *
     * Exceptions thrown inside individual listeners are caught and logged so that
     * remaining listeners are still called.  Sets HaveListenersBeenInvoked = true
     * after all listeners have been attempted.
     */
    void CallListenersWithResult(const FLootLockerResponse& Response);

    bool operator==(const FLootLockerHTTPRequestData& Other) const
    {
        return RequestId == Other.RequestId;
    }

    bool operator!=(const FLootLockerHTTPRequestData& Other) const
    {
        return !(*this == Other);
    }
};
