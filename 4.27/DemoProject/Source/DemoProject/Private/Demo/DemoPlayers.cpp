// Copyright (c) 2021 LootLocker

#include "Demo/DemoPlayers.h"


void ADemoPlayers::DemoGetPlayerInfo()
{
   ULootLockerSDKManager::GetPlayerInfo(FLootLockerPlayerInformationResponse::CreateUObject(this, &ADemoPlayers::OnGetPlayerInfoCompleted));
}

void ADemoPlayers::DemoGetInventory()
{
   ULootLockerSDKManager::GetInventory(FInventoryResponse::CreateUObject(this, &ADemoPlayers::OnGetInventoryCompleted));
}

void ADemoPlayers::DemoSubmitXp()
{
   ULootLockerSDKManager::SubmitXP(points, FSubmitXpResponse::CreateUObject(this, &ADemoPlayers::OnSubmitXpCompleted));
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

void ADemoPlayers::GetCurrencyBalance()
{
    ULootLockerSDKManager::GetCurrencyBalance(FPBalanceResponse::CreateUObject(this, &ADemoPlayers::OnGetCurrencyBalance));
}

void ADemoPlayers::InitiateDLCMigration()
{
    ULootLockerSDKManager::InitiateDLCMigration(FResponseCallback::CreateUObject(this, &ADemoPlayers::OnInitiateDlcMigration));
}


void ADemoPlayers::GetDLCsMigration()
{
    ULootLockerSDKManager::GetDLCsMigration(FPDlcResponse::CreateUObject(this, &ADemoPlayers::OnGotDlcMigration));
}


void ADemoPlayers::SetProfilePrivate()
{
    ULootLockerSDKManager::SetProfilePrivate(FResponseCallback::CreateUObject(this, &ADemoPlayers::OnProfileSetPrivate));
}

void ADemoPlayers::SetProfilePublic()
{
    ULootLockerSDKManager::SetProfilePublic(FResponseCallback::CreateUObject(this, &ADemoPlayers::OnProfileSetPublic));
}


void ADemoPlayers::OnGetCurrencyBalance(FLootLockerBalanceResponse Response)
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

void ADemoPlayers::OnInitiateDlcMigration(FLootLockerResponse Response)
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

void ADemoPlayers::OnGotDlcMigration(FLootLockerDlcResponse Response)
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

void ADemoPlayers::OnProfileSetPrivate(FLootLockerResponse Response)
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

void ADemoPlayers::OnProfileSetPublic(FLootLockerResponse Response)
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

void ADemoPlayers::OnGetPlayerInfoCompleted(FLootLockerPlayerInfoResponse Response)
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

void ADemoPlayers::OnGetInventoryCompleted(FLootLockerInventoryResponse Response)
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

void ADemoPlayers::OnSubmitXpCompleted(FLootLockerSubmitXpResponse Response)
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

void ADemoPlayers::OnGetOtherPlayerInfoCompleted(FLootLockerPlayerInfoResponse Response)
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

void ADemoPlayers::OnCheckPlayerAssetNotificationCompleted(FLootLockerPlayerAssetNotificationResponse Response)
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

void ADemoPlayers::OnCheckPlayerAssetDeactivationNotificationCompleted(FLootLockerPlayerAssetNotificationResponse Response)
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
