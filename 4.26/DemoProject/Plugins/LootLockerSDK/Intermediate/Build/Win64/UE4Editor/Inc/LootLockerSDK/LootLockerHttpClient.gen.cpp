// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LootLockerSDK/Public/LootLockerHttpClient.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLootLockerHttpClient() {}
// Cross Module References
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerHttpClient_NoRegister();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerHttpClient();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_LootLockerSDK();
// End Cross Module References
	void ULootLockerHttpClient::StaticRegisterNativesULootLockerHttpClient()
	{
	}
	UClass* Z_Construct_UClass_ULootLockerHttpClient_NoRegister()
	{
		return ULootLockerHttpClient::StaticClass();
	}
	struct Z_Construct_UClass_ULootLockerHttpClient_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULootLockerHttpClient_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULootLockerHttpClient_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "LootLockerHttpClient.h" },
		{ "ModuleRelativePath", "Public/LootLockerHttpClient.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULootLockerHttpClient_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootLockerHttpClient>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULootLockerHttpClient_Statics::ClassParams = {
		&ULootLockerHttpClient::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_ULootLockerHttpClient_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULootLockerHttpClient_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULootLockerHttpClient()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULootLockerHttpClient_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULootLockerHttpClient, 4008814070);
	template<> LOOTLOCKERSDK_API UClass* StaticClass<ULootLockerHttpClient>()
	{
		return ULootLockerHttpClient::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULootLockerHttpClient(Z_Construct_UClass_ULootLockerHttpClient, &ULootLockerHttpClient::StaticClass, TEXT("/Script/LootLockerSDK"), TEXT("ULootLockerHttpClient"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULootLockerHttpClient);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
