// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerRemoteSessionRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPlatformManager.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerRemoteSessionRequestHandler::HttpClient = nullptr;
TMap<FString, FLootLockerRemoteSessionProcess> ULootLockerRemoteSessionRequestHandler::RemoteSessionProcesses = TMap<FString, FLootLockerRemoteSessionProcess>();

FLootLockerRemoteSessionProcess::FLootLockerRemoteSessionProcess(const float _PollingIntervalSeconds, 
                                                                 float timeOutAfterMinutes)
	: LeasingProcessTimeoutTime(FDateTime::UtcNow() + FTimespan::FromMinutes(timeOutAfterMinutes)),
	PollingIntervalSeconds(_PollingIntervalSeconds),
	LastUpdatedAt(FDateTime::UtcNow())
{
}

ULootLockerRemoteSessionRequestHandler::ULootLockerRemoteSessionRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerRemoteSessionRequestHandler::CancelRemoteSessionProcess(const FString& ProcessID)
{
	FLootLockerRemoteSessionProcess* _processPtr = RemoteSessionProcesses.Find(ProcessID);
	if (nullptr != _processPtr)
	{
		_processPtr->ShouldCancel = true;
	}
}

FString ULootLockerRemoteSessionRequestHandler::StartRemoteSession(
	const FLootLockerPlayerData& PlayerData,
	ELootLockerRemoteSessionLeaseIntent Intent,
	const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformationBP,
	const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation,
	const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdateBP,
	const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate,
	const FLootLockerStartRemoteSessionResponseDelegateBP& OnCompleteBP,
	const FLootLockerStartRemoteSessionResponseDelegate& OnComplete,
	float PollingIntervalSeconds,
	float TimeOutAfterMinutes)
{
	// Cancel any previously ongoing processes
	for (auto& RemoteSessionProcess : RemoteSessionProcesses)
	{
		RemoteSessionProcess.Value.ShouldCancel = true;
	}

	FString ProcessID = FGuid::NewGuid().ToString();
	const FLootLockerRemoteSessionProcess NewRemoteSessionProcess(PollingIntervalSeconds, TimeOutAfterMinutes);
	RemoteSessionProcesses.Add(ProcessID, NewRemoteSessionProcess);
	LeaseRemoteSession(PlayerData,
		Intent,
		LLAPI<FLootLockerLeaseRemoteSessionResponse>::FResponseInspectorCallback::CreateLambda(
			[RemoteSessionLeaseInformationBP,
			RemoteSessionLeaseInformation,
			RemoteSessionLeaseStatusUpdateBP,
			RemoteSessionLeaseStatusUpdate,
			OnCompleteBP,
			OnComplete,
			ProcessID,
			PlayerData](const FLootLockerLeaseRemoteSessionResponse& LeaseResponse)
			{
				FLootLockerRemoteSessionProcess* _processPtr = RemoteSessionProcesses.Find(ProcessID);
				if (nullptr == _processPtr)
				{
					return;
				}
				FLootLockerRemoteSessionProcess& _process = *_processPtr;
				RemoteSessionLeaseInformationBP.ExecuteIfBound(LeaseResponse);
				RemoteSessionLeaseInformation.ExecuteIfBound(LeaseResponse);
				if (!LeaseResponse.success)
				{
					KillProcess(ProcessID);
					return;
				}

				_process.LeaseCode = LeaseResponse.Code;
				_process.LeaseNonce = LeaseResponse.Nonce;
				_process.LastUpdatedAt = FDateTime::UtcNow();
				_process.LastUpdatedStatus = LeaseResponse.Status;
				ContinualPollingAction(PlayerData, ProcessID, RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete);
			}));
	return ProcessID;
}

void ULootLockerRemoteSessionRequestHandler::RefreshRemoteSession(const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegateBP& OnCompleteBP, const FLootLockerRefreshRemoteSessionResponseDelegate& OnComplete)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerRefreshRemoteSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	LLAPI<FLootLockerRefreshRemoteSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshRemoteSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), OnCompleteBP, OnComplete, LLAPI<FLootLockerRefreshRemoteSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerRefreshRemoteSessionResponse& Response)
		{
			if (Response.success)
			{
				FLootLockerPlayerData NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.Refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest), FDateTime::Now().ToString());
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));

}

