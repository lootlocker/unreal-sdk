// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerRemoteSessionRequestHandler.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "LootLockerSDK.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerPlatformManager.h"
#include "LootLockerStateData.h"
#include "Utils/LootLockerUtilities.h"
#include "LootLockerLogger.h"
#include "GameAPI/LootLockerMiscellaneousRequestHandler.h"

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
	ELootLockerRemoteSessionLeaseIntent Intent,
	const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation,
	const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate,
	const FLootLockerStartRemoteSessionResponseDelegate& OnComplete,
	float PollingIntervalSeconds,
	float TimeOutAfterMinutes,
	const FString& ForPlayerWithUlid)
{
	// Cancel any previously ongoing processes
	for (auto& RemoteSessionProcess : RemoteSessionProcesses)
	{
		RemoteSessionProcess.Value.ShouldCancel = true;
	}

	FString ProcessID = FGuid::NewGuid().ToString();
	const FLootLockerRemoteSessionProcess NewRemoteSessionProcess(PollingIntervalSeconds, TimeOutAfterMinutes);
	RemoteSessionProcesses.Add(ProcessID, NewRemoteSessionProcess);

	ULootLockerMiscellaneousRequestHandler::GetGameInfo(FGameInfoResponseDelegate::CreateLambda([
			Intent, 
			ForPlayerWithUlid, 
			RemoteSessionLeaseInformation,
			RemoteSessionLeaseStatusUpdate,
			OnComplete,
			ProcessID](const FLootLockerGameInfoResponse& GameInfoResponse) 
	{
		if(!GameInfoResponse.success) {
				FLootLockerRemoteSessionProcess* _processPtr = RemoteSessionProcesses.Find(ProcessID);
				if (nullptr == _processPtr)
				{
					return;
				}
				KillProcess(ProcessID);
				{
					FLootLockerLeaseRemoteSessionResponse Response;
					Response.success = GameInfoResponse.success;
					Response.FullTextFromServer = GameInfoResponse.FullTextFromServer;
					Response.StatusCode = GameInfoResponse.StatusCode;
					Response.ErrorData = GameInfoResponse.ErrorData;
					Response.Context = GameInfoResponse.Context;
					Response.Status = ELootLockerRemoteSessionLeaseStatus::Failed;
					FLootLockerLeaseRemoteSessionResponseDelegateBP().ExecuteIfBound(Response);
					RemoteSessionLeaseInformation.ExecuteIfBound(Response);
				}
				return;
		}
		LeaseRemoteSession(
			GameInfoResponse.Info.Title_id,
			GameInfoResponse.Info.Environment_id,
			Intent,
			ForPlayerWithUlid, 
			LLAPI<FLootLockerLeaseRemoteSessionResponse>::FResponseInspectorCallback::CreateLambda(
				[RemoteSessionLeaseInformation,
					RemoteSessionLeaseStatusUpdate,
					OnComplete,
					ProcessID](const FLootLockerLeaseRemoteSessionResponse& LeaseResponse)
				{
					FLootLockerRemoteSessionProcess* _processPtr = RemoteSessionProcesses.Find(ProcessID);
					if (nullptr == _processPtr)
					{
						return;
					}
					FLootLockerRemoteSessionProcess& _process = *_processPtr;
					FLootLockerLeaseRemoteSessionResponseDelegateBP().ExecuteIfBound(LeaseResponse);
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
					ContinualPollingAction(ProcessID, RemoteSessionLeaseStatusUpdate, OnComplete);
				}));
				
		}));
	return ProcessID;
}

void ULootLockerRemoteSessionRequestHandler::RefreshRemoteSession(const FString& RefreshToken, const FLootLockerRefreshRemoteSessionResponseDelegate& OnComplete)
{
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	FLootLockerRefreshRemoteSessionRequest AuthRequest;
	AuthRequest.game_key = config->LootLockerGameKey;
	AuthRequest.game_version = config->GameVersion;
	AuthRequest.refresh_token = RefreshToken;

	LLAPI<FLootLockerRefreshRemoteSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshRemoteSessionEndpoint, { }, EmptyQueryParams, FLootLockerPlayerData(), FLootLockerRefreshRemoteSessionResponseDelegateBP(), OnComplete, LLAPI<FLootLockerRefreshRemoteSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerRefreshRemoteSessionResponse& Response)
		{
			if (Response.success)
			{
				FLootLockerPlayerData NewPlayerData = FLootLockerPlayerData::Create(Response.session_token, Response.Refresh_token, Response.player_identifier, Response.player_ulid, Response.public_uid, Response.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Guest), FDateTime::Now().ToString(), Response.player_created_at);
				ULootLockerStateData::SavePlayerData(NewPlayerData);
			}
		}));

}

