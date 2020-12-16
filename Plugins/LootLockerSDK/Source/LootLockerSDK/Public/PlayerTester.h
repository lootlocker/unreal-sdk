// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerRequestHandler.h"
#include "LootLockerSDKManager.h"
#include "AuthenticationRequestHandler.h"
#include "PlayerTester.generated.h"

UCLASS()
class LOOTLOCKERSDK_API APlayerTester : public AActor
{
	GENERATED_BODY()

public:
	APlayerTester();
	void OnGetPlayerInfoRequestCompleted(FPlayerInfoResponse response);
	void OnInventoryRequestCompleted(FInventoryResponse response);
	void OnSubmitXpRequestCompleted(FSubmitXpResponse response);
	void OnGetOtherPlayerInfoRequestCompleted(FPlayerInfoResponse response);
	void OnCheckPlayerAssetNotificationRequestCompleted(FPlayerAssetNotificationResponse response);
	void OnCheckPlayerAssetDeactivationNotificationRequestCompleted(FPlayerAssetNotificationResponse response);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		ULootLockerSDKManager* LootLockerSDKManager;
};
