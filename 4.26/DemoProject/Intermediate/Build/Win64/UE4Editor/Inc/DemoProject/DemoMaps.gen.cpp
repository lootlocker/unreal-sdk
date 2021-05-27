// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoMaps.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoMaps() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoMaps_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoMaps();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
// End Cross Module References
	DEFINE_FUNCTION(ADemoMaps::execGetMaps)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetMaps();
		P_NATIVE_END;
	}
	void ADemoMaps::StaticRegisterNativesADemoMaps()
	{
		UClass* Class = ADemoMaps::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetMaps", &ADemoMaps::execGetMaps },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoMaps_GetMaps_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoMaps_GetMaps_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Maps" },
		{ "ModuleRelativePath", "Public/Demo/DemoMaps.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoMaps_GetMaps_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoMaps, nullptr, "GetMaps", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoMaps_GetMaps_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoMaps_GetMaps_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoMaps_GetMaps()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoMaps_GetMaps_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoMaps_NoRegister()
	{
		return ADemoMaps::StaticClass();
	}
	struct Z_Construct_UClass_ADemoMaps_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoMaps_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoMaps_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoMaps_GetMaps, "GetMaps" }, // 423195048
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoMaps_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoMaps.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoMaps.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoMaps_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoMaps>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoMaps_Statics::ClassParams = {
		&ADemoMaps::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoMaps_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoMaps_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoMaps()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoMaps_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoMaps, 3046288064);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoMaps>()
	{
		return ADemoMaps::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoMaps(Z_Construct_UClass_ADemoMaps, &ADemoMaps::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoMaps"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoMaps);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
