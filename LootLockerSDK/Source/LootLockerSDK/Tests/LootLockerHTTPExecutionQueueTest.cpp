// Copyright (c) 2021 LootLocker

#include "Runtime/Launch/Resources/Version.h"
#include "LootLockerHTTPExecutionQueue.h"
#include "LootLockerHTTPClientConfiguration.h"
#include "LootLockerHTTPRequestData.h"
#include "Misc/AutomationTest.h"

#if ENGINE_MAJOR_VERSION > 4

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

namespace
{
    /** Builds a minimal FLootLockerHTTPRequestData for use in queue tests. */
    FLootLockerHTTPRequestData MakeTestRequest(const FString& RequestId)
    {
        FLootLockerHTTPRequestData Req;
        Req.RequestId      = RequestId;
        Req.ForPlayerUlid  = TEXT("test-player");
        Req.Endpoint       = TEXT("https://api.lootlocker.io/test");
        Req.Verb           = TEXT("POST");
        Req.Body           = TEXT("{}");
        Req.RequestStartTime = FPlatformTime::Seconds();
        return Req;
    }

    /** Appends a lambda listener to Request that sets *bWasCalled and captures the response. */
    void AddListener(FLootLockerHTTPRequestData& Request, bool* bWasCalled,
                     FLootLockerResponse* OutResponse = nullptr)
    {
        Request.Listeners.Add(FResponseCallback::CreateLambda(
            [bWasCalled, OutResponse](const FLootLockerResponse& Response)
            {
                *bWasCalled = true;
                if (OutResponse)
                {
                    *OutResponse = Response;
                }
            }));
    }

    /** Returns a configuration that keeps everything in pending (MaxOngoingRequests = 0). */
    FLootLockerHTTPClientConfiguration MakePendingOnlyConfig()
    {
        FLootLockerHTTPClientConfiguration Config;
        Config.MaxOngoingRequests          = 0;
        Config.MaxQueueSize                = 5000;
        Config.ChokeWarningThreshold       = 500;
        Config.DenyIncomingRequestsWhenBackedUp = true;
        return Config;
    }
}

// ---------------------------------------------------------------------------
// Spec
// ---------------------------------------------------------------------------