void ULootLockerRemoteSessionRequestHandler::ContinualPollingAction(const FString& ProcessID,
                                                                    const FLootLockerRemoteSessionStatusPollingResponseDelegate& RemoteSessionLeaseStatusUpdate,
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
		FLootLockerStartRemoteSessionResponseDelegateBP().ExecuteIfBound(TimedOutResponse);
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
		FLootLockerStartRemoteSessionResponseDelegateBP().ExecuteIfBound(CanceledResponse);
		OnComplete.ExecuteIfBound(CanceledResponse);
		KillProcess(ProcessID);
		return;
	}

	// Get the latest state of the process
	StartRemoteSession(_process.LeaseCode, _process.LeaseNonce, LLAPI<FLootLockerStartRemoteSessionResponse>::FResponseInspectorCallback::CreateLambda([RemoteSessionLeaseStatusUpdate, OnComplete, ProcessID](FLootLockerStartRemoteSessionResponse& RemoteSessionResponse)
		{
			FLootLockerRemoteSessionProcess* _innerProcessPtr = RemoteSessionProcesses.Find(ProcessID);
			if (nullptr == _innerProcessPtr)
			{
				return;
			}
			FLootLockerRemoteSessionProcess& _innerProcess = *_innerProcessPtr;

			auto _scheduleNextPoll = [RemoteSessionLeaseStatusUpdate, OnComplete](FTimerHandle& TimerHandle, const float& timeToNextPoll, const FString& ProcessID) {
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindLambda([RemoteSessionLeaseStatusUpdate, OnComplete, ProcessID]()
					{
						ContinualPollingAction(ProcessID, RemoteSessionLeaseStatusUpdate, OnComplete);
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
				FLootLockerStartRemoteSessionResponseDelegateBP().ExecuteIfBound(RemoteSessionResponse);
				OnComplete.ExecuteIfBound(RemoteSessionResponse);
				KillProcess(ProcessID);
				return;
			}

			// Check if process is completed
			if (ELootLockerRemoteSessionLeaseStatus::Authorized == RemoteSessionResponse.Lease_Status)
			{
				if (!RemoteSessionResponse.player_ulid.IsEmpty())
				{
					FLootLockerPlayerData NewPlayerData = FLootLockerPlayerData::Create(RemoteSessionResponse.session_token, RemoteSessionResponse.Refresh_token, RemoteSessionResponse.player_identifier, RemoteSessionResponse.player_ulid, RemoteSessionResponse.public_uid, RemoteSessionResponse.player_name, "", "", ULootLockerPlatforms::GetPlatformRepresentationForPlatform(ELootLockerPlatform::Remote), FDateTime::Now().ToString(), RemoteSessionResponse.player_created_at);
					ULootLockerStateData::SavePlayerData(NewPlayerData);					
				}
				FLootLockerStartRemoteSessionResponseDelegateBP().ExecuteIfBound(RemoteSessionResponse);
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
			FLootLockerRemoteSessionStatusPollingResponseDelegateBP().ExecuteIfBound(UpdateResponse);
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

void ULootLockerRemoteSessionRequestHandler::LeaseRemoteSession(
    const FString& TitleId,
    const FString& EnvironmentId,
    ELootLockerRemoteSessionLeaseIntent Intent,
    const FString& ForPlayerWithUlid,
    const LLAPI<FLootLockerLeaseRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback)
{
	FLootLockerEndPoints Endpoint = ULootLockerGameEndpoints::LeaseRemoteSessionEndpoint;
	FLootLockerPlayerData UserData = FLootLockerPlayerData();
	if (Intent == ELootLockerRemoteSessionLeaseIntent::link)
	{
		Endpoint = ULootLockerGameEndpoints::LeaseRemoteSessionForLinkingEndpoint;
		UserData = ULootLockerStateData::GetSavedStateOrDefaultOrEmptyForPlayer(ForPlayerWithUlid);
	}
    FLootLockerLeaseRemoteSessionRequest RequestBody;
    RequestBody.Title_id = TitleId;
    RequestBody.Environment_id = EnvironmentId;
	const ULootLockerConfig* config = GetDefault<ULootLockerConfig>();
	RequestBody.Game_version = config ? config->GameVersion : TEXT("");
    LLAPI<FLootLockerLeaseRemoteSessionResponse>::CallAPI(HttpClient, RequestBody, Endpoint, {}, {}, UserData, FLootLockerLeaseRemoteSessionResponseDelegateBP(), FLootLockerLeaseRemoteSessionResponseDelegate(), OnCompleteCallback);
}

void ULootLockerRemoteSessionRequestHandler::StartRemoteSession(const FString& LeaseCode, const FString& LeaseNonce, const LLAPI<FLootLockerStartRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback)
{
	const auto* config = GetDefault<ULootLockerConfig>();
	LLAPI<FLootLockerStartRemoteSessionResponse>::CallAPI(HttpClient, FLootLockerStartRemoteSessionRequest{ config->LootLockerGameKey, config->GameVersion, LeaseCode, LeaseNonce }, ULootLockerGameEndpoints::StartRemoteSessionEndpoint, {}, {}, FLootLockerPlayerData(), FLootLockerStartRemoteSessionResponseDelegateBP(), FLootLockerStartRemoteSessionResponseDelegate(), OnCompleteCallback);
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
		OnProcessFailed.Broadcast(LeaseProcessID, LeaseData, false, "", "", FLootLockerRemoteSessionPlayerData(), static_cast<FLootLockerResponse>(LeaseProcessStartedResponse));
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
	OnProcessStarted.Broadcast(LeaseProcessID, LeaseData, false, "", "", FLootLockerRemoteSessionPlayerData(), static_cast<FLootLockerResponse>(LeaseProcessStartedResponse));
}

void ULootLockerAsyncStartRemoteSession::HandleLeaseProcessUpdate(const FLootLockerRemoteSessionStatusPollingResponse& LeaseProcessUpdateResponse)
{
	//This should only ever be reachable in cases Created, Claimed, and Verified as the other cases are called to ProcessCompleted
	switch (LeaseProcessUpdateResponse.Lease_status)
	{
		case ELootLockerRemoteSessionLeaseStatus::Created:
			FLootLockerLogger::LogVerbose(TEXT("Process Update without change from default state (Created) received"));
			break;
		case ELootLockerRemoteSessionLeaseStatus::Claimed:
			OnLeaseClaimed.Broadcast(LeaseProcessID, LeaseData, false, "", "", FLootLockerRemoteSessionPlayerData(), static_cast<FLootLockerResponse>(LeaseProcessUpdateResponse));
			break;
		case ELootLockerRemoteSessionLeaseStatus::Verified:
			OnLeaseVerified.Broadcast(LeaseProcessID, LeaseData, false, "", "", FLootLockerRemoteSessionPlayerData(), static_cast<FLootLockerResponse>(LeaseProcessUpdateResponse));
			break;
		case ELootLockerRemoteSessionLeaseStatus::Authorized:
		case ELootLockerRemoteSessionLeaseStatus::Cancelled:
		case ELootLockerRemoteSessionLeaseStatus::Timed_out:
		case ELootLockerRemoteSessionLeaseStatus::Failed:
		default:
			FLootLockerResponse Error = LootLockerResponseFactory::Error<FLootLockerResponse>(FString::Printf(TEXT("Unreachable branch was reached for remote session with lease update %d"), LeaseProcessUpdateResponse.Lease_status), LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, "N/A");
        	FLootLockerLogger::LogHttpRequest(Error, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(ULootLockerGameEndpoints::LeaseRemoteSessionEndpoint.requestMethod)), ULootLockerGameEndpoints::LeaseRemoteSessionEndpoint.endpoint, "No Data", "No Headers");
			OnProcessFailed.Broadcast(LeaseProcessID, LeaseData, false, "", "", FLootLockerRemoteSessionPlayerData(), Error);
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
			!LeaseProcessCompletedResponse.session_token.IsEmpty(),
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
				LeaseProcessCompletedResponse.player_created_at,
				LeaseProcessCompletedResponse.wallet_id,
			},
			static_cast<FLootLockerResponse>(LeaseProcessCompletedResponse));
		break;
	case ELootLockerRemoteSessionLeaseStatus::Cancelled:
		OnProcessCancelled.Broadcast(
			LeaseProcessID,
			LeaseData, 
			false,
			"",
			"",
			FLootLockerRemoteSessionPlayerData(),
			static_cast<FLootLockerResponse>(LeaseProcessCompletedResponse));
		break;
	case ELootLockerRemoteSessionLeaseStatus::Timed_out:
		OnProcessTimedOut.Broadcast(
			LeaseProcessID,
			LeaseData,
			false,
			"",
			"",
			FLootLockerRemoteSessionPlayerData(),
			static_cast<FLootLockerResponse>(LeaseProcessCompletedResponse));
		break;
	case ELootLockerRemoteSessionLeaseStatus::Failed:
		OnProcessFailed.Broadcast(
			LeaseProcessID,
			LeaseData,
			false,
			"",
			"",
			FLootLockerRemoteSessionPlayerData(),
			static_cast<FLootLockerResponse>(LeaseProcessCompletedResponse));
		break;

	case ELootLockerRemoteSessionLeaseStatus::Created:
	case ELootLockerRemoteSessionLeaseStatus::Claimed:
	case ELootLockerRemoteSessionLeaseStatus::Verified:
	default:
		FLootLockerResponse Error = LootLockerResponseFactory::Error<FLootLockerResponse>(FString::Printf(TEXT("Unreachable branch was reached for remote session with lease completed %d"), LeaseProcessCompletedResponse.Lease_Status), LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, "N/A");
		FLootLockerLogger::LogHttpRequest(Error, ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerHTTPMethod"), static_cast<int32>(ULootLockerGameEndpoints::LeaseRemoteSessionEndpoint.requestMethod)), ULootLockerGameEndpoints::LeaseRemoteSessionEndpoint.endpoint, "No Data", "No Headers");
		OnProcessFailed.Broadcast(LeaseProcessID, LeaseData, false, "", "", FLootLockerRemoteSessionPlayerData(), Error);
		ULootLockerRemoteSessionRequestHandler::CancelRemoteSessionProcess(LeaseProcessID);
		break;
	}

	SetReadyToDestroy();
}

ULootLockerAsyncStartRemoteSession* ULootLockerAsyncStartRemoteSession::AsyncStartRemoteSession(UObject* WorldContextObject, float PollingIntervalSeconds, float TimeOutAfterMinutes)
{
	ULootLockerAsyncStartRemoteSession* Action = NewObject<ULootLockerAsyncStartRemoteSession>();
	Action->PollingIntervalInSeconds = PollingIntervalSeconds;
	Action->TimeoutAfterMinutes = TimeOutAfterMinutes;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

ULootLockerAsyncStartRemoteSession* ULootLockerAsyncStartRemoteSession::AsyncStartRemoteSessionForLinking(UObject* WorldContextObject, FString ForPlayerWithUlid, float PollingIntervalSeconds, float TimeOutAfterMinutes)
{
	ULootLockerAsyncStartRemoteSession* Action = NewObject<ULootLockerAsyncStartRemoteSession>();
	Action->PollingIntervalInSeconds = PollingIntervalSeconds;
	Action->TimeoutAfterMinutes = TimeOutAfterMinutes;
	Action->Intent = ELootLockerRemoteSessionLeaseIntent::link;
	Action->ForPlayerWithUlid = ForPlayerWithUlid;
	Action->RegisterWithGameInstance(WorldContextObject);
	return Action;
}

void ULootLockerAsyncStartRemoteSession::Activate()
{
	Super::Activate();
	
	LeaseProcessID = ULootLockerRemoteSessionRequestHandler::StartRemoteSession(
		Intent,
		FLootLockerLeaseRemoteSessionResponseDelegate::CreateLambda([this](const FLootLockerLeaseRemoteSessionResponse& R) { HandleLeaseProcessStarted(R); }),
		FLootLockerRemoteSessionStatusPollingResponseDelegate::CreateLambda([this](const FLootLockerRemoteSessionStatusPollingResponse& R) { HandleLeaseProcessUpdate(R); }),
		FLootLockerStartRemoteSessionResponseDelegate::CreateLambda([this](const FLootLockerStartRemoteSessionResponse& R) { HandleLeaseProcessCompleted(R); }),
		PollingIntervalInSeconds,
		TimeoutAfterMinutes,
		ForPlayerWithUlid);
}
