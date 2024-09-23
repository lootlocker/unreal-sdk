// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "Dom/JsonObject.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerMetadataRequestHandler::HttpClient = nullptr;

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

template<typename T>
bool FLootLockerMetadataEntry::TryGetValueAsUStruct(T& Output) const
{
	TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();
	if (!TryGetValueAsJsonObject(jsonObject))
	{
		return false;
	}
	return FJsonObjectConverter::JsonObjectToUStruct<T>(jsonObject.ToSharedRef(), &Output, 0, 0);		
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
	return TryGetValueAsUStruct(Output);
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

ULootLockerMetadataRequestHandler::ULootLockerMetadataRequestHandler()
{
    HttpClient = NewObject<ULootLockerHttpClient>();
}

void ULootLockerMetadataRequestHandler::ListMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const int Page, const int PerPage, const FString& Key, const TArray<FString>& Tags, const bool IgnoreFiles, const FLootLockerListMetadataResponseBP& OnCompleteBP, const FLootLockerListMetadataResponseDelegate& OnComplete)
{
	TMultiMap<FString, FString> QueryParams;
	if (Page > 0) QueryParams.Add("page", FString::FromInt(Page));
	if (PerPage > 0) QueryParams.Add("per_page", FString::FromInt(PerPage));
	if (!Key.IsEmpty()) QueryParams.Add("key", Key);
	if (Tags.Num() <= 0) {
		for (FString Tag : Tags)
		{
			QueryParams.Add("tags", Tag);
		}
	}
	if (IgnoreFiles) QueryParams.Add("ignore_files", "true");

	FString SourceAsString = ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerMetadataSources"), static_cast<int32>(Source)).ToLower();
	SourceAsString.ReplaceCharInline(' ', '_');
	LLAPI<FLootLockerListMetadataResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListMetadata, { SourceAsString, SourceID }, QueryParams, FLootLockerListMetadataResponseBP(), FLootLockerListMetadataResponseDelegate(), LLAPI<FLootLockerListMetadataResponse>::FResponseInspectorCallback::CreateLambda([OnCompleteBP, OnComplete](FLootLockerListMetadataResponse& Response)
	{
		// Make sure we will have entries to parse before continuing
		if(!Response.success || Response.Entries.Num() <= 0)
		{
			OnCompleteBP.ExecuteIfBound(Response);
			OnComplete.ExecuteIfBound(Response);
			return;
		}
		Response.__INTERNAL_GenerateKeyMap();
		TSharedPtr<FJsonObject> obj = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
		// Ensure that the full response was parsed before continuing
		if(!obj.IsValid())
		{
			OnCompleteBP.ExecuteIfBound(Response);
			OnComplete.ExecuteIfBound(Response);
			return;			
		}

		TArray<TSharedPtr<FJsonValue>> JsonEntries = obj.Get()->GetArrayField(TEXT("entries"));
		// Make sure that the entries array was parsed before continuing
		if(JsonEntries.Num() != Response.Entries.Num())
		{
			OnCompleteBP.ExecuteIfBound(Response);
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

		OnCompleteBP.ExecuteIfBound(Response);
		OnComplete.ExecuteIfBound(Response);
	}));
}

void ULootLockerMetadataRequestHandler::GetMetadata(const ELootLockerMetadataSources Source, const FString& SourceID, const FString& Key, const bool IgnoreFiles, const FLootLockerGetMetadataResponseBP& OnCompleteBP, const FLootLockerGetMetadataResponseDelegate& OnComplete)
{
	ListMetadata(Source, SourceID, 1, 1, Key, TArray<FString>(), IgnoreFiles, FLootLockerListMetadataResponseBP(), FLootLockerListMetadataResponseDelegate::CreateLambda([OnCompleteBP, OnComplete, Key](const FLootLockerListMetadataResponse& ListResponse)
	{
		FLootLockerGetMetadataResponse SingleEntryResponse;
		SingleEntryResponse.success = ListResponse.success;
		SingleEntryResponse.StatusCode = ListResponse.StatusCode;
		SingleEntryResponse.FullTextFromServer = ListResponse.FullTextFromServer;
		SingleEntryResponse.ErrorData = ListResponse.ErrorData;
		if(ListResponse.success && ListResponse.Entries.Num() == 1 && ListResponse.Entries[0].Key.Equals(Key))
		{
			SingleEntryResponse.Entry = ListResponse.Entries[0];
		}
		OnCompleteBP.ExecuteIfBound(SingleEntryResponse);
		OnComplete.ExecuteIfBound(SingleEntryResponse);
	}));
}

void ULootLockerMetadataRequestHandler::GetMultisourceMetadata(const TArray<FLootLockerMetadataSourceAndKeys>& SourcesAndKeysToGet, const bool IgnoreFiles,	const FLootLockerGetMultisourceMetadataResponseBP& OnCompleteBP, const FLootLockerGetMultisourceMetadataResponseDelegate& OnComplete)
{
	TMultiMap<FString, FString> QueryParams;
	if (IgnoreFiles) QueryParams.Add("ignore_files", "true");
	LLAPI<FLootLockerGetMultisourceMetadataResponse>::CallAPI(HttpClient, FLootLockerGetMultisourceMetadataRequest{ SourcesAndKeysToGet }, ULootLockerGameEndpoints::GetMultisourceMetadata, {}, QueryParams, FLootLockerGetMultisourceMetadataResponseBP(), FLootLockerGetMultisourceMetadataResponseDelegate(), LLAPI<FLootLockerGetMultisourceMetadataResponse>::FResponseInspectorCallback::CreateLambda([OnComplete, OnCompleteBP](FLootLockerGetMultisourceMetadataResponse& Response)
	{
		// Make sure we will have source and entry combos to parse before continuing
		if (!Response.success || Response.Metadata.Num() <= 0)
		{
			OnCompleteBP.ExecuteIfBound(Response);
			OnComplete.ExecuteIfBound(Response);
			return;
		}
		TSharedPtr<FJsonObject> FullResponseObjectFromServer = LootLockerUtilities::JsonObjectFromFString(Response.FullTextFromServer);
		// Ensure that the full response was parsed before continuing
		if (!FullResponseObjectFromServer.IsValid())
		{
			OnCompleteBP.ExecuteIfBound(Response);
			OnComplete.ExecuteIfBound(Response);
			return;
		}

		const TArray<TSharedPtr<FJsonValue>>* JsonMetadataArray;
		if(!FullResponseObjectFromServer->TryGetArrayField(TEXT("metadata"), JsonMetadataArray) 
			|| JsonMetadataArray == nullptr 
			|| JsonMetadataArray->Num() != Response.Metadata.Num())
		{
			FLootLockerGetMultisourceMetadataResponse Error = LootLockerResponseFactory::Error<
				FLootLockerGetMultisourceMetadataResponse>("Could not parse metadata array");
			OnCompleteBP.ExecuteIfBound(Error);
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
					FLootLockerGetMultisourceMetadataResponse>("Could not parse metadata entry array for metadata with source id " + Metadata.Source_id);
				OnCompleteBP.ExecuteIfBound(Error);
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

		OnCompleteBP.ExecuteIfBound(Response);
		OnComplete.ExecuteIfBound(Response);
	}));

}
