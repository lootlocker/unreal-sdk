#include "LootLockerLogViewerWidget.h"

#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Framework/Application/SlateApplication.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "LootLockerLogger.h"
#include "LootLockerLogLevel.h"
#include "LootLockerErrorData.h"
#include "LootLockerRequestContext.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SHyperlink.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"

void SLootLockerLogViewerWidget::Construct(const FArguments& InArgs)
{
    FLootLockerLogger::OnLogMessage.AddRaw(this, &SLootLockerLogViewerWidget::AddLogEntry);
    FLootLockerLogger::OnHttpLogEntry.AddRaw(this, &SLootLockerLogViewerWidget::AddHttpLogEntry);
    BindToPIEEvents();
    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot().AutoHeight().Padding(2)
        [
            SAssignNew(SearchBox, SSearchBox)
            .OnTextChanged(this, &SLootLockerLogViewerWidget::OnSearchTextChanged)
        ]
        + SVerticalBox::Slot().AutoHeight().Padding(2)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot().AutoWidth().Padding(2)
            [
                SNew(SButton)
                .Text(FText::FromString("Clear Log"))
                .OnClicked(this, &SLootLockerLogViewerWidget::OnClearLogClicked)
            ]
            + SHorizontalBox::Slot().AutoWidth().Padding(2)
            [
                SNew(SCheckBox)
                .IsChecked(this, &SLootLockerLogViewerWidget::GetClearOnPIEState)
                .OnCheckStateChanged(this, &SLootLockerLogViewerWidget::OnClearOnPIEChanged)
                [
                    SNew(STextBlock).Text(FText::FromString("Clear log on Play (PIE)"))
                ]
            ]
        ]
        + SVerticalBox::Slot().FillHeight(1).Padding(2)
        [
            SAssignNew(LogListView, SListView<FLootLockerLogEntryPtr>)
            .ListItemsSource(&FilteredEntries)
            .OnGenerateRow(this, &SLootLockerLogViewerWidget::OnGenerateRow)
            .SelectionMode(ESelectionMode::Single)
        ]
    ];
    RefreshFilter();
}

void SLootLockerLogViewerWidget::AddLogEntry(const FString& Message, ELootLockerLogLevel Level)
{
    // Only handle non-HTTP logs here. HTTP logs should use AddHttpLogEntry.
    if (Message.Contains("request to ") && (Level == ELootLockerLogLevel::Log || Level == ELootLockerLogLevel::Error))
    {
        return;
    }
    FLootLockerLogEntryPtr Entry = MakeShared<FLootLockerLogEntry>();
    Entry->Message = Message;
    Entry->Level = Level;
    Entry->Timestamp = FDateTime::Now();
    Entry->bIsRequestLog = false;
    Entry->Summary = Message;
    LogEntries.Add(Entry);
    RefreshFilter();
}

void SLootLockerLogViewerWidget::AddHttpLogEntry(const FLootLockerHttpLogEntry& HttpEntry)
{
    FLootLockerLogEntryPtr Entry = MakeShared<FLootLockerLogEntry>();
    Entry->bIsRequestLog = true;
    Entry->HttpMethod = HttpEntry.Method;
    Entry->RequestPath = HttpEntry.Path;
    Entry->StatusCode = HttpEntry.StatusCode;
    Entry->Duration = FString::Printf(TEXT("%.3fs"), HttpEntry.Duration);
    Entry->Timestamp = HttpEntry.Timestamp;
    Entry->Level = HttpEntry.bSuccess ? ELootLockerLogLevel::Log : ELootLockerLogLevel::Error;
    Entry->ForPlayerWithUlid = HttpEntry.RequestContext.PlayerUlid.IsEmpty() ? TEXT("N/A") : HttpEntry.RequestContext.PlayerUlid;
    Entry->Message = FString::Printf(TEXT("Request made for player with ULID: %s\nRequest Data: %s\nResponse Data: %s\nRequest Headers: %s"),
        *Entry->ForPlayerWithUlid,
        *HttpEntry.RequestData,
        *HttpEntry.ResponseData,
        *HttpEntry.RequestHeaders);
    Entry->ErrorDocUrl = HttpEntry.ErrorData.Doc_url;
    Entry->ForPlayerWithUlid = HttpEntry.RequestContext.PlayerUlid.IsEmpty() ? TEXT("N/A") : HttpEntry.RequestContext.PlayerUlid;
    // Build summary
    if (!HttpEntry.bSuccess)
    {
        FString ErrorSummary = "";
        if (!HttpEntry.ErrorData.Code.IsEmpty() && !HttpEntry.ErrorData.Message.IsEmpty())
        {
            ErrorSummary = FString::Printf(TEXT("\nError Code: %s\nError Message: %s"), *HttpEntry.ErrorData.Code, *HttpEntry.ErrorData.Message);
        }
        else if (!HttpEntry.ErrorData.Message.IsEmpty())
        {
            ErrorSummary = FString::Printf(TEXT("\nError Message: %s"), *HttpEntry.ErrorData.Message);
        }
        else if (!HttpEntry.ErrorData.Code.IsEmpty())
        {
            ErrorSummary = FString::Printf(TEXT("\nError Code: %s"), *HttpEntry.ErrorData.Code);
        }
        else
        {
            ErrorSummary = TEXT("\nRequest failed");
        }
        Entry->Summary = FString::Printf(TEXT("%s %s Response code: %d %s"), *Entry->HttpMethod, *Entry->RequestPath, Entry->StatusCode, *ErrorSummary);
    }
    else
    {
        Entry->Summary = FString::Printf(TEXT("%s %s  Status: %d"), *Entry->HttpMethod, *Entry->RequestPath, Entry->StatusCode);
    }
    LogEntries.Add(Entry);
    RefreshFilter();
}

