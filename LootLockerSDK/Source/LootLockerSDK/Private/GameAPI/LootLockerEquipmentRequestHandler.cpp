// Copyright LootLocker AB

#include "GameAPI/LootLockerEquipmentRequestHandler.h"

#include "LootLockerGameEndpoints.h"
#include "Utils/LootLockerUtilities.h"

namespace
{
    // Builds the page/per_page query map shared by every equipment read. Both are only sent when
    // positive, so the server applies its own defaults.
    TMultiMap<FString, FString> MakePageQueryParams(int32 Page, int32 PerPage)
    {
        TMultiMap<FString, FString> QueryParams;
        if (Page > 0) { QueryParams.Add("page", FString::FromInt(Page)); }
        if (PerPage > 0) { QueryParams.Add("per_page", FString::FromInt(PerPage)); }
        return QueryParams;
    }

    // The equip body is serialized by hand because count and replace are optional: sending them as
    // 0/false would override the server defaults.
    FString EquipRequestToJsonString(const FLootLockerEquipmentEquipRequest& Request)
    {
        const TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
        JsonObject->SetStringField(TEXT("entity_type"), Request.entity_type);
        JsonObject->SetStringField(TEXT("source_id"), Request.source_id);
        JsonObject->SetStringField(TEXT("slot_id"), Request.slot_id);
        JsonObject->SetStringField(TEXT("inventory_id"), Request.inventory_id);
        if (Request.count > 0)
        {
            JsonObject->SetNumberField(TEXT("count"), Request.count);
        }
        JsonObject->SetBoolField(TEXT("replace"), Request.replace);

        return LootLockerUtilities::JsonObjectToString(JsonObject);
    }

    // FJsonObjectConverter only fills a struct field when the JSON key is present, so a null stack
    // leaves the member defaulted. This flag records which slots actually carried a stack.
    void MarkAttachedStacks(FLootLockerEquipmentLoadoutResponse& Response)
    {
        if (Response.FullTextFromServer.IsEmpty())
        {
            return;
        }

        const TSharedPtr<FJsonObject> JsonObject = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
        if (!JsonObject.IsValid())
        {
            return;
        }

        const TArray<TSharedPtr<FJsonValue>>* GroupsJson = nullptr;
        if (!JsonObject->TryGetArrayField(TEXT("groups"), GroupsJson) || GroupsJson == nullptr)
        {
            return;
        }

        const int32 GroupCount = FMath::Min(GroupsJson->Num(), Response.groups.Num());
        for (int32 GroupIndex = 0; GroupIndex < GroupCount; ++GroupIndex)
        {
            const TSharedPtr<FJsonObject>* GroupObject = nullptr;
            if (!(*GroupsJson)[GroupIndex].IsValid() || !(*GroupsJson)[GroupIndex]->TryGetObject(GroupObject) || GroupObject == nullptr)
            {
                continue;
            }

            const TArray<TSharedPtr<FJsonValue>>* SlotsJson = nullptr;
            if (!(*GroupObject)->TryGetArrayField(TEXT("slots"), SlotsJson) || SlotsJson == nullptr)
            {
                continue;
            }

            TArray<FLootLockerEquipmentSlotAndStack>& Slots = Response.groups[GroupIndex].slots;
            const int32 SlotCount = FMath::Min(SlotsJson->Num(), Slots.Num());
            for (int32 SlotIndex = 0; SlotIndex < SlotCount; ++SlotIndex)
            {
                if (!(*SlotsJson)[SlotIndex].IsValid())
                {
                    continue;
                }

                const TSharedPtr<FJsonObject>* SlotObject = nullptr;
                if (!(*SlotsJson)[SlotIndex]->TryGetObject(SlotObject) || SlotObject == nullptr)
                {
                    continue;
                }

                const TSharedPtr<FJsonValue>* StackValue = (*SlotObject)->Values.Find(TEXT("stack"));
                Slots[SlotIndex].HasStack = StackValue != nullptr && (*StackValue).IsValid() && (*StackValue)->Type != EJson::Null;
            }
        }
    }
}

