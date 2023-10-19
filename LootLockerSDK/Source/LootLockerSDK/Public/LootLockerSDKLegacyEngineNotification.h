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
	FString EngineVersionOutOfMarketplaceSupportWarning = "Due to Unreal Engine Marketplace restrictions you will no longer be able to update LootLocker through the Unreal Marketplace.\nPlease update using GitHub instead";
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LootLocker")
	bool IsEngineVersionOutOfMarketplaceSupport = true;
private:
	int BackOff = 1;
	int BackOffRate = 10;
	float InitialTimer = 5.0f;
	float ShowNotificationInSeconds = 0.0f;
};