void ULootLockerRemoteSessionRequestHandler::ContinualPollingAction(const FLootLockerPlayerData& PlayerData, const FString& ProcessID,
	const FLootLockerRemoteSessionStatusPollingResponseDelegateBP& RemoteSessionLeaseStatusUpdateBP,
	const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate,
	const FLootLockerStartRemoteSessionResponseDelegateBP& OnCompleteBP,
	const FLootLockerStartRemoteSessionResponseDelegate& OnComplete)
{
	const FLootLockerRemoteSessionProcess* _processPtr = RemoteSessionProcesses.Find(ProcessID);
	if (nullptr == _processPtr)
	{
		return;
	}
	const FLootLockerRemoteSessionProcess& _process = *_processPtr;

	// Are we timed out?
	if (_process.LeasingProcessTimeoutTime <= FDateTime::UtcNow())
	{
		FLootLockerStartRemoteSessionResponse TimedOutResponse;
		TimedOutResponse.Lease_Status = ELootLockerRemoteSessionLeaseStatus::Timed_out;
		TimedOutResponse.success = false;
		TimedOutResponse.Context.PlayerUlid = PlayerData.PlayerUlid;
		OnCompleteBP.ExecuteIfBound(TimedOutResponse);
		OnComplete.ExecuteIfBound(TimedOutResponse);
		KillProcess(ProcessID);
		return;
	}

	// Should we cancel?
	if (_process.ShouldCancel)
	{
		FLootLockerStartRemoteSessionResponse CanceledResponse;
		CanceledResponse.Lease_Status = ELootLockerRemoteSessionLeaseStatus::Cancelled;
		CanceledResponse.success = false;
		CanceledResponse.Context.PlayerUlid = PlayerData.PlayerUlid;
		OnCompleteBP.ExecuteIfBound(CanceledResponse);
		OnComplete.ExecuteIfBound(CanceledResponse);
		KillProcess(ProcessID);
		return;
	}

	// Get the latest state of the process
	StartRemoteSession(PlayerData, _process.LeaseCode, _process.LeaseNonce, LLAPI<FLootLockerStartRemoteSessionResponse>::FResponseInspectorCallback::CreateLambda([RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete, ProcessID, PlayerData](FLootLockerStartRemoteSessionResponse& RemoteSessionResponse)
		{
			FLootLockerRemoteSessionProcess* _innerProcessPtr = RemoteSessionProcesses.Find(ProcessID);
			if (nullptr == _innerProcessPtr)
			{
				return;
			}
			FLootLockerRemoteSessionProcess& _innerProcess = *_innerProcessPtr;

			auto _scheduleNextPoll = [RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete, PlayerData](FTimerHandle& TimerHandle, const float& timeToNextPoll, const FString& ProcessID) {
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete, ProcessID, PlayerData]()
					{
						ContinualPollingAction(PlayerData, ProcessID, RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete);
					});

				SetTimer(TimerHandle, TimerDelegate, timeToNextPoll);
				};

			if (!RemoteSessionResponse.success)
			{
				// Check if it's a recoverable error and if so, schedule poller again
				if (RemoteSessionResponse.StatusCode >= 500 && RemoteSessionResponse.StatusCode <= 599 && _innerProcess.Retries <= _innerProcess.RetryLimit)
				{
					_innerProcess.Retries++;
					_scheduleNextPoll(_innerProcess.RemoteSessionProcessTimerHandle, _innerProcess.PollingIntervalSeconds, ProcessID);
					return;
				}

				// Non recoverable error, fail process
				RemoteSessionResponse.Lease_Status = ELootLockerRemoteSessionLeaseStatus::Failed;
				OnCompleteBP.ExecuteIfBound(RemoteSessionResponse);
				OnComplete.ExecuteIfBound(RemoteSessionResponse);
				KillProcess(ProcessID);
				return;
			}

			// Check if process is completed
			if (ELootLockerRemoteSessionLeaseStatus::Authorized == RemoteSessionResponse.Lease_Status)
			{
				if (!RemoteSessionResponse.player_ulid.IsEmpty())
				{
					FLootLockerPlayerData NewPlayerData = FLootLockerPlayerData::Create(RemoteSessionResponse.session_token, RemoteSessionResponse.Refresh_token, RemoteSessionResponse.player_identifier, RemoteSessionResponse.player_ulid, RemoteSessionResponse.public_uid, RemoteSessionResponse.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest), FDateTime::Now().ToString());
					ULootLockerStateData::SavePlayerData(NewPlayerData);					
				}
				OnCompleteBP.ExecuteIfBound(RemoteSessionResponse);
				OnComplete.ExecuteIfBound(RemoteSessionResponse);
				KillProcess(ProcessID);
				return;
			}

			// Trigger update callback and reschedule poller
			FLootLockerRemoteSessionStatusPollingResponse UpdateResponse;
			UpdateResponse.Lease_status = RemoteSessionResponse.Lease_Status;
			UpdateResponse.FullTextFromServer = RemoteSessionResponse.FullTextFromServer;
			UpdateResponse.StatusCode = RemoteSessionResponse.StatusCode;
			UpdateResponse.success = RemoteSessionResponse.success;
			UpdateResponse.ErrorData = RemoteSessionResponse.ErrorData;
			RemoteSessionLeaseStatusUpdateBP.ExecuteIfBound(UpdateResponse);
			RemoteSessionLeaseStatusUpdate.ExecuteIfBound(UpdateResponse);
			_innerProcess.LastUpdatedAt = FDateTime::UtcNow();
			_innerProcess.LastUpdatedStatus = UpdateResponse.Lease_status;
			_scheduleNextPoll(_innerProcess.RemoteSessionProcessTimerHandle, _innerProcess.PollingIntervalSeconds, ProcessID);
		}));
}

