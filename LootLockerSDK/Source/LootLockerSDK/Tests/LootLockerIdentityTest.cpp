// Copyright LootLocker AB

#include "Runtime/Launch/Resources/Version.h"
#include "GameAPI/LootLockerIdentityRequestHandler.h"
#include "Misc/AutomationTest.h"

#if ENGINE_MAJOR_VERSION > 4

BEGIN_DEFINE_SPEC(
    FLootLockerIdentitySpec,
    "LootLocker.Identity",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FLootLockerIdentitySpec)

void FLootLockerIdentitySpec::Define()
{
    Describe("provider slugs", [this]()
    {
        // The wire value is the lowercased enumerator name. These must not drift from the backend platform
        // catalog, and must not depend on editor-only display metadata.
        const TArray<TPair<ELootLockerIdentityProvider, FString>> Cases = {
            { ELootLockerIdentityProvider::Steam,              TEXT("steam")              },
            { ELootLockerIdentityProvider::Psn,                TEXT("psn")                },
            { ELootLockerIdentityProvider::Apple_app_store,    TEXT("apple_app_store")    },
            { ELootLockerIdentityProvider::Google_play_store,  TEXT("google_play_store")  },
            { ELootLockerIdentityProvider::Xbox_one,           TEXT("xbox_one")           },
            { ELootLockerIdentityProvider::Nintendo_switch,    TEXT("nintendo_switch")    },
            { ELootLockerIdentityProvider::White_label_login,  TEXT("white_label_login")  },
            { ELootLockerIdentityProvider::Apple_game_center,  TEXT("apple_game_center")  },
            { ELootLockerIdentityProvider::Google_play_games,  TEXT("google_play_games")  },
            { ELootLockerIdentityProvider::Lootlocker_delegation, TEXT("lootlocker_delegation") },
        };

        for (const TPair<ELootLockerIdentityProvider, FString>& Pair : Cases)
        {
            const ELootLockerIdentityProvider Provider = Pair.Key;
            const FString Expected = Pair.Value;

            It(FString::Printf(TEXT("'%s' maps to '%s'"), *Expected, *Expected), [this, Provider, Expected]()
            {
                TestEqual("Provider slug", ULootLockerIdentityRequestHandler::ProviderToSlug(Provider), Expected);
            });
        }

        It("every provider maps to a non-empty slug", [this]()
        {
            const UEnum* Enum = StaticEnum<ELootLockerIdentityProvider>();
            if (!TestNotNull("ELootLockerIdentityProvider UEnum must exist", Enum)) return;

            for (int32 Index = 0; Index < Enum->NumEnums() - 1; ++Index)
            {
                const ELootLockerIdentityProvider Provider = static_cast<ELootLockerIdentityProvider>(Enum->GetValueByIndex(Index));
                const FString Slug = ULootLockerIdentityRequestHandler::ProviderToSlug(Provider);
                TestFalse(FString::Printf(TEXT("slug for index %d must not be empty"), Index), Slug.IsEmpty());
                TestFalse(FString::Printf(TEXT("slug '%s' must not contain a namespace separator"), *Slug), Slug.Contains(TEXT(":")));
                TestEqual(FString::Printf(TEXT("slug '%s' must be lowercase"), *Slug), Slug, Slug.ToLower());
            }
        });
    });

    Describe("link conflict parsing", [this]()
    {
        It("a 409 populates the conflict and sets has_conflict", [this]()
        {
            FLootLockerIdentityLinkResponse Response;
            Response.success = false;
            Response.StatusCode = 409;
            Response.FullTextFromServer = TEXT("{\"message\":\"This platform is already linked to another account\",\"conflicting_identity_id\":\"01K8Q3V6ZC9S2W4G7K3M8X0BQR\",\"merge_preview\":{\"keep_identity_id\":\"01K8Q3KH8N4R2V6W3Z0P5M9XDT\",\"merge_identity_id\":\"01K8Q3V6ZC9S2W4G7K3M8X0BQR\",\"player_conflicts\":[{\"game_id\":1234,\"keep_player_id\":1001,\"merge_player_id\":1002}]}}");

            ULootLockerIdentityRequestHandler::ParseLinkConflict(Response);

            TestTrue("has_conflict must be set", Response.has_conflict);
            TestEqual("conflicting_identity_id", Response.conflict.conflicting_identity_id, TEXT("01K8Q3V6ZC9S2W4G7K3M8X0BQR"));
            TestEqual("keep_identity_id", Response.conflict.merge_preview.keep_identity_id, TEXT("01K8Q3KH8N4R2V6W3Z0P5M9XDT"));
            TestEqual("player_conflicts count", Response.conflict.merge_preview.player_conflicts.Num(), 1);
            TestEqual("conflict game_id", Response.conflict.merge_preview.player_conflicts[0].game_id, 1234);
            TestEqual("conflict keep_player_id", Response.conflict.merge_preview.player_conflicts[0].keep_player_id, 1001);
            TestEqual("conflict merge_player_id", Response.conflict.merge_preview.player_conflicts[0].merge_player_id, 1002);
        });

        It("a 409 with no conflicts still carries the merge offer", [this]()
        {
            FLootLockerIdentityLinkResponse Response;
            Response.success = false;
            Response.StatusCode = 409;
            Response.FullTextFromServer = TEXT("{\"message\":\"This platform is already linked to another account\",\"conflicting_identity_id\":\"01K8Q3V6ZC9S2W4G7K3M8X0BQR\",\"merge_preview\":{\"keep_identity_id\":\"01K8Q3KH8N4R2V6W3Z0P5M9XDT\",\"merge_identity_id\":\"01K8Q3V6ZC9S2W4G7K3M8X0BQR\",\"player_conflicts\":[]}}");

            ULootLockerIdentityRequestHandler::ParseLinkConflict(Response);

            TestTrue("has_conflict must be set", Response.has_conflict);
            TestEqual("player_conflicts must be empty", Response.conflict.merge_preview.player_conflicts.Num(), 0);
        });

        It("a successful response is left untouched", [this]()
        {
            FLootLockerIdentityLinkResponse Response;
            Response.success = true;
            Response.StatusCode = 200;
            Response.FullTextFromServer = TEXT("{\"created\":true}");

            ULootLockerIdentityRequestHandler::ParseLinkConflict(Response);

            TestFalse("has_conflict must not be set", Response.has_conflict);
        });

        It("a non-409 failure is left untouched", [this]()
        {
            FLootLockerIdentityLinkResponse Response;
            Response.success = false;
            Response.StatusCode = 400;
            Response.FullTextFromServer = TEXT("{\"message\":\"invalid provider\"}");

            ULootLockerIdentityRequestHandler::ParseLinkConflict(Response);

            TestFalse("has_conflict must not be set", Response.has_conflict);
        });

        It("an unparseable 409 body does not set has_conflict", [this]()
        {
            FLootLockerIdentityLinkResponse Response;
            Response.success = false;
            Response.StatusCode = 409;
            Response.FullTextFromServer = TEXT("not json");

            ULootLockerIdentityRequestHandler::ParseLinkConflict(Response);

            TestFalse("has_conflict must not be set", Response.has_conflict);
        });
    });
}

#endif