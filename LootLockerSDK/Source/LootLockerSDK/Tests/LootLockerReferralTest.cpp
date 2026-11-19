// Copyright LootLocker AB

#include "Runtime/Launch/Resources/Version.h"
#include "Dom/JsonObject.h"
#include "GameAPI/LootLockerReferralRequestHandler.h"
#include "JsonObjectConverter.h"
#include "Misc/AutomationTest.h"

#if ENGINE_MAJOR_VERSION > 4

BEGIN_DEFINE_SPEC(
    FLootLockerReferralSpec,
    "LootLocker.Referrals",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
END_DEFINE_SPEC(FLootLockerReferralSpec)

namespace
{
    // Mirrors what LLAPI does with a response body: convert the JSON into the struct, then populate the
    // convenience structures that FJsonObjectConverter cannot derive on its own.
    template<typename ResponseType>
    bool ParseLikeLLAPI(const FString& Json, ResponseType& OutResponse)
    {
        OutResponse.FullTextFromServer = Json;
        if (!FJsonObjectConverter::JsonObjectStringToUStruct<ResponseType>(Json, &OutResponse, 0, 0))
        {
            return false;
        }
        OutResponse.PopulateConvenienceStructures();
        return true;
    }

    const FString InviteJson = TEXT(R"({
        "code": "FRIEND-UID",
        "programs": [
            {
                "program_key": "invite_a_friend",
                "name": "Invite a friend",
                "qualifier": "session_started",
                "referral_count": 3,
                "referrer_cap": 10
            },
            {
                "program_key": "uncapped",
                "name": "Uncapped",
                "qualifier": "game_asserted",
                "referral_count": 0,
                "referrer_cap": null
            }
        ]
    })");

    const FString ListJson = TEXT(R"({
        "referrals": [
            {
                "id": "01K9AAAAAAAAAAAAAAAAAAAAAA",
                "program_key": "invite_a_friend",
                "program_name": "Invite a friend",
                "referee_public_uid": "FRIEND-UID",
                "status": "qualified",
                "claimed_at": "2026-10-19T20:27:03Z",
                "qualified_at": "2026-10-19T20:30:00Z"
            },
            {
                "id": "01K9BBBBBBBBBBBBBBBBBBBBBB",
                "program_key": "invite_a_friend",
                "program_name": "Invite a friend",
                "referee_public_uid": null,
                "status": "claimed",
                "claimed_at": "2026-10-20T08:00:00Z",
                "qualified_at": null
            },
            {
                "id": "01K9CCCCCCCCCCCCCCCCCCCCCC",
                "program_key": "invite_a_friend",
                "program_name": "Invite a friend",
                "referee_public_uid": "GONE-UID",
                "status": "void",
                "claimed_at": "2026-10-21T08:00:00Z",
                "qualified_at": null
            }
        ],
        "pagination": {
            "errors": [],
            "per_page": 10,
            "offset": 0,
            "total": 3,
            "last_page": 1,
            "current_page": 1,
            "next_page": null,
            "prev_page": null
        }
    })");
}

