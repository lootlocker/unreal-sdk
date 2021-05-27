// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoCollectables.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoCollectables() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoCollectables_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoCollectables();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
	LOOTLOCKERSDK_API UScriptStruct* Z_Construct_UScriptStruct_FLootLockerCollectItemPayload();
// End Cross Module References
	DEFINE_FUNCTION(ADemoCollectables::execDemoCollectItem)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoCollectItem();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoCollectables::execDemoGetAllCollectables)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoGetAllCollectables();
		P_NATIVE_END;
	}
	void ADemoCollectables::StaticRegisterNativesADemoCollectables()
	{
		UClass* Class = ADemoCollectables::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoCollectItem", &ADemoCollectables::execDemoCollectItem },
			{ "DemoGetAllCollectables", &ADemoCollectables::execDemoGetAllCollectables },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoCollectables_DemoCollectItem_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCollectables_DemoCollectItem_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Collectables" },
		{ "ModuleRelativePath", "Public/Demo/DemoCollectables.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCollectables_DemoCollectItem_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCollectables, nullptr, "DemoCollectItem", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCollectables_DemoCollectItem_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCollectables_DemoCollectItem_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCollectables_DemoCollectItem()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCollectables_DemoCollectItem_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoCollectables_DemoGetAllCollectables_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoCollectables_DemoGetAllCollectables_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Collectables" },
		{ "ModuleRelativePath", "Public/Demo/DemoCollectables.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoCollectables_DemoGetAllCollectables_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoCollectables, nullptr, "DemoGetAllCollectables", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoCollectables_DemoGetAllCollectables_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoCollectables_DemoGetAllCollectables_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoCollectables_DemoGetAllCollectables()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoCollectables_DemoGetAllCollectables_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoCollectables_NoRegister()
	{
		return ADemoCollectables::StaticClass();
	}
	struct Z_Construct_UClass_ADemoCollectables_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Item_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Item;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoCollectables_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoCollectables_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoCollectables_DemoCollectItem, "DemoCollectItem" }, // 3807429115
		{ &Z_Construct_UFunction_ADemoCollectables_DemoGetAllCollectables, "DemoGetAllCollectables" }, // 1126044271
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCollectables_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoCollectables.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoCollectables.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoCollectables_Statics::NewProp_Item_MetaData[] = {
		{ "Category", "DemoCollectables" },
		{ "ModuleRelativePath", "Public/Demo/DemoCollectables.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_ADemoCollectables_Statics::NewProp_Item = { "Item", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoCollectables, Item), Z_Construct_UScriptStruct_FLootLockerCollectItemPayload, METADATA_PARAMS(Z_Construct_UClass_ADemoCollectables_Statics::NewProp_Item_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCollectables_Statics::NewProp_Item_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoCollectables_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoCollectables_Statics::NewProp_Item,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoCollectables_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoCollectables>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoCollectables_Statics::ClassParams = {
		&ADemoCollectables::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoCollectables_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCollectables_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoCollectables_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoCollectables_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoCollectables()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoCollectables_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoCollectables, 554596396);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoCollectables>()
	{
		return ADemoCollectables::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoCollectables(Z_Construct_UClass_ADemoCollectables, &ADemoCollectables::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoCollectables"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoCollectables);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
