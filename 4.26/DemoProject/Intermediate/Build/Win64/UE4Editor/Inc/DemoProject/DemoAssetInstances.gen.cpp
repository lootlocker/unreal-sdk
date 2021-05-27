// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoAssetInstances.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoAssetInstances() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoAssetInstances_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoAssetInstances();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerAssetInstanceStorageItem();
// End Cross Module References
	DEFINE_FUNCTION(ADemoAssetInstances::execDemoOpenLootBox)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoOpenLootBox();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssetInstances::execDemoInspectLootBox)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoInspectLootBox();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssetInstances::execDemoDeleteAKeyValuePairByIdForAssetInstance)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoDeleteAKeyValuePairByIdForAssetInstance();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssetInstances::execDemoUpdateAKeyValuePairByIdForAssetInstance)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoUpdateAKeyValuePairByIdForAssetInstance();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssetInstances::execDemoUpdateOneOrMoreKeyValuePairForAssetInstance)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoUpdateOneOrMoreKeyValuePairForAssetInstance();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssetInstances::execDemoCreateAKeyValuePairForAssetInstance)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoCreateAKeyValuePairForAssetInstance();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssetInstances::execDemoGetAKeyValuePairByIdForAssetInstance)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAKeyValuePairByIdForAssetInstance();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssetInstances::execDemoGetAllKeyValuePairsToAnInstanceForAssetInstance)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAllKeyValuePairsToAnInstanceForAssetInstance();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAssetInstances::execDemoGetAllKeyValuePairsForAssetInstance)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAllKeyValuePairsForAssetInstance();
		P_NATIVE_END;
	}
	void ADemoAssetInstances::StaticRegisterNativesADemoAssetInstances()
	{
		UClass* Class = ADemoAssetInstances::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoCreateAKeyValuePairForAssetInstance", &ADemoAssetInstances::execDemoCreateAKeyValuePairForAssetInstance },
			{ "DemoDeleteAKeyValuePairByIdForAssetInstance", &ADemoAssetInstances::execDemoDeleteAKeyValuePairByIdForAssetInstance },
			{ "DemoGetAKeyValuePairByIdForAssetInstance", &ADemoAssetInstances::execDemoGetAKeyValuePairByIdForAssetInstance },
			{ "DemoGetAllKeyValuePairsForAssetInstance", &ADemoAssetInstances::execDemoGetAllKeyValuePairsForAssetInstance },
			{ "DemoGetAllKeyValuePairsToAnInstanceForAssetInstance", &ADemoAssetInstances::execDemoGetAllKeyValuePairsToAnInstanceForAssetInstance },
			{ "DemoInspectLootBox", &ADemoAssetInstances::execDemoInspectLootBox },
			{ "DemoOpenLootBox", &ADemoAssetInstances::execDemoOpenLootBox },
			{ "DemoUpdateAKeyValuePairByIdForAssetInstance", &ADemoAssetInstances::execDemoUpdateAKeyValuePairByIdForAssetInstance },
			{ "DemoUpdateOneOrMoreKeyValuePairForAssetInstance", &ADemoAssetInstances::execDemoUpdateOneOrMoreKeyValuePairForAssetInstance },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoAssetInstances_DemoCreateAKeyValuePairForAssetInstance_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssetInstances_DemoCreateAKeyValuePairForAssetInstance_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Asset Instances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssetInstances_DemoCreateAKeyValuePairForAssetInstance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssetInstances, nullptr, "DemoCreateAKeyValuePairForAssetInstance", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssetInstances_DemoCreateAKeyValuePairForAssetInstance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssetInstances_DemoCreateAKeyValuePairForAssetInstance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssetInstances_DemoCreateAKeyValuePairForAssetInstance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssetInstances_DemoCreateAKeyValuePairForAssetInstance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssetInstances_DemoDeleteAKeyValuePairByIdForAssetInstance_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssetInstances_DemoDeleteAKeyValuePairByIdForAssetInstance_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Asset Instances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssetInstances_DemoDeleteAKeyValuePairByIdForAssetInstance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssetInstances, nullptr, "DemoDeleteAKeyValuePairByIdForAssetInstance", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssetInstances_DemoDeleteAKeyValuePairByIdForAssetInstance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssetInstances_DemoDeleteAKeyValuePairByIdForAssetInstance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssetInstances_DemoDeleteAKeyValuePairByIdForAssetInstance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssetInstances_DemoDeleteAKeyValuePairByIdForAssetInstance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssetInstances_DemoGetAKeyValuePairByIdForAssetInstance_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssetInstances_DemoGetAKeyValuePairByIdForAssetInstance_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Asset Instances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssetInstances_DemoGetAKeyValuePairByIdForAssetInstance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssetInstances, nullptr, "DemoGetAKeyValuePairByIdForAssetInstance", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssetInstances_DemoGetAKeyValuePairByIdForAssetInstance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssetInstances_DemoGetAKeyValuePairByIdForAssetInstance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssetInstances_DemoGetAKeyValuePairByIdForAssetInstance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssetInstances_DemoGetAKeyValuePairByIdForAssetInstance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsForAssetInstance_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsForAssetInstance_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Asset Instances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsForAssetInstance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssetInstances, nullptr, "DemoGetAllKeyValuePairsForAssetInstance", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsForAssetInstance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsForAssetInstance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsForAssetInstance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsForAssetInstance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsToAnInstanceForAssetInstance_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsToAnInstanceForAssetInstance_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Asset Instances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsToAnInstanceForAssetInstance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssetInstances, nullptr, "DemoGetAllKeyValuePairsToAnInstanceForAssetInstance", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsToAnInstanceForAssetInstance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsToAnInstanceForAssetInstance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsToAnInstanceForAssetInstance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsToAnInstanceForAssetInstance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssetInstances_DemoInspectLootBox_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssetInstances_DemoInspectLootBox_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Asset Instances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssetInstances_DemoInspectLootBox_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssetInstances, nullptr, "DemoInspectLootBox", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssetInstances_DemoInspectLootBox_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssetInstances_DemoInspectLootBox_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssetInstances_DemoInspectLootBox()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssetInstances_DemoInspectLootBox_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssetInstances_DemoOpenLootBox_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssetInstances_DemoOpenLootBox_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Asset Instances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssetInstances_DemoOpenLootBox_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssetInstances, nullptr, "DemoOpenLootBox", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssetInstances_DemoOpenLootBox_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssetInstances_DemoOpenLootBox_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssetInstances_DemoOpenLootBox()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssetInstances_DemoOpenLootBox_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateAKeyValuePairByIdForAssetInstance_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateAKeyValuePairByIdForAssetInstance_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Asset Instances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateAKeyValuePairByIdForAssetInstance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssetInstances, nullptr, "DemoUpdateAKeyValuePairByIdForAssetInstance", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateAKeyValuePairByIdForAssetInstance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateAKeyValuePairByIdForAssetInstance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateAKeyValuePairByIdForAssetInstance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateAKeyValuePairByIdForAssetInstance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateOneOrMoreKeyValuePairForAssetInstance_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateOneOrMoreKeyValuePairForAssetInstance_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Asset Instances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateOneOrMoreKeyValuePairForAssetInstance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAssetInstances, nullptr, "DemoUpdateOneOrMoreKeyValuePairForAssetInstance", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateOneOrMoreKeyValuePairForAssetInstance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateOneOrMoreKeyValuePairForAssetInstance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateOneOrMoreKeyValuePairForAssetInstance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateOneOrMoreKeyValuePairForAssetInstance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoAssetInstances_NoRegister()
	{
		return ADemoAssetInstances::StaticClass();
	}
	struct Z_Construct_UClass_ADemoAssetInstances_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetInstanceId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_AssetInstanceId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StorageItemId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_StorageItemId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Item_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Item;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Items_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Items_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_Items;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoAssetInstances_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoAssetInstances_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoAssetInstances_DemoCreateAKeyValuePairForAssetInstance, "DemoCreateAKeyValuePairForAssetInstance" }, // 3988297167
		{ &Z_Construct_UFunction_ADemoAssetInstances_DemoDeleteAKeyValuePairByIdForAssetInstance, "DemoDeleteAKeyValuePairByIdForAssetInstance" }, // 292277637
		{ &Z_Construct_UFunction_ADemoAssetInstances_DemoGetAKeyValuePairByIdForAssetInstance, "DemoGetAKeyValuePairByIdForAssetInstance" }, // 776908570
		{ &Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsForAssetInstance, "DemoGetAllKeyValuePairsForAssetInstance" }, // 98610748
		{ &Z_Construct_UFunction_ADemoAssetInstances_DemoGetAllKeyValuePairsToAnInstanceForAssetInstance, "DemoGetAllKeyValuePairsToAnInstanceForAssetInstance" }, // 2483274985
		{ &Z_Construct_UFunction_ADemoAssetInstances_DemoInspectLootBox, "DemoInspectLootBox" }, // 2675484267
		{ &Z_Construct_UFunction_ADemoAssetInstances_DemoOpenLootBox, "DemoOpenLootBox" }, // 755677943
		{ &Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateAKeyValuePairByIdForAssetInstance, "DemoUpdateAKeyValuePairByIdForAssetInstance" }, // 2510482978
		{ &Z_Construct_UFunction_ADemoAssetInstances_DemoUpdateOneOrMoreKeyValuePairForAssetInstance, "DemoUpdateOneOrMoreKeyValuePairForAssetInstance" }, // 1445613160
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssetInstances_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoAssetInstances.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_AssetInstanceId_MetaData[] = {
		{ "Category", "DemoAssetInstances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_AssetInstanceId = { "AssetInstanceId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAssetInstances, AssetInstanceId), METADATA_PARAMS(Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_AssetInstanceId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_AssetInstanceId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_StorageItemId_MetaData[] = {
		{ "Category", "DemoAssetInstances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_StorageItemId = { "StorageItemId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAssetInstances, StorageItemId), METADATA_PARAMS(Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_StorageItemId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_StorageItemId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Item_MetaData[] = {
		{ "Category", "DemoAssetInstances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Item = { "Item", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAssetInstances, Item), Z_Construct_UScriptStruct_FLootLockerAssetInstanceStorageItem, METADATA_PARAMS(Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Item_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Item_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Items_Inner = { "Items", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerAssetInstanceStorageItem, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Items_MetaData[] = {
		{ "Category", "DemoAssetInstances" },
		{ "ModuleRelativePath", "Public/Demo/DemoAssetInstances.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Items = { "Items", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAssetInstances, Items), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Items_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Items_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoAssetInstances_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_AssetInstanceId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_StorageItemId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Item,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Items_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAssetInstances_Statics::NewProp_Items,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoAssetInstances_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoAssetInstances>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoAssetInstances_Statics::ClassParams = {
		&ADemoAssetInstances::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoAssetInstances_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssetInstances_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoAssetInstances_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAssetInstances_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoAssetInstances()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoAssetInstances_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoAssetInstances, 2012378789);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoAssetInstances>()
	{
		return ADemoAssetInstances::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoAssetInstances(Z_Construct_UClass_ADemoAssetInstances, &ADemoAssetInstances::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoAssetInstances"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoAssetInstances);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