TSharedRef<ITableRow> SLootLockerLogViewerWidget::OnGenerateRow(FLootLockerLogEntryPtr InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
    if (InItem->bIsRequestLog)
    {
        FSlateColor SummaryColor = (InItem->StatusCode >= 200 && InItem->StatusCode < 300)
            ? FSlateColor(FLinearColor(0.2f, 0.8f, 0.2f))
            : FSlateColor(FLinearColor(0.9f, 0.2f, 0.2f));
        TWeakPtr<SListView<FLootLockerLogEntryPtr>> WeakListView = LogListView;
        // Add a flag to the entry for doc panel and area expansion
        if (!InItem->bIsExpanded) InItem->bIsExpanded = false;
        return SNew(STableRow<FLootLockerLogEntryPtr>, OwnerTable)
            [
                SNew(SVerticalBox)
                + SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SExpandableArea)
                    .InitiallyCollapsed(!InItem->bIsExpanded)
                    .OnAreaExpansionChanged_Lambda([InItem, WeakListView](bool bExpanded)
                    {
                        InItem->bIsExpanded = bExpanded;
                        if (TSharedPtr<SListView<FLootLockerLogEntryPtr>> ListView = WeakListView.Pin())
                        {
                            ListView->RequestListRefresh();
                        }
                    })
                    .HeaderContent()
                    [
                        SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
                        [
                            SNew(SMultiLineEditableTextBox)
                            .Text(FText::FromString(InItem->Summary))
                            .IsReadOnly(true)
                            .SelectAllTextWhenFocused(false)
                            .AlwaysShowScrollbars(false)
                            .AutoWrapText(true)
                            .Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
                            .ForegroundColor(SummaryColor)
                        ]
                        // Redundant clickable hyperlink in summary
                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Top).Padding(8,0,0,0)
                        [
                            InItem->ErrorDocUrl.IsEmpty() ? SNullWidget::NullWidget :
                            SNew(SButton)
                            .ButtonStyle(FCoreStyle::Get(), "NoBorder")
                            .ToolTipText(FText::FromString(InItem->ErrorDocUrl))
                            .OnClicked_Lambda([Url = InItem->ErrorDocUrl]() {
                                FPlatformProcess::LaunchURL(*Url, nullptr, nullptr);
                                return FReply::Handled();
                            })
                            [
                                SNew(SImage)
                                .Image(FCoreStyle::Get().GetBrush("Icons.Help"))
                                .ColorAndOpacity(FSlateColor(FLinearColor(0.2f,0.5f,1.0f,1.0f)))
                            ]
                        ]
                    ]
                    .BodyContent()
                    [
                        SNew(SBorder)
                        .BorderBackgroundColor(FLinearColor(1,0,0,0.2f))
                        [
                            SNew(SVerticalBox)
                            + SVerticalBox::Slot().AutoHeight()
                            [
                                SNew(STextBlock)
                                .Text(FText::FromString(FString::Printf(TEXT("Timestamp: %s"), *InItem->Timestamp.ToString())))
                                .Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
                                .ColorAndOpacity(FSlateColor(FLinearColor(0.7f,0.7f,0.7f)))
                            ]
                            + SVerticalBox::Slot().AutoHeight()
                            [
                                SNew(STextBlock)
                                .Text(FText::FromString(FString::Printf(TEXT("Duration: %s s"), *InItem->Duration)))
                                .Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
                                .ColorAndOpacity(FSlateColor(FLinearColor(0.7f,0.7f,0.7f)))
                            ]
                            + SVerticalBox::Slot().AutoHeight()
                            [
                                SNew(SMultiLineEditableTextBox)
                                .Text(FText::FromString(InItem->Message))
                                .IsReadOnly(true)
                                .SelectAllTextWhenFocused(false)
                                .AlwaysShowScrollbars(false)
                                .AutoWrapText(true)
                                .Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
                            ]
                        ]
                    ]
                ]
            ];
    }
    FSlateColor SummaryColor;
    switch (InItem->Level)
    {
        case ELootLockerLogLevel::Error:
            SummaryColor = FSlateColor(FLinearColor(0.9f, 0.2f, 0.2f));
            break;
        case ELootLockerLogLevel::Warning:
            SummaryColor = FSlateColor(FLinearColor(1.0f, 0.7f, 0.2f));
            break;
        default:
            SummaryColor = FSlateColor(FLinearColor(0.7f, 0.7f, 0.7f));
            break;
    }
    TWeakPtr<SListView<FLootLockerLogEntryPtr>> WeakListView = LogListView;
    if (!InItem->bIsExpanded) InItem->bIsExpanded = false;
    return SNew(STableRow<FLootLockerLogEntryPtr>, OwnerTable)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot().AutoHeight()
            [
                SNew(SExpandableArea)
                .InitiallyCollapsed(!InItem->bIsExpanded)
                .OnAreaExpansionChanged_Lambda([InItem, WeakListView](bool bExpanded)
                {
                    InItem->bIsExpanded = bExpanded;
                    if (TSharedPtr<SListView<FLootLockerLogEntryPtr>> ListView = WeakListView.Pin())
                    {
                        ListView->RequestListRefresh();
                    }
                })
                .HeaderContent()
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
                    [
                        SNew(SMultiLineEditableTextBox)
                        .Text(FText::FromString(InItem->Summary.IsEmpty() ? InItem->Message : InItem->Summary))
                        .IsReadOnly(true)
                        .SelectAllTextWhenFocused(false)
                        .AlwaysShowScrollbars(false)
                        .AutoWrapText(true)
                        .Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
                        .ForegroundColor(SummaryColor)
                    ]
                    + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Top).Padding(8,0,0,0)
                    [
                        InItem->ErrorDocUrl.IsEmpty() ? SNullWidget::NullWidget :
                        SNew(SButton)
                        .ButtonStyle(FCoreStyle::Get(), "NoBorder")
                        .ToolTipText(FText::FromString(InItem->ErrorDocUrl))
                        .OnClicked_Lambda([Url = InItem->ErrorDocUrl]() {
                            FPlatformProcess::LaunchURL(*Url, nullptr, nullptr);
                            return FReply::Handled();
                        })
                        [
                            SNew(SImage)
                            .Image(FCoreStyle::Get().GetBrush("Icons.Help"))
                            .ColorAndOpacity(FSlateColor(FLinearColor(0.2f,0.5f,1.0f,1.0f)))
                        ]
                    ]
                ]
                .BodyContent()
                [
                    SNew(SBorder)
                    .BorderBackgroundColor(FLinearColor(0,0,0,0.2f))
                    [
                        SNew(SVerticalBox)
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            SNew(STextBlock)
                            .Text(FText::FromString(FString::Printf(TEXT("Timestamp: %s"), *InItem->Timestamp.ToString())))
                            .Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
                            .ColorAndOpacity(FSlateColor(FLinearColor(0.7f,0.7f,0.7f)))
                        ]
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            SNew(SMultiLineEditableTextBox)
                            .Text(FText::FromString(InItem->Message))
                            .IsReadOnly(true)
                            .SelectAllTextWhenFocused(false)
                            .AlwaysShowScrollbars(false)
                            .AutoWrapText(true)
                            .Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
                        ]
                    ]
                ]
            ]
        ];
}

