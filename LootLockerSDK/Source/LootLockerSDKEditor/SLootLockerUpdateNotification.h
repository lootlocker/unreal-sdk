// Copyright (c) LootLocker. All Rights Reserved.
#pragma once

#include "Widgets/SCompoundWidget.h"
#include "Templates/SharedPointer.h"

/**
 * Non-modal Slate window content shown when a newer LootLocker SDK version is available.
 * Hosted inside an SWindow created by FLootLockerUpdateChecker::ShowUpdateNotification().
 */
class SLootLockerUpdateNotification : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SLootLockerUpdateNotification) {}
        SLATE_ARGUMENT(FString, CurrentVersion)
        SLATE_ARGUMENT(FString, LatestVersion)
        SLATE_ARGUMENT(FString, ReleaseUrl)
        SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

private:
    FReply OnSeeWhatsNewClicked();
    FReply OnUpdateNowClicked();
    FReply OnSkipVersionClicked();
    FReply OnRemindLaterClicked();
    FReply OnNeverNotifyClicked();

    void CloseParentWindow();

    FString CurrentVersion;
    FString LatestVersion;
    FString ReleaseUrl;
    TWeakPtr<SWindow> ParentWindow;
};
