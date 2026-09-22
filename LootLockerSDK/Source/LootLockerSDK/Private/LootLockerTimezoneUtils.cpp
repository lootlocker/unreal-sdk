// Copyright (c) 2021 LootLocker

#include "LootLockerTimezoneUtils.h"
#include "HAL/PlatformMisc.h"
#include "Misc/DateTime.h"

namespace
{
	/**
	 * Minimal Windows-to-IANA mapping covering the timezones actually exposed by
	 * Windows' GetTimeZoneInformation. Names are case-normalized ("Dateline Standard Time"
	 * style) and matched case-insensitively, since Windows display strings vary by SKU.
	 */
	const TMap<FString, FString>& GetWindowsToIanaMap()
	{
		static TMap<FString, FString> WindowsToIana = {
			{"Dateline Standard Time", "Etc/GMT+12"},
			{"UTC-11", "Etc/GMT+11"},
			{"Aleutian Standard Time", "America/Adak"},
			{"Hawaiian Standard Time", "Pacific/Honolulu"},
			{"Marquesas Standard Time", "Pacific/Marquesas"},
			{"Alaskan Standard Time", "America/Anchorage"},
			{"UTC-09", "Etc/GMT+9"},
			{"Pacific Standard Time (Mexico)", "America/Tijuana"},
			{"UTC-08", "Etc/GMT+8"},
			{"Pacific Standard Time", "America/Los_Angeles"},
			{"US Mountain Standard Time", "America/Phoenix"},
			{"Mountain Standard Time (Mexico)", "America/Chihuahua"},
			{"Mountain Standard Time", "America/Denver"},
			{"Central America Standard Time", "America/Guatemala"},
			{"Central Standard Time", "America/Chicago"},
			{"Easter Island Standard Time", "Pacific/Easter"},
			{"Central Standard Time (Mexico)", "America/Mexico_City"},
			{"Canada Central Standard Time", "America/Regina"},
			{"SA Pacific Standard Time", "America/Bogota"},
			{"Eastern Standard Time", "America/New_York"},
			{"US Eastern Standard Time", "America/Indiana/Petersburg"},
			{"Venezuela Standard Time", "America/Caracas"},
			{"Paraguay Standard Time", "America/Asuncion"},
			{"Atlantic Standard Time", "America/Halifax"},
			{"Central Brazilian Standard Time", "America/Cuiaba"},
			{"SA Western Standard Time", "America/La_Paz"},
			{"Pacific SA Standard Time", "America/Santiago"},
			{"Newfoundland Standard Time", "America/St_Johns"},
			{"Tocantins Standard Time", "America/Araguaina"},
			{"E. South America Standard Time", "America/Sao_Paulo"},
			{"SA Eastern Standard Time", "America/Cayenne"},
			{"Argentina Standard Time", "America/Buenos_Aires"},
			{"Greenland Standard Time", "America/Nuuk"},
			{"Montevideo Standard Time", "America/Montevideo"},
			{"Magallanes Standard Time", "America/Punta_Arenas"},
			{"Saint Pierre Standard Time", "America/Miquelon"},
			{"Bahia Standard Time", "America/Bahia"},
			{"UTC-02", "Etc/GMT+2"},
			{"Azores Standard Time", "Atlantic/Azores"},
			{"Cape Verde Standard Time", "Atlantic/Cape_Verde"},
			{"UTC", "Etc/UTC"},
			{"GMT Standard Time", "Europe/London"},
			{"Greenwich Standard Time", "Atlantic/Reykjavik"},
			{"Sao Tome Standard Time", "Africa/Sao_Tome"},
			{"Morocco Standard Time", "Africa/Casablanca"},
			{"W. Europe Standard Time", "Europe/Berlin"},
			{"Central Europe Standard Time", "Europe/Prague"},
			{"Romance Standard Time", "Europe/Paris"},
			{"Central European Standard Time", "Europe/Warsaw"},
			{"W. Central Africa Standard Time", "Africa/Lagos"},
			{"Jordan Standard Time", "Asia/Amman"},
			{"GTB Standard Time", "Europe/Athens"},
			{"Middle East Standard Time", "Asia/Beirut"},
			{"Egypt Standard Time", "Africa/Cairo"},
			{"E. Europe Standard Time", "Europe/Bucharest"},
			{"Syria Standard Time", "Asia/Damascus"},
			{"West Bank Standard Time", "Asia/Hebron"},
			{"South Africa Standard Time", "Africa/Johannesburg"},
			{"FLE Standard Time", "Europe/Kiev"},
			{"Israel Standard Time", "Asia/Jerusalem"},
			{"Kaliningrad Standard Time", "Europe/Kaliningrad"},
			{"Sudan Standard Time", "Africa/Khartoum"},
			{"Libya Standard Time", "Africa/Tripoli"},
			{"Namibia Standard Time", "Africa/Windhoek"},
			{"Arabic Standard Time", "Asia/Baghdad"},
			{"Turkey Standard Time", "Europe/Istanbul"},
			{"Arab Standard Time", "Asia/Riyadh"},
			{"Belarus Standard Time", "Europe/Minsk"},
			{"Russian Standard Time", "Europe/Moscow"},
			{"E. Africa Standard Time", "Africa/Nairobi"},
			{"Iran Standard Time", "Asia/Tehran"},
			{"Arabian Standard Time", "Asia/Dubai"},
			{"Astrakhan Standard Time", "Europe/Astrakhan"},
			{"Azerbaijan Standard Time", "Asia/Baku"},
			{"Russia Time Zone 3", "Europe/Samara"},
			{"Mauritius Standard Time", "Indian/Mauritius"},
			{"Saratov Standard Time", "Europe/Saratov"},
			{"Georgian Standard Time", "Asia/Tbilisi"},
			{"Caucasus Standard Time", "Asia/Yerevan"},
			{"Afghanistan Standard Time", "Asia/Kabul"},
			{"West Asia Standard Time", "Asia/Karachi"},
			{"Ekaterinburg Standard Time", "Asia/Yekaterinburg"},
			{"Pakistan Standard Time", "Asia/Karachi"},
			{"India Standard Time", "Asia/Calcutta"},
			{"Sri Lanka Standard Time", "Asia/Colombo"},
			{"Nepal Standard Time", "Asia/Kathmandu"},
			{"Central Asia Standard Time", "Asia/Almaty"},
			{"Bangladesh Standard Time", "Asia/Dhaka"},
			{"Omsk Standard Time", "Asia/Omsk"},
			{"Myanmar Standard Time", "Asia/Rangoon"},
			{"SE Asia Standard Time", "Asia/Bangkok"},
			{"Altai Standard Time", "Asia/Barnaul"},
			{"W. Mongolia Standard Time", "Asia/Hovd"},
			{"North Asia Standard Time", "Asia/Krasnoyarsk"},
			{"N. Central Asia Standard Time", "Asia/Novosibirsk"},
			{"Tomsk Standard Time", "Asia/Tomsk"},
			{"China Standard Time", "Asia/Shanghai"},
			{"North Asia East Standard Time", "Asia/Irkutsk"},
			{"Singapore Standard Time", "Asia/Singapore"},
			{"W. Australia Standard Time", "Australia/Perth"},
			{"Taipei Standard Time", "Asia/Taipei"},
			{"Ulaanbaatar Standard Time", "Asia/Ulaanbaatar"},
			{"Aus Central W. Standard Time", "Australia/Eucla"},
			{"Tokyo Standard Time", "Asia/Tokyo"},
			{"North Korea Standard Time", "Asia/Pyongyang"},
			{"Korea Standard Time", "Asia/Seoul"},
			{"Yakutsk Standard Time", "Asia/Yakutsk"},
			{"Cen. Australia Standard Time", "Australia/Adelaide"},
			{"AUS Central Standard Time", "Australia/Darwin"},
			{"E. Australia Standard Time", "Australia/Brisbane"},
			{"AUS Eastern Standard Time", "Australia/Sydney"},
			{"West Pacific Standard Time", "Pacific/Guam"},
			{"Tasmania Standard Time", "Australia/Hobart"},
			{"Vladivostok Standard Time", "Asia/Vladivostok"},
			{"Lord Howe Standard Time", "Australia/Lord_Howe"},
			{"Bougainville Standard Time", "Pacific/Bougainville"},
			{"Russia Time Zone 10", "Asia/Magadan"},
			{"Magadan Standard Time", "Asia/Magadan"},
			{"Sakhalin Standard Time", "Asia/Sakhalin"},
			{"Central Pacific Standard Time", "Pacific/Guadalcanal"},
			{"Australia Central Standard Time", "Australia/Darwin"},
			{"Russia Time Zone 11", "Asia/Kamchatka"},
			{"New Zealand Standard Time", "Pacific/Auckland"},
			{"UTC+12", "Etc/GMT-12"},
			{"Fiji Standard Time", "Pacific/Fiji"},
			{"Chatham Islands Standard Time", "Pacific/Chatham"},
			{"UTC+13", "Etc/GMT-13"},
			{"Tonga Standard Time", "Pacific/Tongatapu"},
			{"Samoa Standard Time", "Pacific/Pago_Pago"},
			{"Kamchatka Standard Time", "Asia/Kamchatka"}
		};
		return WindowsToIana;
	}
}

