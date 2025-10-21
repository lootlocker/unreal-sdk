// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "LootLockerLogger.h"
#include "Dom/JsonObject.h"
#include "Utils/LootLockerUtilities.h"

//==================================================
// Metadata Entry Methods
//==================================================

bool FLootLockerMetadataEntry::TryGetValueAsString(FString& Output) const
{
	return EntryAsJson.TryGetStringField(TEXT("value"), Output);
}

bool FLootLockerMetadataEntry::TryGetValueAsFloat(float& Output) const
{
#if ENGINE_MAJOR_VERSION > 5
	return EntryAsJson.TryGetNumberField(TEXT("value"), Output);
#else
	double outDouble = 0.0f;
	bool success = EntryAsJson.TryGetNumberField(TEXT("value"), outDouble);
	Output = static_cast<float>(outDouble);
	return success;
#endif
}

bool FLootLockerMetadataEntry::TryGetValueAsInteger(int& Output) const
{
	return EntryAsJson.TryGetNumberField(TEXT("value"), Output);
}

bool FLootLockerMetadataEntry::TryGetValueAsBool(bool& Output) const
{
	return EntryAsJson.TryGetBoolField(TEXT("value"), Output);
}

bool FLootLockerMetadataEntry::TryGetRawValue(TSharedPtr<FJsonValue>& Output) const
{
	if (!EntryAsJson.HasField(TEXT("value")))
	{
		return false;
	}
	Output = EntryAsJson.Values[TEXT("value")];
	return Output.IsValid();
}

bool FLootLockerMetadataEntry::TryGetSerializedValue(FString& Output) const
{
	TSharedPtr<FJsonValue> Val;
	if(!TryGetRawValue(Val) || !Val.IsValid())
	{
		return false;
	}
	if (Type == ELootLockerMetadataTypes::Json || Type == ELootLockerMetadataTypes::Base64)
	{
		if (Val->Type == EJson::Object) {
			Output = LootLockerUtilities::FStringFromJsonObject(Val->AsObject());
			return !Output.IsEmpty();
		}
		Output = LootLockerUtilities::FStringFromJsonArray(Val->AsArray());
		return !Output.IsEmpty();
	}
	return Val->TryGetString(Output);
}

bool FLootLockerMetadataEntry::TryGetValueAsJsonObject(TSharedPtr<FJsonObject>& Output) const
{
	if(!EntryAsJson.HasTypedField<EJson::Object>(TEXT("value")))
	{
		return false;
	}
	Output = EntryAsJson.GetObjectField(TEXT("value"));
	return Output.IsValid();
}

bool FLootLockerMetadataEntry::TryGetValueAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const
{
	if (!EntryAsJson.HasTypedField<EJson::Array>(TEXT("value")))
	{
		return false;
	}
	Output = EntryAsJson.GetArrayField(TEXT("value"));
	return true;
}

bool FLootLockerMetadataEntry::TryGetValueAsBase64(FLootLockerMetadataBase64Value& Output) const
{
	TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();
	if (!TryGetValueAsJsonObject(jsonObject))
	{
		return false;
	}
	return FJsonObjectConverter::JsonObjectToUStruct<FLootLockerMetadataBase64Value>(jsonObject.ToSharedRef(), &Output, 0, 0);
}

void FLootLockerMetadataEntry::SetValueAsString(const FString& Value) 
{
	EntryAsJson.SetStringField(TEXT("value"), Value);
	Type = ELootLockerMetadataTypes::String;
}

void FLootLockerMetadataEntry::SetValueAsFloat(const float& Value) 
{
	EntryAsJson.SetNumberField(TEXT("value"), Value);
	Type = ELootLockerMetadataTypes::Number;
}

void FLootLockerMetadataEntry::SetValueAsInteger(const int& Value) 
{
	EntryAsJson.SetNumberField(TEXT("value"), Value);
	Type = ELootLockerMetadataTypes::Number;
}

void FLootLockerMetadataEntry::SetValueAsBool(const bool& Value) 
{
	EntryAsJson.SetBoolField(TEXT("value"), Value);
	Type = ELootLockerMetadataTypes::Bool;
}

