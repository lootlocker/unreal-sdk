// Copyright (c) 2021 LootLocker


#include "GameAPI/LootLockerPlayerRequestHandler.h"
#include "Dom/JsonObject.h"
#include "LootLockerGameEndpoints.h"
#include "LootLockerLogger.h"
#include "LootLockerPlatformManager.h"
#include "Utils/LootLockerUtilities.h"

FString ULootLockerPlayerRequestHandler::GetCurrentPlayerInfo(const FLootLockerPlayerData& PlayerData, const FLootLockerGetCurrentPlayerInfoResponseDelegate& OnCompletedRequest)
{
	return LLAPI<FLootLockerGetCurrentPlayerInfoResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetInfoFromSession, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::ListPlayerInfo(const FLootLockerPlayerData& PlayerData, TArray<FString> PlayerIdsToLookUp, TArray<int> PlayerLegacyIdsToLookUp, TArray<FString> PlayerPublicUidsToLookUp, const FLootLockerListPlayerInfoResponseDelegate& OnCompletedRequest)
{
	if (PlayerIdsToLookUp.Num() == 0 && PlayerLegacyIdsToLookUp.Num() == 0 && PlayerPublicUidsToLookUp.Num() == 0)
	{
		FLootLockerListPlayerInfoResponse emptySuccess;
		emptySuccess.success = true;
		emptySuccess.StatusCode = 200;
		emptySuccess.FullTextFromServer = "{}";
		emptySuccess.Context.PlayerUlid = PlayerData.PlayerUlid;
		OnCompletedRequest.ExecuteIfBound(emptySuccess);
		return "";
	}

	FLootLockerListPlayerInfoRequest request
	{
		PlayerIdsToLookUp,
		PlayerLegacyIdsToLookUp,
		PlayerPublicUidsToLookUp
	};

	return LLAPI<FLootLockerListPlayerInfoResponse>::CallAPI(request, ULootLockerGameEndpoints::ListPlayerInfo, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::GetInventory(const FLootLockerPlayerData& PlayerData, const FInventoryResponse& OnCompletedRequest)
{
	return GetFullInventory(PlayerData, OnCompletedRequest, 0);
}

FString ULootLockerPlayerRequestHandler::GetFullInventory(const FLootLockerPlayerData& PlayerData, const FInventoryResponse& OnCompletedRequest, int32 StartIndex)
{
	TMultiMap<FString, FString> QueryParams;

	if (StartIndex != 0)
	{
		QueryParams.Add("after", FString::FromInt(StartIndex));
	}

	QueryParams.Add("count", "200");

	return LLAPI<FLootLockerInventoryResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerInventoryEndPoint, { }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::GetCurrencyBalance(const FLootLockerPlayerData& PlayerData, const FPBalanceResponse& OnCompletedRequest)
{
	return LLAPI<FLootLockerBalanceResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetCurrencyBalance, { }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::CheckPlayerAssetNotification(const FLootLockerPlayerData& PlayerData, const FLootLockerAssetNotificationResponse& OnCompletedRequest)
{
	return LLAPI<FLootLockerPlayerAssetNotificationResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::CheckPlayerAssetActivationEndpoint, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::InitiateDLCMigration(const FLootLockerPlayerData& PlayerData, const FResponseCallback& OnCompletedRequest)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::InitiateDLCMigration, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::GetDLCsMigration(const FLootLockerPlayerData& PlayerData, const FPDlcResponse& OnCompletedRequest)
{
	return LLAPI<FLootLockerDlcResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetDLCsMigrated, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::SetProfilePrivate(const FLootLockerPlayerData& PlayerData, const FResponseCallback& OnCompletedRequest)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePrivate, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::SetProfilePublic(const FLootLockerPlayerData& PlayerData, const FResponseCallback& OnCompletedRequest)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::SetProfilePublic, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::SetPlayerName(const FLootLockerPlayerData& PlayerData, FString Name, const FPNameResponse& OnCompletedRequest)
{

	if (PlayerData.CurrentPlatform.Platform == ELootLockerPlatform::Guest)
	{
		if (Name.Equals(PlayerData.PlayerIdentifier, ESearchCase::IgnoreCase))
		{
			FLootLockerNameResponse Error = LootLockerResponseFactory::Error<FLootLockerNameResponse>("Cannot set the Player name to their Identifier", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        	FLootLockerLogger::LogHttpRequest(Error, "No Headers");
			OnCompletedRequest.ExecuteIfBound(Error);
			return "";
		}
		else if (Name.Equals("player", ESearchCase::IgnoreCase)) {
			FLootLockerNameResponse Error = LootLockerResponseFactory::Error<FLootLockerNameResponse>("Cannot set the Player name to 'Player'", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        	FLootLockerLogger::LogHttpRequest(Error, "No Headers");
			OnCompletedRequest.ExecuteIfBound(Error);
			return "";
		}
	}

	FLootLockerPlayerNameRequest Data;

	Data.name = Name;

	return LLAPI<FLootLockerNameResponse>::CallAPI(Data, ULootLockerGameEndpoints::SetPlayerName, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::GetPlayerName(const FLootLockerPlayerData& PlayerData, const FPNameResponse& OnCompletedRequest)
{
	return LLAPI<FLootLockerNameResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::GetPlayerName, {  }, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::LookupMultiplePlayerNamesUsingIDs(const FLootLockerPlayerData& PlayerData, FLootLockerMultiplePlayerNamesRequest Request, const FPMultiplePlayerNames& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;

	for (const auto& player : Request.player_ids)
	{
		QueryParams.Add(player.platform, player.player_id);
	}
	return LLAPI<FLootLockerMultiplePlayersNamesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::LookupMultiplePlayersDataUsingIDs(const FLootLockerPlayerData& PlayerData, FLootLockerLookupMultiplePlayersDataRequest Request, const FPMultiplePlayerNames& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	for (int i = 0; i < Request.player_ids.Num(); ++i) {
		FString Key = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerPlayerDataLookupIdType"), static_cast<int32_t>(Request.player_ids[i].IdType)).ToLower();
		Key.ReplaceCharInline(TEXT(' '), TEXT('_'));
		QueryParams.Add(Key, Request.player_ids[i].Id);
	}
	return LLAPI<FLootLockerMultiplePlayersNamesResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayerNamesUsingIDs, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::LookupMultiplePlayerNames1stPlatformIDs(const FLootLockerPlayerData& PlayerData, const FLootLockerMultiplePlayerNamesAndPlatformsRequest& Request, const FPMultiplePlayersPlatformIdsNames& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;

	for (const auto& player_id : Request.player_ids)
	{
		QueryParams.Add("player_id", player_id);
	}
	for (const auto& player_public_uid : Request.player_public_uids)
	{
		QueryParams.Add("player_public_uid", player_public_uid);
	}
	return LLAPI<FLootLockerMultiplePlayersPlatformIdsResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::LookupMultiplePlayer1stPlatformID, {  }, QueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::DeletePlayer(const FLootLockerPlayerData& PlayerData, const FLootLockerDefaultDelegate OnCompletedRequest)
{
	return LLAPI<FLootLockerResponse>::CallAPI(LootLockerEmptyRequest, ULootLockerGameEndpoints::DeletePlayer, {}, EmptyQueryParams, PlayerData, OnCompletedRequest);
}

FString ULootLockerPlayerRequestHandler::ListPlayerInventory(const FLootLockerPlayerData& PlayerData, const FLootLockerListSimplifiedInventoryRequest& Request, int32 PerPage, int32 Page, const FLootLockerSimpleInventoryResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	QueryParams.Add("per_page", FString::FromInt(PerPage > 0 ? PerPage : 100));
	QueryParams.Add("page", FString::FromInt(Page > 0 ? Page : 1));

	auto requestJsonObj = LootLockerUtilities::UStructToJsonObject(Request);

	if (Request.Includes.Metadata.Keys.Num() > 0) {
		requestJsonObj->GetObjectField(TEXT("includes"))->GetObjectField(TEXT("metadata"))->RemoveField(TEXT("all"));
	} else if (Request.Includes.Metadata.All) {
		requestJsonObj->GetObjectField(TEXT("includes"))->GetObjectField(TEXT("metadata"))->RemoveField(TEXT("keys"));
	} else {
		requestJsonObj->GetObjectField(TEXT("includes"))->SetField(TEXT("metadata"), MakeShared<FJsonValueNull>());
	}

	FString ContentString = LootLockerUtilities::FStringFromJsonObject(requestJsonObj);

	LLAPI<FLootLockerSimpleInventoryResponse>::FResponseInspectorCallback ResponseParser = LLAPI<FLootLockerSimpleInventoryResponse>::FResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerSimpleInventoryResponse& Response)
	{
		if (!Response.success || Response.Items.Num() == 0)
		{
			OnCompletedRequest.ExecuteIfBound(Response);
			return;
		}
		TSharedPtr<FJsonObject> obj = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
		if (!obj.IsValid())
		{
			OnCompletedRequest.ExecuteIfBound(Response);
			return;
		}

		TArray<TSharedPtr<FJsonValue>> JsonItems = obj.Get()->GetArrayField(TEXT("items"));
		if (JsonItems.Num() != Response.Items.Num())
		{
			OnCompletedRequest.ExecuteIfBound(Response);
			return;
		}

		auto findCorrectItem = [](TArray<FLootLockerSimpleInventoryItem>& Items, TArray<TSharedPtr<FJsonValue>>& JsonItems, int instance_id, int startIndex) -> FLootLockerSimpleInventoryItem*
		{
			int i = startIndex;
			do {
				FLootLockerSimpleInventoryItem& Item = Items[i];
				if (Item.Instance_id == instance_id)
				{
					return &Item;
				}
				i++;
				if (i >= JsonItems.Num())
				{
					i = 0;
				}
			} while (i != startIndex);
			return nullptr;
		};

		auto findCorrectMetadataEntry = [&](FLootLockerSimpleInventoryItem& Item, const FString& metadataKey, int startIndex) -> FLootLockerMetadataEntry*
		{
			int i = startIndex;
			do {
				FLootLockerMetadataEntry& MetadataEntry = Item.Metadata[i];
				if (MetadataEntry.Key.Equals(metadataKey))
				{
					return &MetadataEntry;
				}
				i++;
				if (i >= Item.Metadata.Num())
				{
					i = 0;
				}
			} while (i != startIndex);
			return nullptr;
		};

		for (int i = 0; i < JsonItems.Num(); i++)
		{
			TSharedPtr<FJsonObject> JsonItemObject = JsonItems[i].Get()->AsObject();
			int InstanceId = JsonItemObject.Get()->GetIntegerField(TEXT("instance_id"));
			FLootLockerSimpleInventoryItem* ItemPtr = findCorrectItem(Response.Items, JsonItems, InstanceId, i);
			if (!ItemPtr)
			{
				continue;
			}
			FLootLockerSimpleInventoryItem& Item = *ItemPtr;
			if (Item.Metadata.Num() == 0)
			{
				continue;
			}
			TArray<TSharedPtr<FJsonValue>> JsonMetadataArray = JsonItemObject.Get()->GetArrayField(TEXT("metadata"));
			if (JsonMetadataArray.Num() != Item.Metadata.Num())
			{
				OnCompletedRequest.ExecuteIfBound(Response);
				return;
			}

			for (int j = 0; j < JsonMetadataArray.Num(); j++)
			{
				TSharedPtr<FJsonObject> JsonMetadataObject = JsonMetadataArray[j].Get()->AsObject();
				FString MetadataKey = JsonMetadataObject.Get()->GetStringField(TEXT("key"));
				FLootLockerMetadataEntry* MetadataEntryPtr = findCorrectMetadataEntry(Item, MetadataKey, j);
				if (!MetadataEntryPtr)
				{
					continue;
				}
				FLootLockerMetadataEntry& MetadataEntry = *MetadataEntryPtr;
				MetadataEntry._INTERNAL_SetJsonRepresentation(*JsonMetadataObject.Get());
			}
		}

		OnCompletedRequest.ExecuteIfBound(Response);
	});

	return LLAPI<FLootLockerSimpleInventoryResponse>::CallAPIUsingRawJSON(ContentString, ULootLockerGameEndpoints::ListPlayerSimpleInventoryEndPoint, {}, QueryParams, PlayerData, FLootLockerSimpleInventoryResponseDelegate(), ResponseParser);
}

FString ULootLockerPlayerRequestHandler::ListCharacterInventory(const FLootLockerPlayerData& PlayerData, const FLootLockerListSimplifiedInventoryRequest& Request, int32 CharacterId, int32 PerPage, int32 Page, const FLootLockerSimpleInventoryResponseDelegate& OnCompletedRequest)
{
	TMultiMap<FString, FString> QueryParams;
	if (CharacterId > 0)
	{
		QueryParams.Add("character_id", FString::FromInt(CharacterId));
	}
	QueryParams.Add("per_page", FString::FromInt(PerPage > 0 ? PerPage : 100));
	QueryParams.Add("page", FString::FromInt(Page > 0 ? Page : 1));

	auto requestJsonObj = LootLockerUtilities::UStructToJsonObject(Request);

	if (Request.Includes.Metadata.Keys.Num() > 0) {
		requestJsonObj->GetObjectField(TEXT("includes"))->GetObjectField(TEXT("metadata"))->RemoveField(TEXT("all"));
	} else if (Request.Includes.Metadata.All) {
		requestJsonObj->GetObjectField(TEXT("includes"))->GetObjectField(TEXT("metadata"))->RemoveField(TEXT("keys"));
	} else {
		requestJsonObj->GetObjectField(TEXT("includes"))->SetField(TEXT("metadata"), MakeShared<FJsonValueNull>());
	}

	FString ContentString = LootLockerUtilities::FStringFromJsonObject(requestJsonObj);

	LLAPI<FLootLockerSimpleInventoryResponse>::FResponseInspectorCallback ResponseParser = LLAPI<FLootLockerSimpleInventoryResponse>::FResponseInspectorCallback::CreateLambda([OnCompletedRequest](FLootLockerSimpleInventoryResponse& Response)
	{
		if (!Response.success || Response.Items.Num() == 0)
		{
			OnCompletedRequest.ExecuteIfBound(Response);
			return;
		}
		TSharedPtr<FJsonObject> obj = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
		if (!obj.IsValid())
		{
			OnCompletedRequest.ExecuteIfBound(Response);
			return;
		}

		TArray<TSharedPtr<FJsonValue>> JsonItems = obj.Get()->GetArrayField(TEXT("items"));
		if (JsonItems.Num() != Response.Items.Num())
		{
			OnCompletedRequest.ExecuteIfBound(Response);
			return;
		}

		auto findCorrectItem = [](TArray<FLootLockerSimpleInventoryItem>& Items, TArray<TSharedPtr<FJsonValue>>& JsonItems, int instance_id, int startIndex) -> FLootLockerSimpleInventoryItem*
		{
			int i = startIndex;
			do {
				FLootLockerSimpleInventoryItem& Item = Items[i];
				if (Item.Instance_id == instance_id)
				{
					return &Item;
				}
				i++;
				if (i >= JsonItems.Num())
				{
					i = 0;
				}
			} while (i != startIndex);
			return nullptr;
		};

		auto findCorrectMetadataEntry = [&](FLootLockerSimpleInventoryItem& Item, const FString& metadataKey, int startIndex) -> FLootLockerMetadataEntry*
		{
			int i = startIndex;
			do {
				FLootLockerMetadataEntry& MetadataEntry = Item.Metadata[i];
				if (MetadataEntry.Key.Equals(metadataKey))
				{
					return &MetadataEntry;
				}
				i++;
				if (i >= Item.Metadata.Num())
				{
					i = 0;
				}
			} while (i != startIndex);
			return nullptr;
		};

		for (int i = 0; i < JsonItems.Num(); i++)
		{
			TSharedPtr<FJsonObject> JsonItemObject = JsonItems[i].Get()->AsObject();
			int InstanceId = JsonItemObject.Get()->GetIntegerField(TEXT("instance_id"));
			FLootLockerSimpleInventoryItem* ItemPtr = findCorrectItem(Response.Items, JsonItems, InstanceId, i);
			if (!ItemPtr)
			{
				continue;
			}
			FLootLockerSimpleInventoryItem& Item = *ItemPtr;
			if (Item.Metadata.Num() == 0)
			{
				continue;
			}
			TArray<TSharedPtr<FJsonValue>> JsonMetadataArray = JsonItemObject.Get()->GetArrayField(TEXT("metadata"));
			if (JsonMetadataArray.Num() != Item.Metadata.Num())
			{
				OnCompletedRequest.ExecuteIfBound(Response);
				return;
			}

			for (int j = 0; j < JsonMetadataArray.Num(); j++)
			{
				TSharedPtr<FJsonObject> JsonMetadataObject = JsonMetadataArray[j].Get()->AsObject();
				FString MetadataKey = JsonMetadataObject.Get()->GetStringField(TEXT("key"));
				FLootLockerMetadataEntry* MetadataEntryPtr = findCorrectMetadataEntry(Item, MetadataKey, j);
				if (!MetadataEntryPtr)
				{
					continue;
				}
				FLootLockerMetadataEntry& MetadataEntry = *MetadataEntryPtr;
				MetadataEntry._INTERNAL_SetJsonRepresentation(*JsonMetadataObject.Get());
			}
		}

		OnCompletedRequest.ExecuteIfBound(Response);
	});

	return LLAPI<FLootLockerSimpleInventoryResponse>::CallAPIUsingRawJSON(ContentString, ULootLockerGameEndpoints::ListPlayerSimpleInventoryEndPoint, {}, QueryParams, PlayerData, FLootLockerSimpleInventoryResponseDelegate(), ResponseParser);
}

bool FLootLockerSimpleInventoryItem::TryGetPurchaseData(FLootLockerInventoryItemPurchaseData& Output) const
{
	if (Metadata.Num() == 0)
	{
		return false;
	}
	for (size_t i = 0; i < Metadata.Num(); i++)
	{
		const FLootLockerMetadataEntry& MetadataEntry = Metadata[i];
		if (MetadataEntry.Key.Equals("ll.purchased", ESearchCase::IgnoreCase))
		{
			FString jsonString = "";
			if (MetadataEntry.TryGetSerializedValue(jsonString))
			{
				return FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerInventoryItemPurchaseData>(jsonString, &Output, 0, 0);
			}
		}
	}
	return false;	
}

