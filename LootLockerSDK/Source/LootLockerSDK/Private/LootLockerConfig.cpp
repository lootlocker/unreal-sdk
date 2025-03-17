// Copyright (c) 2021 LootLocker

#include "LootLockerConfig.h"

#include "LootLockerSDK.h"
#include "Interfaces/IPluginManager.h"

FString ULootLockerConfig::SDKVersion = "";

FString ULootLockerConfig::GetSDKVersionString()
{
	if (SDKVersion.IsEmpty())
	{
		SDKVersion = ReadSDKVersionFromPlugin();
	}
	return SDKVersion;
}

FString ULootLockerConfig::ReadSDKVersionFromPlugin()
{
	FString _SDKVersion;
	const TSharedPtr<IPlugin> Ptr = IPluginManager::Get().FindPlugin("LootLockerSDK");
	if (Ptr.IsValid())
	{
		UE_LOG(LogLootLockerGameSDK, Verbose, TEXT("LootLocker version: v%s"), *_SDKVersion);
		_SDKVersion = Ptr->GetDescriptor().VersionName;
	}
	return _SDKVersion;
}
