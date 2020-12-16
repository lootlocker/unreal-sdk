// Fill out your copyright notice in the Description page of Project Settings.

#include "AdminAPI/LootLockerAdminEndpoints.h"

FString LootLockerAdminEndpoints::AdminBaseUrl = "https://api.lootlocker.io/admin/";

FEndPoints LootLockerAdminEndpoints::AuthenticateUserEndpoint = InitEndpoint("v1/session", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::VerifyUserCodeEndpoint = InitEndpoint("v1/2fa", ELootLockerHTTPMethod::POST);

FEndPoints LootLockerAdminEndpoints::GetAllGamesForCurrentUserEndpoint = InitEndpoint("v1/games", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::CreateGameEndpoint = InitEndpoint("v1/game", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::GetGameInfoEndpoint = InitEndpoint("v1/game/{0}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::UpdateGameEndpoint = InitEndpoint("v1/game/{0}", ELootLockerHTTPMethod::PATCH);
FEndPoints LootLockerAdminEndpoints::DeleteGameEndpoint = InitEndpoint("v1/game/{0}", ELootLockerHTTPMethod::DELETE);

FEndPoints LootLockerAdminEndpoints::SearchForPlayerEndpoint = InitEndpoint("v1/game/{0}/players", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::GetPlayerEndpoint = InitEndpoint("v1/game/{0}/player/{1}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::GetPlayerScoreEndpoint = InitEndpoint("v1/game/{0}/player/{1}/score", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::AddPlayerScoreEndpoint = InitEndpoint("v1/game/{0}/player/{1}/score", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::ResetPlayerScoreEndpoint = InitEndpoint("v1/game/{0}/player/{1}/score", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerAdminEndpoints::GetPlayerSteamProfileEndpoint = InitEndpoint("v1/game/{0}/steam/{1}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::GetPlayerInventoryEndpoint = InitEndpoint("v1/game/{0}/player/{1}/inventory", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::RefundPlayerPurchaseEndpoint = InitEndpoint("v1/game/{0}/player/{1}/inventory/{2}", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerAdminEndpoints::GetPlayerCurrenciesEndpoint = InitEndpoint("v1/game/{0}/player/{1}/currencies", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::GetPlayerOrdersEndpoint = InitEndpoint("v1/game/{0}/player/{1}/orders", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::SetPlayerProfilePublicEndpoint = InitEndpoint("v1/game/{0}/player/{1}/public", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::SetPlayerProfilePrivateEndpoint = InitEndpoint("v1/game/{0}/player/{1}/public", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerAdminEndpoints::ResetPlayerProfileEndpoint = InitEndpoint("v1/game/{0}/player/{1}", ELootLockerHTTPMethod::DELETE);

FEndPoints LootLockerAdminEndpoints::GetAssetsEndpoint = InitEndpoint("v1/game/{0}/assets", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::GetDetailedAssetInfoEndpoint = InitEndpoint("v1/game/{0}/asset/{1}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::CreateAssetEndpoint = InitEndpoint("v1/asset", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::CheckIfAssetCanBeActivatedEndpoint = InitEndpoint("v1/asset/{0}/can/activate", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::ActivateAssetEndpoint = InitEndpoint("v1/asset/{0}/activate", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::DeactivateAssetEndpoint = InitEndpoint("v1/asset/{0}/deactivate", ELootLockerHTTPMethod::PATCH);
FEndPoints LootLockerAdminEndpoints::GetAssetContextsEndpoint = InitEndpoint("v1/game/{0}/assets/contexts", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::UpdateAssetContextsEndpoint = InitEndpoint("v1/game/{0}/assets/contexts", ELootLockerHTTPMethod::PATCH);
FEndPoints LootLockerAdminEndpoints::GetAssetTypesEndpoint = InitEndpoint("v1/game/{0}/assets/types", ELootLockerHTTPMethod::GET);

FEndPoints LootLockerAdminEndpoints::ListCharacterClassesEndpoint = InitEndpoint("v1/game/{0}/loadout/default", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::CreateCharacterClassEndpoint = InitEndpoint("v1/game/{0}/loadout/default/{1}", ELootLockerHTTPMethod::PATCH);
FEndPoints LootLockerAdminEndpoints::DeleteCharacterClassEndpoint = InitEndpoint("v1/game/{0}/loadout/default/{1}", ELootLockerHTTPMethod::DELETE);

FEndPoints LootLockerAdminEndpoints::ListHeroesEndpoint = InitEndpoint("v1/game/{0}/heroes", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::GetHeroEndpoint = InitEndpoint("v1/game/{0}/heroes/{1}", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::CreateHeroEndpoint = InitEndpoint("v1/game/{0}/heroes", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::UpdateHeroEndpoint = InitEndpoint("v1/game/{0}/heroes/{1}", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::DeleteHeroEndpoint = InitEndpoint("v1/game/{0}/heroes/{1}", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerAdminEndpoints::AddAssetToDefaultHeroLoadoutEndpoint = InitEndpoint("v1/game/{0}/heroes/{1}/defaults", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::RemoveAssetFromDefaultHeroLoadoutEndpoint = InitEndpoint("v1/game/{0}/heroes/{1}/defaults/{2}", ELootLockerHTTPMethod::DELETE);
FEndPoints LootLockerAdminEndpoints::AddHeroExceptionEndpoint = InitEndpoint("v1/game/{0}/heroes/{1}/exceptions", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::RemoveHeroExceptionEndpoint = InitEndpoint("v1/game/{0}/heroes/{1}/exceptions/{2}", ELootLockerHTTPMethod::DELETE);

FEndPoints LootLockerAdminEndpoints::CreateMissionEndpoint = InitEndpoint("v1/missions", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::UpdateMissionEndpoint = InitEndpoint("v1/missions/{0}", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::GetAllMissionsEndpoint = InitEndpoint("v1/missions/game/{0}", ELootLockerHTTPMethod::GET);

FEndPoints LootLockerAdminEndpoints::ListTriggersEndpoint = InitEndpoint("v1/game/{0}/triggers", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::CreateTriggerEndpoint = InitEndpoint("v1/game/{0}/triggers", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::UpdateTriggerEndpoint = InitEndpoint("v1/game/{0}/triggers/{1}", ELootLockerHTTPMethod::PATCH);
FEndPoints LootLockerAdminEndpoints::DeleteTriggerEndpoint = InitEndpoint("v1/game/{0}/triggers/{1}", ELootLockerHTTPMethod::DELETE);

FEndPoints LootLockerAdminEndpoints::UploadFileEndpoint = InitEndpoint("v1/upload", ELootLockerHTTPMethod::POST);
FEndPoints LootLockerAdminEndpoints::GetFilesEndpoint = InitEndpoint("v1/game/{0}/files", ELootLockerHTTPMethod::GET);
FEndPoints LootLockerAdminEndpoints::UpdateFileTagsEndpoint = InitEndpoint("v1/game/{0}/files/{1}", ELootLockerHTTPMethod::PATCH);
FEndPoints LootLockerAdminEndpoints::DeleteFileEndpoint = InitEndpoint("v1/game/{0}/files/{1}", ELootLockerHTTPMethod::DELETE);

FEndPoints LootLockerAdminEndpoints::InitEndpoint(const FString& Endpoint, ELootLockerHTTPMethod Method)
{
    FEndPoints Result;
    Result.endpoint = AdminBaseUrl + Endpoint;
    Result.requestMethod = Method;
    return Result;
}
