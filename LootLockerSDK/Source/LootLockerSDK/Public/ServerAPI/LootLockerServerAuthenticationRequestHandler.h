// Copyright (c) 2021 LootLocker

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootLockerConfig.h"
#include "LootLockerHttpClient.h"
#include "JsonObjectConverter.h"

#include "LootLockerServerAuthenticationRequestHandler.generated.h"

USTRUCT(BlueprintType)
struct FLootLockerServerAuthenticationRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	FString game_version;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Startup Item")
	bool is_development = false;
};

USTRUCT(BlueprintType)
struct FLootLockerServerAuthenticationResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	FString token;
};

USTRUCT(BlueprintType)
struct FLootLockerServerPingResponse : public FLootLockerResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LootLocker")
	int pong = -1;
};

USTRUCT(BlueprintType)
struct FLootLockerServerEndSessionResponse : public FLootLockerResponse
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FServerAuthResponseDelegateBP, FLootLockerServerAuthenticationResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FServerPingResponseDelegateBP, FLootLockerServerPingResponse, Response);
DECLARE_DYNAMIC_DELEGATE_OneParam(FServerEndSessionResponseDelegateBP, FLootLockerServerEndSessionResponse, Response);

DECLARE_DELEGATE_OneParam(FServerAuthResponseDelegate, FLootLockerServerAuthenticationResponse);
DECLARE_DELEGATE_OneParam(FServerPingResponseDelegate, FLootLockerServerPingResponse);
DECLARE_DELEGATE_OneParam(FServerEndSessionResponseDelegate, FLootLockerServerEndSessionResponse);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOOTLOCKERSDK_API ULootLockerServerAuthenticationRequestHandler : public UObject
{
	GENERATED_BODY()
public:
	ULootLockerServerAuthenticationRequestHandler();

public:
	static void StartSession(const FServerAuthResponseDelegateBP& OnCompletedRequestBP = FServerAuthResponseDelegateBP(), const FServerAuthResponseDelegate& OnCompletedRequest = FServerAuthResponseDelegate());
	static void Ping(const FServerPingResponseDelegateBP& OnCompletedRequestBP = FServerPingResponseDelegateBP(), const FServerPingResponseDelegate& OnCompletedRequest = FServerPingResponseDelegate());
	static void EndSession(const FServerEndSessionResponseDelegateBP& OnCompletedRequestBP = FServerEndSessionResponseDelegateBP(), const FServerEndSessionResponseDelegate& OnCompletedRequest = FServerEndSessionResponseDelegate());
	static ULootLockerHttpClient* HttpClient;
};