void FLootLockerMetadataEntry::SetRawValue(const TSharedPtr<FJsonValue>& Value) 
{
	EntryAsJson.SetField(TEXT("value"), Value);
	Type = ELootLockerMetadataTypes::Json;
}

template<typename T>
bool FLootLockerMetadataEntry::SetValueAsUStruct(const T& Value) 
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Value);
	if(!JsonObject.IsValid())
	{
		return false;
	}
	SetValueAsJsonObject(*JsonObject);
	return true;
}

void FLootLockerMetadataEntry::SetValueAsJsonObject(const FJsonObject& Value) 
{
	EntryAsJson.SetObjectField(TEXT("value"), MakeShared<FJsonObject>(Value));
	Type = ELootLockerMetadataTypes::Json;
}

void FLootLockerMetadataEntry::SetValueAsJsonArray(const TArray<TSharedPtr<FJsonValue>>& Value) 
{
	EntryAsJson.SetArrayField(TEXT("value"), Value);
	Type = ELootLockerMetadataTypes::Json;
}

void FLootLockerMetadataEntry::SetValueAsBase64(const FLootLockerMetadataBase64Value& Value) 
{
	SetValueAsUStruct(Value);
}

FLootLockerMetadataEntry FLootLockerMetadataEntry::MakeStringEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const FString& Value)
{
	FLootLockerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerMetadataTypes::String);
	Entry.SetValueAsString(Value);
	return Entry;
}

FLootLockerMetadataEntry FLootLockerMetadataEntry::MakeFloatEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const float& Value)
{
	FLootLockerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerMetadataTypes::Number);
	Entry.SetValueAsFloat(Value);
	return Entry;
}

FLootLockerMetadataEntry FLootLockerMetadataEntry::MakeIntegerEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const int Value)
{
	FLootLockerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerMetadataTypes::Number);
	Entry.SetValueAsInteger(Value);
	return Entry;
}

FLootLockerMetadataEntry FLootLockerMetadataEntry::MakeBoolEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const bool Value)
{
	FLootLockerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerMetadataTypes::Bool);
	Entry.SetValueAsBool(Value);
	return Entry;
}

FLootLockerMetadataEntry FLootLockerMetadataEntry::MakeJsonValueEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const ELootLockerMetadataTypes Type, const TSharedPtr<FJsonValue> Value)
{
	FLootLockerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerMetadataTypes::Json);
	Entry.SetRawValue(Value);
	return Entry;
}

FLootLockerMetadataEntry FLootLockerMetadataEntry::MakeJsonObjectEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const FJsonObject& Value)
{
	FLootLockerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerMetadataTypes::Json);
	Entry.SetValueAsJsonObject(Value);
	return Entry;
}

FLootLockerMetadataEntry FLootLockerMetadataEntry::MakeJsonArrayEntry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const TArray<TSharedPtr<FJsonValue>>& Value)
{
	FLootLockerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerMetadataTypes::Json);
	Entry.SetValueAsJsonArray(Value);
	return Entry;
}

FLootLockerMetadataEntry FLootLockerMetadataEntry::MakeBase64Entry(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const FLootLockerMetadataBase64Value& Value)
{
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(Value);
	if (!JsonObject.IsValid())
	{
		return FLootLockerMetadataEntry();
	}
	FLootLockerMetadataEntry Entry = MakeEntryExceptValue(Key, Tags, Access, ELootLockerMetadataTypes::Json);
	Entry.SetValueAsJsonObject(*JsonObject);
	return Entry;
}

