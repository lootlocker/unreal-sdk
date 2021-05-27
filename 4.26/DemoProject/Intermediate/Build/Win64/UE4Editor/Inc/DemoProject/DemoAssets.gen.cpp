// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoAssets.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoAssets() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoAssets_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoAssets();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
	LOOTLOCKERSDK_API UEnum* Z_Construct_UEnum_LootLockerSDK_ELootLockerAssetFilter();
// End Cross Module References
	DEFINE_FUNCTION(ADemoAssets::execDemoRemoveAssetFromFavourites)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoRemoveAssetFromFavourites();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssets::execDemoAddAssetToFavourites)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoAddAssetToFavourites();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssets::execDemoGetFavouriteAssetIndices)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetFavouriteAssetIndices();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssets::execDemoGetAssetBones)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAssetBones();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssets::execDemoGetAssetsByIds)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAssetsByIds();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssets::execDemoGetAssets)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAssets();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssets::execDemoGetContexts)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetContexts();
		P_NATIVE_END;
	}
	void ADemoAssets::StaticRegisterNativesADemoAssets()
	{
		UClass* Class = ADemoAssets::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoAddAssetToFavourites", &ADemoAssets::execDemoAddAssetToFavourites },
			{ "DemoGetAssetBones", &ADemoAssets::execDemoGetAssetBones },
			{ "DemoGetAssets", &ADemoAssets::execDemoGetAssets },
			{ "DemoGetAssetsByIds", &ADemoAssets::execDemoGetAssetsByIds },
			{ "DemoGetContexts", &ADemoAssets::execDemoGetContexts },
			{ "DemoGetFavouriteAssetIndices", &ADemoAssets::execDemoGetFavouriteAssetIndices },
			{ "DemoRemoveAssetFromFavourites", &ADemoAssets::execDemoRemoveAssetFromFavourites },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoAssets_DemoAddAssetToFavourites_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssets_DemoAddAssetToFavourites_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Assets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssets_DemoAddAssetToFavourites_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssets, nullptr, "DemoAddAssetToFavourites", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssets_DemoAddAssetToFavourites_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssets_DemoAddAssetToFavourites_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssets_DemoAddAssetToFavourites()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssets_DemoAddAssetToFavourites_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssets_DemoGetAssetBones_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssets_DemoGetAssetBones_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Assets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssets_DemoGetAssetBones_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssets, nullptr, "DemoGetAssetBones", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssets_DemoGetAssetBones_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssets_DemoGetAssetBones_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssets_DemoGetAssetBones()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssets_DemoGetAssetBones_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssets_DemoGetAssets_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssets_DemoGetAssets_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Assets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssets_DemoGetAssets_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssets, nullptr, "DemoGetAssets", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssets_DemoGetAssets_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssets_DemoGetAssets_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssets_DemoGetAssets()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssets_DemoGetAssets_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssets_DemoGetAssetsByIds_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssets_DemoGetAssetsByIds_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Assets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssets_DemoGetAssetsByIds_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssets, nullptr, "DemoGetAssetsByIds", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssets_DemoGetAssetsByIds_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssets_DemoGetAssetsByIds_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssets_DemoGetAssetsByIds()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssets_DemoGetAssetsByIds_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssets_DemoGetContexts_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssets_DemoGetContexts_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Assets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssets_DemoGetContexts_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssets, nullptr, "DemoGetContexts", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssets_DemoGetContexts_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssets_DemoGetContexts_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssets_DemoGetContexts()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssets_DemoGetContexts_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssets_DemoGetFavouriteAssetIndices_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssets_DemoGetFavouriteAssetIndices_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Assets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssets_DemoGetFavouriteAssetIndices_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssets, nullptr, "DemoGetFavouriteAssetIndices", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssets_DemoGetFavouriteAssetIndices_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssets_DemoGetFavouriteAssetIndices_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssets_DemoGetFavouriteAssetIndices()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssets_DemoGetFavouriteAssetIndices_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssets_DemoRemoveAssetFromFavourites_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssets_DemoRemoveAssetFromFavourites_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Assets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssets_DemoRemoveAssetFromFavourites_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssets, nullptr, "DemoRemoveAssetFromFavourites", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssets_DemoRemoveAssetFromFavourites_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssets_DemoRemoveAssetFromFavourites_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssets_DemoRemoveAssetFromFavourites()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssets_DemoRemoveAssetFromFavourites_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoAssets_NoRegister()
	{
		return ADemoAssets::StaticClass();
	}
	struct Z_Construct_UClass_ADemoAssets_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StartFromIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_StartFromIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ItemsCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ItemsCount;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_AssetFilter_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetFilter_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_AssetFilter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IncludeUGC_MetaData[];
#endif
		static void NewProp_IncludeUGC_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_IncludeUGC;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_AssetIds_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetIds_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_AssetIds;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_AssetId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoAssets_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoAssets_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoAssets_DemoAddAssetToFavourites, "DemoAddAssetToFavourites" }, // 187846897
		{ &Z_Construct_UFunction_ADemoAssets_DemoGetAssetBones, "DemoGetAssetBones" }, // 3331935407
		{ &Z_Construct_UFunction_ADemoAssets_DemoGetAssets, "DemoGetAssets" }, // 2252734066
		{ &Z_Construct_UFunction_ADemoAssets_DemoGetAssetsByIds, "DemoGetAssetsByIds" }, // 3553963689
		{ &Z_Construct_UFunction_ADemoAssets_DemoGetContexts, "DemoGetContexts" }, // 780139396
		{ &Z_Construct_UFunction_ADemoAssets_DemoGetFavouriteAssetIndices, "DemoGetFavouriteAssetIndices" }, // 1382914270
		{ &Z_Construct_UFunction_ADemoAssets_DemoRemoveAssetFromFavourites, "DemoRemoveAssetFromFavourites" }, // 904833918
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssets_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoAssets.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssets_Statics::NewProp_StartFromIndex_MetaData[] = {
		{ "Category", "DemoAssets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoAssets_Statics::NewProp_StartFromIndex = { "StartFromIndex", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAssets, StartFromIndex), METADATA_PARAMS(Z_Construct_UClass_ADemoAssets_Statics::NewProp_StartFromIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssets_Statics::NewProp_StartFromIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssets_Statics::NewProp_ItemsCount_MetaData[] = {
		{ "Category", "DemoAssets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoAssets_Statics::NewProp_ItemsCount = { "ItemsCount", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAssets, ItemsCount), METADATA_PARAMS(Z_Construct_UClass_ADemoAssets_Statics::NewProp_ItemsCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssets_Statics::NewProp_ItemsCount_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetFilter_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetFilter_MetaData[] = {
		{ "Category", "DemoAssets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetFilter = { "AssetFilter", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAssets, AssetFilter), Z_Construct_UEnum_LootLockerSDK_ELootLockerAssetFilter, METADATA_PARAMS(Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetFilter_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetFilter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssets_Statics::NewProp_IncludeUGC_MetaData[] = {
		{ "Category", "DemoAssets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	void Z_Construct_UClass_ADemoAssets_Statics::NewProp_IncludeUGC_SetBit(void* Obj)
	{
		((ADemoAssets*)Obj)->IncludeUGC = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ADemoAssets_Statics::NewProp_IncludeUGC = { "IncludeUGC", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(ADemoAssets), &Z_Construct_UClass_ADemoAssets_Statics::NewProp_IncludeUGC_SetBit, METADATA_PARAMS(Z_Construct_UClass_ADemoAssets_Statics::NewProp_IncludeUGC_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssets_Statics::NewProp_IncludeUGC_MetaData)) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetIds_Inner = { "AssetIds", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetIds_MetaData[] = {
		{ "Category", "DemoAssets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetIds = { "AssetIds", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAssets, AssetIds), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetIds_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetIds_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetId_MetaData[] = {
		{ "Category", "DemoAssets" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssets.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetId = { "AssetId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAssets, AssetId), METADATA_PARAMS(Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoAssets_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssets_Statics::NewProp_StartFromIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssets_Statics::NewProp_ItemsCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetFilter_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetFilter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssets_Statics::NewProp_IncludeUGC,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetIds_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetIds,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssets_Statics::NewProp_AssetId,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoAssets_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoAssets>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoAssets_Statics::ClassParams = {
		&ADemoAssets::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoAssets_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssets_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoAssets_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssets_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoAssets()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoAssets_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoAssets, 2138183770);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoAssets>()
	{
		return ADemoAssets::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoAssets(Z_Construct_UClass_ADemoAssets, &ADemoAssets::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoAssets"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoAssets);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
