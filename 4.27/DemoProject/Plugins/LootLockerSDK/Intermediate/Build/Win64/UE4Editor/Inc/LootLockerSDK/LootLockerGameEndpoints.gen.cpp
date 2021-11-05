// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LootLockerSDK/Public/LootLockerGameEndpoints.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLootLockerGameEndpoints() {}
// Cross Module References
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerGameEndpoints_NoRegister();
	LOOTLOCKERSDK_API UClass* Z_Construct_UClass_ULootLockerGameEndpoints();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_LootLockerSDK();
// End Cross Module References
	void ULootLockerGameEndpoints::StaticRegisterNativesULootLockerGameEndpoints()
	{
	}
	UClass* Z_Construct_UClass_ULootLockerGameEndpoints_NoRegister()
	{
		return ULootLockerGameEndpoints::StaticClass();
	}
	struct Z_Construct_UClass_ULootLockerGameEndpoints_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ULootLockerGameEndpoints_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_LootLockerSDK,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ULootLockerGameEndpoints_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "LootLockerGameEndpoints.h" },
		{ "ModuleRelativePath", "Public/LootLockerGameEndpoints.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ULootLockerGameEndpoints_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULootLockerGameEndpoints>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ULootLockerGameEndpoints_Statics::ClassParams = {
		&ULootLockerGameEndpoints::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_ULootLockerGameEndpoints_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ULootLockerGameEndpoints_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ULootLockerGameEndpoints()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ULootLockerGameEndpoints_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ULootLockerGameEndpoints, 4242777250);
	template<> LOOTLOCKERSDK_API UClass* StaticClass<ULootLockerGameEndpoints>()
	{
		return ULootLockerGameEndpoints::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ULootLockerGameEndpoints(Z_Construct_UClass_ULootLockerGameEndpoints, &ULootLockerGameEndpoints::StaticClass, TEXT("/Script/LootLockerSDK"), TEXT("ULootLockerGameEndpoints"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ULootLockerGameEndpoints);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
