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
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::MagicTriggers, ESearchCase::IgnoreCase))
    {
        // Magic triggers have no source specific identifying context key, only the standard reward summary keys
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                "currencies",
                FGuid::NewGuid().ToString()
            }
        };
    }
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::PlaystationStore, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::PlaystationStore::TransactionId,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::PlaystationStore::CatalogItemId,
                FGuid::NewGuid().ToString(),
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::PlaystationStore::CatalogId,
                FGuid::NewGuid().ToString()
            }
        };
    }
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::StripeStore, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::StripeStore::EntitlementId,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::StripeStore::CatalogItemId,
                FGuid::NewGuid().ToString()
            }
        };
    }
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::EpicGamesStore, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::EpicGamesStore::EpicEntitlementId,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::EpicGamesStore::CatalogItemId,
                FGuid::NewGuid().ToString(),
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::Purchasing::EpicGamesStore::CatalogId,
                FGuid::NewGuid().ToString()
            }
        };
    }
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::LeaderboardReward, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::LeaderboardReward::LeaderboardId,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::LeaderboardReward::PlayerPublicId,
                FGuid::NewGuid().ToString()
            }
        };
    }
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::RewardCampaign, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::RewardCampaign::GiveawayId,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::RewardCampaign::RewardId,
                FGuid::NewGuid().ToString()
            }
        };
    }
    else if (source.Equals(LootLockerNotificationsStaticStrings::NotificationSources::RewardsGrant, ESearchCase::IgnoreCase))
    {
        context = TArray<FLootLockerNotificationContextEntry>
        {
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::RewardsGrant::ItemTemplateId,
                identifyingValue
            },
            FLootLockerNotificationContextEntry {
                LootLockerNotificationsStaticStrings::StandardContextKeys::RewardsGrant::TemplateName,
                FGuid::NewGuid().ToString()
            }
        };
    }
    auto contentRewardBody = FLootLockerNotificationContentRewardBody{
        /*Kind*/
        ELootLockerNotificationContentRewardKind::currency,
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
    };
    FString contentRewardBodyString = "";
	FJsonObjectConverter::UStructToJsonObjectString(contentRewardBody, contentRewardBodyString);
    TSharedPtr<FJsonValue> contentRewardBodyJson = LootLockerUtilities::JsonValueFromFString(contentRewardBodyString);
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
        /*SourceEnum*/
        ELootLockerNotificationSource::triggers,
        /*Content*/
        FLootLockerNotificationContent {
            /*Context*/
            context,
            /*ContextAsDictionary*/
            TMap<FString, FString>(),
            /*IdentifyingContextKey*/
            "",
            /*Body*/
            ELootLockerNotificationContentBodyType::reward,
			contentRewardBodyString,
            contentRewardBodyJson            
        },
        /*Id*/
        notificationId,
        /*Player_id*/
        FGuid::NewGuid().ToString(),
        /*Read*/
        false,
        /*Custom*/
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
            FString magicTriggerNotification1Id = FGuid::NewGuid().ToString();
            FString PlaystationStorePurchaseIdentifyingValue = "playstation_transaction_id";
            FString playstationStoreNotification1Id = FGuid::NewGuid().ToString();
            FString StripeStorePurchaseIdentifyingValue = "stripe_entitlement_id";
            FString stripeStoreNotification1Id = FGuid::NewGuid().ToString();
            FString EpicGamesStorePurchaseIdentifyingValue = "epic_entitlement_id";
            FString epicGamesStoreNotification1Id = FGuid::NewGuid().ToString();
            FString LeaderboardRewardIdentifyingValue = "leaderboard_id";
            FString leaderboardRewardNotification1Id = FGuid::NewGuid().ToString();
            FString RewardCampaignIdentifyingValue = "giveaway_id";
            FString rewardCampaignNotification1Id = FGuid::NewGuid().ToString();
            FString RewardsGrantIdentifyingValue = "item_template_id";
            FString rewardsGrantNotification1Id = FGuid::NewGuid().ToString();
            FString unknownSourceNotification1Id = FGuid::NewGuid().ToString();

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
                GenerateLootLockerNotification(googlePlayStoreNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::GooglePlayStore, GooglePlayStoreStorePurchaseIdentifyingValue),
                GenerateLootLockerNotification(magicTriggerNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::MagicTriggers, LootLockerNotificationsStaticStrings::NotificationTypes::PullRewardAcquired),
                GenerateLootLockerNotification(playstationStoreNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::PlaystationStore, PlaystationStorePurchaseIdentifyingValue),
                GenerateLootLockerNotification(stripeStoreNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::StripeStore, StripeStorePurchaseIdentifyingValue),
                GenerateLootLockerNotification(epicGamesStoreNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::Purchasing::EpicGamesStore, EpicGamesStorePurchaseIdentifyingValue),
                GenerateLootLockerNotification(leaderboardRewardNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::LeaderboardReward, LeaderboardRewardIdentifyingValue),
                GenerateLootLockerNotification(rewardCampaignNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::RewardCampaign, RewardCampaignIdentifyingValue),
                GenerateLootLockerNotification(rewardsGrantNotification1Id, LootLockerNotificationsStaticStrings::NotificationSources::RewardsGrant, RewardsGrantIdentifyingValue),
                GenerateLootLockerNotification(unknownSourceNotification1Id, "some.future_source", "some_identifying_value")
            };
            fakeResponse.Pagination = FLootLockerExtendedIndexBasedPagination{
                14,
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

            TArray<FLootLockerNotification> magicTriggerNotifications;
            bool magicTriggerLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(LootLockerNotificationsStaticStrings::NotificationTypes::PullRewardAcquired, magicTriggerNotifications);

            TArray<FLootLockerNotification> playstationStoreNotifications;
            bool playstationStoreLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(PlaystationStorePurchaseIdentifyingValue, playstationStoreNotifications);

            TArray<FLootLockerNotification> stripeStoreNotifications;
            bool stripeStoreLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(StripeStorePurchaseIdentifyingValue, stripeStoreNotifications);

            TArray<FLootLockerNotification> epicGamesStoreNotifications;
            bool epicGamesStoreLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(EpicGamesStorePurchaseIdentifyingValue, epicGamesStoreNotifications);

            TArray<FLootLockerNotification> leaderboardRewardNotifications;
            bool leaderboardRewardLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(LeaderboardRewardIdentifyingValue, leaderboardRewardNotifications);

            TArray<FLootLockerNotification> rewardCampaignNotifications;
            bool rewardCampaignLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(RewardCampaignIdentifyingValue, rewardCampaignNotifications);

            TArray<FLootLockerNotification> rewardsGrantNotifications;
            bool rewardsGrantLookupSucceeded = fakeResponse.TryGetNotificationsByIdentifyingValue(RewardsGrantIdentifyingValue, rewardsGrantNotifications);

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

            TestTrue("Magic trigger notification lookup failed", magicTriggerLookupSucceeded);
            TestTrue("Magic trigger notification lookup array was empty", magicTriggerNotifications.Num() > 0);
            TestEqual("The retrieved magic trigger notification id was not as expected", magicTriggerNotifications[0].Id, magicTriggerNotification1Id);
            TestTrue("The magic trigger notification source enum was not as expected", magicTriggerNotifications[0].SourceEnum == ELootLockerNotificationSource::magic_triggers);

            TestTrue("PlayStation store notification lookup failed", playstationStoreLookupSucceeded);
            TestTrue("PlayStation store notification lookup array was empty", playstationStoreNotifications.Num() > 0);
            TestEqual("The retrieved PlayStation store notification id was not as expected", playstationStoreNotifications[0].Id, playstationStoreNotification1Id);
            TestTrue("The PlayStation store notification source enum was not as expected", playstationStoreNotifications[0].SourceEnum == ELootLockerNotificationSource::purchasing_playstation_store);

            TestTrue("Stripe store notification lookup failed", stripeStoreLookupSucceeded);
            TestTrue("Stripe store notification lookup array was empty", stripeStoreNotifications.Num() > 0);
            TestEqual("The retrieved Stripe store notification id was not as expected", stripeStoreNotifications[0].Id, stripeStoreNotification1Id);
            TestTrue("The Stripe store notification source enum was not as expected", stripeStoreNotifications[0].SourceEnum == ELootLockerNotificationSource::purchasing_stripe_store);

            TestTrue("Epic Games store notification lookup failed", epicGamesStoreLookupSucceeded);
            TestTrue("Epic Games store notification lookup array was empty", epicGamesStoreNotifications.Num() > 0);
            TestEqual("The retrieved Epic Games store notification id was not as expected", epicGamesStoreNotifications[0].Id, epicGamesStoreNotification1Id);
            TestTrue("The Epic Games store notification source enum was not as expected", epicGamesStoreNotifications[0].SourceEnum == ELootLockerNotificationSource::purchasing_epic_games_store);

            TestTrue("Leaderboard reward notification lookup failed", leaderboardRewardLookupSucceeded);
            TestTrue("Leaderboard reward notification lookup array was empty", leaderboardRewardNotifications.Num() > 0);
            TestEqual("The retrieved leaderboard reward notification id was not as expected", leaderboardRewardNotifications[0].Id, leaderboardRewardNotification1Id);
            TestTrue("The leaderboard reward notification source enum was not as expected", leaderboardRewardNotifications[0].SourceEnum == ELootLockerNotificationSource::leaderboard_reward);

            TestTrue("Reward campaign notification lookup failed", rewardCampaignLookupSucceeded);
            TestTrue("Reward campaign notification lookup array was empty", rewardCampaignNotifications.Num() > 0);
            TestEqual("The retrieved reward campaign notification id was not as expected", rewardCampaignNotifications[0].Id, rewardCampaignNotification1Id);
            TestTrue("The reward campaign notification source enum was not as expected", rewardCampaignNotifications[0].SourceEnum == ELootLockerNotificationSource::reward_campaign);

            TestTrue("Rewards grant notification lookup failed", rewardsGrantLookupSucceeded);
            TestTrue("Rewards grant notification lookup array was empty", rewardsGrantNotifications.Num() > 0);
            TestEqual("The retrieved rewards grant notification id was not as expected", rewardsGrantNotifications[0].Id, rewardsGrantNotification1Id);
            TestTrue("The rewards grant notification source enum was not as expected", rewardsGrantNotifications[0].SourceEnum == ELootLockerNotificationSource::rewards_grant);

            const FLootLockerNotification* unknownSourceNotification = fakeResponse.Notifications.FindByPredicate([&unknownSourceNotification1Id](const FLootLockerNotification& Notification) { return Notification.Id == unknownSourceNotification1Id; });
            TestNotNull("The unknown source notification was not found in the response", unknownSourceNotification);
            if (unknownSourceNotification != nullptr)
            {
                TestTrue("The unknown source notification source enum was not as expected", unknownSourceNotification->SourceEnum == ELootLockerNotificationSource::unknown);
            }

            TArray<FLootLockerNotification> unknownSourceLookupNotifications;
            TestFalse("The unknown source notification should not be registered in the lookup table", fakeResponse.TryGetNotificationsByIdentifyingValue("some_identifying_value", unknownSourceLookupNotifications));

            TestDone.ExecuteIfBound();
        });
    });
}
#endif

