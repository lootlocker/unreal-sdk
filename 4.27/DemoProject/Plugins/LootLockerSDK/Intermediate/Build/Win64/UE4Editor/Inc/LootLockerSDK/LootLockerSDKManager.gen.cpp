// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LootLockerSDK/Public/LootLockerSDKManager.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLootLockerSDKManager() {}
// Cross Module References
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerSDKManager_NoRegister();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerSDKManager();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_LootLockerSDK();
// End Cross Module References
	void ULootLockerSDKManager::StaticRegisterNativesULootLockerSDKManager()
	{
	}
	UClass* Z_Construct_UClass_ULootLockerSDKManager_NoRegister()
	{
		return ULootLockerSDKManager::StaticClass();
	}
	struct Z_Construct_UClass_ULootLockerSDKManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULootLockerSDKManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULootLockerSDKManager_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "LootLockerSDKManager.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/LootLockerSDKManager.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULootLockerSDKManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootLockerSDKManager>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULootLockerSDKManager_Statics::ClassParams = {
		&ULootLockerSDKManager::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULootLockerSDKManager_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULootLockerSDKManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULootLockerSDKManager()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULootLockerSDKManager_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULootLockerSDKManager, 594338734);
	template<> LOOTLOCKERSDK_API UClass* StaticClass<ULootLockerSDKManager>()
	{
		return ULootLockerSDKManager::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULootLockerSDKManager(Z_Construct_UClass_ULootLockerSDKManager, &ULootLockerSDKManager::StaticClass, TEXT("/Script/LootLockerSDK"), TEXT("ULootLockerSDKManager"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULootLockerSDKManager);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
