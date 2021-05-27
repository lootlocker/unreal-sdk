// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoPurchases.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoPurchases() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoPurchases_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoPurchases();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerAssetPurchaseData();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerAndroidAssetPurchaseData();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerVerifyPurchaseIosData();
// End Cross Module References
	DEFINE_FUNCTION(ADemoPurchases::execDemoActivateRentalAsset)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoActivateRentalAsset();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPurchases::execDemoPollingOrderStatus)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoPollingOrderStatus();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPurchases::execDemoPurchaseAssetsIOS)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoPurchaseAssetsIOS();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPurchases::execDemoPurchaseAssetsAndroid)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoPurchaseAssetsAndroid();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoPurchases::execDemoPurchaseAssets)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoPurchaseAssets();
		P_NATIVE_END;
	}
	void ADemoPurchases::StaticRegisterNativesADemoPurchases()
	{
		UClass* Class = ADemoPurchases::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoActivateRentalAsset", &ADemoPurchases::execDemoActivateRentalAsset },
			{ "DemoPollingOrderStatus", &ADemoPurchases::execDemoPollingOrderStatus },
			{ "DemoPurchaseAssets", &ADemoPurchases::execDemoPurchaseAssets },
			{ "DemoPurchaseAssetsAndroid", &ADemoPurchases::execDemoPurchaseAssetsAndroid },
			{ "DemoPurchaseAssetsIOS", &ADemoPurchases::execDemoPurchaseAssetsIOS },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoPurchases_DemoActivateRentalAsset_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPurchases_DemoActivateRentalAsset_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Purchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPurchases_DemoActivateRentalAsset_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPurchases, nullptr, "DemoActivateRentalAsset", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPurchases_DemoActivateRentalAsset_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPurchases_DemoActivateRentalAsset_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPurchases_DemoActivateRentalAsset()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPurchases_DemoActivateRentalAsset_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPurchases_DemoPollingOrderStatus_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPurchases_DemoPollingOrderStatus_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Purchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPurchases_DemoPollingOrderStatus_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPurchases, nullptr, "DemoPollingOrderStatus", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPurchases_DemoPollingOrderStatus_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPurchases_DemoPollingOrderStatus_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPurchases_DemoPollingOrderStatus()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPurchases_DemoPollingOrderStatus_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssets_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssets_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Purchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssets_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPurchases, nullptr, "DemoPurchaseAssets", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssets_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssets_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssets()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssets_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsAndroid_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsAndroid_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Purchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsAndroid_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPurchases, nullptr, "DemoPurchaseAssetsAndroid", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsAndroid_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsAndroid_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsAndroid()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsAndroid_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsIOS_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsIOS_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Purchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsIOS_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoPurchases, nullptr, "DemoPurchaseAssetsIOS", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsIOS_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsIOS_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsIOS()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsIOS_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoPurchases_NoRegister()
	{
		return ADemoPurchases::StaticClass();
	}
	struct Z_Construct_UClass_ADemoPurchases_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_PurchaseData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PurchaseData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_PurchaseData;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_AndroidPurchaseData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AndroidPurchaseData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_AndroidPurchaseData;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_IosPurchaseData_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IosPurchaseData_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_IosPurchaseData;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PurchaseId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_PurchaseId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_AssetId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoPurchases_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoPurchases_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoPurchases_DemoActivateRentalAsset, "DemoActivateRentalAsset" }, // 60790141
		{ &Z_Construct_UFunction_ADemoPurchases_DemoPollingOrderStatus, "DemoPollingOrderStatus" }, // 147433827
		{ &Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssets, "DemoPurchaseAssets" }, // 308844354
		{ &Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsAndroid, "DemoPurchaseAssetsAndroid" }, // 2097203191
		{ &Z_Construct_UFunction_ADemoPurchases_DemoPurchaseAssetsIOS, "DemoPurchaseAssetsIOS" }, // 3224390431
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPurchases_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoPurchases.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseData_Inner = { "PurchaseData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerAssetPurchaseData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseData_MetaData[] = {
		{ "Category", "DemoPurchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseData = { "PurchaseData", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPurchases, PurchaseData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseData_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AndroidPurchaseData_Inner = { "AndroidPurchaseData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerAndroidAssetPurchaseData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AndroidPurchaseData_MetaData[] = {
		{ "Category", "DemoPurchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AndroidPurchaseData = { "AndroidPurchaseData", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPurchases, AndroidPurchaseData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AndroidPurchaseData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AndroidPurchaseData_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoPurchases_Statics::NewProp_IosPurchaseData_Inner = { "IosPurchaseData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FLootLockerVerifyPurchaseIosData, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPurchases_Statics::NewProp_IosPurchaseData_MetaData[] = {
		{ "Category", "DemoPurchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ADemoPurchases_Statics::NewProp_IosPurchaseData = { "IosPurchaseData", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPurchases, IosPurchaseData), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_IosPurchaseData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_IosPurchaseData_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseId_MetaData[] = {
		{ "Category", "DemoPurchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseId = { "PurchaseId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPurchases, PurchaseId), METADATA_PARAMS(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AssetId_MetaData[] = {
		{ "Category", "DemoPurchases" },
		{ "ModuleRelativePath", "Public/Demo/DemoPurchases.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AssetId = { "AssetId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoPurchases, AssetId), METADATA_PARAMS(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AssetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AssetId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoPurchases_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AndroidPurchaseData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AndroidPurchaseData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPurchases_Statics::NewProp_IosPurchaseData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPurchases_Statics::NewProp_IosPurchaseData,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPurchases_Statics::NewProp_PurchaseId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoPurchases_Statics::NewProp_AssetId,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoPurchases_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoPurchases>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoPurchases_Statics::ClassParams = {
		&ADemoPurchases::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoPurchases_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPurchases_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoPurchases_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoPurchases_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoPurchases()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoPurchases_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoPurchases, 2560193249);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoPurchases>()
	{
		return ADemoPurchases::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoPurchases(Z_Construct_UClass_ADemoPurchases, &ADemoPurchases::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoPurchases"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoPurchases);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
