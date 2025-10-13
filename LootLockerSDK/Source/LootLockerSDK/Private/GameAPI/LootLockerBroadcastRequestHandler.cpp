// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerBroadcastRequestHandler.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerSDK.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerBroadcastRequestHandler::HttpClient = nullptr;

ULootLockerBroadcastRequestHandler::ULootLockerBroadcastRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerBroadcastRequestHandler::ListBroadcasts(const FLootLockerPlayerData& PlayerData, const TArray<FString>& Languages, int32 Limit, const FLootLockerListBroadcastsResponseDelegate& OnComplete)
{
    TMap<FString, FString> CustomHeaders;
    if (Languages.Num() > 0)
    {
        CustomHeaders.Add("Accept-Language", FString::Join(Languages, TEXT(",")));
    }
    TMultiMap<FString, FString> QueryParams;
    if (Limit > 0)
    {
        QueryParams.Add("limit", FString::FromInt(Limit));
    }
    
    LLAPI<FLootLockerInternalListBroadcastsResponse>::CallAPI(
        HttpClient, 
        FLootLockerEmptyRequest{}, 
        ULootLockerGameEndpoints::ListBroadcasts, 
        {}, 
        QueryParams, 
        PlayerData,
        FLootLockerInternalListBroadcastsResponseDelegate(), 
        LLAPI<FLootLockerInternalListBroadcastsResponse>::FResponseInspectorCallback::CreateLambda([OnComplete](FLootLockerInternalListBroadcastsResponse& InternalResponse)
        {
            FLootLockerListBroadcastsResponse UserResponse(InternalResponse);
            FLootLockerListBroadcastsResponseBP().ExecuteIfBound(UserResponse);
            OnComplete.ExecuteIfBound(UserResponse);
        }),
        CustomHeaders
    );
}

FLootLockerListBroadcastsResponse::FLootLockerListBroadcastsResponse(const FLootLockerInternalListBroadcastsResponse& OtherResponse) : FLootLockerResponse{OtherResponse.success, OtherResponse.StatusCode, OtherResponse.FullTextFromServer, OtherResponse.ErrorData, OtherResponse.Context}
{    
    for (const FLootLockerInternalBroadcast& OtherBroadcast : OtherResponse.broadcasts)
    {
        broadcasts.Add(FLootLockerBroadcast(OtherBroadcast));
    }
}

FLootLockerBroadcast::FLootLockerBroadcast(const FLootLockerInternalBroadcast& OtherBroadcast)
{
    id = OtherBroadcast.id;
    name = OtherBroadcast.name;
    game_name = OtherBroadcast.game_name;
    games = OtherBroadcast.games;
    publication_settings = OtherBroadcast.publication_settings;
    for (const FLootLockerInternalBroadcastLanguage& OtherLanguage : OtherBroadcast.languages)
    {
        FLootLockerBroadcastLanguage Language(OtherLanguage);
        languages.Add(OtherLanguage.language_code, Language);
        language_codes.Add(OtherLanguage.language_code);
    }
}

FLootLockerBroadcastLanguage::FLootLockerBroadcastLanguage(const FLootLockerInternalBroadcastLanguage& OtherLanguage)
{
    language_code = OtherLanguage.language_code;
    
    for (const FLootLockerInternalBroadcastLocalizationEntry& Localization : OtherLanguage.localizations)
    {
        // Lift standard keys to dedicated fields
        if (Localization.key == TEXT("ll.headline"))
        {
            headline = Localization.value;
            continue;
        }
        else if (Localization.key == TEXT("ll.body"))
        {
            body = Localization.value;
            continue;
        }
        else if (Localization.key == TEXT("ll.image_url"))
        {
            image_url = Localization.value;
            continue;
        }
        else if (Localization.key == TEXT("ll.action"))
        {
            action = Localization.value;
            continue;
        }
        
        // Add other localizations to the map and list
        localizations.Add(Localization.key, Localization.value);
        localization_keys.Add(Localization.key);
    }
}