#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/FileHelper.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerPurchaseRequest, "LootLocker",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	FLootLockerAuthenticationResponse AuthenticationResponse;
END_DEFINE_SPEC(FTestLootLockerPurchaseRequest)

void FTestLootLockerPurchaseRequest::Define()
{
	// TODO: how to test
	
}
#endif