FString ULLEquipmentRequestHandler::GetLoadout(const FLootLockerPlayerData& PlayerData, int32 Page, int32 PerPage, const FLootLockerEquipmentLoadoutResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerEquipmentLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetEquipmentLoadoutEndpoint, { }, MakePageQueryParams(Page, PerPage), PlayerData, OnCompletedRequest, LLAPI<FLootLockerEquipmentLoadoutResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerEquipmentLoadoutResponse& Response)
        {
            if (Response.success)
            {
                MarkAttachedStacks(Response);
            }
        }));
}

FString ULLEquipmentRequestHandler::GetEntityLoadout(const FLootLockerPlayerData& PlayerData, const FString& EntityType, const FString& SourceId, int32 Page, int32 PerPage, const FLootLockerEquipmentLoadoutResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerEquipmentLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetEntityEquipmentLoadoutEndpoint, { EntityType, SourceId }, MakePageQueryParams(Page, PerPage), PlayerData, OnCompletedRequest, LLAPI<FLootLockerEquipmentLoadoutResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerEquipmentLoadoutResponse& Response)
        {
            if (Response.success)
            {
                MarkAttachedStacks(Response);
            }
        }));
}

FString ULLEquipmentRequestHandler::GetOtherPlayerLoadout(const FLootLockerPlayerData& PlayerData, const FString& PlayerPublicUid, int32 Page, int32 PerPage, const FLootLockerEquipmentLoadoutResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerEquipmentLoadoutResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetOtherPlayersEquipmentLoadoutEndpoint, { PlayerPublicUid }, MakePageQueryParams(Page, PerPage), PlayerData, OnCompletedRequest, LLAPI<FLootLockerEquipmentLoadoutResponse>::FResponseInspectorCallback::CreateLambda([](FLootLockerEquipmentLoadoutResponse& Response)
        {
            if (Response.success)
            {
                MarkAttachedStacks(Response);
            }
        }));
}

FString ULLEquipmentRequestHandler::ListSlotCandidates(const FLootLockerPlayerData& PlayerData, const FString& SlotId, int32 Page, int32 PerPage, const FLootLockerEquipmentSlotCandidatesResponseDelegate& OnCompletedRequest)
{
    return LLAPI<FLootLockerEquipmentSlotCandidatesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::ListEquipmentSlotCandidatesEndpoint, { SlotId }, MakePageQueryParams(Page, PerPage), PlayerData, OnCompletedRequest);
}

FString ULLEquipmentRequestHandler::EquipStack(const FLootLockerPlayerData& PlayerData, const FLootLockerEquipmentEquipRequest& Request, const FLootLockerEquipmentEquipResponseDelegate& OnCompletedRequest)
{
    if (Request.entity_type.IsEmpty() || Request.source_id.IsEmpty() || Request.slot_id.IsEmpty() || Request.inventory_id.IsEmpty())
    {
        const FLootLockerEquipmentEquipResponse ErrorResponse = LootLockerResponseFactory::Error<FLootLockerEquipmentEquipResponse>(TEXT("entity_type, source_id, slot_id and inventory_id are required"), 0, PlayerData.PlayerUlid);
        OnCompletedRequest.ExecuteIfBound(ErrorResponse);
        return FString();
    }

    FString ContentString = EquipRequestToJsonString(Request);
    return LLAPI<FLootLockerEquipmentEquipResponse>::CallAPIUsingRawJSON(ContentString, ULootLockerGameEndpoints::EquipToEquipmentSlotEndpoint, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULLEquipmentRequestHandler::UnequipStack(const FLootLockerPlayerData& PlayerData, const FString& EntryId, const FLootLockerDefaultDelegate& OnCompletedRequest)
{
    if (EntryId.IsEmpty())
    {
        OnCompletedRequest.ExecuteIfBound(LootLockerResponseFactory::Error<FLootLockerResponse>(TEXT("entry_id is required"), 0, PlayerData.PlayerUlid));
        return FString();
    }

    return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::UnequipFromEquipmentSlotEndpoint, { EntryId }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}
