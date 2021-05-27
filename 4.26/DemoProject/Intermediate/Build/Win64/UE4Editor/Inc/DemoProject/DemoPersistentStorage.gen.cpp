// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoPersistentStorage.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoPersistentStorage() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoPersistentStorage_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoPersistentStorage();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerPersistentStorageItem();
// End Cross Module References
	DEFINE_FUNCTION(ADemoPersistentStorage::execDemoGetPlayerPersistentStorage)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetPlayerPersistentStorage();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPersistentStorage::execDemoDeleteItemFromPersistentStorage)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoDeleteItemFromPersistentStorage();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPersistentStorage::execDemoAddItemsToPersistentStorage)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoAddItemsToPersistentStorage();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPersistentStorage::execDemoGetItemFromPersistentStorage)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetItemFromPersistentStorage();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPersistentStorage::execDemoGetEntirePersistentStorage)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetEntirePersistentStorage();
		P_NATIVE_END;
	}
	void ADemoPersistentStorage::StaticRegisterNativesADemoPersistentStorage()
	{
		UClass* Class = ADemoPersistentStorage::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoAddItemsToPersistentStorage", &ADemoPersistentStorage::execDemoAddItemsToPersistentStorage },
			{ "DemoDeleteItemFromPersistentStorage", &ADemoPersistentStorage::execDemoDeleteItemFromPersistentStorage },
			{ "DemoGetEntirePersistentStorage", &ADemoPersistentStorage::execDemoGetEntirePersistentStorage },
			{ "DemoGetItemFromPersistentStorage", &ADemoPersistentStorage::execDemoGetItemFromPersistentStorage },
			{ "DemoGetPlayerPersistentStorage", &ADemoPersistentStorage::execDemoGetPlayerPersistentStorage },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoPersistentStorage_DemoAddItemsToPersistentStorage_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPersistentStorage_DemoAddItemsToPersistentStorage_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Persistent Storage" },
		{ "ModuleRelativePath", "Public/Demo/DemoPersistentStorage.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPersistentStorage_DemoAddItemsToPersistentStorage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPersistentStorage, nullptr, "DemoAddItemsToPersistentStorage", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPersistentStorage_DemoAddItemsToPersistentStorage_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPersistentStorage_DemoAddItemsToPersistentStorage_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPersistentStorage_DemoAddItemsToPersistentStorage()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPersistentStorage_DemoAddItemsToPersistentStorage_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPersistentStorage_DemoDeleteItemFromPersistentStorage_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPersistentStorage_DemoDeleteItemFromPersistentStorage_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Persistent Storage" },
		{ "ModuleRelativePath", "Public/Demo/DemoPersistentStorage.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPersistentStorage_DemoDeleteItemFromPersistentStorage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPersistentStorage, nullptr, "DemoDeleteItemFromPersistentStorage", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPersistentStorage_DemoDeleteItemFromPersistentStorage_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPersistentStorage_DemoDeleteItemFromPersistentStorage_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPersistentStorage_DemoDeleteItemFromPersistentStorage()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPersistentStorage_DemoDeleteItemFromPersistentStorage_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPersistentStorage_DemoGetEntirePersistentStorage_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPersistentStorage_DemoGetEntirePersistentStorage_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Persistent Storage" },
		{ "ModuleRelativePath", "Public/Demo/DemoPersistentStorage.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPersistentStorage_DemoGetEntirePersistentStorage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPersistentStorage, nullptr, "DemoGetEntirePersistentStorage", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPersistentStorage_DemoGetEntirePersistentStorage_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPersistentStorage_DemoGetEntirePersistentStorage_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPersistentStorage_DemoGetEntirePersistentStorage()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPersistentStorage_DemoGetEntirePersistentStorage_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPersistentStorage_DemoGetItemFromPersistentStorage_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPersistentStorage_DemoGetItemFromPersistentStorage_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Persistent Storage" },
		{ "ModuleRelativePath", "Public/Demo/DemoPersistentStorage.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPersistentStorage_DemoGetItemFromPersistentStorage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPersistentStorage, nullptr, "DemoGetItemFromPersistentStorage", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPersistentStorage_DemoGetItemFromPersistentStorage_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPersistentStorage_DemoGetItemFromPersistentStorage_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPersistentStorage_DemoGetItemFromPersistentStorage()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPersistentStorage_DemoGetItemFromPersistentStorage_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPersistentStorage_DemoGetPlayerPersistentStorage_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPersistentStorage_DemoGetPlayerPersistentStorage_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Persistent Storage" },
		{ "ModuleRelativePath", "Public/Demo/DemoPersistentStorage.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPersistentStorage_DemoGetPlayerPersistentStorage_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPersistentStorage, nullptr, "DemoGetPlayerPersistentStorage", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPersistentStorage_DemoGetPlayerPersistentStorage_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPersistentStorage_DemoGetPlayerPersistentStorage_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPersistentStorage_DemoGetPlayerPersistentStorage()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPersistentStorage_DemoGetPlayerPersistentStorage_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoPersistentStorage_NoRegister()
	{
		return ADemoPersistentStorage::StaticClass();
	}
	struct Z_Construct_UClass_ADemoPersistentStorage_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Key;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Items_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Items_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Items;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlayerId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PlayerId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoPersistentStorage_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoPersistentStorage_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoPersistentStorage_DemoAddItemsToPersistentStorage, "DemoAddItemsToPersistentStorage" }, // 2859458857
		{ &Z_Construct_UFunction_ADemoPersistentStorage_DemoDeleteItemFromPersistentStorage, "DemoDeleteItemFromPersistentStorage" }, // 277348126
		{ &Z_Construct_UFunction_ADemoPersistentStorage_DemoGetEntirePersistentStorage, "DemoGetEntirePersistentStorage" }, // 705707877
		{ &Z_Construct_UFunction_ADemoPersistentStorage_DemoGetItemFromPersistentStorage, "DemoGetItemFromPersistentStorage" }, // 2452341633
		{ &Z_Construct_UFunction_ADemoPersistentStorage_DemoGetPlayerPersistentStorage, "DemoGetPlayerPersistentStorage" }, // 2546281375
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPersistentStorage_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoPersistentStorage.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoPersistentStorage.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Key_MetaData[] = {
		{ "Category", "DemoPersistentStorage" },
		{ "ModuleRelativePath", "Public/Demo/DemoPersistentStorage.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPersistentStorage, Key), METADATA_PARAMS(Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Key_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Key_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Items_Inner = { "Items", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerPersistentStorageItem, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Items_MetaData[] = {
		{ "Category", "DemoPersistentStorage" },
		{ "ModuleRelativePath", "Public/Demo/DemoPersistentStorage.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Items = { "Items", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPersistentStorage, Items), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Items_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Items_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_PlayerId_MetaData[] = {
		{ "Category", "DemoPersistentStorage" },
		{ "ModuleRelativePath", "Public/Demo/DemoPersistentStorage.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_PlayerId = { "PlayerId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPersistentStorage, PlayerId), METADATA_PARAMS(Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_PlayerId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_PlayerId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoPersistentStorage_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Key,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Items_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_Items,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPersistentStorage_Statics::NewProp_PlayerId,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoPersistentStorage_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoPersistentStorage>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoPersistentStorage_Statics::ClassParams = {
		&ADemoPersistentStorage::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoPersistentStorage_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPersistentStorage_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoPersistentStorage_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPersistentStorage_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoPersistentStorage()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoPersistentStorage_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoPersistentStorage, 247151798);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoPersistentStorage>()
	{
		return ADemoPersistentStorage::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoPersistentStorage(Z_Construct_UClass_ADemoPersistentStorage, &ADemoPersistentStorage::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoPersistentStorage"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoPersistentStorage);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
