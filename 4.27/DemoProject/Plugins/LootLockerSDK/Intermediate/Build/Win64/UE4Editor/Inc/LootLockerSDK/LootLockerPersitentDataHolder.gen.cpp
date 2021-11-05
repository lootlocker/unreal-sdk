// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LootLockerSDK/Public/LootLockerPersitentDataHolder.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLootLockerPersitentDataHolder() {}
// Cross Module References
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerPersitentDataHolder_NoRegister();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerPersitentDataHolder();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_LootLockerSDK();
// End Cross Module References
	void ULootLockerPersitentDataHolder::StaticRegisterNativesULootLockerPersitentDataHolder()
	{
	}
	UClass* Z_Construct_UClass_ULootLockerPersitentDataHolder_NoRegister()
	{
		return ULootLockerPersitentDataHolder::StaticClass();
	}
	struct Z_Construct_UClass_ULootLockerPersitentDataHolder_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULootLockerPersitentDataHolder_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULootLockerPersitentDataHolder_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "LootLockerPersitentDataHolder.h" },
		{ "ModuleRelativePath", "Public/LootLockerPersitentDataHolder.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULootLockerPersitentDataHolder_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootLockerPersitentDataHolder>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULootLockerPersitentDataHolder_Statics::ClassParams = {
		&ULootLockerPersitentDataHolder::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULootLockerPersitentDataHolder_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULootLockerPersitentDataHolder_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULootLockerPersitentDataHolder()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULootLockerPersitentDataHolder_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULootLockerPersitentDataHolder, 4172309737);
	template<> LOOTLOCKERSDK_API UClass* StaticClass<ULootLockerPersitentDataHolder>()
	{
		return ULootLockerPersitentDataHolder::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULootLockerPersitentDataHolder(Z_Construct_UClass_ULootLockerPersitentDataHolder, &ULootLockerPersitentDataHolder::StaticClass, TEXT("/Script/LootLockerSDK"), TEXT("ULootLockerPersitentDataHolder"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULootLockerPersitentDataHolder);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
