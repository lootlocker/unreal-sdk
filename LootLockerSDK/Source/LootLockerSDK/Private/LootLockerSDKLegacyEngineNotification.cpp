// Copyright (c) 2021 LootLocker

#include "LootLockerSDKLegacyEngineNotification.h"

#include "LootLockerSDK.h"

#if WITH_EDITOR
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

void ULootLockerSDKLegacyEngineNotification::Tick(float DeltaTime)
{
#if WITH_EDITOR
	if (ShowNotificationInSeconds > 0.01f) {
		ShowNotificationInSeconds -= DeltaTime;
		if (ShowNotificationInSeconds < 0.01f)
		{
			ShowNotificationInSeconds = InitialTimer * BackOff;
			BackOff *= BackOffRate;
			if(ShowNotificationInSeconds >= 14400.0f)
			{
				ShowNotificationInSeconds = -1.0f;
			}
			ShowEngineVersionOutOfMarketplaceSupportNotification();
		}
	}
#endif
}

bool ULootLockerSDKLegacyEngineNotification::IsTickable() const
{
#if WITH_EDITOR
	return ShowNotificationInSeconds >= -0.001f;
#else
		return false;
#endif
}

bool ULootLockerSDKLegacyEngineNotification::IsTickableInEditor() const
{
#if WITH_EDITOR
	return ShowNotificationInSeconds >= -0.001f;
#else
		return false;
#endif
}

TStatId ULootLockerSDKLegacyEngineNotification::GetStatId() const
{
	return UObject::GetStatID();
}

void ULootLockerSDKLegacyEngineNotification::ShowEngineVersionOutOfMarketplaceSupportNotification() const
{
#if WITH_EDITOR
	if (IsEngineVersionOutOfMarketplaceSupport) {
#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION <= 25
		UE_LOG(LogLootLockerGameSDK, Warning, TEXT("%s, Read more: %s"), *EngineVersionOutOfMarketplaceSupportWarning, TEXT("https://docs.lootlocker.com/support/getting-help/unreal-marketplace-plugin-support"));
#else
		FNotificationInfo Info(FText::FromString(EngineVersionOutOfMarketplaceSupportWarning));
		Info.ExpireDuration = 10.0f;
		Info.bUseSuccessFailIcons = true;
		Info.Image = FEditorStyle::GetBrush(TEXT("MessageLog.Warning"));
		Info.Hyperlink = FSimpleDelegate::CreateLambda([this]() {
			const FString DocsURL = TEXT("https://docs.lootlocker.com/support/getting-help/unreal-marketplace-plugin-support");
			FPlatformProcess::LaunchURL(*DocsURL, nullptr, nullptr);
		});

		Info.HyperlinkText = FText::FromString("Read More...");
		FSlateNotificationManager::Get().AddNotification(Info);
#endif
	}
#endif
}
