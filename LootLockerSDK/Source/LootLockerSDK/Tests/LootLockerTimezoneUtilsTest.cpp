// Copyright (c) 2021 LootLocker

#include "Runtime/Launch/Resources/Version.h"
#include "LootLockerTimezoneUtils.h"
#include "Misc/AutomationTest.h"

#if ENGINE_MAJOR_VERSION > 4

BEGIN_DEFINE_SPEC(
    FLootLockerTimezoneUtilsSpec,
    "LootLocker.TimezoneUtils",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FLootLockerTimezoneUtilsSpec)

void FLootLockerTimezoneUtilsSpec::Define()
{
    Describe("Timezone utils", [this]()
    {
        It("UTCOffsetToIanaTimezone_NegativeOffset_UsesInvertedEtcSign", [this]()
        {
            // UTC-5 must be "Etc/GMT+5" (IANA inverts the sign for Etc/GMT zones)
            TestEqual("UTC-5", LootLockerTimezoneUtils::UTCOffsetToIanaTimezone(-5), TEXT("Etc/GMT+5"));
            TestEqual("UTC-2", LootLockerTimezoneUtils::UTCOffsetToIanaTimezone(-2), TEXT("Etc/GMT+2"));
        });

        It("UTCOffsetToIanaTimezone_PositiveOffset_UsesInvertedEtcSign", [this]()
        {
            // UTC+2 must be "Etc/GMT-2" (IANA inverts the sign for Etc/GMT zones)
            TestEqual("UTC+2", LootLockerTimezoneUtils::UTCOffsetToIanaTimezone(2), TEXT("Etc/GMT-2"));
            TestEqual("UTC+11", LootLockerTimezoneUtils::UTCOffsetToIanaTimezone(11), TEXT("Etc/GMT-11"));
        });

        It("UTCOffsetToIanaTimezone_ZeroOffset_ReturnsEtcUTC", [this]()
        {
            TestEqual("UTC+0", LootLockerTimezoneUtils::UTCOffsetToIanaTimezone(0), TEXT("Etc/UTC"));
        });

        It("UTCOffsetToIanaTimezone_OutOfRangeOffset_IsClamped", [this]()
        {
            TestEqual("UTC-99", LootLockerTimezoneUtils::UTCOffsetToIanaTimezone(-99), TEXT("Etc/GMT+12"));
            TestEqual("UTC+99", LootLockerTimezoneUtils::UTCOffsetToIanaTimezone(99), TEXT("Etc/GMT-14"));
        });

        It("IsValidIanaTimezone_AcceptsCorrectlyCasedNames", [this]()
        {
            TestTrue("Etc/UTC", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("Etc/UTC")));
            TestTrue("Etc/GMT+3", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("Etc/GMT+3")));
            TestTrue("Europe/Paris", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("Europe/Paris")));
            TestTrue("America/New_York", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("America/New_York")));
        });

        It("IsValidIanaTimezone_RejectsWronglyCasedNames", [this]()
        {
            // The customer-reported bug: "ETC/GMT" is not a valid IANA name
            TestFalse("ETC/GMT", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("ETC/GMT")));
            TestFalse("etc/utc", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("etc/utc")));
            TestFalse("EUROPE/PARIS", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("EUROPE/PARIS")));
        });

        It("IsValidIanaTimezone_RejectsEmptyAndGarbage", [this]()
        {
            TestFalse("empty", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("")));
            TestFalse("no slash", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("Europe")));
            TestFalse("garbage", LootLockerTimezoneUtils::IsValidIanaTimezone(TEXT("Not/A/Timezone")));
        });

        It("GetLocalIanaTimezone_ReturnsValidTimezone", [this]()
        {
            TestTrue("local timezone is valid IANA", LootLockerTimezoneUtils::IsValidIanaTimezone(LootLockerTimezoneUtils::GetLocalIanaTimezone()));
        });
    });
}

#endif