BEGIN_DEFINE_SPEC(
    FLootLockerHTTPExecutionQueueSpec,
    "LootLocker.HTTPExecutionQueue",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

END_DEFINE_SPEC(FLootLockerHTTPExecutionQueueSpec)

void FLootLockerHTTPExecutionQueueSpec::Define()
{
    BeforeEach([this]()
    {
        FLootLockerHTTPExecutionQueue::Initialize();
        // Use a config that keeps requests pending so they never reach the HTTP layer
        FLootLockerHTTPExecutionQueue::Get().OverrideConfiguration(MakePendingOnlyConfig());
    });

    AfterEach([this]()
    {
        FLootLockerHTTPExecutionQueue::Shutdown();
    });

    Describe("ScheduleRequest", [this]()
    {
        It("QueueFull_DenyIncoming_CallsListenerWithFailure", [this]()
        {
            // Given: a queue that allows exactly 1 pending item
            FLootLockerHTTPClientConfiguration Config = MakePendingOnlyConfig();
            Config.MaxQueueSize = 1;
            FLootLockerHTTPExecutionQueue::Get().OverrideConfiguration(Config);

            // Fill the single available slot
            FLootLockerHTTPRequestData FirstReq = MakeTestRequest(TEXT("req-1"));
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(FirstReq);

            // When: a second request arrives
            bool bCallbackFired = false;
            FLootLockerResponse ReceivedResponse;
            FLootLockerHTTPRequestData SecondReq = MakeTestRequest(TEXT("req-2"));
            AddListener(SecondReq, &bCallbackFired, &ReceivedResponse);
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(SecondReq);

            // Then: the second request is rejected immediately via callback
            TestTrue("Callback was fired for rejected request", bCallbackFired);
            TestFalse("Rejected request response is not success", ReceivedResponse.success);
        });

        It("DuplicateRequestId_MergesListeners_BothCalledOnShutdown", [this]()
        {
            // Given: two requests sharing the same RequestId
            bool bFirstListenerCalled  = false;
            bool bSecondListenerCalled = false;

            FLootLockerHTTPRequestData Req1 = MakeTestRequest(TEXT("shared-id"));
            AddListener(Req1, &bFirstListenerCalled);
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(Req1);

            FLootLockerHTTPRequestData Req2 = MakeTestRequest(TEXT("shared-id"));
            AddListener(Req2, &bSecondListenerCalled);
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(Req2);

            // When: the queue is shut down
            FLootLockerHTTPExecutionQueue::Shutdown();
            // Re-initialize so AfterEach's Shutdown() does not crash
            FLootLockerHTTPExecutionQueue::Initialize();

            // Then: both listeners were invoked exactly once
            TestTrue("First listener was called", bFirstListenerCalled);
            TestTrue("Second listener was called", bSecondListenerCalled);
        });

        It("ChokeThresholdExceeded_DenyIncoming_CallsListenerWithFailure", [this]()
        {
            // Given: a config where the choke threshold is 1 (2 pending items triggers denial)
            FLootLockerHTTPClientConfiguration Config = MakePendingOnlyConfig();
            Config.ChokeWarningThreshold = 1;
            Config.MaxQueueSize          = 5000;
            FLootLockerHTTPExecutionQueue::Get().OverrideConfiguration(Config);

            // Fill past the threshold (2 pending items = PendingCount > 1)
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(MakeTestRequest(TEXT("req-1")));
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(MakeTestRequest(TEXT("req-2")));

            // When: a third request arrives
            bool bCallbackFired = false;
            FLootLockerResponse ReceivedResponse;
            FLootLockerHTTPRequestData ThirdReq = MakeTestRequest(TEXT("req-3"));
            AddListener(ThirdReq, &bCallbackFired, &ReceivedResponse);
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(ThirdReq);

            // Then: the third request is rejected immediately
            TestTrue("Callback was fired for choke-rejected request", bCallbackFired);
            TestFalse("Choke-rejected request response is not success", ReceivedResponse.success);
        });
    });

    Describe("Shutdown", [this]()
    {
        It("PendingRequest_Shutdown_CallsListenerWithError", [this]()
        {
            // Given: one pending request in the queue
            bool bCallbackFired = false;
            FLootLockerResponse ReceivedResponse;
            FLootLockerHTTPRequestData Req = MakeTestRequest(TEXT("pending-req"));
            AddListener(Req, &bCallbackFired, &ReceivedResponse);
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(Req);

            // When: the queue is shut down
            FLootLockerHTTPExecutionQueue::Shutdown();
            // Re-initialize so AfterEach's Shutdown() does not crash
            FLootLockerHTTPExecutionQueue::Initialize();

            // Then: the pending request's listener receives a failure response
            TestTrue("Listener was called during shutdown", bCallbackFired);
            TestFalse("Shutdown response is not success", ReceivedResponse.success);
        });

        It("MultipleRequests_Shutdown_AllListenersCalled", [this]()
        {
            // Given: three pending requests
            bool bCalled1 = false, bCalled2 = false, bCalled3 = false;

            FLootLockerHTTPRequestData R1 = MakeTestRequest(TEXT("r1"));
            AddListener(R1, &bCalled1);
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(R1);

            FLootLockerHTTPRequestData R2 = MakeTestRequest(TEXT("r2"));
            AddListener(R2, &bCalled2);
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(R2);

            FLootLockerHTTPRequestData R3 = MakeTestRequest(TEXT("r3"));
            AddListener(R3, &bCalled3);
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(R3);

            // When
            FLootLockerHTTPExecutionQueue::Shutdown();
            FLootLockerHTTPExecutionQueue::Initialize();

            // Then
            TestTrue("Listener 1 was called", bCalled1);
            TestTrue("Listener 2 was called", bCalled2);
            TestTrue("Listener 3 was called", bCalled3);
        });
    });

    Describe("OverrideConfiguration", [this]()
    {
        It("NewConfig_DisablesDenyIncoming_AllowsRequestsWhenQueueFull", [this]()
        {
            // Given: config with MaxQueueSize=1 but DenyIncomingRequestsWhenBackedUp=false
            FLootLockerHTTPClientConfiguration Config = MakePendingOnlyConfig();
            Config.MaxQueueSize                    = 1;
            Config.DenyIncomingRequestsWhenBackedUp = false;
            FLootLockerHTTPExecutionQueue::Get().OverrideConfiguration(Config);

            // Fill the queue past its declared limit
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(MakeTestRequest(TEXT("r1")));

            // When: another request arrives (deny is off, so it should be accepted)
            bool bCallbackFired = false;
            FLootLockerHTTPRequestData R2 = MakeTestRequest(TEXT("r2"));
            AddListener(R2, &bCallbackFired);
            FLootLockerHTTPExecutionQueue::Get().ScheduleRequest(R2);

            // Then: the callback was NOT fired (request was accepted into the queue)
            TestFalse("Callback should not fire when denial is disabled", bCallbackFired);
        });
    });
}

#endif // ENGINE_MAJOR_VERSION > 4
