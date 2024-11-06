#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerNotificationsRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerNotifications, "LootLocker.Notifications", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerNotifications)

FLootLockerNotification GenerateLootLockerNotification(const FString& notificationId, const FString& source, const FString& identifyingValue)
{
    TArray<FLootLockerNotificationContextEntry> context;
    if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Triggers, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Key,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Id,
                FGuid::NewGuid().ToString(),
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Triggers::Limit,
                "10"
            }
        };
    }
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::LootLocker, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::LootLocker::CatalogItemId,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::LootLocker::CatalogId,
                FGuid::NewGuid().ToString(),
            }
        };
    }
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::GooglePlayStore, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::ProductId,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::CatalogItemId,
                FGuid::NewGuid().ToString(),
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::GooglePlayStore::CatalogId,
                FGuid::NewGuid().ToString()
            }
        };
    }
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::AppleAppStore, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::TransactionId,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::CatalogItemId,
                FGuid::NewGuid().ToString(),
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::AppleAppStore::CatalogId,
                FGuid::NewGuid().ToString()
            }
        };
    }
    return FLootLockerNotification
    {
        /*Created_at*/
        FDateTime::Now().ToString(),
        /*Expiration_date*/
        FDateTime::Now().ToString(),
        /*Read_at*/
        FDateTime::Now().ToString(),
        /*Notification_type*/
        LootLockerNotificationsStaticStrings::NotificationTypes::PullRewardAcquired,
        /*Priority*/
        ELootLockerNotificationPriority::medium,
        /*Source*/
        source,
        /*Content*/
        FLootLockerNotificationContent {
            /*Context*/
            context,
            /*ContextAsDictionary*/
            TMap<FString, FString>(),
            /*IdentifyingContextKey*/
            "",
            /*Body*/
            FLootLockerNotificationContentBody {
                /*Kind*/
                ELootLockerNotificationContentKind::currency,
                /*Group*/
                FLootLockerNotificationRewardGroup(),
                /*Currency*/
                FLootLockerNotificationRewardCurrency {
                    /*Created_at*/
                    FDateTime::Now().ToString(),
                    /*Updated_at*/
                    FDateTime::Now().ToString(),
                    /*Amount*/
                    "100",
                    /*Details*/
                    FLootLockerNotificationRewardCurrencyDetails {
                        /*Name*/
                        "Gold",
                        /*Code*/
                        "GLD",
                        /*Amount*/
                        "100",
                        /*Id*/
                        FGuid::NewGuid().ToString()
                    },
                    /*Reward_id*/
                    FGuid::NewGuid().ToString(),
                    /*Currency_id*/
                    FGuid::NewGuid().ToString()
                },
                /*Asset*/
                FLootLockerNotificationRewardAsset(),
                /*Progression_reset*/
                FLootLockerNotificationRewardProgressionReset(),
                /*Progression_points*/
                FLootLockerNotificationRewardProgression()
            }
        },
        /*Id*/
        notificationId,
        /*Player_id*/
        FGuid::NewGuid().ToString(),
        /*Read*/
        false
    };
}

