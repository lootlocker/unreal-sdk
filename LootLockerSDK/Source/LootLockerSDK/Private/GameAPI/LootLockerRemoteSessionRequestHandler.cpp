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
	if(nullptr != _processPtr)
	{
		_processPtr->ShouldCancel = true;
	}
}

FString ULootLockerRemoteSessionRequestHandler::StartRemoteSession(
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
	LeaseRemoteSession(
		LLAPI<FLootLockerLeaseRemoteSessionResponse>::FResponseInspectorCallback::CreateLambda(
			[RemoteSessionLeaseInformationBP,
			RemoteSessionLeaseInformation,
			RemoteSessionLeaseStatusUpdateBP,
			RemoteSessionLeaseStatusUpdate,
			OnCompleteBP,
			OnComplete,
			ProcessID](const FLootLockerLeaseRemoteSessionResponse& LeaseResponse)
	{
		FLootLockerRemoteSessionProcess* _processPtr = RemoteSessionProcesses.Find(ProcessID);
		if (nullptr == _processPtr)
		{
			return;
		}
		FLootLockerRemoteSessionProcess& _process = *_processPtr;
		RemoteSessionLeaseInformationBP.ExecuteIfBound(LeaseResponse);
		RemoteSessionLeaseInformation.ExecuteIfBound(LeaseResponse);
		if(!LeaseResponse.success)
		{
			KillProcess(ProcessID);
			return;
		}

		_process.LeaseCode = LeaseResponse.Code;
		_process.LeaseNonce = LeaseResponse.Nonce;
		_process.LastUpdatedAt = FDateTime::UtcNow();
		_process.LastUpdatedStatus = LeaseResponse.Status;
		ContinualPollingAction(ProcessID, RemoteSessionLeaseInformationBP, RemoteSessionLeaseInformation, RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete);
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

	ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Remote);
	LLAPI<FLootLockerRefreshRemoteSessionResponse>::CallAPI(HttpClient, AuthRequest, ULootLockerGameEndpoints::RefreshRemoteSessionEndpoint, { }, EmptyQueryParams, OnCompleteBP, OnComplete, LLAPI<FLootLockerRefreshRemoteSessionResponse>::FResponseInspectorCallback::CreateLambda([](const FLootLockerRefreshRemoteSessionResponse& Response)
		{
			if (Response.success)
			{
				ULootLockerStateData::SetPlayerIdentifier(Response.player_identifier);
				ULootLockerStateData::SetToken(Response.session_token);
				ULootLockerStateData::SetRefreshToken(Response.Refresh_token);
			}
			else
			{
				ULootLockerCurrentPlatform::Reset();
			}
		}));

}

void ULootLockerRemoteSessionRequestHandler::ContinualPollingAction(const FString& ProcessID,
                                                                    const FLootLockerLeaseRemoteSessionResponseDelegateBP& RemoteSessionLeaseInformationBP,
                                                                    const FLootLockerLeaseRemoteSessionResponseDelegate& RemoteSessionLeaseInformation,
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
	if(_process.LeasingProcessTimeoutTime <= FDateTime::UtcNow())
	{
		FLootLockerStartRemoteSessionResponse TimedOutResponse;
		TimedOutResponse.Lease_Status = ELootLockerRemoteSessionLeaseStatus::Timed_out;
		TimedOutResponse.success = false;
		OnCompleteBP.ExecuteIfBound(TimedOutResponse);
		OnComplete.ExecuteIfBound(TimedOutResponse);
		KillProcess(ProcessID);
		return;
	}

	// Should we cancel?
	if(_process.ShouldCancel)
	{
		FLootLockerStartRemoteSessionResponse CanceledResponse;
		CanceledResponse.Lease_Status = ELootLockerRemoteSessionLeaseStatus::Cancelled;
		CanceledResponse.success = false;
		OnCompleteBP.ExecuteIfBound(CanceledResponse);
		OnComplete.ExecuteIfBound(CanceledResponse);
		KillProcess(ProcessID);
		return;
	}

	// Get the latest state of the process
	StartRemoteSession(_process.LeaseCode, _process.LeaseNonce, LLAPI<FLootLockerStartRemoteSessionResponse>::FResponseInspectorCallback::CreateLambda([RemoteSessionLeaseInformationBP, RemoteSessionLeaseInformation, RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete, ProcessID](FLootLockerStartRemoteSessionResponse& RemoteSessionResponse)
	{
		FLootLockerRemoteSessionProcess* _innerProcessPtr = RemoteSessionProcesses.Find(ProcessID);
		if (nullptr == _innerProcessPtr)
		{
			return;
		}
		FLootLockerRemoteSessionProcess& _innerProcess = *_innerProcessPtr;

		auto _scheduleNextPoll = [RemoteSessionLeaseInformationBP, RemoteSessionLeaseInformation, RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete](FTimerHandle& TimerHandle, const float& timeToNextPoll, const FString& ProcessID) {
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([RemoteSessionLeaseInformationBP, RemoteSessionLeaseInformation, RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete, ProcessID]()
				{
					ContinualPollingAction(ProcessID, RemoteSessionLeaseInformationBP, RemoteSessionLeaseInformation, RemoteSessionLeaseStatusUpdateBP, RemoteSessionLeaseStatusUpdate, OnCompleteBP, OnComplete);
				});

			SetTimer(TimerHandle, TimerDelegate, timeToNextPoll);
		};

		if(!RemoteSessionResponse.success)
		{
			// Check if it's a recoverable error and if so, schedule poller again
			if(RemoteSessionResponse.StatusCode >= 500 && RemoteSessionResponse.StatusCode <= 599 && _innerProcess.Retries <= _innerProcess.RetryLimit)
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
		if(ELootLockerRemoteSessionLeaseStatus::Authorized == RemoteSessionResponse.Lease_Status)
		{
			ULootLockerCurrentPlatform::Set(ELootLockerPlatform::Remote);
			ULootLockerStateData::SetToken(RemoteSessionResponse.session_token);
			ULootLockerStateData::SetRefreshToken(RemoteSessionResponse.Refresh_token);
			ULootLockerStateData::SetPlayerIdentifier(RemoteSessionResponse.player_ulid);
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

void ULootLockerRemoteSessionRequestHandler::LeaseRemoteSession(const LLAPI<FLootLockerLeaseRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback)
{
	const auto* config = GetDefault<ULootLockerConfig>();
	LLAPI<FLootLockerLeaseRemoteSessionResponse>::CallAPI(HttpClient, FLootLockerLeaseRemoteSessionRequest{ config->LootLockerGameKey, config->GameVersion }, ULootLockerGameEndpoints::LeaseRemoteSessionEndpoint, {}, {}, FLootLockerLeaseRemoteSessionResponseDelegateBP(), FLootLockerLeaseRemoteSessionResponseDelegate(), OnCompleteCallback);
}

void ULootLockerRemoteSessionRequestHandler::StartRemoteSession(const FString& LeaseCode, const FString& LeaseNonce, const LLAPI<FLootLockerStartRemoteSessionResponse>::FResponseInspectorCallback& OnCompleteCallback)
{
	const auto* config = GetDefault<ULootLockerConfig>();
	LLAPI<FLootLockerStartRemoteSessionResponse>::CallAPI(HttpClient, FLootLockerStartRemoteSessionRequest{ config->LootLockerGameKey, config->GameVersion, LeaseCode, LeaseNonce }, ULootLockerGameEndpoints::StartRemoteSessionEndpoint, {}, {}, FLootLockerStartRemoteSessionResponseDelegateBP(), FLootLockerStartRemoteSessionResponseDelegate(), OnCompleteCallback);
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