void ULootLockerRemoteSessionRequestHandler::KillProcess(const FString& ProcessID)
{
	FLootLockerRemoteSessionProcess* _processPtr = RemoteSessionProcesses.Find(ProcessID);
	if (nullptr == _processPtr)
	{
		return;
	}
	FLootLockerRemoteSessionProcess& _process = *_processPtr;

	ClearTimer(_process.RemoteSessionProcessTimerHandle);
	RemoteSessionProcesses.Remove(ProcessID);
}

void ULootLockerRemoteSessionRequestHandler::LeaseRemoteSession(const FLootLockerPlayerData& PlayerData, ELootLockerRemoteSessionLeaseIntent Intent, const LLAPI<FLootLockerLeaseRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback)
{
	const auto* config = GetDefault<ULootLockerConfig>();
	LLAPI<FLootLockerLeaseRemoteSessionResponse>::CallAPI(HttpClient, FLootLockerLeaseRemoteSessionRequest{ config->LootLockerGameKey, config->GameVersion }, Intent == ELootLockerRemoteSessionLeaseIntent::login ? ULootLockerGameEndpoints::LeaseRemoteSessionEndpoint : ULootLockerGameEndpoints::LeaseRemoteSessionForLinkingEndpoint, {}, {}, PlayerData, FLootLockerLeaseRemoteSessionResponseDelegateBP(), FLootLockerLeaseRemoteSessionResponseDelegate(), OnCompleteCallback);
}

void ULootLockerRemoteSessionRequestHandler::StartRemoteSession(const FLootLockerPlayerData& PlayerData, const FString& LeaseCode, const FString& LeaseNonce, const LLAPI<FLootLockerStartRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback)
{
	const auto* config = GetDefault<ULootLockerConfig>();
	LLAPI<FLootLockerStartRemoteSessionResponse>::CallAPI(HttpClient, FLootLockerStartRemoteSessionRequest{ config->LootLockerGameKey, config->GameVersion, LeaseCode, LeaseNonce }, ULootLockerGameEndpoints::StartRemoteSessionEndpoint, {}, {}, PlayerData, FLootLockerStartRemoteSessionResponseDelegateBP(), FLootLockerStartRemoteSessionResponseDelegate(), OnCompleteCallback);
}

