// Copyright (c) 2021 LootLocker

#include "GameAPI/LootLockerMetadataRequestHandler.h"
#include "Dom/JsonObject.h"
#include "Utils/LootLockerUtilities.h"

ULootLockerHttpClient* ULootLockerMetadataRequestHandler::HttpClient = nullptr;

//==================================================
// Metadata Entry Methods
//==================================================

bool FLootLockerMetadataEntry::GetValueAsString(FString& Output) const
{
	Output = Value;
	return true;
}

bool FLootLockerMetadataEntry::GetValueAsDouble(double& Output) const
{
	if(!FCString::IsNumeric(*Value))
	{
		return false;
	}

	errno = 0;
	const double RetVal = FCString::Atod(*Value);
	//Check for under and overflow
	if(RetVal > -FLT_EPSILON && RetVal < FLT_EPSILON && errno == ERANGE)
	{
		return false;
	}
	if (!FString::SanitizeFloat(RetVal).Equals(Value))
	{
		return false;
	}
	Output = RetVal;
	return true;
}

bool FLootLockerMetadataEntry::GetValueAsInteger(int& Output) const
{
	if (!FCString::IsNumeric(*Value))
	{
		return false;
	}

	errno = 0;
	wchar_t* EndPtr = nullptr;
	const int RetVal = FCString::Strtoi(*Value, &EndPtr, 10);
	//Check for under and overflow
	if (EndPtr == *Value && errno == ERANGE)
	{
		return false;
	}
	if(!FString::FromInt(RetVal).Equals(Value))
	{
		return false;
	}
	Output = RetVal;
	return true;
}

bool FLootLockerMetadataEntry::GetValueAsBool(bool& Output) const
{
	Output = Value.ToBool();
	return true;
}

bool FLootLockerMetadataEntry::GetValueAsJsonObject(TSharedPtr<FJsonObject>& Output) const
{
	if(const TSharedPtr<FJsonObject> ParsedObject = LootLockerUtilities::JsonObjectFromFString(Value); ParsedObject.IsValid())
	{
		Output = ParsedObject;
		return true;
	}
	return false;
}

bool FLootLockerMetadataEntry::GetValueAsJsonArray(TArray<TSharedPtr<FJsonValue>>& Output) const
{
	if (LootLockerUtilities::JsonArrayFromFString(Value, Output))
	{
		return true;
	}
	return false;
}

bool FLootLockerMetadataEntry::GetValueAsBase64(FLootLockerMetadataBase64Value& Output) const
{
	return FJsonObjectConverter::JsonObjectStringToUStruct<FLootLockerMetadataBase64Value>(Value, &Output, 0, 0);
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
	if (!Tags.IsEmpty()) {
		FString TagList;
		int index = 0;
		for (FString Tag : Tags)
		{
			if(index >= 0)
			{
				TagList += ",";
			}
			TagList += Tag;
			++index;
		}
		QueryParams.Add("tags", TagList);
	}
	if (IgnoreFiles) QueryParams.Add("ignore_files", "true");

	LLAPI<FLootLockerListMetadataResponse>::CallAPI(HttpClient, FLootLockerEmptyRequest(), ULootLockerGameEndpoints::ListMetadata, {ULootLockerEnumUtils::GetEnum(TEXT("ELootLockerMetadataSources"), static_cast<int32>(Source)).ToLower(), SourceID }, QueryParams, OnCompleteBP, OnComplete);
}
