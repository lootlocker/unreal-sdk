// Copyright (c) 2021 LootLocker


#include "LootLockerSDKManager.h"

//Authentication
void ULootLockerSDKManager::StartSession(const FString& PlayerIdentifier, const FLootLockerSessionResponse& OnCompleteRequest)
{
	ULootLockerAuthenticationRequestHandler::StartSession(PlayerIdentifier, FAuthResponseBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::VerifyPlayer(const FString& SteamSessionTicket, const FLootLockerDefaultAuthenticationResponse& OnCompleteRequest)
{
	ULootLockerAuthenticationRequestHandler::VerifyPlayer(SteamSessionTicket, FAuthDefaultResponseBP(), OnCompleteRequest);
}

void ULootLockerSDKManager::EndSession(const FLootLockerDefaultAuthenticationResponse& OnCompleteRequest)
{
	ULootLockerAuthenticationRequestHandler::EndSession(FAuthDefaultResponseBP(), OnCompleteRequest);
}
//Player
void ULootLockerSDKManager::GetPlayerInfo(const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	ULootLockerPlayerRequestHandler::GetPlayerInfo(FPInfoResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetInventory(const FInventoryResponse& OnCompletedRequest)
{
	ULootLockerPlayerRequestHandler::GetInventory(FPInventoryResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetUniversalAssets(const FUniversalAssetsResponse& OnCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetUniversalAssets(FPUniversalAssetsResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SubmitXP(int Points, const FSubmitXpResponse& OnCompletedRequest)
{
	ULootLockerPlayerRequestHandler::SubmitXp(Points, FPSubmitResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayerInfo(FLootLockerGetRequests& GetRequests, const FLootLockerPlayerInformationResponse& OnCompletedRequest)
{
	ULootLockerPlayerRequestHandler::GetOtherPlayerInfo(GetRequests, FPInfoResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CheckPlayerAssetActivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(FPAssetNotificationResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CheckPlayerAssetDeactivationNotification(const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	ULootLockerPlayerRequestHandler::CheckPlayerAssetDeactivationNotification(FPAssetNotificationResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrencyBalance(const FPBalanceResponse& onCompletedRequest)
{
    ULootLockerPlayerRequestHandler::GetCurrencyBalance(FPBalanceResponseBP(), onCompletedRequest);
}


void ULootLockerSDKManager::InitiateDLCMigration(const FResponseCallback& OnCompletedRequest) 
{
    ULootLockerPlayerRequestHandler::InitiateDLCMigration(FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SetPlayerName(FString name, const FPNameResponse& OnCompletedRequest) 
{
    ULootLockerPlayerRequestHandler::SetPlayerName(name, FPNameResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerName(const FPNameResponse& OnCompletedRequest) 
{
    ULootLockerPlayerRequestHandler::GetPlayerName(FPNameResponseBP(), OnCompletedRequest);
}


void ULootLockerSDKManager::GetDLCsMigration(const FPDlcResponse& OnCompletedRequest) 
{
    ULootLockerPlayerRequestHandler::GetDLCsMigration(FPDlcResponseBP(), OnCompletedRequest);
}


void ULootLockerSDKManager::SetProfilePrivate(const FResponseCallback& OnCompletedRequest) 
{
    ULootLockerPlayerRequestHandler::SetProfilePrivate(FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SetProfilePublic(const FResponseCallback& OnCompletedRequest) 
{
    ULootLockerPlayerRequestHandler::SetProfilePublic(FResponseCallbackBP(), OnCompletedRequest);
}

//Character
void ULootLockerSDKManager::GetCharacterLoadout(const FCharacterLoadoutResponse& OnCompletedRequest)
{
	ULootLockerCharacterRequestHandler::GetCharacterLoadout(FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateCharacter(int CharacterId, bool isDefault, FString& Name, const FCharacterLoadoutResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::UpdateCharacter(CharacterId,isDefault, Name, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateCharacter(bool IsDefault, const FString& CharacterName, const FString& CharacterId, const FCharacterLoadoutResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::CreateCharacter(IsDefault, CharacterName, CharacterId, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ListCharacterTypes(const FPLootLockerListCharacterTypesResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::ListCharacterTypes(FPLootLockerListCharacterTypesResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	ULootLockerCharacterRequestHandler::EquipAssetToDefaultCharacter(InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToCharacterById(int CharacterId, int AssetId, int AssetVariationId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(CharacterId);
	ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(GetRequests, AssetId, AssetVariationId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::EquipAssetToCharacterById(FString CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
    ULootLockerCharacterRequestHandler::EquipAssetToCharacterById(CharacterId,InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToDefaultCharacter(int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	ULootLockerCharacterRequestHandler::UnEquipAssetToDefaultCharacter(InstanceId, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UnEquipAssetToCharacterById(int CharacterId, int InstanceId, const FLootLockerCharacterDefaultResponse& OnCompletedRequest)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(CharacterId);
    GetRequests.args.Add(InstanceId);
	ULootLockerCharacterRequestHandler::UnEquipAssetToCharacterById(GetRequests, FPCharacterDefaultResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetCurrentLoadoutToDefaultCharacter(const FCharacterLoadoutResponse& OnCompletedRequest)
{
	ULootLockerCharacterRequestHandler::GetCurrentLoadoutToDefaultCharacter(FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetOtherPlayersCurrentLoadoutToDefaultCharacter(const FString& OtherPlayerId, const FCharacterLoadoutResponse& OnCompletedRequest)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(OtherPlayerId);
	ULootLockerCharacterRequestHandler::GetOtherPlayersCurrentLoadoutToDefaultCharacter(GetRequests, FPCharacterLoadoutResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsToDefaultCharacter(const FContextDelegate& OnCompletedRequest)
{
	ULootLockerCharacterRequestHandler::GetEquipableContextsToDefaultCharacter(FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetEquipableContextsByCharacterId(const FString& OtherCharacterId, const FContextDelegate& OnCompletedRequest)
{
	FLootLockerGetRequests GetRequests;
	GetRequests.args.Add(OtherCharacterId);
	ULootLockerCharacterRequestHandler::GetEquipableContextsByCharacterId(GetRequests, FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetGameHeroes(const FGameHeroesResponse& OnGetGameHeroesRequestCompleted)
{
	ULootLockerHeroRequestHandler::GetGameHeroes(FPGameHeroesResponseBP(), OnGetGameHeroesRequestCompleted);
}

void ULootLockerSDKManager::ListPlayerHeroes(const FHeroesResponse& OnListPlayerHeroesRequestCompleted)
{
	ULootLockerHeroRequestHandler::ListPlayerHeroes(FPHeroesResponseBP(), OnListPlayerHeroesRequestCompleted);
}

void ULootLockerSDKManager::CreateHero(FString CharacterName, int HeroId, const FHeroResponse& OnCompletedRequestBP)
{
	ULootLockerHeroRequestHandler::CreateHero(CharacterName, HeroId, FPHeroResponseBP(), OnCompletedRequestBP);
}

void ULootLockerSDKManager::GetHero(int HeroId, const FHeroResponse& OnCompletedRequestBP)
{
	ULootLockerHeroRequestHandler::GetHero(HeroId, FPHeroResponseBP(), OnCompletedRequestBP);
}

void ULootLockerSDKManager::GetHeroLoadout(int HeroId, const FHeroLoadoutResponse& OnCompletedRequestBP)
{
	ULootLockerHeroRequestHandler::GetHeroLoadout(HeroId, FPHeroLoadoutResponseBP(), OnCompletedRequestBP);
}

void ULootLockerSDKManager::DeleteHero(int HeroId, const FHeroDefaultResponse& OnCompletedRequestBP)
{
    ULootLockerHeroRequestHandler::DeleteHero(HeroId, FPHeroDefaultResponseBP(), OnCompletedRequestBP);
}

//Persisitent Storage
void ULootLockerSDKManager::GetEntirePersistentStorage(const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::GetEntirePersistentStorage(FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::GetItemFromPersistentStorage(Key, FPersistentStorageItemResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddItemsToPersistentStorage(const TArray<FLootLockerPersistentStorageItem>& Items, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::AddItemsToPersistentStorage(Items, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteItemFromPersistentStorage(const FString& Key, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::DeleteItemFromPersistentStorage(Key, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetPlayerPersistentStorage(const FString& PlayerId, const FPersistentStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerPersistentStorageRequestHandler::GetPlayerPersistentStorage(PlayerId, FPersistentStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

//Assets
void ULootLockerSDKManager::GetContexts(const FContextDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetContexts(FContextDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssets(const FAssetsResponseDelegate& OnCompletedRequest, int StartFromIndex, int ItemsCount, ELootLockerAssetFilter AssetFilter, int Context, bool IncludeUGC)
{
    ULootLockerAssetsRequestHandler::GetAssets(StartFromIndex, ItemsCount, AssetFilter, Context, IncludeUGC, FAssetsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetsByIds(const TArray<int>& AssetIds, const FAssetsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetAssetsByIds(AssetIds, FAssetsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetBones(const FAssetBonesResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetAssetBones(FAssetBonesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetFavouriteAssetIndices(const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::GetFavouriteAssetIndices(FGetFavouriteAssetIndicesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddAssetToFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::AddAssetToFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::RemoveAssetFromFavourites(int AssetId, const FGetFavouriteAssetIndicesResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetsRequestHandler::RemoveAssetFromFavourites(AssetId, FGetFavouriteAssetIndicesResponseDelegateBP(), OnCompletedRequest);
}

//Asset Instance

void ULootLockerSDKManager::GetAllKeyValuePairsForAssetInstance(const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsForAssetInstance(FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllKeyValuePairsToAnInstanceForAssetInstance(int AssetInstanceId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::GetAllKeyValuePairsToAnInstanceForAssetInstance(AssetInstanceId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::GetAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CreateAKeyValuePairForAssetInstance(int AssetInstanceId, const FLootLockerAssetInstanceStorageItem& Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::CreateAKeyValuePairForAssetInstance(AssetInstanceId, Item, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateOneOrMoreKeyValuePairForAssetInstance(int AssetInstanceId, const TArray<FLootLockerAssetInstanceStorageItem>& Items, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::UpdateOneOrMoreKeyValuePairForAssetInstance(AssetInstanceId, Items, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FLootLockerAssetInstanceStorageItem Item, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::UpdateAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, Item, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAKeyValuePairByIdForAssetInstance(int AssetInstanceId, int StorageItemId, const FAssetInstanceStorageItemsResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::DeleteAKeyValuePairByIdForAssetInstance(AssetInstanceId, StorageItemId, FAssetInstanceStorageItemsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::InspectLootBox(int AssetInstanceId, const FLootBoxContentResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::InspectLootBox(AssetInstanceId, FLootBoxContentResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::OpenLootBox(int AssetInstanceId, const FOpenLootBoxResponseDelegate& OnCompletedRequest)
{
    ULootLockerAssetInstancesRequestHandler::OpenLootBox(AssetInstanceId, FOpenLootBoxResponseDelegateBP(), OnCompletedRequest);
}

//User Generated Candidate
void ULootLockerSDKManager::CreateAssetCandidate(const FLootLockerAssetCandidate2& AsssetCandidate, const FCreateAssetCandidateResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::CreateAssetCandidate(AsssetCandidate, FCreateAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::UpdateAssetCandidate(int AssetCandidateId, const FLootLockerAssetCandidate2& AsssetCandidate, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::UpdateAssetCandidate(AssetCandidateId, AsssetCandidate, FAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteAssetCandidate(int AssetCandidateId, const FResponseCallback& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteAssetCandidate(AssetCandidateId, FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAllAssetCandidates(const FAssetCandidatesResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAllAssetCandidates(FAssetCandidatesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetAssetCandidate(int AssetCandidateId, const FAssetCandidateResponseDelegate& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::GetAssetCandidate(AssetCandidateId, FAssetCandidateResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::AddFileToAssetCandidate(int AssetCandidateId, const FString& FilePath, ELootLockerAssetFilePurpose FilePurpose, const FResponseCallback& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::AddFileToAssetCandidate(AssetCandidateId, FilePath, FilePurpose, FResponseCallbackBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::DeleteFileFromAssetCandidate(int AssetCandidateId, int FileId, const FResponseCallback& OnCompletedRequest)
{
    ULootLockerUserGeneratedContentRequestHandler::DeleteFileFromAssetCandidate(AssetCandidateId, FileId, FResponseCallbackBP(), OnCompletedRequest);
}

//Missions
void ULootLockerSDKManager::GetAllMissions(const FMissionsResponseDelegate& OnCompletedRequest)
{
    ULootLockerMissionsRequestHandler::GetAllMissions(FMissionsResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetMission(int MissionId, const FMissionResponseDelegate& OnCompletedRequest)
{
    ULootLockerMissionsRequestHandler::GetMission(MissionId, FMissionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::StartMission(int MissionId, const FStartMissionResponseDelegate& OnCompletedRequest)
{
    ULootLockerMissionsRequestHandler::StartMission(MissionId, FStartMissionResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::FinishMission(int MissionId, const FLootLockerFinishMissionData& MissionData, const FFinishMissionResponseDelegate& OnCompletedRequest)
{
    ULootLockerMissionsRequestHandler::FinishMission(MissionId, MissionData, FFinishMissionResponseDelegateBP(), OnCompletedRequest);
}

//Maps
void ULootLockerSDKManager::GetMaps(const FGetMapsResponseDelegate& OnCompletedRequest)
{
    ULootLockerMapsRequestHandler::GetMaps(FGetMapsResponseDelegateBP(), OnCompletedRequest);
}

//Purchasing
void ULootLockerSDKManager::PurchaseAssets(const TArray<FLootLockerAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseAssets(PurchaseData, FPurchaseResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PurchaseAssetsAndroid(const TArray<FLootLockerAndroidAssetPurchaseData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseAssetsAndroid(PurchaseData, FPurchaseResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PurchaseAssetsIOS(const TArray<FLootLockerVerifyPurchaseIosData>& PurchaseData, const FPurchaseResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PurchaseAssetsIOS(PurchaseData, FPurchaseResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::PollingOrderStatus(int PurchaseId, const FPurchaseStatusResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::PollingOrderStatus(PurchaseId, FPurchaseStatusResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ActivateRentalAsset(int AssetId, const FActivateRentalAssetResponseDelegate& OnCompletedRequest)
{
    ULootLockerPurchasesRequestHandler::ActivateRentalAsset(AssetId, FActivateRentalAssetResponseDelegateBP(), OnCompletedRequest);
}

//Trigger
void ULootLockerSDKManager::TriggerEvent(const FLootLockerTriggerEvent& Event, const FTriggerEventResponseDelegate& OnCompletedRequest)
{
    ULootLockerTriggerEventsRequestHandler::TriggerEvent(Event, FTriggerEventResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetTriggeredEvents(const FTriggersResponseDelegate& OnCompletedRequest)
{
    ULootLockerTriggerEventsRequestHandler::GetTriggeredEvents(FTriggersResponseDelegateBP(), OnCompletedRequest);
}

//Collectables
void ULootLockerSDKManager::GetAllCollectables(const FCollectablesResponseDelegate& OnCompletedRequest)
{
    ULootLockerCollectablesRequestHandler::GetAllCollectables(FCollectablesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::CollectItem(const FLootLockerCollectItemPayload& Item, const FCollectablesResponseDelegate& OnCompletedRequest)
{
    ULootLockerCollectablesRequestHandler::CollectItem(Item, FCollectablesResponseDelegateBP(), OnCompletedRequest);
}

//Messages
void ULootLockerSDKManager::GetMessages(const FMessagesResponseDelegate& OnCompletedRequest)
{
    ULootLockerMessagesRequestHandler::GetMessages(FMessagesResponseDelegateBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetMemberRank(int LeaderboardId, int MemberId, const FLootLockerGetMemberRankResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetMemberRankRequest MemberRequest;
    MemberRequest.leaderboardId = LeaderboardId;
    MemberRequest.member_id = MemberId;

    ULootLockerLeaderboardRequestHandler::GetMemberRank(MemberRequest, FLootLockerGetMemberRankResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetByListOfMembers(TArray<FString> Members, int LeaderboardId, const FLootLockerGetByListOfMembersResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetByListMembersRequest GetByListMembersRequest;
    GetByListMembersRequest.members = Members;
    ULootLockerLeaderboardRequestHandler::GetByListOfMembers(GetByListMembersRequest, LeaderboardId,FLootLockerGetByListOfMembersResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetScoreList(int LeaderboardId, int Count, int After, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = After;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboardId = LeaderboardId;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetScoreListRequest, FLootLockerGetScoreListResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::GetScoreListInitial(int LeaderboardId, int Count, const FLootLockerGetScoreListResponseDelegate& OnCompletedRequest)
{
    FLootLockerGetScoreListRequest GetScoreListRequest;
    GetScoreListRequest.after = -1;
    GetScoreListRequest.count = Count;
    GetScoreListRequest.leaderboardId = LeaderboardId;
    ULootLockerLeaderboardRequestHandler::GetScoreList(GetScoreListRequest, FLootLockerGetScoreListResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::SubmitScore(FString MemberId, int LeaderboardId, int Score, const FLootLockerSubmitScoreResponseDelegate& OnCompletedRequest)
{
    FLootLockerSubmitScoreRequest SubmitScoreRequest;
    SubmitScoreRequest.member_id = MemberId;
    SubmitScoreRequest.score = Score;
    ULootLockerLeaderboardRequestHandler::SubmitScore(SubmitScoreRequest, LeaderboardId, FLootLockerSubmitScoreResponseBP(), OnCompletedRequest);
}

void ULootLockerSDKManager::ComputeAndLockDropTable(int TableId, const FLootLockerComputeAndLockDropTableResponseDelegate& OnCompletedRequest)
{
    ULLDropTablesRequestHandler::ComputeAndLockDropTable(TableId, FLootLockerComputeAndLockDropTableResponseBP(),OnCompletedRequest);
}

void ULootLockerSDKManager::PickDropsFromDropTable(TArray<int> picks, int TableId, const FFLootLockerPickDropsFromDropTableResponseDelegate& OnCompletedRequest)
{
    FLootLockerPickDropsFromDropTableRequest request;
    request.picks = picks;
    ULLDropTablesRequestHandler::PickDropsFromDropTable(request, TableId, FFLootLockerPickDropsFromDropTableResponseBP(),OnCompletedRequest);
}

