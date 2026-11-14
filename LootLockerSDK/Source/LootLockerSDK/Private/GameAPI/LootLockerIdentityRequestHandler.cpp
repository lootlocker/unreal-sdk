// Copyright LootLocker AB

#include "GameAPI/LootLockerIdentityRequestHandler.h"

#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

namespace
{
    // The identity routes sit at the domain root rather than under /game, and several optional fields must
    // be omitted rather than sent as their zero value. The bodies are therefore serialized by hand.
    FString LookupRequestToJsonString(const FLootLockerIdentityLookupRequest& Request)
    {
        const TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();

        if (Request.identity_ids.Num() > 0)
        {
            TArray<TSharedPtr<FJsonValue>> IdentityIds;
            for (const FString& IdentityId : Request.identity_ids)
            {
                IdentityIds.Add(MakeShared<FJsonValueString>(IdentityId));
            }
            JsonObject->SetArrayField(TEXT("identity_ids"), IdentityIds);
        }

        if (Request.game_ids.Num() > 0)
        {
            TArray<TSharedPtr<FJsonValue>> GameIds;
            for (const int32 GameId : Request.game_ids)
            {
                GameIds.Add(MakeShared<FJsonValueNumber>(GameId));
            }
            JsonObject->SetArrayField(TEXT("game_ids"), GameIds);
        }

        // Only sent when true so the server default applies.
        if (Request.include_game_activity)
        {
            JsonObject->SetBoolField(TEXT("include_game_activity"), true);
        }

        return LootLockerUtilities::JsonObjectToString(JsonObject);
    }

    FString LinkRequestToJsonString(const FLootLockerIdentityLinkRequest& Request)
    {
        const TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();

        // The enumerator name is the wire value, so it must be lowercased rather than converted to a display
        // name.
        JsonObject->SetStringField(TEXT("provider"), ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerIdentityProvider"), static_cast<int32>(Request.provider)).ToLower());
        JsonObject->SetStringField(TEXT("provider_uid"), Request.provider_uid);

        return LootLockerUtilities::JsonObjectToString(JsonObject);
    }

    // A 409 is not fatal: it carries the merge offer the player must act on, so it is parsed onto the
    // response instead of being left in ErrorData.
    void ParseLinkConflict(FLootLockerIdentityLinkResponse& Response)
    {
        if (Response.success || Response.StatusCode != 409 || Response.FullTextFromServer.IsEmpty())
        {
            return;
        }

        const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
        if (!JsonObject.IsValid())
        {
            return;
        }

        FLootLockerIdentityLinkConflict Conflict;
        if (FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), FLootLockerIdentityLinkConflict::StaticStruct(), &Conflict, 0, 0))
        {
            Response.conflict = Conflict;
            Response.has_conflict = true;
        }
    }
}

FString ULootLockerIdentityRequestHandler::GetIdentity(const FLootLockerPlayerData& PlayerData, const FLootLockerIdentityResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerIdentityResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetIdentityEndpoint, {}, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerIdentityRequestHandler::LookupIdentities(const FLootLockerPlayerData& PlayerData, const FLootLockerIdentityLookupRequest& Request, const FLootLockerIdentityLookupResponseDelegate& OnComplete)
{
    if (Request.identity_ids.Num() == 0 && Request.game_ids.Num() == 0)
    {
        const FLootLockerIdentityLookupResponse ErrorResponse = LootLockerResponseFactory::Error<FLootLockerIdentityLookupResponse>(TEXT("at least one of identity_ids and game_ids must be supplied"), LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        OnComplete.ExecuteIfBound(ErrorResponse);
        return FString();
    }

    FString ContentString = LookupRequestToJsonString(Request);
    return LLAPI<FLootLockerIdentityLookupResponse>::CallAPIUsingRawJSON(ContentString, ULootLockerGameEndpoints::LookupIdentitiesEndpoint, {}, EmptyQueryParams, PlayerData, OnComplete, LLAPI<FLootLockerIdentityLookupResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerIdentityLookupResponse& Response)
        {
            // The lookup answers with a bare JSON array, which cannot be mapped onto a response object, so the
            // array is deserialized element by element and carried on the response.
            if (!Response.success || Response.FullTextFromServer.IsEmpty())
            {
                return;
            }

            TArray<TSharedPtr<FJsonValue>> IdentitiesJson;
            if (!LootLockerUtilities::JsonArrayFromFString(Response.FullTextFromServer, IdentitiesJson))
            {
                return;
            }

            TArray<FLootLockerIdentityResponse> Identities;
            Identities.Reserve(IdentitiesJson.Num());
            for (const TSharedPtr<FJsonValue>& IdentityJson : IdentitiesJson)
            {
                const TSharedPtr<FJsonObject>* IdentityObject = nullptr;
                if (!IdentityJson.IsValid() || !IdentityJson->TryGetObject(IdentityObject) || IdentityObject == nullptr)
                {
                    continue;
                }

                FLootLockerIdentityResponse Identity;
                if (FJsonObjectConverter::JsonObjectToUStruct((*IdentityObject).ToSharedRef(), FLootLockerIdentityResponse::StaticStruct(), &Identity, 0, 0))
                {
                    Identities.Add(Identity);
                }
            }

            Response.identities = Identities;
        }));
}