namespace LootLockerTimezoneUtils
{
	FString GetLocalIanaTimezone()
	{
#if PLATFORM_WINDOWS
		const FString WindowsTz = FPlatformMisc::GetTimeZoneSetting();
		if (!WindowsTz.IsEmpty())
		{
			const TMap<FString, FString>& Map = GetWindowsToIanaMap();
			const FString* Found = Map.Find(WindowsTz);
			if (Found)
			{
				return *Found;
			}
		}
		// Fall through to offset-based fallback
#endif
		// Offset-based fallback: derive the UTC offset from local vs UTC clock.
		const FDateTime Now = FDateTime::Now();
		const FDateTime UtcNow = FDateTime::UtcNow();
		const int32 OffsetHours = static_cast<int32>((Now - UtcNow).GetTotalHours());
		return UTCOffsetToIanaTimezone(OffsetHours);
	}

	FString UTCOffsetToIanaTimezone(int32 UTCOffsetHours)
	{
		UTCOffsetHours = FMath::Clamp(UTCOffsetHours, -12, 14);
		if (UTCOffsetHours < 0)
		{
			return FString::Printf(TEXT("Etc/GMT+%d"), -UTCOffsetHours); // Note the reversed sign for Etc/GMT
		}
		if (UTCOffsetHours > 0)
		{
			return FString::Printf(TEXT("Etc/GMT-%d"), UTCOffsetHours); // Note the reversed sign for Etc/GMT
		}
		return TEXT("Etc/UTC");
	}

