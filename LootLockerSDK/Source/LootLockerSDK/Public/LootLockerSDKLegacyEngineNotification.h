// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "LootLockerSDKLegacyEngineNotification.generated.h"

UCLASS()
class LOOTLOCKERSDK_API ULootLockerSDKLegacyEngineNotification : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	ULootLockerSDKLegacyEngineNotification()
	{
		ShowNotificationInSeconds = InitialTimer * BackOff;
		BackOff *= BackOffRate;
	}

	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual bool IsTickableInEditor() const override;
	virtual TStatId GetStatId() const override;

	UFUNCTION()
	void ShowEngineVersionOutOfMarketplaceSupportNotification() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker")
	FString EngineVersionOutOfMarketplaceSupportWarning = "Due to Unreal Marketplace restrictions, LootLocker can no longer be updated through the marketplace for this Unreal Engine version. \nTo get new features and fixes, update using our GitHub (https://github.com/LootLocker/unreal-sdk) to get the latest version.";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker")
	bool IsEngineVersionOutOfMarketplaceSupport = true;
private:
	int BackOff = 1;
	int BackOffRate = 10;
	float InitialTimer = 60.0f;
	float ShowNotificationInSeconds = 0.0f;
};
