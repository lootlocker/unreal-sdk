// Copyright (c) 2021 LootLocker

#include "Demo/DemoPlayers.h"


void ADemoPlayers::DemoGetPlayerInfo()
{
   ULootLockerSDKManager::GetPlayerInfo(FLootLockerPlayerInformationResponse::CreateUObject(this, &ADemoPlayers::OnGetPlayerInfoCompleted));
}

void ADemoPlayers::DemoGetInventory()
{
   ULootLockerSDKManager::GetInventory(FLootLockerInventoryResponse::CreateUObject(this, &ADemoPlayers::OnGetInventoryCompleted));
}

void ADemoPlayers::DemoSubmitXp()
{
   ULootLockerSDKManager::SubmitXP(points, FLootLockerSubmitXpResponse::CreateUObject(this, &ADemoPlayers::OnSubmitXpCompleted));
}

void ADemoPlayers::DemoGetOtherPlayerInfo()
{
   ULootLockerSDKManager::GetOtherPlayerInfo(getRequests, FLootLockerPlayerInformationResponse::CreateUObject(this, &ADemoPlayers::OnGetOtherPlayerInfoCompleted));
}

void ADemoPlayers::DemoCheckPlayerAssetNotification()
{
   ULootLockerSDKManager::CheckPlayerAssetActivationNotification(FLootLockerAssetNotificationResponse::CreateUObject(this, &ADemoPlayers::OnCheckPlayerAssetNotificationCompleted));
}

void ADemoPlayers::DemoCheckPlayerAssetDeactivationNotification()
{
   ULootLockerSDKManager::CheckPlayerAssetDeactivationNotification(FLootLockerAssetNotificationResponse::CreateUObject(this, &ADemoPlayers::OnCheckPlayerAssetDeactivationNotificationCompleted));
}

void ADemoPlayers::OnGetPlayerInfoCompleted(FPlayerInfoResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetPlayerInfo Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetPlayerInfo Failed"));
    }
}

void ADemoPlayers::OnGetInventoryCompleted(FInventoryResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetInventory Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetInventory Failed"));
    }
}

void ADemoPlayers::OnSubmitXpCompleted(FSubmitXpResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnSubmitXp Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnSubmitXp Failed"));
    }
}

void ADemoPlayers::OnGetOtherPlayerInfoCompleted(FPlayerInfoResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetOtherPlayerInfo Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnGetOtherPlayerInfo Failed"));
    }
}

void ADemoPlayers::OnCheckPlayerAssetNotificationCompleted(FPlayerAssetNotificationResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCheckPlayerAssetNotification Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCheckPlayerAssetNotification Failed"));
    }
}

void ADemoPlayers::OnCheckPlayerAssetDeactivationNotificationCompleted(FPlayerAssetNotificationResponse Response)
{
    if (Response.success)
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCheckPlayerAssetDeactivationNotification Success"));
    }
    else
    {
        UE_LOG(LogTemp, Verbose, TEXT("OnCheckPlayerAssetDeactivationNotification Failed"));
    }
}