	bool IsValidIanaTimezone(const FString& Timezone)
	{
		if (Timezone.IsEmpty())
		{
			return false;
		}
		// Etc/UTC, Etc/GMT, Etc/GMT+X and Etc/GMT-X are the offset zones we produce ourselves
		if (Timezone == TEXT("Etc/UTC") || Timezone == TEXT("Etc/GMT"))
		{
			return true;
		}
		if (Timezone.StartsWith(TEXT("Etc/GMT+")) || Timezone.StartsWith(TEXT("Etc/GMT-")))
		{
			const FString Suffix = Timezone.RightChop(8);
			if (Suffix.IsNumeric())
			{
				const int32 Value = FCString::Atoi(*Suffix);
				return Value >= 0 && Value <= 14;
			}
			return false;
		}
		// Any named zone we can map back from is considered valid (case-sensitive lookup)
		const TMap<FString, FString>& Map = GetWindowsToIanaMap();
		for (const auto& Pair : Map)
		{
			if (Pair.Value == Timezone)
			{
				return true;
			}
		}
		// Common named zones not present in the Windows map (non-Windows platforms report
		// these directly); accept well-formed "Area/Location" names with a known IANA area.
		static const TArray<FString> ValidAreas = {
			TEXT("Africa"), TEXT("America"), TEXT("Antarctica"), TEXT("Arctic"),
			TEXT("Asia"), TEXT("Atlantic"), TEXT("Australia"), TEXT("Europe"),
			TEXT("Indian"), TEXT("Pacific")
		};
		if (!Timezone.Contains(TEXT("/")))
		{
			return false;
		}
		const FString Area = Timezone.Left(Timezone.Find(TEXT("/"), ESearchCase::CaseSensitive));
		return ValidAreas.Contains(Area);
	}
}
