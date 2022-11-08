#include <future>

#include "LootLockerManager.h"
#include "LootLockerSDKManager.h"
#include "GameAPI/LootLockerAuthenticationRequestHandler.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "TestUtils.h"

#if ENGINE_MAJOR_VERSION > 4
BEGIN_DEFINE_SPEC(FTestLootLockerHeroes, "LootLocker", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FTestLootLockerHeroes)

void FTestLootLockerHeroes::Define()
{
	Describe("Heroes", [this]()
	{
		LatentIt("When Working with Heroes", EAsyncExecution::ThreadPool, [this](const FDoneDelegate TestDone)
		{
			int32 GameHeroID=-1;

			// get game heroes
			// TODO: add player id to start session
			test_util::StartSession();

			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerGameHeroListResponse,FLootLockerGameHeroListDelegate>();

				ULootLockerSDKManager::GetGameHeroes(Delegate);

				const auto Response = Promise ->get_future().get();
				TestTrue("GetGameHeroesList success", Response.success);
				TestTrue("Game hero available", Response.game_heroes.Num()>0);
				delete(Promise);

				GameHeroID = Response.game_heroes[0].hero_id; 
			}
			TestTrue("GameHeroID found",GameHeroID != -1);

			int32 PlayerHeroId=-1;
			
			// get player heroes
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerHeroListResponse,FLootLockerHeroListDelegate>();
			
				ULootLockerSDKManager::ListPlayerHeroes(Delegate);
			
				const auto Response = Promise ->get_future().get();
				TestTrue("ListPlayerHeroes success", Response.success);
			
				auto FoundHero = Response.heroes.FindByPredicate([GameHeroID](const FLootLockerPlayerHero& InItem) { return InItem.hero_id==GameHeroID; });
			
				if (FoundHero)
				{
					PlayerHeroId = FoundHero->id;
				}
				delete(Promise);
			}
			
			// check if we need to remove existing player hero
			if (PlayerHeroId!=-1)
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerResponse,FLLHeroDefaultResponseDelegate>();
				
				ULootLockerSDKManager::DeleteHero(PlayerHeroId, Delegate);
				
				FLootLockerResponse Response = Promise->get_future().get();
				TestTrue("Delete existing hero ok", Response.success);
				delete(Promise);				
			}
			
			int32 NewPlayerHeroId=-1;
			
			// create a player hero
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPlayerHeroResponse,FLootLockerPlayerHeroDelegate>();
			
				FLootLockerCreateHeroRequest CreateHeroRequest;
				CreateHeroRequest.hero_id = GameHeroID; // existing prefab
				CreateHeroRequest.name = "Hero instance";
			
				ULootLockerSDKManager::CreateHero(CreateHeroRequest, Delegate);
			
				const auto Response = Promise->get_future().get();
				TestTrue("Created hero success", Response.success);
				TestTrue("Created hero id verified", Response.hero.hero_id == 24);
				NewPlayerHeroId = Response.hero.id;
				delete(Promise);
			}
			// update a player hero
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
			
			// get a player hero
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerPlayerHeroResponse,FLootLockerPlayerHeroDelegate>();
			
				FLootLockerUpdateHeroRequest UpdateHeroRequest;
				UpdateHeroRequest.name ="new_hero_name";
			
				ULootLockerSDKManager::GetHero(NewPlayerHeroId,Delegate);
			
				const auto Response = Promise->get_future().get();
				TestTrue("GetHero success", Response.success);
				delete(Promise);
			}
			
			// get hero inventory
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerInventoryResponse,FInventoryResponse>();
			
				ULootLockerSDKManager::GetHeroInventory(NewPlayerHeroId,Delegate);
			
				const auto Response = Promise->get_future().get();
				TestTrue("GetHero success", Response.success);
				delete(Promise);
			}
			
			// get hero loadout
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerInventoryResponse,FInventoryResponse>();
					
				ULootLockerSDKManager::GetHeroInventory(NewPlayerHeroId,Delegate);
					
				const auto Response = Promise->get_future().get();
				TestTrue("GetHero success", Response.success);
				delete(Promise);
			}
			
			int32 AssetId = 0;
			
			// add asset to loadout
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerHeroLoadoutResponse,FHeroLoadoutReseponseDelegate>();
					
				ULootLockerSDKManager::AddAssetToHeroLoadout(NewPlayerHeroId,AssetId,Delegate);
					
				const auto Response = Promise->get_future().get();
				TestTrue("Add asset to loadout success", Response.success);
				delete(Promise);
			}			
			
			// remove asset from loadout
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerResponse,FHeroLoadoutReseponseDelegate>();
					
				ULootLockerSDKManager::RemoveAssetToHeroLoadout(NewPlayerHeroId,AssetId,Delegate);
					
				const auto Response = Promise->get_future().get();
				TestTrue("GetHero success", Response.success);
				delete(Promise);
			}			
			
			// delete the hero
			{
				const auto [Promise , Delegate] = test_util::CreateDelegate<FLootLockerResponse,FLLHeroDefaultResponseDelegate>();
				
				ULootLockerSDKManager::DeleteHero(NewPlayerHeroId, Delegate);
			
				FLootLockerResponse Response = Promise->get_future().get();
				TestTrue("Delete hero ok", Response.success);
				delete(Promise);
			}
			TestDone.Execute();
		});
	});
}
#endif

