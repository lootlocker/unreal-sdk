// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LootLockerResponse.h"
#include "LootLockerConfig.h"
#include "JsonObjectConverter.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "GameAPI/LootLockerAssetsRequestHandler.h"
#include "LootLockerPlayerRequestHandler.generated.h"


USTRUCT(BlueprintType)
struct FLootLockerBalanceResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	float balance = 0.0f;
};

USTRUCT(BlueprintType)
struct FLootLockerDlcResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FString> dlcs;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerInfoResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 account_balance = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerLevelThresholds level_thresholds;
};

USTRUCT(BlueprintType)
struct FLootLockerOtherPlayersXpAndLevelResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerRental {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool is_rental = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString time_left;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString duration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString is_active;
};
USTRUCT(BlueprintType)
struct FLootLockerInventory {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString rental_option_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerRental rental;
};
USTRUCT(BlueprintType)
struct FLootLockerInventoryResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerInventory> inventory;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerLevel {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp_threshold = 0;
};
USTRUCT(BlueprintType)
struct FLootLockerXp {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 previous = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 current = 0;
};
USTRUCT(BlueprintType)
struct FLootLockerSubmitXpResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerXp xp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerLevel> levels;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	bool check_grant_notifications = false;
};
USTRUCT(BlueprintType)
struct FLootLockerSubmitXpRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 points = 0;
};
USTRUCT(BlueprintType)
struct FLootLockerObjects
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 instance_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 variation_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerAsset asset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString acquisition_source;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString reason;
};
USTRUCT(BlueprintType)
struct FLootLockerPlayerAssetNotificationResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerObjects> objects;
};

USTRUCT(BlueprintType)
struct FLootLockerNameResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerNameRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
};

USTRUCT(BlueprintType)
struct FLootLockerPlayerXpInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 xp = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 level = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayerXpResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerPlayerXpInfo> players;
};


USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayersNames
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_public_uid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString last_active_platform;
};

