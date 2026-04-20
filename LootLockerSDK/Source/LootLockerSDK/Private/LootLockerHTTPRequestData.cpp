// Copyright (c) 2021 LootLocker

#include "LootLockerHTTPRequestData.h"
#include "LootLockerLogger.h"

void FLootLockerHTTPRequestData::CallListenersWithResult(const FLootLockerResponse& Response)
{
    for (FResponseCallback& Listener : Listeners)
    {
        if (!Listener.IsBound())
        {
            continue;
        }

        try
        {
            Listener.Execute(Response);
        }
        catch (const std::exception& Ex)
        {
            FLootLockerLogger::LogWarning(FString::Printf(
                TEXT("Exception thrown in HTTP request listener for request id %s. Exception: %s"),
                *RequestId,
                UTF8_TO_TCHAR(Ex.what())));
        }
        catch (...)
        {
            FLootLockerLogger::LogWarning(FString::Printf(
                TEXT("Unknown exception thrown in HTTP request listener for request id %s."),
                *RequestId));
        }
    }

    HaveListenersBeenInvoked = true;
}
