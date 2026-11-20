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

        JsonObject->SetStringField(TEXT("provider"), ULootLockerIdentityRequestHandler::ProviderToSlug(Request.provider));
        JsonObject->SetStringField(TEXT("provider_uid"), Request.provider_uid);

        return LootLockerUtilities::JsonObjectToString(JsonObject);
    }
}

FString ULootLockerIdentityRequestHandler::ProviderToSlug(ELootLockerIdentityProvider Provider)
{
    // The enumerator name is the wire value. GetNameStringByValue is used rather than
    // ULootLockerEnumUtils::GetEnum because that helper is backed by GetDisplayNameTextByValue, which reads
    // editor-only display metadata: in a packaged build it falls back to the C++ identifier, so the same
    // request could send a different slug in the editor than in shipping.
    const UEnum* Enum = StaticEnum<ELootLockerIdentityProvider>();
    if (Enum == nullptr)
    {
        return FString();
    }

    FString Name = Enum->GetNameStringByValue(static_cast<int64>(Provider));

    // Strip the "ELootLockerIdentityProvider::" prefix that GetNameStringByValue includes.
    int32 SeparatorIndex = INDEX_NONE;
    if (Name.FindLastChar(TEXT(':'), SeparatorIndex))
    {
        Name = Name.RightChop(SeparatorIndex + 1);
    }

    return Name.ToLower();
}

void ULootLockerIdentityRequestHandler::ParseLinkConflict(FLootLockerIdentityLinkResponse& Response)
{
    // A 409 is not fatal: it carries the merge offer the player must act on, so it is parsed onto the
    // response instead of being left in ErrorData.
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

void ULootLockerIdentityRequestHandler::MarkProvidersPresent(FLootLockerIdentityResponse& Response)
{
    // FJsonObjectConverter cannot tell an absent key from an empty array, so the flag is resolved from the raw
    // body. Lookup and merge omit providers entirely; GetIdentity always sends it.
    if (Response.FullTextFromServer.IsEmpty())
    {
        return;
    }

    const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
    if (!JsonObject.IsValid())
    {
        return;
    }

    const TSharedPtr<FJsonValue>* ProvidersValue = JsonObject->Values.Find(TEXT("providers"));
    Response.has_providers = ProvidersValue != nullptr && (*ProvidersValue).IsValid() && (*ProvidersValue)->Type == EJson::Array;

    if (!Response.has_providers)
    {
        return;
    }

    // FJsonObjectConverter fills the raw slug but cannot map it onto the enum without throwing or defaulting
    // silently, so each entry's provider_type is resolved from its slug here.
    for (FLootLockerIdentityProviderInfo& Provider : Response.providers)
    {
        Provider.provider_type = ULootLockerIdentityRequestHandler::SlugToProvider(Provider.provider);
    }
}

ELootLockerIdentityProvider ULootLockerIdentityRequestHandler::SlugToProvider(const FString& Slug)
{
    // The enumerator name is the wire value. GetNameStringByValue is used rather than
    // ULootLockerEnumUtils::GetEnum because that helper is backed by GetDisplayNameTextByValue, which reads
    // editor-only display metadata.
    const UEnum* Enum = StaticEnum<ELootLockerIdentityProvider>();
    if (Enum == nullptr || Slug.IsEmpty())
    {
        return ELootLockerIdentityProvider::Unknown;
    }

    for (int32 Index = 0; Index < Enum->NumEnums() - 1; ++Index)
    {
        const int64 Value = Enum->GetValueByIndex(Index);
        const ELootLockerIdentityProvider Candidate = static_cast<ELootLockerIdentityProvider>(Value);
        if (Candidate == ELootLockerIdentityProvider::Unknown)
        {
            continue;
        }

        if (ProviderToSlug(Candidate).Equals(Slug, ESearchCase::IgnoreCase))
        {
            return Candidate;
        }
    }

    return ELootLockerIdentityProvider::Unknown;
}

FString ULootLockerIdentityRequestHandler::GetProviderCredentialId(const FLootLockerIdentityResponse& Identity, ELootLockerIdentityProvider Provider)
{
    if (Provider == ELootLockerIdentityProvider::Unknown)
    {
        // unknown never identifies a specific credential.
        return FString();
    }

    for (const FLootLockerIdentityProviderInfo& Linked : Identity.providers)
    {
        if (Linked.provider_type == Provider)
        {
            return Linked.id;
        }
    }

    return FString();
}

FString ULootLockerIdentityRequestHandler::GetIdentity(const FLootLockerPlayerData& PlayerData, const FLootLockerIdentityResponseDelegate& OnComplete)
{
    return LLAPI<FLootLockerIdentityResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetIdentityEndpoint, {}, EmptyQueryParams, PlayerData, OnComplete, LLAPI<FLootLockerIdentityResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerIdentityResponse& Response)
        {
            if (Response.success)
            {
                MarkProvidersPresent(Response);
            }
        }));
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

    // Unknown is not a provider; sending it would fail the backend's platform catalog check with a 400.
    if (Request.provider == ELootLockerIdentityProvider::Unknown)
    {
        const FLootLockerIdentityLinkResponse ErrorResponse = LootLockerResponseFactory::Error<FLootLockerIdentityLinkResponse>(TEXT("provider must be set to a known provider"), LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
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