void SLootLockerLogViewerWidget::OnSearchTextChanged(const FText& InText)
{
    SearchText = InText.ToString();
    RefreshFilter();
}

void SLootLockerLogViewerWidget::RefreshFilter()
{
    FilteredEntries.Empty();
    for (const FLootLockerLogEntryPtr& Entry : LogEntries)
    {
        if (Entry->Level <= MinLevel && (SearchText.IsEmpty() || Entry->Message.Contains(SearchText)))
        {
            FilteredEntries.Add(Entry);
        }
    }
    if (LogListView.IsValid())
    {
        LogListView->RequestListRefresh();
    }
}

void SLootLockerLogViewerWidget::OnLevelChanged(ELootLockerLogLevel NewLevel)
{
    MinLevel = NewLevel;
    RefreshFilter();
}

void SLootLockerLogViewerWidget::ClearLog()
{
    LogEntries.Empty();
    RefreshFilter();
}

FReply SLootLockerLogViewerWidget::OnClearLogClicked()
{
    ClearLog();
    return FReply::Handled();
}

void SLootLockerLogViewerWidget::OnClearOnPIEChanged(ECheckBoxState NewState)
{
    bClearOnPIE = (NewState == ECheckBoxState::Checked);
}

ECheckBoxState SLootLockerLogViewerWidget::GetClearOnPIEState() const
{
    return bClearOnPIE ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SLootLockerLogViewerWidget::BindToPIEEvents()
{
#if WITH_EDITOR
    FEditorDelegates::BeginPIE.AddRaw(this, &SLootLockerLogViewerWidget::OnBeginPIE);
#endif
}

void SLootLockerLogViewerWidget::OnBeginPIE(bool /*bIsSimulating*/)
{
    if (bClearOnPIE)
    {
        ClearLog();
    }
}

SLootLockerLogViewerWidget::~SLootLockerLogViewerWidget()
{
    FLootLockerLogger::OnLogMessage.RemoveAll(this);
    FLootLockerLogger::OnHttpLogEntry.RemoveAll(this);
#if WITH_EDITOR
    FEditorDelegates::BeginPIE.RemoveAll(this);
#endif
}