FLootLockerMetadataEntry FLootLockerMetadataEntry::MakeEntryExceptValue(const FString& Key, const TArray<FString>& Tags, const TArray<FString>& Access, const ELootLockerMetadataTypes Type)
{
	FLootLockerMetadataEntry Entry;
	Entry.Key = Key;
	Entry.Tags = Tags;
	Entry.Type = Type;
	Entry.Access = Access;
	FJsonObject JsonRepresentation;
	JsonRepresentation.SetStringField(TEXT("key"), Key);
	TArray<TSharedPtr<FJsonValue>> TagArray;
	for (const FString& Tag : Tags)
	{
		TagArray.Add(MakeShared<FJsonValueString>(Tag));
	}
	JsonRepresentation.SetArrayField(TEXT("tags"), TagArray);
	JsonRepresentation.SetStringField(TEXT("type"), ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerMetadataTypes"), static_cast<int32>(Type)).ToLower());
	Entry.EntryAsJson = JsonRepresentation;
	return Entry;
}

void FLootLockerMetadataEntry::_INTERNAL_SetJsonRepresentation(const FJsonObject& obj)
{
	EntryAsJson = obj;
}

int FLootLockerListMetadataResponse::__INTERNAL_GetEntryIndexByKey(const FString& Key) const
{
	if(KeyToEntryIndex.Contains(Key))
	{
		const int* index = KeyToEntryIndex.Find(Key);
		if (index != nullptr && *index >= 0 && *index < Entries.Num()) {
			const FLootLockerMetadataEntry& EntryRef = Entries[*index];
			if(EntryRef.Key.Equals(Key)) {
				return *index;
			}
		}
	}
	return -1;
}

void FLootLockerListMetadataResponse::__INTERNAL_GenerateKeyMap()
{
	KeyToEntryIndex = TMap<FString, int>();
	int index = 0;
	for (FLootLockerMetadataEntry& Entry : Entries)
	{
		KeyToEntryIndex.Add(Entry.Key, index++);
	}
}

int FLootLockerMetadataSourceAndEntries::__INTERNAL_GetEntryIndexByKey(const FString& Key) const
{
	if (KeyToEntryIndex.Contains(Key))
	{
		const int* index = KeyToEntryIndex.Find(Key);
		if (index != nullptr && *index >= 0 && *index < Entries.Num()) {
			const FLootLockerMetadataEntry& EntryRef = Entries[*index];
			if (EntryRef.Key.Equals(Key)) {
				return *index;
			}
		}
	}
	return -1;
}

void FLootLockerMetadataSourceAndEntries::__INTERNAL_GenerateKeyMap()
{
	KeyToEntryIndex = TMap<FString, int>();
	int index = 0;
	for (FLootLockerMetadataEntry& Entry : Entries)
	{
		KeyToEntryIndex.Add(Entry.Key, index++);
	}
}

//==================================================
// Metadata Request Handler
//==================================================

FString ULootLockerMetadataRequestHandler::ListMetadata(const FLootLockerPlayerData& PlayerData, const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const FString& Key, const TArray<FString>& Tags, const bool IgnoreFiles, const FLootLockerListMetadataResponseDelegate& OnComplete)
{
	FString _SourceID = SourceID;
	if (Source == ELootLockerMetadataSources::self)
	{
		_SourceID = "self";
	}

	if (_SourceID.IsEmpty())
	{
		FLootLockerListMetadataResponse Error = LootLockerResponseFactory::Error<FLootLockerListMetadataResponse>("Can not list metadata for source with empty id", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(Error, "No Headers");
		OnComplete.ExecuteIfBound(Error);
		return "";
	}
	TMultiMap<FString, FString> QueryParams;
	if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
	if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
	if (!Key.IsEmpty()) QueryParams.Add("key", Key);
	if (Tags.Num() > 0) {
		for (FString Tag : Tags)
		{
			QueryParams.Add("tags", Tag);
		}
	}
	if (IgnoreFiles) QueryParams.Add("ignore_files", "true");

	FString SourceAsString = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerMetadataSources"), static_cast<int32>(Source)).ToLower();
	SourceAsString.ReplaceCharInline(' ', '_');
	return LLAPI<FLootLockerListMetadataResponse>::CallAPI(FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListMetadata, { SourceAsString, _SourceID }, QueryParams, PlayerData, FLootLockerListMetadataResponseDelegate(), LLAPI<FLootLockerListMetadataResponse>::FResponseInspectorCallback::CreateLambda([OnComplete](FLootLockerListMetadataResponse& Response)
		{
			// Make sure we will have entries to parse before continuing
			if (!Response.success || Response.Entries.Num() <= 0)
			{
				OnComplete.ExecuteIfBound(Response);
				return;
			}
			Response.__INTERNAL_GenerateKeyMap();
			TSharedPtr<FJsonObject> obj = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
			// Ensure that the full response was parsed before continuing
			if (!obj.IsValid())
			{
				OnComplete.ExecuteIfBound(Response);
				return;
			}

			TArray<TSharedPtr<FJsonValue>> JsonEntries = obj.Get()->GetArrayField(TEXT("entries"));
			// Make sure that the entries array was parsed before continuing
			if (JsonEntries.Num() != Response.Entries.Num())
			{
				OnComplete.ExecuteIfBound(Response);
				return;
			}

			for (TSharedPtr<FJsonValue> JsonEntry : JsonEntries)
			{
				TSharedPtr<FJsonObject> JsonEntryObject = JsonEntry.Get()->AsObject();
				FString EntryKey = JsonEntryObject.Get()->GetStringField(TEXT("key"));
				int EntryIndex = Response.__INTERNAL_GetEntryIndexByKey(EntryKey);
				// If the fetched entry index is out of range or if it points to the wrong key, try to find the entry the old-fashioned way before giving up
				if (EntryIndex < 0 || EntryIndex >= Response.Entries.Num()
					|| !Response.Entries[EntryIndex].Key.Equals(EntryKey)) {
					for (FLootLockerMetadataEntry& ResponseEntry : Response.Entries)
					{
						if (ResponseEntry.Key.Equals(EntryKey))
						{
							ResponseEntry._INTERNAL_SetJsonRepresentation(*JsonEntryObject.Get());
						}
					}
				}
				else
				{
					Response.Entries[EntryIndex]._INTERNAL_SetJsonRepresentation(*JsonEntryObject.Get());
				}
			}

			OnComplete.ExecuteIfBound(Response);
		}));
}

FString ULootLockerMetadataRequestHandler::GetMetadata(const FLootLockerPlayerData& PlayerData, const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerGetMetadataResponseDelegate& OnComplete)
{
	FString _SourceID = SourceID;
	if (Source == ELootLockerMetadataSources::self)
	{
		_SourceID = "self";
	}
	if (_SourceID.IsEmpty())
	{
		FLootLockerGetMetadataResponse Error = LootLockerResponseFactory::Error<FLootLockerGetMetadataResponse>("Can not list metadata for source with empty id", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(Error, "No Headers");
		OnComplete.ExecuteIfBound(Error);
		return "";
	}
	return ListMetadata(PlayerData, Source, _SourceID, 1, 1, Key, TArray<FString>(), IgnoreFiles, FLootLockerListMetadataResponseDelegate::CreateLambda([OnComplete, Key](const FLootLockerListMetadataResponse& ListResponse)
		{
			FLootLockerGetMetadataResponse SingleEntryResponse;
			SingleEntryResponse.success = ListResponse.success;
			SingleEntryResponse.StatusCode = ListResponse.StatusCode;
			SingleEntryResponse.FullTextFromServer = ListResponse.FullTextFromServer;
			SingleEntryResponse.ErrorData = ListResponse.ErrorData;
			if (ListResponse.success && ListResponse.Entries.Num() == 1 && ListResponse.Entries[0].Key.Equals(Key))
			{
				SingleEntryResponse.Entry = ListResponse.Entries[0];
			}
			OnComplete.ExecuteIfBound(SingleEntryResponse);
		}));
}

FString ULootLockerMetadataRequestHandler::GetMultisourceMetadata(const FLootLockerPlayerData& PlayerData, const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles, const FLootLockerGetMultisourceMetadataResponseDelegate& OnComplete)
{
	TMultiMap<FString, FString> QueryParams;
	if (IgnoreFiles) QueryParams.Add("ignore_files", "true");
	return LLAPI<FLootLockerGetMultisourceMetadataResponse>::CallAPI(FLootLockerGetMultisourceMetadataRequest{ SourcesAndKeysToGet }, ULootLockerGameEndpoints::GetMultisourceMetadata, {}, QueryParams, PlayerData, FLootLockerGetMultisourceMetadataResponseDelegate(), LLAPI<FLootLockerGetMultisourceMetadataResponse>::FResponseInspectorCallback::CreateLambda([OnComplete, PlayerData](FLootLockerGetMultisourceMetadataResponse& Response)
		{
			// Make sure we will have source and entry combos to parse before continuing
			if (!Response.success || Response.Metadata.Num() <= 0)
			{
				OnComplete.ExecuteIfBound(Response);
				return;
			}
			TSharedPtr<FJsonObject> FullResponseObjectFromServer = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
			// Ensure that the full response was parsed before continuing
			if (!FullResponseObjectFromServer.IsValid())
			{
				OnComplete.ExecuteIfBound(Response);
				return;
			}

			const TArray<TSharedPtr<FJsonValue>>* JsonMetadataArray;
			if (!FullResponseObjectFromServer->TryGetArrayField(TEXT("metadata"), JsonMetadataArray)
				|| JsonMetadataArray == nullptr
				|| JsonMetadataArray->Num() != Response.Metadata.Num())
			{
				FLootLockerGetMultisourceMetadataResponse Error = LootLockerResponseFactory::Error<
					FLootLockerGetMultisourceMetadataResponse>("Could not parse metadata array", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_PARSE_ERROR, PlayerData.PlayerUlid);
        		FLootLockerLogger::LogHttpRequest(Error, "No Headers");
				OnComplete.ExecuteIfBound(Error);
				return;
			}

			// Iterate over each source and do manual entry parsing
			for (int i = 0; i < Response.Metadata.Num(); ++i)
			{
				FLootLockerMetadataSourceAndEntries& Metadata = Response.Metadata[i];
				FJsonObject& MetadaAsJson = *(*JsonMetadataArray)[i]->AsObject();
				Metadata.__INTERNAL_GenerateKeyMap();

				TArray<TSharedPtr<FJsonValue>> JsonEntries = MetadaAsJson.GetArrayField(TEXT("entries"));
				// Make sure that the entries array was parsed before continuing
				if (JsonEntries.Num() != Metadata.Entries.Num())
				{
					FLootLockerGetMultisourceMetadataResponse Error = LootLockerResponseFactory::Error<
						FLootLockerGetMultisourceMetadataResponse>("Could not parse metadata entry array for metadata with source id " + Metadata.Source_id, LootLockerStaticRequestErrorStatusCodes::LL_ERROR_PARSE_ERROR, PlayerData.PlayerUlid);
        			FLootLockerLogger::LogHttpRequest(Error, "No Headers");
					OnComplete.ExecuteIfBound(Error);
					return;
				}

				for (TSharedPtr<FJsonValue> JsonEntry : JsonEntries)
				{
					TSharedPtr<FJsonObject> JsonEntryObject = JsonEntry.Get()->AsObject();
					FString EntryKey = JsonEntryObject.Get()->GetStringField(TEXT("key"));
					int EntryIndex = Metadata.__INTERNAL_GetEntryIndexByKey(EntryKey);
					// If the fetched entry index is out of range or if it points to the wrong key, try to find the entry the old-fashioned way before giving up
					if (EntryIndex < 0 || EntryIndex >= Metadata.Entries.Num()
						|| !Metadata.Entries[EntryIndex].Key.Equals(EntryKey)) {
						for (FLootLockerMetadataEntry& ResponseEntry : Metadata.Entries)
						{
							if (ResponseEntry.Key.Equals(EntryKey))
							{
								ResponseEntry._INTERNAL_SetJsonRepresentation(*JsonEntryObject.Get());
							}
						}
					}
					else
					{
						Metadata.Entries[EntryIndex]._INTERNAL_SetJsonRepresentation(*JsonEntryObject.Get());
					}
				}

			}

			OnComplete.ExecuteIfBound(Response);
		}));
}

FString ULootLockerMetadataRequestHandler::SetMetadata(const FLootLockerPlayerData& PlayerData, const ELootLockerMetadataSources Source, const FString& SourceID, const TArray<FLootLockerSetMetadataAction>& MetadataToActionsToPerform, const FLootLockerSetMetadataResponseDelegate& OnComplete)
{
	if (Source != ELootLockerMetadataSources::self && SourceID.IsEmpty())
	{
        FLootLockerSetMetadataResponse Error = LootLockerResponseFactory::Error<FLootLockerSetMetadataResponse>("Can not perform actions for source with empty id", LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        FLootLockerLogger::LogHttpRequest(Error, "No Headers");
		OnComplete.ExecuteIfBound(Error);
		return "";
	}

	// Set source and source id
	FJsonObject ManuallySerializedRequest;
	FString SourceAsString = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerMetadataSources"), static_cast<int32>(Source)).ToLower();
	SourceAsString.ReplaceCharInline(' ', '_');
	if (Source == ELootLockerMetadataSources::self)
	{
		ManuallySerializedRequest.SetBoolField(TEXT("self"), true);
	}
	else {
		ManuallySerializedRequest.SetStringField(TEXT("source"), SourceAsString);
		ManuallySerializedRequest.SetStringField(TEXT("source_id"), SourceID);
	}

	// Iterate over actions to perform and manually construct json since there's a ton of magic to it
	TArray<TSharedPtr<FJsonValue>> entries;
	for (const FLootLockerSetMetadataAction& ActionToPerform : MetadataToActionsToPerform)
	{
		// Serialize the brunt of the entry automatically
		// Should handle the fields key, tags, and access
		TSharedPtr<FJsonObject> JsonEntry = FJsonObjectConverter::UStructToJsonObject(ActionToPerform.Entry);
		if (!JsonEntry.IsValid())
		{
			FLootLockerSetMetadataResponse Error = LootLockerResponseFactory::Error<
				FLootLockerSetMetadataResponse>("Could not serialize action for key " + ActionToPerform.Entry.Key, LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        	FLootLockerLogger::LogHttpRequest(Error, "No Headers");
			OnComplete.ExecuteIfBound(Error);
			return "";
		}

		// Make type lowercase
		JsonEntry->SetStringField(TEXT("type"), ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerMetadataTypes"), static_cast<int32>(ActionToPerform.Entry.Type)).ToLower());

		auto action = ActionToPerform.Action;
		// Add the action that should be performed to the entry
		if(action == ELootLockerMetadataActions::Create_or_Update) 
		{
			action = ELootLockerMetadataActions::Upsert; // Convert to Upsert for consistency
		}
		
		JsonEntry->SetStringField(TEXT("action"), ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerMetadataActions"), static_cast<int32>(action)).ToLower());

		// Manually set the field "value"
		TSharedPtr<FJsonValue> RawEntryValue;
		if (!ActionToPerform.Entry.TryGetRawValue(RawEntryValue))
		{
			FLootLockerSetMetadataResponse Error = LootLockerResponseFactory::Error<
				FLootLockerSetMetadataResponse>("Could not get value to perform action " + JsonEntry->GetStringField(TEXT("action")) + " for key " + ActionToPerform.Entry.Key, LootLockerStaticRequestErrorStatusCodes::LL_ERROR_INVALID_INPUT, PlayerData.PlayerUlid);
        	FLootLockerLogger::LogHttpRequest(Error, "No Headers");
			OnComplete.ExecuteIfBound(Error);
			return "";
		}
		JsonEntry->SetField(TEXT("value"), RawEntryValue);

		// Add manually serialized to entries array
		entries.Add(MakeShared<FJsonValueObject>(JsonEntry));
	}

	// Add entries to manually serialized request
	ManuallySerializedRequest.SetArrayField(TEXT("entries"), entries);
	FString SerializedRequest = LootLockerUtilities::FStringFromJsonObject(MakeShared<FJsonObject>(ManuallySerializedRequest));
	return LLAPI<FLootLockerSetMetadataResponse>::CallAPIUsingRawJSON(SerializedRequest, ULootLockerGameEndpoints::MetadataActions, {}, {}, PlayerData, OnComplete);
}