void FLootLockerReferralSpec::Define()
{
    Describe("Referrals", [this]()
    {
        It("Invite_CappedProgram_MapsFieldsAndCap", [this]()
        {
            FLootLockerReferralInviteResponse Response;
            TestTrue("invite response failed to parse", ParseLikeLLAPI(InviteJson, Response));

            TestEqual("code", Response.code, TEXT("FRIEND-UID"));
            TestEqual("program count", Response.programs.Num(), 2);

            TestEqual("program_key", Response.programs[0].program_key, TEXT("invite_a_friend"));
            TestEqual("name", Response.programs[0].name, TEXT("Invite a friend"));
            TestTrue("qualifier", Response.programs[0].qualifier == ELootLockerReferralQualifier::session_started);
            TestEqual("referral_count", Response.programs[0].referral_count, 3);
            TestEqual("referrer_cap", Response.programs[0].referrer_cap, 10);
            TestTrue("capped program must report HasReferrerCap", Response.programs[0].HasReferrerCap);
        });

        It("Invite_NullCap_ReportsNoCap", [this]()
        {
            FLootLockerReferralInviteResponse Response;
            TestTrue("invite response failed to parse", ParseLikeLLAPI(InviteJson, Response));

            TestTrue("qualifier", Response.programs[1].qualifier == ELootLockerReferralQualifier::game_asserted);
            TestFalse("a null referrer_cap must report HasReferrerCap false", Response.programs[1].HasReferrerCap);
        });

        It("Invite_MissingCapKey_ReportsNoCap", [this]()
        {
            // An absent key must behave like a null one: the server omits nothing today, but a shape change
            // must not silently turn "uncapped" into "capped at zero".
            const FString Json = TEXT(R"({"code":"C","programs":[{"program_key":"p","name":"P","qualifier":"entitlement_owned","referral_count":0}]})");

            FLootLockerReferralInviteResponse Response;
            TestTrue("invite response failed to parse", ParseLikeLLAPI(Json, Response));

            TestEqual("program count", Response.programs.Num(), 1);
            TestFalse("a missing referrer_cap must report HasReferrerCap false", Response.programs[0].HasReferrerCap);
        });

        It("Invite_BodyWithoutPrograms_LeavesArrayEmpty", [this]()
        {
            FLootLockerReferralInviteResponse Response;
            TestTrue("invite response failed to parse", ParseLikeLLAPI(TEXT(R"({"code":"C"})"), Response));
            TestEqual("program count", Response.programs.Num(), 0);
        });

        It("List_MapsStatusesAndNullableFields", [this]()
        {
            FLootLockerReferralListResponse Response;
            TestTrue("referral list response failed to parse", ParseLikeLLAPI(ListJson, Response));

            TestEqual("referral count", Response.referrals.Num(), 3);

            TestTrue("qualified status", Response.referrals[0].status == ELootLockerReferralStatus::qualified);
            TestTrue("qualified referral must report HasQualifiedAt", Response.referrals[0].HasQualifiedAt);
            TestTrue("qualified referral must report HasRefereePublicUid", Response.referrals[0].HasRefereePublicUid);
            TestEqual("referee_public_uid", Response.referrals[0].referee_public_uid, TEXT("FRIEND-UID"));

            TestTrue("claimed status", Response.referrals[1].status == ELootLockerReferralStatus::claimed);
            TestFalse("a pending referral must report HasQualifiedAt false", Response.referrals[1].HasQualifiedAt);
            TestFalse("a removed referee must report HasRefereePublicUid false", Response.referrals[1].HasRefereePublicUid);
        });

        It("List_VoidStatus_MapsToVoidEnumerator", [this]()
        {
            // The backend sends lowercase "void"; the enumerator is Void because void is a C++ keyword.
            FLootLockerReferralListResponse Response;
            TestTrue("referral list response failed to parse", ParseLikeLLAPI(ListJson, Response));

            TestTrue("void status", Response.referrals[2].status == ELootLockerReferralStatus::Void);
        });

        It("List_MapsPagination", [this]()
        {
            FLootLockerReferralListResponse Response;
            TestTrue("referral list response failed to parse", ParseLikeLLAPI(ListJson, Response));

            TestEqual("total", Response.pagination.Total, 3);
            TestEqual("per_page", Response.pagination.Per_page, 10);
            TestEqual("current_page", Response.pagination.Current_page, 1);
        });

        It("List_BodyWithoutReferrals_LeavesArrayEmpty", [this]()
        {
            FLootLockerReferralListResponse Response;
            TestTrue("referral list response failed to parse", ParseLikeLLAPI(TEXT(R"({"referrals":[]})"), Response));
            TestEqual("referral count", Response.referrals.Num(), 0);
        });

        It("List_ArrayLengthMismatch_LeavesDataUntouched", [this]()
        {
            // Defensive: if the parsed array and the raw array disagree, the inspector must bail out rather
            // than index past the end of the parsed entries or misalign the flags.
            FLootLockerReferralListResponse Response;
            Response.FullTextFromServer = ListJson;
            TestTrue("parse failed", FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerReferralListResponse>(ListJson, &Response, 0, 0));

            // Drop the first entry so the raw body and the parsed array no longer line up.
            Response.referrals.RemoveAt(0);
            Response.PopulateConvenienceStructures();

            TestEqual("referral count is unchanged", Response.referrals.Num(), 2);
            TestFalse("the inspector must not populate flags from a mismatched body", Response.referrals[0].HasQualifiedAt);
            TestFalse("the inspector must not populate flags from a mismatched body", Response.referrals[0].HasRefereePublicUid);
        });
    });
}

#endif
