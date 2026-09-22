// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"

/**
 * Internal helper for producing IANA timezone strings accepted by the LootLocker backend.
 *
 * LootLocker expects IANA timezone names (https://www.iana.org/time-zones) when starting
 * a session. IANA names are case-sensitive: "ETC/GMT" is invalid while "Etc/GMT" is valid.
 *
 * Note the inverted Etc/GMT sign convention mandated by IANA: Etc/GMT+X means UTC-X.
 */
namespace LootLockerTimezoneUtils
{
	/**
	 * Get the local system timezone as an IANA timezone string.
	 * On Windows the OS reports Windows timezone names, which are converted to IANA.
	 *
	 * @return IANA timezone string, eg "Europe/Paris", "America/New_York" or "Etc/UTC"
	 */
	FString LOOTLOCKERSDK_API GetLocalIanaTimezone();

	/**
	 * Convert a UTC offset in hours to an IANA Etc/GMT timezone string.
	 *
	 * @param UTCOffsetHours UTC offset in hours (eg -5 for UTC-5); clamped to [-12, 14]
	 * @return IANA timezone string, eg "Etc/GMT+5", "Etc/GMT-2" or "Etc/UTC"
	 */
	FString LOOTLOCKERSDK_API UTCOffsetToIanaTimezone(int32 UTCOffsetHours);

	/**
	 * Check whether the given string is a known IANA timezone.
	 *
	 * @param Timezone Timezone string to validate
	 * @return True if the string is a supported IANA timezone
	 */
	bool LOOTLOCKERSDK_API IsValidIanaTimezone(const FString& Timezone);
}