void FTestLootLockerNotifications::Define()
{
    Describe("Notifications", [this]()
    {
        LatentIt("Testing notifications convenience method", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
        {
            // Given
            FString TriggerIdentifyingValue = "trigger_key";
            FString triggerNotification1Id = FGuid::NewGuid().ToString();
            FString triggerNotification2Id = FGuid::NewGuid().ToString();
            FString triggerNotification3Id = FGuid::NewGuid().ToString();
            FString LootLockerVirtualStorePurchaseIdentifyingValue = "catalog_item_id";
            FString lootLockerVirtualStoreNotification1Id = FGuid::NewGuid().ToString();
            FString AppleAppStorePurchaseIdentifyingValue = "transaction_id";
            FString appleAppStoreNotification1Id = FGuid::NewGuid().ToString();
            FString GooglePlayStoreStorePurchaseIdentifyingValue = "product_id";
            FString googlePlayStoreNotification1Id = FGuid::NewGuid().ToString();

            FLootLockerListNotificationsResponse fakeResponse;
            fakeResponse.success = true;
            fakeResponse.StatusCode = 200;
            fakeResponse.FullTextFromServer = "";
            fakeResponse.ErrorData = FLootLockerErrorData();
            fakeResponse.Notifications = TArray<FLootLockerNotification>{
                GenerateLootLockerNotification(triggerNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::Triggers, TriggerIdentifyingValue),
                GenerateLootLockerNotification(triggerNotification2Id, LootLockerNotificationsStaticStrings::NotificationSources::Triggers, TriggerIdentifyingValue),
                GenerateLootLockerNotification(triggerNotification3Id, LootLockerNotificationsStaticStrings::NotificationSources::Triggers, "some_other_trigger"),
                GenerateLootLockerNotification(lootLockerVirtualStoreNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::LootLocker, LootLockerVirtualStorePurchaseIdentifyingValue),
                GenerateLootLockerNotification(appleAppStoreNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::AppleAppStore, AppleAppStorePurchaseIdentifyingValue),
                GenerateLootLockerNotification(googlePlayStoreNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::GooglePlayStore, GooglePlayStoreStorePurchaseIdentifyingValue)
            };
            fakeResponse.Pagination = FLootLockerExtendedIndexBasedPagination{
                6,
                0,
                100,
                1,
                1,
                "",
                "",
                TArray<FLootLockerExtendedPaginationError>()
            };

            fakeResponse.PopulateConvenienceStructures();

            // When
            TArray<FLootLockerNotification> triggerNotifications;
            bool triggerLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(TriggerIdentifyingValue, triggerNotifications);

            TArray<FLootLockerNotification> lootLockerVirtualStoreNotifications;
            bool lootLockerVirtualStoreLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(LootLockerVirtualStorePurchaseIdentifyingValue, lootLockerVirtualStoreNotifications);

            TArray<FLootLockerNotification> appleAppStoreNotifications;
            bool appleAppStoreLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(AppleAppStorePurchaseIdentifyingValue, appleAppStoreNotifications);

            TArray<FLootLockerNotification> googlePlayStoreNotifications;
            bool googlePlayStoreLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(GooglePlayStoreStorePurchaseIdentifyingValue, googlePlayStoreNotifications);

            // Then

            TestTrue("Trigger notification lookup failed", triggerLookupSucceeded);
            TestTrue("Trigger notification lookup array was empty", triggerNotifications.Num() > 0);
            TestEqual("The right amount of trigger notifications were not retrieved", triggerNotifications.Num(), 2);
            TArray<FString> retrievedNotificationIds;
            for (const FLootLockerNotification& N : triggerNotifications) {
                retrievedNotificationIds.Add(N.Id);
            }
            TestTrue("The retrieved trigger notifications did not contain the expected id", retrievedNotificationIds.Contains(triggerNotification1Id));
            TestTrue("The retrieved trigger notifications did not contain the expected id", retrievedNotificationIds.Contains(triggerNotification2Id));

            TestTrue("LootLocker Virtual Store notification lookup failed", lootLockerVirtualStoreLookupSucceeded);
            TestTrue("LootLocker Virtual Store notification lookup array was empty", lootLockerVirtualStoreNotifications.Num() > 0);
            TestEqual("The retrieved lootlocker virtual store notification id was not as expected", lootLockerVirtualStoreNotifications[0].Id, lootLockerVirtualStoreNotification1Id);

            TestTrue("Apple app store notification lookup failed", appleAppStoreLookupSucceeded);
            TestTrue("Apple app store notification lookup array was empty", appleAppStoreNotifications.Num() > 0);
            TestEqual("The retrieved Apple app store notification id was not as expected", appleAppStoreNotifications[0].Id, appleAppStoreNotification1Id);

            TestTrue("Google Play store notification lookup failed", googlePlayStoreLookupSucceeded);
            TestTrue("Google Play store notification lookup array was empty", googlePlayStoreNotifications.Num() > 0);
            TestEqual("The retrieved Google Play store notification id was not as expected", googlePlayStoreNotifications[0].Id, googlePlayStoreNotification1Id);
            TestDone.ExecuteIfBound();
        });
    });
}
#endif

