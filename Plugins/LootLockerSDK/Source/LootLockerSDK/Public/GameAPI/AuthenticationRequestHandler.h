// Copyright (c) 2020 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootLockerConfig.h"
#include "HttpClient.h"
#include "JsonObjectConverter.h"
#include "AuthenticationRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FAuthenticationRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString platform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString player_identifier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_version;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool development_mode;
	FAuthenticationRequest() {}
};

USTRUCT(BlueprintType)
struct FVerificationRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString platform;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString token;
	FVerificationRequest() {}
};

USTRUCT(BlueprintType)
struct FLevelThresholds
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 current;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool current_is_prestige;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 next;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool next_is_prestige;
};


USTRUCT(BlueprintType)
struct FAuthenticationResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 player_id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool seen_before;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool check_grant_notifications;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool check_deactivation_notifications;

	// TODO: This warning property. I`m dont know what type in Array
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//TArray<?> check_dlcs;

	// TODO: "public" is not valid property name. "public" is C++ key word 
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//bool public;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 xp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 level;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLevelThresholds level_thresholds;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 account_balance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString session_token;
public:
	FAuthenticationResponse()
	{

	}
};



USTRUCT(BlueprintType)
struct FAuthenticationDefaultResponse : public FLootLockerResponse
{
	GENERATED_BODY()
public:
	FAuthenticationDefaultResponse()
	{

	}
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAuthResponseBP, FAuthenticationResponse, AuthVar);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAuthDefaultResponseBP, FAuthenticationDefaultResponse, AuthVar);
DECLARE_DELEGATE_OneParam(FLootLockerSessionResponse, FAuthenticationResponse);
DECLARE_DELEGATE_OneParam(FLootLockerDefaultAuthenticationResponse, FAuthenticationDefaultResponse);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOOTLOCKERSDK_API UAuthenticationRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	UAuthenticationRequestHandler();

public:
	static void StartSession(const FString& PlayerId, const FAuthResponseBP& OnCompletedRequestBP = FAuthResponseBP(), const FLootLockerSessionResponse& OnCompletedRequest = FLootLockerSessionResponse());
	static void VerifyPlayer(const FString& SteamToken, const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static void EndSession(const FAuthDefaultResponseBP& OnCompletedRequestBP = FAuthDefaultResponseBP(), const FLootLockerDefaultAuthenticationResponse& OnCompletedRequest = FLootLockerDefaultAuthenticationResponse());
	static UHttpClient* HttpClient;
};