USTRUCT(BlueprintType)
struct FLootLockerPlatformIds
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int32 steam_id = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString xbox_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
    int32 psn_id = 0;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayersPlatformIds
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_public_uid;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString last_active_platform;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FLootLockerPlatformIds platform_ids;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayersPlatformIdsResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerMultiplePlayersPlatformIds> players;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayersNamesResponse : public FLootLockerResponse {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerMultiplePlayersNames> players;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayersXpRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString platform;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FString> player_ids;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayerNameRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString platform;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString player_id;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayerNamesRequest {
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	TArray<FLootLockerMultiplePlayerNameRequest> player_ids;
};

USTRUCT(BlueprintType)
struct FLootLockerMultiplePlayerNamesAndPlatformsRequest {
	GENERATED_BODY()
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		TArray<FString> player_ids;
	    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
		TArray<FString> player_public_uids;
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FPInfoResponseBP, FLootLockerPlayerInfoResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPInventoryResponseBP, FLootLockerInventoryResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPSubmitResponseBP, FLootLockerSubmitXpResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPAssetNotificationResponseBP, FLootLockerPlayerAssetNotificationResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPBalanceResponseBP, FLootLockerBalanceResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPDlcResponseBP, FLootLockerDlcResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPNameResponseBP, FLootLockerNameResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPMultiplePlayersXPBP, FLootLockerMultiplePlayerXpResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPMultiplePlayerNamesBP, FLootLockerMultiplePlayersNamesResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPMultiplePlayersPlatformIdsBP, FLootLockerMultiplePlayersPlatformIdsResponse, Value);

DECLARE_DYNAMIC_DELEGATE_OneParam(FPOtherPlayersXpAndLevelBP, FLootLockerOtherPlayersXpAndLevelResponse, Value);

DECLARE_DELEGATE_OneParam(FPMultiplePlayersXP, FLootLockerMultiplePlayerXpResponse);

DECLARE_DELEGATE_OneParam(FLootLockerPlayerInformationResponse, FLootLockerPlayerInfoResponse);

DECLARE_DELEGATE_OneParam(FOtherPlayersXpAndLevelResponse, FLootLockerOtherPlayersXpAndLevelResponse);

DECLARE_DELEGATE_OneParam(FInventoryResponse, FLootLockerInventoryResponse);

DECLARE_DELEGATE_OneParam(FSubmitXpResponse, FLootLockerSubmitXpResponse);

DECLARE_DELEGATE_OneParam(FLootLockerAssetNotificationResponse, FLootLockerPlayerAssetNotificationResponse);

DECLARE_DELEGATE_OneParam(FPBalanceResponse, FLootLockerBalanceResponse);

DECLARE_DELEGATE_OneParam(FPDlcResponse, FLootLockerDlcResponse);

DECLARE_DELEGATE_OneParam(FPNameResponse, FLootLockerNameResponse);

DECLARE_DELEGATE_OneParam(FPMultiplePlayerNames, FLootLockerMultiplePlayersNamesResponse)

DECLARE_DELEGATE_OneParam(FPMultiplePlayersPlatformIdsNames, FLootLockerMultiplePlayersPlatformIdsResponse);

UCLASS()
class LOOTLOCKERSDK_API ULootLockerPlayerRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerPlayerRequestHandler();
	static void GetPlayerInfo(const FPInfoResponseBP& OnCompletedRequestBP = FPInfoResponseBP(), const FLootLockerPlayerInformationResponse& OnCompletedRequest = FLootLockerPlayerInformationResponse());
	static void GetInventory(const FPInventoryResponseBP& OnCompletedRequestBP = FPInventoryResponseBP(), const FInventoryResponse& OnCompletedRequest = FInventoryResponse());
	static void GetFullInventory(const FPInventoryResponseBP& OnCompletedRequestBP, const FInventoryResponse& OnCompletedRequest = FInventoryResponse(), int32
	                             StartIndex = 0);
	static void SubmitXp(int Points, const FPSubmitResponseBP& OnCompletedRequestBP = FPSubmitResponseBP(), const FSubmitXpResponse& OnCompletedRequest = FSubmitXpResponse());
	static void GetOtherPlayersXpAndLevel(FString OtherPlayerId, FString OtherPlayerPlatform, const FPOtherPlayersXpAndLevelBP OnCompletedRequestBP = FPOtherPlayersXpAndLevelBP(), const
	                               FOtherPlayersXpAndLevelResponse& OnCompletedRequest = FOtherPlayersXpAndLevelResponse());
	static void GetMultiplePlayersXp(FLootLockerMultiplePlayersXpRequest Request, const FPMultiplePlayersXPBP& OnCompletedRequestBP =
		                                 FPMultiplePlayersXPBP(), const FPMultiplePlayersXP& OnCompletedRequest = FPMultiplePlayersXP());
	static void CheckPlayerAssetNotification(const FPAssetNotificationResponseBP& OnCompletedRequestBP = FPAssetNotificationResponseBP(), const FLootLockerAssetNotificationResponse& OnCompletedRequest = FLootLockerAssetNotificationResponse());
	static void GetCurrencyBalance(const FPBalanceResponseBP& OnCompletedRequestBP = FPBalanceResponseBP(), const FPBalanceResponse& OnCompletedRequest = FPBalanceResponse());
	static void InitiateDLCMigration(const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
	static void GetDLCsMigration(const FPDlcResponseBP& OnCompletedRequestBP = FPDlcResponseBP(), const FPDlcResponse& OnCompletedRequest = FPDlcResponse());
	static void SetProfilePrivate(const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
	static void SetProfilePublic(const FResponseCallbackBP& OnCompletedRequestBP = FResponseCallbackBP(), const FResponseCallback& OnCompletedRequest = FResponseCallback());
	static void SetPlayerName(FString Name, const FPNameResponseBP& OnCompletedRequestBP = FPNameResponseBP(), const FPNameResponse& OnCompletedRequest = FPNameResponse());
	static void GetPlayerName(const FPNameResponseBP& OnCompletedRequestBP = FPNameResponseBP(), const FPNameResponse& OnCompletedRequest = FPNameResponse());
	static void LookupMultiplePlayerNamesUsingIDs(FLootLockerMultiplePlayerNamesRequest Request, const FPMultiplePlayerNamesBP& OnCompletedRequestBP = FPMultiplePlayerNamesBP(), const FPMultiplePlayerNames& OnCompletedRequest = FPMultiplePlayerNames());
	static void LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsBP& OnCompletedRequestBP = FPMultiplePlayersPlatformIdsBP(), const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest = FPMultiplePlayersPlatformIdsNames());
    static void DeletePlayer(const FLootLockerDefaultResponseBP& OnCompletedRequestBP = FLootLockerDefaultResponseBP(), const FLootLockerDefaultDelegate OnCompletedRequest = FLootLockerDefaultDelegate());

public:
	static ULootLockerHttpClient* HttpClient;
};
