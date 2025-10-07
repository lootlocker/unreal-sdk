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

	bool IsSet() const
	{
		return !Timezone.IsEmpty();
	}
};