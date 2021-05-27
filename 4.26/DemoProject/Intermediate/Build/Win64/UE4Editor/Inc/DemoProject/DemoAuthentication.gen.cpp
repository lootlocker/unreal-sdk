// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoProject/Public/Demo/DemoAuthentication.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoAuthentication() {}
// Cross Module References
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoAuthentication_NoRegister();
	DEMOPROJECT_API UClass* Z_Construct_UClass_ADemoAuthentication();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_DemoProject();
// End Cross Module References
	DEFINE_FUNCTION(ADemoAuthentication::execGetSteamSessionTicket)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=ADemoAuthentication::GetSteamSessionTicket();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAuthentication::execDemoEndSession)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoEndSession();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAuthentication::execDemoVerifyPlayer)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoVerifyPlayer();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ADemoAuthentication::execDemoStartSession)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DemoStartSession();
		P_NATIVE_END;
	}
	void ADemoAuthentication::StaticRegisterNativesADemoAuthentication()
	{
		UClass* Class = ADemoAuthentication::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DemoEndSession", &ADemoAuthentication::execDemoEndSession },
			{ "DemoStartSession", &ADemoAuthentication::execDemoStartSession },
			{ "DemoVerifyPlayer", &ADemoAuthentication::execDemoVerifyPlayer },
			{ "GetSteamSessionTicket", &ADemoAuthentication::execGetSteamSessionTicket },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ADemoAuthentication_DemoEndSession_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAuthentication_DemoEndSession_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoAuthentication.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAuthentication_DemoEndSession_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAuthentication, nullptr, "DemoEndSession", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAuthentication_DemoEndSession_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAuthentication_DemoEndSession_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAuthentication_DemoEndSession()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAuthentication_DemoEndSession_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAuthentication_DemoStartSession_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAuthentication_DemoStartSession_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoAuthentication.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAuthentication_DemoStartSession_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAuthentication, nullptr, "DemoStartSession", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAuthentication_DemoStartSession_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAuthentication_DemoStartSession_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAuthentication_DemoStartSession()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAuthentication_DemoStartSession_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAuthentication_DemoVerifyPlayer_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAuthentication_DemoVerifyPlayer_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoAuthentication.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAuthentication_DemoVerifyPlayer_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAuthentication, nullptr, "DemoVerifyPlayer", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAuthentication_DemoVerifyPlayer_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAuthentication_DemoVerifyPlayer_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAuthentication_DemoVerifyPlayer()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAuthentication_DemoVerifyPlayer_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics
	{
		struct DemoAuthentication_eventGetSteamSessionTicket_Parms
		{
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(DemoAuthentication_eventGetSteamSessionTicket_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "LootLocker Demo | Authentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoAuthentication.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ADemoAuthentication, nullptr, "GetSteamSessionTicket", nullptr, nullptr, sizeof(DemoAuthentication_eventGetSteamSessionTicket_Parms), Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_ADemoAuthentication_NoRegister()
	{
		return ADemoAuthentication::StaticClass();
	}
	struct Z_Construct_UClass_ADemoAuthentication_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlayerId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_PlayerId;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SteamToken_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_SteamToken;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ADemoAuthentication_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_DemoProject,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_ADemoAuthentication_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoAuthentication_DemoEndSession, "DemoEndSession" }, // 2575165074
		{ &Z_Construct_UFunction_ADemoAuthentication_DemoStartSession, "DemoStartSession" }, // 314724758
		{ &Z_Construct_UFunction_ADemoAuthentication_DemoVerifyPlayer, "DemoVerifyPlayer" }, // 3389786318
		{ &Z_Construct_UFunction_ADemoAuthentication_GetSteamSessionTicket, "GetSteamSessionTicket" }, // 2889648242
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAuthentication_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "Demo/DemoAuthentication.h" },
		{ "ModuleRelativePath", "Public/Demo/DemoAuthentication.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_PlayerId_MetaData[] = {
		{ "Category", "DemoAuthentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoAuthentication.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_PlayerId = { "PlayerId", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAuthentication, PlayerId), METADATA_PARAMS(Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_PlayerId_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_PlayerId_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_SteamToken_MetaData[] = {
		{ "Category", "DemoAuthentication" },
		{ "ModuleRelativePath", "Public/Demo/DemoAuthentication.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_SteamToken = { "SteamToken", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ADemoAuthentication, SteamToken), METADATA_PARAMS(Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_SteamToken_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_SteamToken_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ADemoAuthentication_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_PlayerId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ADemoAuthentication_Statics::NewProp_SteamToken,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ADemoAuthentication_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoAuthentication>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ADemoAuthentication_Statics::ClassParams = {
		&ADemoAuthentication::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ADemoAuthentication_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAuthentication_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_ADemoAuthentication_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ADemoAuthentication_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ADemoAuthentication()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ADemoAuthentication_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ADemoAuthentication, 2339144135);
	template<> DEMOPROJECT_API UClass* StaticClass<ADemoAuthentication>()
	{
		return ADemoAuthentication::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ADemoAuthentication(Z_Construct_UClass_ADemoAuthentication, &ADemoAuthentication::StaticClass, TEXT("/Script/DemoProject"), TEXT("ADemoAuthentication"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ADemoAuthentication);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
