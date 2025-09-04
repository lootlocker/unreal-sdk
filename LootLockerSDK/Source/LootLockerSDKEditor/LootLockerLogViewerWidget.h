// Copyright (c) 2025 LootLocker
// LootLockerLogViewerWidget.h
#pragma once

#include "Widgets/SCompoundWidget.h"
#include "LootLockerLogger.h"
#include "Widgets/Views/SListView.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Templates/SharedPointer.h"
#include "Containers/Map.h"

class SSearchBox;

struct FLootLockerLogEntry
{
    FString Message;
    ELootLockerLogLevel Level;
    FDateTime Timestamp;
    // Request log summary fields
    bool bIsRequestLog = false;
    FString RequestPath;
    FString HttpMethod;
    int32 StatusCode = -1;
    FString Summary;
    FString Duration;
    FString ForPlayerWithUlid;
    bool bIsExpanded = false;
    FString ErrorDocUrl;
};

typedef TSharedPtr<FLootLockerLogEntry> FLootLockerLogEntryPtr;

class SLootLockerLogViewerWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SLootLockerLogViewerWidget) {}
    SLATE_END_ARGS()
    void Construct(const FArguments& InArgs);
    ~SLootLockerLogViewerWidget();
    /**
     * Adds a log entry from a string message and log level. Only parses legacy or non-HTTP logs.
     * @param Message The log message.
     * @param Level The log verbosity level.
     */
    void AddLogEntry(const FString& Message, ELootLockerLogLevel Level);

    /**
     * Adds a log entry from a structured HTTP log entry. This is the preferred method for HTTP logs.
     * @param HttpEntry The structured HTTP log entry.
     */
    void AddHttpLogEntry(const FLootLockerHttpLogEntry& HttpEntry);

    /**
     * Clears the log entries from the viewer.
     */
    void ClearLog();

    /**
     * Gets whether the log should be cleared on PIE (Play In Editor).
     */
    bool GetClearOnPIE() const { return bClearOnPIE; }
    /**
     * Sets whether the log should be cleared on PIE (Play In Editor).
     */
    void SetClearOnPIE(bool bInClear) { bClearOnPIE = bInClear; }
private:
    TArray<FLootLockerLogEntryPtr> LogEntries;
    TArray<FLootLockerLogEntryPtr> FilteredEntries;
    TSharedPtr<SListView<FLootLockerLogEntryPtr>> LogListView;
    TSharedPtr<SSearchBox> SearchBox;
    FString SearchText;
    ELootLockerLogLevel MinLevel = ELootLockerLogLevel::Verbose;
    bool bClearOnPIE = false;
    TSharedRef<ITableRow> OnGenerateRow(FLootLockerLogEntryPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);
    void OnSearchTextChanged(const FText& InText);
    void RefreshFilter();
    void OnLevelChanged(ELootLockerLogLevel NewLevel);
    FReply OnClearLogClicked();
    void OnClearOnPIEChanged(ECheckBoxState NewState);
    ECheckBoxState GetClearOnPIEState() const;
    void BindToPIEEvents();
    void OnBeginPIE(bool bIsSimulating);

    // Static doc content cache and helpers for static popup
    static TMap<FString, FString> DocUrlContentCache;
    static TSet<FString> DocUrlContentPending;
    static FString ExtractHtmlSectionById(const FString& Html, const FString& Id);
    static void FetchDocUrlContentStatic(const FString& Url, const FString& Fragment, FLootLockerLogEntryPtr Entry);
};