void ULootLockerRemoteSessionRequestHandler::SetTimer(FTimerHandle TimerHandle, const FTimerDelegate& BaseDelegate, float TimeToNextPoll)
{
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->GetWorld()) {
		GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(TimerHandle, BaseDelegate, TimeToNextPoll, false);
	}
}

void ULootLockerRemoteSessionRequestHandler::ClearTimer(FTimerHandle TimerHandle)
{
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->GetWorld()) {
		GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(TimerHandle, -1.0f, false);
	}
}

void ULootLockerAsyncStartRemoteSession::HandleLeaseProcessStarted(const FLootLockerLeaseRemoteSessionResponse& LeaseProcessStartedResponse)
{
	if (!LeaseProcessStartedResponse.success)
	{
		OnProcessFailed.Broadcast(LeaseProcessID, LeaseData, "", "", FLootLockerRemoteSessionPlayerData(), static_cast<FLootLockerResponse>(LeaseProcessStartedResponse));
		SetReadyToDestroy();
		return;
	}

	LeaseData = FLootLockerRemoteSessionLeaseData{
		LeaseProcessStartedResponse.Code,
		LeaseProcessStartedResponse.Nonce,
		LeaseProcessStartedResponse.Redirect_url,
		LeaseProcessStartedResponse.Redirect_url_qr_base64,
		LeaseProcessStartedResponse.Display_url
	};
	OnProcessStarted.Broadcast(LeaseProcessID, LeaseData, "", "", FLootLockerRemoteSessionPlayerData(), static_cast<FLootLockerResponse>(LeaseProcessStartedResponse));
}

void ULootLockerAsyncStartRemoteSession::HandleLeaseProcessUpdate(const FLootLockerRemoteSessionStatusPollingResponse& LeaseProcessUpdateResponse)
{
	//This should only ever be reachable in cases Created, Claimed, and Verified as the other cases are called to ProcessCompleted
	switch (LeaseProcessUpdateResponse.Lease_status)
	{
		case ELootLockerRemoteSessionLeaseStatus::Created:
			UE_LOG(LogLootLockerGameSDK, Verbose, TEXT("Process Update without change from default state (Created) received"))
			break;
		case ELootLockerRemoteSessionLeaseStatus::Claimed:
			OnLeaseClaimed.Broadcast(LeaseProcessID, LeaseData, "", "", FLootLockerRemoteSessionPlayerData(), static_cast<FLootLockerResponse>(LeaseProcessUpdateResponse));
			break;
		case ELootLockerRemoteSessionLeaseStatus::Verified:
			OnLeaseVerified.Broadcast(LeaseProcessID, LeaseData, "", "", FLootLockerRemoteSessionPlayerData(), static_cast<FLootLockerResponse>(LeaseProcessUpdateResponse));
			break;
		case ELootLockerRemoteSessionLeaseStatus::Authorized:
		case ELootLockerRemoteSessionLeaseStatus::Cancelled:
		case ELootLockerRemoteSessionLeaseStatus::Timed_out:
		case ELootLockerRemoteSessionLeaseStatus::Failed:
		default:
			UE_LOG(LogLootLockerGameSDK, Error, TEXT("Unreachable branch was reached for remote session with lease update %d"), LeaseProcessUpdateResponse.Lease_status)
			OnProcessFailed.Broadcast(LeaseProcessID, LeaseData, "", "", FLootLockerRemoteSessionPlayerData(), LootLockerResponseFactory::Error<FLootLockerResponse>("Unreachable branch was reached for remote session with lease update " + FString::FromInt(static_cast<int>(LeaseProcessUpdateResponse.Lease_status)), LootLockerStaticRequestErrorStatusCodes::LL_UNDEFINED_BEHAVIOUR_ERROR, ForPlayerWithUlid));
			ULootLockerRemoteSessionRequestHandler::CancelRemoteSessionProcess(LeaseProcessID);
			SetReadyToDestroy();
			break;
	}
}

