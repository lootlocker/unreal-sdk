// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoUserGeneratedContent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoUserGeneratedContent() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoUserGeneratedContent_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoUserGeneratedContent();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerAssetCandidate2();
	LOOTLOCKERSDK_API UEnum* Z_Construct_UEnum_LootLockerSDK_ELootLockerAssetFilePurpose();
// End Cross Module References
	DEFINE_FUNCTION(ADemoUserGeneratedContent::execDemoDeleteFileFromAssetCandidate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoDeleteFileFromAssetCandidate();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoUserGeneratedContent::execDemoAddFileToAssetCandidate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoAddFileToAssetCandidate();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoUserGeneratedContent::execDemoGetAssetCandidate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAssetCandidate();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoUserGeneratedContent::execDemoGetAllAssetCandidates)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAllAssetCandidates();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoUserGeneratedContent::execDemoDeleteAssetCandidate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoDeleteAssetCandidate();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoUserGeneratedContent::execDemoUpdateAssetCandidate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoUpdateAssetCandidate();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoUserGeneratedContent::execDemoCreateAssetCandidate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoCreateAssetCandidate();
		P_NATIVE_END;
	}
	void ADemoUserGeneratedContent::StaticRegisterNativesADemoUserGeneratedContent()
	{
		UClass* Class = ADemoUserGeneratedContent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoAddFileToAssetCandidate", &ADemoUserGeneratedContent::execDemoAddFileToAssetCandidate },
			{ "DemoCreateAssetCandidate", &ADemoUserGeneratedContent::execDemoCreateAssetCandidate },
			{ "DemoDeleteAssetCandidate", &ADemoUserGeneratedContent::execDemoDeleteAssetCandidate },
			{ "DemoDeleteFileFromAssetCandidate", &ADemoUserGeneratedContent::execDemoDeleteFileFromAssetCandidate },
			{ "DemoGetAllAssetCandidates", &ADemoUserGeneratedContent::execDemoGetAllAssetCandidates },
			{ "DemoGetAssetCandidate", &ADemoUserGeneratedContent::execDemoGetAssetCandidate },
			{ "DemoUpdateAssetCandidate", &ADemoUserGeneratedContent::execDemoUpdateAssetCandidate },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoUserGeneratedContent_DemoAddFileToAssetCandidate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoUserGeneratedContent_DemoAddFileToAssetCandidate_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | User Generated Content" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoUserGeneratedContent_DemoAddFileToAssetCandidate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoUserGeneratedContent, nullptr, "DemoAddFileToAssetCandidate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoAddFileToAssetCandidate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoAddFileToAssetCandidate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoUserGeneratedContent_DemoAddFileToAssetCandidate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoUserGeneratedContent_DemoAddFileToAssetCandidate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoUserGeneratedContent_DemoCreateAssetCandidate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoUserGeneratedContent_DemoCreateAssetCandidate_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | User Generated Content" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoUserGeneratedContent_DemoCreateAssetCandidate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoUserGeneratedContent, nullptr, "DemoCreateAssetCandidate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoCreateAssetCandidate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoCreateAssetCandidate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoUserGeneratedContent_DemoCreateAssetCandidate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoUserGeneratedContent_DemoCreateAssetCandidate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteAssetCandidate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteAssetCandidate_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | User Generated Content" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteAssetCandidate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoUserGeneratedContent, nullptr, "DemoDeleteAssetCandidate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteAssetCandidate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteAssetCandidate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteAssetCandidate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteAssetCandidate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteFileFromAssetCandidate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteFileFromAssetCandidate_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | User Generated Content" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteFileFromAssetCandidate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoUserGeneratedContent, nullptr, "DemoDeleteFileFromAssetCandidate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteFileFromAssetCandidate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteFileFromAssetCandidate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteFileFromAssetCandidate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteFileFromAssetCandidate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAllAssetCandidates_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAllAssetCandidates_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | User Generated Content" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAllAssetCandidates_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoUserGeneratedContent, nullptr, "DemoGetAllAssetCandidates", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAllAssetCandidates_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAllAssetCandidates_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAllAssetCandidates()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAllAssetCandidates_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAssetCandidate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAssetCandidate_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | User Generated Content" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAssetCandidate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoUserGeneratedContent, nullptr, "DemoGetAssetCandidate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAssetCandidate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAssetCandidate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAssetCandidate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAssetCandidate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoUserGeneratedContent_DemoUpdateAssetCandidate_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoUserGeneratedContent_DemoUpdateAssetCandidate_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | User Generated Content" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoUserGeneratedContent_DemoUpdateAssetCandidate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoUserGeneratedContent, nullptr, "DemoUpdateAssetCandidate", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoUpdateAssetCandidate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoUserGeneratedContent_DemoUpdateAssetCandidate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoUserGeneratedContent_DemoUpdateAssetCandidate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoUserGeneratedContent_DemoUpdateAssetCandidate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoUserGeneratedContent_NoRegister()
	{
		return ADemoUserGeneratedContent::StaticClass();
	}
	struct Z_Construct_UClass_ADemoUserGeneratedContent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AsssetCandidate_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_AsssetCandidate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AssetCandidateId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_AssetCandidateId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FilePath_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_FilePath;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_FilePurpose_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FilePurpose_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_FilePurpose;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FileId_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_FileId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoUserGeneratedContent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoUserGeneratedContent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoUserGeneratedContent_DemoAddFileToAssetCandidate, "DemoAddFileToAssetCandidate" }, // 4100392115
		{ &Z_Construct_UFunction_ADemoUserGeneratedContent_DemoCreateAssetCandidate, "DemoCreateAssetCandidate" }, // 2369909000
		{ &Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteAssetCandidate, "DemoDeleteAssetCandidate" }, // 1081620625
		{ &Z_Construct_UFunction_ADemoUserGeneratedContent_DemoDeleteFileFromAssetCandidate, "DemoDeleteFileFromAssetCandidate" }, // 3420392483
		{ &Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAllAssetCandidates, "DemoGetAllAssetCandidates" }, // 3591825931
		{ &Z_Construct_UFunction_ADemoUserGeneratedContent_DemoGetAssetCandidate, "DemoGetAssetCandidate" }, // 4111776364
		{ &Z_Construct_UFunction_ADemoUserGeneratedContent_DemoUpdateAssetCandidate, "DemoUpdateAssetCandidate" }, // 311583460
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoUserGeneratedContent_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoUserGeneratedContent.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AsssetCandidate_MetaData[] = {
		{ "Category", "DemoUserGeneratedContent" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AsssetCandidate = { "AsssetCandidate", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoUserGeneratedContent, AsssetCandidate), Z_Construct_UScriptStruct_FLootLockerAssetCandidate2, METADATA_PARAMS(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AsssetCandidate_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AsssetCandidate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AssetCandidateId_MetaData[] = {
		{ "Category", "DemoUserGeneratedContent" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AssetCandidateId = { "AssetCandidateId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoUserGeneratedContent, AssetCandidateId), METADATA_PARAMS(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AssetCandidateId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AssetCandidateId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePath_MetaData[] = {
		{ "Category", "DemoUserGeneratedContent" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePath = { "FilePath", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoUserGeneratedContent, FilePath), METADATA_PARAMS(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePath_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePurpose_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePurpose_MetaData[] = {
		{ "Category", "DemoUserGeneratedContent" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePurpose = { "FilePurpose", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoUserGeneratedContent, FilePurpose), Z_Construct_UEnum_LootLockerSDK_ELootLockerAssetFilePurpose, METADATA_PARAMS(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePurpose_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePurpose_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FileId_MetaData[] = {
		{ "Category", "DemoUserGeneratedContent" },
		{ "ModuleRelativePath", "Public/Demo/DemoUserGeneratedContent.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FileId = { "FileId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoUserGeneratedContent, FileId), METADATA_PARAMS(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FileId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FileId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoUserGeneratedContent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AsssetCandidate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_AssetCandidateId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePath,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePurpose_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FilePurpose,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoUserGeneratedContent_Statics::NewProp_FileId,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoUserGeneratedContent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoUserGeneratedContent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoUserGeneratedContent_Statics::ClassParams = {
		&ADemoUserGeneratedContent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoUserGeneratedContent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoUserGeneratedContent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoUserGeneratedContent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoUserGeneratedContent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoUserGeneratedContent, 230371431);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoUserGeneratedContent>()
	{
		return ADemoUserGeneratedContent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoUserGeneratedContent(Z_Construct_UClass_ADemoUserGeneratedContent, &ADemoUserGeneratedContent::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoUserGeneratedContent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoUserGeneratedContent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
