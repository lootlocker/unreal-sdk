#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerCharacters, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerCharacters)

void FTestLootLockerCharacters::Define()
{
	Describe("Characters", [this]()
	{
		LatentIt("When Working with Characters", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			test_util::StartSession();

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerCharacterLoadoutResponse,FCharacterLoadoutResponse>();

				ULootLockerSDKManager::GetCharacterLoadout(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetCharacterLoadouts success", Response.success);
				TestTrue("GetCharacterLoadouts available", Response.loadouts.Num()>0);
				delete(Promise);
			}
			
			int32 CharacterID=-1;
			
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerListCharacterTypesResponse,FPLootLockerListCharacterTypesResponse>();

				ULootLockerSDKManager::ListCharacterTypes(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetGameHeroesList success", Response.success);
				TestTrue("Game hero available", Response.character_types.Num()>0);
				delete(Promise);

				CharacterID = Response.character_types[0].id; 
			}
			TestTrue("GameHeroID found",CharacterID != -1);

			// do we need o delete first ?, how to delete ?
			
			int32 NewPlayerHeroId=-1;
			
			// create a character
			{
				const auto [Promise2 , Delegate] = test_util::CreateDelegate<FLootLockerCharacterLoadoutResponse,FCharacterLoadoutResponse>();
			
				bool IsDefault = true;
				FString CharacterName = "Test character";
				ULootLockerSDKManager::CreateCharacter(IsDefault, CharacterName, FString::FromInt(CharacterID), Delegate);
			
				const auto Response2 = Promise2->get_future().get();
				TestTrue("CreateHero success", Response2.success);
				// TestTrue("CreateHero id verified", Response..hero_id == 24);
				// NewPlayerHeroId = Response.hero.id;
				delete(Promise2);
			}
			
			// update character
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPlayerHeroResponse,FLootLockerPlayerHeroDelegate>();
			
				FLootLockerUpdateHeroRequest UpdateHeroRequest;
				UpdateHeroRequest.name ="new_hero_name";
			
				ULootLockerSDKManager::UpdateHero(NewPlayerHeroId,UpdateHeroRequest, Delegate);
			
				const auto Response = Promise->get_future().get();
				TestTrue("UpdateHero success", Response.success);
				TestTrue("UpdateHero change verified", Response.hero.hero_name == UpdateHeroRequest.name);
				delete(Promise);
			}

			// equip asset to default character
			// get current loadout to default character
			// unequip asset to default character
			
			// equip asset to character by id
			// unequip asset to character by id
			
			// // get hero loadout
			// {
			// 	const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerInventoryResponse,FInventoryResponse>();
			// 		
			// 	ULootLockerSDKManager::GetHeroInventory(NewPlayerHeroId,Delegate);
			// 		
			// 	const auto Response = Promise->get_future().get();
			// 	TestTrue("GetHero success", Response.success);
			// 	delete(Promise);
			// }
			//
			// int32 AssetId = 0;
			//
			// // add asset to loadout
			// {
			// 	const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerHeroLoadoutResponse,FHeroLoadoutReseponseDelegate>();
			// 		
			// 	ULootLockerSDKManager::AddAssetToHeroLoadout(NewPlayerHeroId,AssetId,Delegate);
			// 		
			// 	const auto Response = Promise->get_future().get();
			// 	TestTrue("Add asset to loadout success", Response.success);
			// 	delete(Promise);
			// }			
			//
			// // remove asset from loadout
			// {
			// 	const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerResponse,FHeroLoadoutReseponseDelegate>();
			// 		
			// 	ULootLockerSDKManager::RemoveAssetToHeroLoadout(NewPlayerHeroId,AssetId,Delegate);
			// 		
			// 	const auto Response = Promise->get_future().get();
			// 	TestTrue("GetHero success", Response.success);
			// 	delete(Promise);
			// }			
			//
		});
	});
}
#endif