FString ULootLockerIdentityRequestHandler::LinkProvider(const FLootLockerPlayerData& PlayerData, const FLootLockerIdentityLinkRequest& Request, const FLootLockerIdentityLinkResponseDelegate& OnComplete)
{
    if (Request.provider_uid.IsEmpty())
    {
        const FLootLockerIdentityLinkResponse ErrorResponse = LootLockerResponseFactory::Error<FLootLockerIdentityLinkResponse>(TEXT("provider_uid is required"), LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        OnComplete.ExecuteIfBound(ErrorResponse);
        return FString();
    }

    FString ContentString = LinkRequestToJsonString(Request);
    return LLAPI<FLootLockerIdentityLinkResponse>::CallAPIUsingRawJSON(ContentString, ULootLockerGameEndpoints::LinkIdentityProviderEndpoint, {}, EmptyQueryParams, PlayerData, OnComplete, LLAPI<FLootLockerIdentityLinkResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerIdentityLinkResponse& Response)
        {
            ParseLinkConflict(Response);
        }));
}

FString ULootLockerIdentityRequestHandler::UnlinkProvider(const FLootLockerPlayerData& PlayerData, const FString& CredentialId, const FLootLockerDefaultDelegate& OnComplete)
{
    if (CredentialId.IsEmpty())
    {
        OnComplete.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerResponse>(TEXT("credential_id is required"), LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid));
        return FString();
    }

    return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::UnlinkIdentityProviderEndpoint, { CredentialId }, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerIdentityRequestHandler::PreviewIdentityMerge(const FLootLockerPlayerData& PlayerData, const FString& MergeIdentityId, const FLootLockerIdentityMergePreviewResponseDelegate& OnComplete)
{
    if (MergeIdentityId.IsEmpty())
    {
        const FLootLockerIdentityMergePreviewResponse ErrorResponse = LootLockerResponseFactory::Error<FLootLockerIdentityMergePreviewResponse>(TEXT("merge_identity_id is required"), LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        OnComplete.ExecuteIfBound(ErrorResponse);
        return FString();
    }

    const TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    JsonObject->SetStringField(TEXT("merge_identity_id"), MergeIdentityId);
    FString ContentString = LootLockerUtilities::JsonObjectToString(JsonObject);

    return LLAPI<FLootLockerIdentityMergePreviewResponse>::CallAPIUsingRawJSON(ContentString, ULootLockerGameEndpoints::PreviewIdentityMergeEndpoint, {}, EmptyQueryParams, PlayerData, OnComplete);
}

FString ULootLockerIdentityRequestHandler::MergeIdentities(const FLootLockerPlayerData& PlayerData, const FLootLockerIdentityMergeRequest& Request, const FLootLockerIdentityMergeResponseDelegate& OnComplete)
{
    if (Request.merge_identity_id.IsEmpty())
    {
        const FLootLockerIdentityMergeResponse ErrorResponse = LootLockerResponseFactory::Error<FLootLockerIdentityMergeResponse>(TEXT("merge_identity_id is required"), LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        OnComplete.ExecuteIfBound(ErrorResponse);
        return FString();
    }

    FString ContentString = LootLockerUtilities::UStructToJsonString(Request);
    return LLAPI<FLootLockerIdentityMergeResponse>::CallAPIUsingRawJSON(ContentString, ULootLockerGameEndpoints::MergeIdentitiesEndpoint, {}, EmptyQueryParams, PlayerData, OnComplete);
}