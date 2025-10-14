// Copyright (c) 2021 LootLocker

#include "LootLockerManagerAsync.h"

#include "LootLockerPlatformManager.h"
#include "LootLockerStateData.h"
#include "GameAPI/LootLockerCatalogRequestHandler.h"
#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"
#include "LootLockerSDKManager.h"

void ULootLockerAsyncStartGuestSession::Activate()
{
	Super::Activate();

    ULootLockerSDKManager::GuestLogin(FLootLockerSessionResponse::CreateLambda([this](const FLootLockerAuthenticationResponse& Response) {
        if (Response.success)
        {
            OnSuccess.Broadcast(
                FLootLockerAsyncSessionResponse{
                    Response.session_token,
                    Response.player_name,
                    Response.player_id,
                    Response.public_uid,
                    Response.player_ulid,
                    Response.player_created_at,
                    Response.seen_before,
                    Response.check_grant_notifications,
                    Response.check_deactivation_notifications,
                    Response.xp,
                    Response.level,
                    Response.level_thresholds,
                    Response.account_balance,
                    Response.player_identifier,
                    Response.wallet_id,
                },
                Response.StatusCode,
                Response.FullTextFromServer,
                Response.ErrorData,
                Response.Context
            );
        }
        else
        {
            OnFailure.Broadcast(
                FLootLockerAsyncSessionResponse(),
                Response.StatusCode,
                Response.FullTextFromServer,
                Response.ErrorData,
                Response.Context
            );            
        }
    }), PlayerIdentifier, Optionals);
}

ULootLockerAsyncStartGuestSession* ULootLockerAsyncStartGuestSession::AsyncStartGuestSession(UObject* WorldContextObject, const FString& PlayerIdentifier, const FLootLockerSessionOptionals& Optionals)
{
	ULootLockerAsyncStartGuestSession* Action = NewObject<ULootLockerAsyncStartGuestSession>();
	Action->PlayerIdentifier = PlayerIdentifier;
	Action->Optionals = Optionals;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}