void ULootLockerAsyncStartRemoteSession::HandleLeaseProcessCompleted(const FLootLockerStartRemoteSessionResponse& LeaseProcessCompletedResponse)
{
	//This should only ever be reachable in cases Authorized, Cancelled, Timed Out, and Failed as the other cases are called to ProcessUpdate
	switch (LeaseProcessCompletedResponse.Lease_Status)
	{
	case ELootLockerRemoteSessionLeaseStatus::Authorized:
		OnProcessFinished.Broadcast(
			LeaseProcessID,
			LeaseData,
			LeaseProcessCompletedResponse.session_token,
			LeaseProcessCompletedResponse.Refresh_token,
			FLootLockerRemoteSessionPlayerData{
				LeaseProcessCompletedResponse.player_name,
				LeaseProcessCompletedResponse.player_id,
				LeaseProcessCompletedResponse.public_uid,
				LeaseProcessCompletedResponse.player_ulid,
				LeaseProcessCompletedResponse.seen_before,
				LeaseProcessCompletedResponse.check_grant_notifications,
				LeaseProcessCompletedResponse.check_deactivation_notifications,
				LeaseProcessCompletedResponse.xp,
				LeaseProcessCompletedResponse.level,
				LeaseProcessCompletedResponse.level_thresholds,
				LeaseProcessCompletedResponse.account_balance,
				LeaseProcessCompletedResponse.player_identifier,
				LeaseProcessCompletedResponse.wallet_id,
			},
			static_cast<FLootLockerResponse>(LeaseProcessCompletedResponse));
		break;
	case ELootLockerRemoteSessionLeaseStatus::Cancelled:
		OnProcessCancelled.Broadcast(
			LeaseProcessID,
			LeaseData,
			LeaseProcessCompletedResponse.session_token,
			LeaseProcessCompletedResponse.Refresh_token,
			FLootLockerRemoteSessionPlayerData{
				LeaseProcessCompletedResponse.player_name,
				LeaseProcessCompletedResponse.player_id,
				LeaseProcessCompletedResponse.public_uid,
				LeaseProcessCompletedResponse.player_ulid,
				LeaseProcessCompletedResponse.seen_before,
				LeaseProcessCompletedResponse.check_grant_notifications,
				LeaseProcessCompletedResponse.check_deactivation_notifications,
				LeaseProcessCompletedResponse.xp,
				LeaseProcessCompletedResponse.level,
				LeaseProcessCompletedResponse.level_thresholds,
				LeaseProcessCompletedResponse.account_balance,
				LeaseProcessCompletedResponse.player_identifier,
				LeaseProcessCompletedResponse.wallet_id,
			},
			static_cast<FLootLockerResponse>(LeaseProcessCompletedResponse));
		break;
	case ELootLockerRemoteSessionLeaseStatus::Timed_out:
		OnProcessTimedOut.Broadcast(
			LeaseProcessID,
			LeaseData,
			LeaseProcessCompletedResponse.session_token,
			LeaseProcessCompletedResponse.Refresh_token,
			FLootLockerRemoteSessionPlayerData{
				LeaseProcessCompletedResponse.player_name,
				LeaseProcessCompletedResponse.player_id,
				LeaseProcessCompletedResponse.public_uid,
				LeaseProcessCompletedResponse.player_ulid,
				LeaseProcessCompletedResponse.seen_before,
				LeaseProcessCompletedResponse.check_grant_notifications,
				LeaseProcessCompletedResponse.check_deactivation_notifications,
				LeaseProcessCompletedResponse.xp,
				LeaseProcessCompletedResponse.level,
				LeaseProcessCompletedResponse.level_thresholds,
				LeaseProcessCompletedResponse.account_balance,
				LeaseProcessCompletedResponse.player_identifier,
				LeaseProcessCompletedResponse.wallet_id,
			},
			static_cast<FLootLockerResponse>(LeaseProcessCompletedResponse));
		break;
	case ELootLockerRemoteSessionLeaseStatus::Failed:
		OnProcessFailed.Broadcast(
			LeaseProcessID,
			LeaseData,
			LeaseProcessCompletedResponse.session_token,
			LeaseProcessCompletedResponse.Refresh_token,
			FLootLockerRemoteSessionPlayerData{
				LeaseProcessCompletedResponse.player_name,
				LeaseProcessCompletedResponse.player_id,
				LeaseProcessCompletedResponse.public_uid,
				LeaseProcessCompletedResponse.player_ulid,
				LeaseProcessCompletedResponse.seen_before,
				LeaseProcessCompletedResponse.check_grant_notifications,
				LeaseProcessCompletedResponse.check_deactivation_notifications,
				LeaseProcessCompletedResponse.xp,
				LeaseProcessCompletedResponse.level,
				LeaseProcessCompletedResponse.level_thresholds,
				LeaseProcessCompletedResponse.account_balance,
				LeaseProcessCompletedResponse.player_identifier,
				LeaseProcessCompletedResponse.wallet_id,
			},
			static_cast<FLootLockerResponse>(LeaseProcessCompletedResponse));
		break;

	case ELootLockerRemoteSessionLeaseStatus::Created:
	case ELootLockerRemoteSessionLeaseStatus::Claimed:
	case ELootLockerRemoteSessionLeaseStatus::Verified:
	default:
		UE_LOG(LogLootLockerGameSDK, Error, TEXT("Unreachable branch was reached for remote session with lease completed %d"), LeaseProcessCompletedResponse.Lease_Status)
		OnProcessFailed.Broadcast(LeaseProcessID, LeaseData, "", "", FLootLockerRemoteSessionPlayerData(), LootLockerResponseFactory::Error<FLootLockerResponse>("Unreachable branch was reached for remote session with lease completed " + FString::FromInt(static_cast<int>(LeaseProcessCompletedResponse.Lease_Status)), LootLockerStaticRequestErrorStatusCodes::LL_UNDEFINED_BEHAVIOUR_ERROR, ForPlayerWithUlid));
		ULootLockerRemoteSessionRequestHandler::CancelRemoteSessionProcess(LeaseProcessID);
		break;
	}

	SetReadyToDestroy();
}

