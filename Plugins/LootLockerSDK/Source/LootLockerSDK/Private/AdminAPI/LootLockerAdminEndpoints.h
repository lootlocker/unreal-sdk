// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LootLockerConfig.h"

class LootLockerAdminEndpoints
{
public:
    //Authentication
    static FEndPoints AuthenticateUserEndpoint;
    static FEndPoints VerifyUserCodeEndpoint;
    
    //Games
    static FEndPoints GetAllGamesForCurrentUserEndpoint;
    static FEndPoints CreateGameEndpoint;
    static FEndPoints GetGameInfoEndpoint;
    static FEndPoints UpdateGameEndpoint;
    static FEndPoints DeleteGameEndpoint;
    
    //Players
    static FEndPoints SearchForPlayerEndpoint;
    static FEndPoints GetPlayerEndpoint;
    static FEndPoints GetPlayerScoreEndpoint;
    static FEndPoints AddPlayerScoreEndpoint;
    static FEndPoints ResetPlayerScoreEndpoint;
    static FEndPoints GetPlayerSteamProfileEndpoint;
    static FEndPoints GetPlayerInventoryEndpoint;
    static FEndPoints RefundPlayerPurchaseEndpoint;
    static FEndPoints GetPlayerCurrenciesEndpoint;
    static FEndPoints GetPlayerOrdersEndpoint;
    static FEndPoints SetPlayerProfilePublicEndpoint;
    static FEndPoints SetPlayerProfilePrivateEndpoint;
    static FEndPoints ResetPlayerProfileEndpoint;
    
    //Assets
    static FEndPoints GetAssetsEndpoint;
    static FEndPoints GetDetailedAssetInfoEndpoint;
    static FEndPoints CreateAssetEndpoint;
    static FEndPoints CheckIfAssetCanBeActivatedEndpoint;
    static FEndPoints ActivateAssetEndpoint;
    static FEndPoints DeactivateAssetEndpoint;
    static FEndPoints GetAssetContextsEndpoint;
    static FEndPoints UpdateAssetContextsEndpoint;
    static FEndPoints GetAssetTypesEndpoint;
    
    //Characters
    static FEndPoints ListCharacterClassesEndpoint;
    static FEndPoints CreateCharacterClassEndpoint;
    static FEndPoints DeleteCharacterClassEndpoint;
    
    //Heroes
    static FEndPoints ListHeroesEndpoint;
    static FEndPoints GetHeroEndpoint;
    static FEndPoints CreateHeroEndpoint;
    static FEndPoints UpdateHeroEndpoint;
    static FEndPoints DeleteHeroEndpoint;
    static FEndPoints AddAssetToDefaultHeroLoadoutEndpoint;
    static FEndPoints RemoveAssetFromDefaultHeroLoadoutEndpoint;
    static FEndPoints AddHeroExceptionEndpoint;
    static FEndPoints RemoveHeroExceptionEndpoint;
    
    //Missions
    static FEndPoints CreateMissionEndpoint;
    static FEndPoints UpdateMissionEndpoint;
    static FEndPoints GetAllMissionsEndpoint;
    
    //Triggers
    static FEndPoints ListTriggersEndpoint;
    static FEndPoints CreateTriggerEndpoint;
    static FEndPoints UpdateTriggerEndpoint;
    static FEndPoints DeleteTriggerEndpoint;
    
    //Files
    static FEndPoints UploadFileEndpoint;
    static FEndPoints GetFilesEndpoint;
    static FEndPoints UpdateFileTagsEndpoint;
    static FEndPoints DeleteFileEndpoint;
private:
    static FString AdminBaseUrl;

    static FEndPoints InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method);
};
