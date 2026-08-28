#pragma once

#include "CoreMinimal.h"
#include "LootLockerSessionOptionals.generated.h"

/**
Optional parameters that can be sent when starting a session.
These are a collection of configuration options relating to the player whom the session is being started for.
*/
USTRUCT(BlueprintType)
struct FLootLockerSessionOptionals 
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	/**
	 * Timezone in IANA format. If not supplied, will be set to UTC.
	 */
	FString Timezone = "";
	/**
	 * The name of the player (same as set by SetPlayerName). If not supplied, will be left blank.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	FString Player_name = "";
	/**
	 * Whether to automatically create a profile for the player if one does not exist. Defaults to true.
	 * 
	 * Set to false if you want to ensure that a profile is not created for the player if one does not exist. In this case, the session will fail with a 404 Player Not Found error if the player does not have a profile.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LootLocker")
	bool Auto_create_profile = true;

	bool IsSet() const
	{
		return !Timezone.IsEmpty() || !Player_name.IsEmpty() || Auto_create_profile != true;
	}
};