ULootLockerAsyncStartRemoteSession* ULootLockerAsyncStartRemoteSession::AsyncStartRemoteSession(UObject* WorldContextObject, const FString& ForPlayerWithUlid, float PollingIntervalSeconds, float TimeOutAfterMinutes)
{
	ULootLockerAsyncStartRemoteSession* Action = NewObject<ULootLockerAsyncStartRemoteSession>();
	Action->ForPlayerWithUlid = ForPlayerWithUlid;
	Action->PollingIntervalInSeconds = PollingIntervalSeconds;
	Action->TimeoutAfterMinutes = TimeOutAfterMinutes;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

ULootLockerAsyncStartRemoteSession* ULootLockerAsyncStartRemoteSession::AsyncStartRemoteSessionForLinking(UObject* WorldContextObject, const FString& ForPlayerWithUlid, float PollingIntervalSeconds, float TimeOutAfterMinutes)
{
	ULootLockerAsyncStartRemoteSession* Action = NewObject<ULootLockerAsyncStartRemoteSession>();
	Action->ForPlayerWithUlid = ForPlayerWithUlid;
	Action->PollingIntervalInSeconds = PollingIntervalSeconds;
	Action->TimeoutAfterMinutes = TimeOutAfterMinutes;
	Action->Intent = ELootLockerRemoteSessionLeaseIntent::link;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void ULootLockerAsyncStartRemoteSession::Activate()
{
	Super::Activate();

	LeaseProcessID = ULootLockerRemoteSessionRequestHandler::StartRemoteSession(ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid),
		Intent,
		FLootLockerLeaseRemoteSessionResponseDelegateBP(),
		FLootLockerLeaseRemoteSessionResponseDelegate::CreateLambda([this](const FLootLockerLeaseRemoteSessionResponse& R) { HandleLeaseProcessStarted(R); }),
		FLootLockerRemoteSessionStatusPollingResponseDelegateBP(),
		FLootLockerRemoteSessionStatusPollingResponseDelegate::CreateLambda([this](const FLootLockerRemoteSessionStatusPollingResponse& R) { HandleLeaseProcessUpdate(R); }),
		FLootLockerStartRemoteSessionResponseDelegateBP(),
		FLootLockerStartRemoteSessionResponseDelegate::CreateLambda([this](const FLootLockerStartRemoteSessionResponse& R) { HandleLeaseProcessCompleted(R); }),
		PollingIntervalInSeconds,
		TimeoutAfterMinutes);
}
