// Copyright (c) LootLocker. All Rights Reserved.
#include "SLootLockerUpdateNotification.h"
#include "LootLockerUpdateChecker.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SBoxPanel.h"
#include "HAL/PlatformProcess.h"
#include "Framework/Application/SlateApplication.h"

void SLootLockerUpdateNotification::Construct(const FArguments& InArgs)
{
    CurrentVersion = InArgs._CurrentVersion;
    LatestVersion  = InArgs._LatestVersion;
    ReleaseUrl     = InArgs._ReleaseUrl;
    ParentWindow   = InArgs._ParentWindow;

    ChildSlot
    [
        SNew(SBorder)
        .Padding(FMargin(16.0f))
        [
            SNew(SVerticalBox)

            // Header
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(0.0f, 0.0f, 0.0f, 8.0f)
            [
                SNew(STextBlock)
                .Text(FText::FromString(TEXT("A new version of the LootLocker SDK is available.")))
                .Font(FCoreStyle::GetDefaultFontStyle("Bold", 12))
            ]

            // Version info
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(0.0f, 0.0f, 0.0f, 4.0f)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot().AutoWidth()
                [
                    SNew(STextBlock).Text(FText::FromString(TEXT("Installed:  ")))
                ]
                + SHorizontalBox::Slot().AutoWidth()
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(FString::Printf(TEXT("v%s"), *CurrentVersion)))
                    .ColorAndOpacity(FSlateColor(FLinearColor(0.6f, 0.6f, 0.6f)))
                ]
            ]

            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(0.0f, 0.0f, 0.0f, 12.0f)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot().AutoWidth()
                [
                    SNew(STextBlock).Text(FText::FromString(TEXT("Available:  ")))
                ]
                + SHorizontalBox::Slot().AutoWidth()
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(FString::Printf(TEXT("v%s"), *LatestVersion)))
                    .ColorAndOpacity(FSlateColor(FLinearColor(0.2f, 0.8f, 0.2f)))
                ]
            ]

            // "See what's new" link button
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(0.0f, 0.0f, 0.0f, 16.0f)
            [
                SNew(SButton)
                .ButtonStyle(FCoreStyle::Get(), "NoBorder")
                .OnClicked(this, &SLootLockerUpdateNotification::OnSeeWhatsNewClicked)
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(TEXT("See what's new \u2197")))
                    .ColorAndOpacity(FSlateColor(FLinearColor(0.2f, 0.6f, 1.0f)))
                ]
            ]

            // Action buttons — fill available width evenly
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)

                + SHorizontalBox::Slot()
                .FillWidth(1.0f)
                .Padding(0.0f, 0.0f, 4.0f, 0.0f)
                [
                    SNew(SButton)
                    .HAlign(HAlign_Center)
                    .Text(FText::FromString(TEXT("Update Now")))
                    .OnClicked(this, &SLootLockerUpdateNotification::OnUpdateNowClicked)
                ]

                + SHorizontalBox::Slot()
                .FillWidth(1.0f)
                .Padding(0.0f, 0.0f, 4.0f, 0.0f)
                [
                    SNew(SButton)
                    .HAlign(HAlign_Center)
                    .Text(FText::FromString(TEXT("Skip This Version")))
                    .OnClicked(this, &SLootLockerUpdateNotification::OnSkipVersionClicked)
                ]

                + SHorizontalBox::Slot()
                .FillWidth(1.0f)
                .Padding(0.0f, 0.0f, 4.0f, 0.0f)
                [
                    SNew(SButton)
                    .HAlign(HAlign_Center)
                    .Text(FText::FromString(TEXT("Remind in 7 Days")))
                    .OnClicked(this, &SLootLockerUpdateNotification::OnRemindLaterClicked)
                ]

                + SHorizontalBox::Slot()
                .FillWidth(1.0f)
                [
                    SNew(SButton)
                    .HAlign(HAlign_Center)
                    .Text(FText::FromString(TEXT("Never Notify Me")))
                    .OnClicked(this, &SLootLockerUpdateNotification::OnNeverNotifyClicked)
                ]
            ]
        ]
    ];
}

FReply SLootLockerUpdateNotification::OnSeeWhatsNewClicked()
{
    if (!ReleaseUrl.IsEmpty())
    {
        // Validate URL is from github.com before launching
        if (ReleaseUrl.StartsWith(TEXT("https://github.com/")))
        {
            FPlatformProcess::LaunchURL(*ReleaseUrl, nullptr, nullptr);
        }
    }
    return FReply::Handled();
}

FReply SLootLockerUpdateNotification::OnUpdateNowClicked()
{
    if (!ReleaseUrl.IsEmpty())
    {
        if (ReleaseUrl.StartsWith(TEXT("https://github.com/")))
        {
            FPlatformProcess::LaunchURL(*ReleaseUrl, nullptr, nullptr);
        }
    }
    CloseParentWindow();
    return FReply::Handled();
}

FReply SLootLockerUpdateNotification::OnSkipVersionClicked()
{
    FLootLockerUpdateChecker::SetSkippedVersion(LatestVersion);
    CloseParentWindow();
    return FReply::Handled();
}

FReply SLootLockerUpdateNotification::OnRemindLaterClicked()
{
    FLootLockerUpdateChecker::SetRemindAfterTime(FDateTime::UtcNow() + FTimespan::FromDays(7.0));
    CloseParentWindow();
    return FReply::Handled();
}

FReply SLootLockerUpdateNotification::OnNeverNotifyClicked()
{
    FLootLockerUpdateChecker::SetNeverNotify(true);
    CloseParentWindow();
    return FReply::Handled();
}

void SLootLockerUpdateNotification::CloseParentWindow()
{
    if (const TSharedPtr<SWindow> Window = ParentWindow.Pin())
    {
        Window->RequestDestroyWindow();
    }
}
