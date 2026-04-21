// Copyright (c) 2021 LootLocker

#include "LootLockerTestGame.h"

#if ENGINE_MAJOR_VERSION > 4

#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "HAL/PlatformMisc.h"
#include "LootLockerConfig.h"
#include "Misc/Guid.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

// ─── Internal helpers ─────────────────────────────────────────────────────────

namespace
{

TSharedPtr<FJsonObject> ParseJson(const FString& Body)
{
	TSharedPtr<FJsonObject> Json;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Body);
	FJsonSerializer::Deserialize(Reader, Json);
	return Json;
}

FString SerializeJson(const TSharedRef<FJsonObject>& Object)
{
	FString Out;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
	FJsonSerializer::Serialize(Object, Writer);
	return Out;
}

} // namespace

// ─── Lifecycle ────────────────────────────────────────────────────────────────

bool FLootLockerTestGame::CreateGame(FLootLockerTestGame& OutGame, const FString& TestName)
{
	// Shortcut: use a pre-existing key from env var (no admin credentials needed)
	const FString EnvKey = FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_GAME_API_KEY"));
	if (!EnvKey.IsEmpty())
	{
		OutGame.GameApiKey            = EnvKey;
		OutGame.DevelopmentGameApiKey = EnvKey;
		OutGame.GameId                = -1; // Sentinel: DeleteGame() is a no-op
		OutGame.DevelopmentGameId     = -1;
		OutGame.ActiveGameId          = -1;
		UE_LOG(LogTemp, Log,
			TEXT("LootLockerTestGame: Using LOOTLOCKER_GAME_API_KEY env var (skipping game creation)"));
		return true;
	}

	if (!FLootLockerAdminRequest::EnsureSignedIn())
	{
		return false;
	}

	// ── Create game ──────────────────────────────────────────────────────────
	const FString GameName = FString::Printf(TEXT("%s-%s"),
		TestName.IsEmpty() ? TEXT("UE-CI") : *TestName,
		*FGuid::NewGuid().ToString(EGuidFormats::Short));

	TSharedRef<FJsonObject> CreateGameBody = MakeShared<FJsonObject>();
	CreateGameBody->SetStringField(TEXT("name"),            GameName);
	CreateGameBody->SetNumberField(TEXT("genre"),           1);
	CreateGameBody->SetNumberField(TEXT("organisation_id"), FLootLockerAdminRequest::OrganisationId);

	const FLootLockerAdminResponse CreateGameResponse =
		FLootLockerAdminRequest::Send(TEXT("v1/game"), TEXT("POST"), SerializeJson(CreateGameBody));

	if (!CreateGameResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateGame failed (%d): %s"),
			CreateGameResponse.StatusCode, *CreateGameResponse.Body);
		return false;
	}

	TSharedPtr<FJsonObject> CreateGameJson = ParseJson(CreateGameResponse.Body);
	if (!CreateGameJson.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: Failed to parse CreateGame response"));
		return false;
	}

	const TSharedPtr<FJsonObject>* GameObj;
	if (!CreateGameJson->TryGetObjectField(TEXT("game"), GameObj))
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateGame response missing 'game' field"));
		return false;
	}

	(*GameObj)->TryGetNumberField(TEXT("id"),         OutGame.GameId);
	(*GameObj)->TryGetStringField(TEXT("name"),       OutGame.GameName);
	(*GameObj)->TryGetStringField(TEXT("domain_key"), OutGame.GameDomainKey);

	const TSharedPtr<FJsonObject>* DevObj;
	if ((*GameObj)->TryGetObjectField(TEXT("development"), DevObj))
	{
		(*DevObj)->TryGetNumberField(TEXT("id"), OutGame.DevelopmentGameId);
	}

	UE_LOG(LogTemp, Log,
		TEXT("LootLockerTestGame: Created game '%s' (id=%d, dev_id=%d)"),
		*OutGame.GameName, OutGame.GameId, OutGame.DevelopmentGameId);

	// ── Create prod API key ──────────────────────────────────────────────────
	OutGame.SwitchToProdEnvironment();

	TSharedRef<FJsonObject> ProdKeyBody = MakeShared<FJsonObject>();
	ProdKeyBody->SetStringField(TEXT("name"), TEXT("ci-prod"));

	const FLootLockerAdminResponse ProdKeyResponse =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/api_keys"), TEXT("POST"), SerializeJson(ProdKeyBody));

	if (!ProdKeyResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: Create prod API key failed (%d): %s"),
			ProdKeyResponse.StatusCode, *ProdKeyResponse.Body);
		return false;
	}

	TSharedPtr<FJsonObject> ProdKeyJson = ParseJson(ProdKeyResponse.Body);
	if (ProdKeyJson.IsValid())
	{
		ProdKeyJson->TryGetStringField(TEXT("api_key"), OutGame.GameApiKey);
	}

	// ── Create dev / stage API key ───────────────────────────────────────────
	OutGame.SwitchToStageEnvironment();

	TSharedRef<FJsonObject> DevKeyBody = MakeShared<FJsonObject>();
	DevKeyBody->SetStringField(TEXT("name"), TEXT("ci-dev"));

	const FLootLockerAdminResponse DevKeyResponse =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/api_keys"), TEXT("POST"), SerializeJson(DevKeyBody));

	if (!DevKeyResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: Create dev API key failed (%d): %s"),
			DevKeyResponse.StatusCode, *DevKeyResponse.Body);
		return false;
	}

	TSharedPtr<FJsonObject> DevKeyJson = ParseJson(DevKeyResponse.Body);
	if (DevKeyJson.IsValid())
	{
		DevKeyJson->TryGetStringField(TEXT("api_key"), OutGame.DevelopmentGameApiKey);
	}

	// Tests always run against the stage / dev environment
	OutGame.SwitchToStageEnvironment();

	UE_LOG(LogTemp, Log, TEXT("LootLockerTestGame: Game ready (prod_key=%.8s..., dev_key=%.8s...)"),
		*OutGame.GameApiKey, *OutGame.DevelopmentGameApiKey);

	return true;
}

bool FLootLockerTestGame::DeleteGame()
{
	if (GameId <= 0)
	{
		// Either invalid or we used the env-var shortcut — nothing to delete
		return true;
	}

	SwitchToProdEnvironment();

	const FLootLockerAdminResponse Response =
		FLootLockerAdminRequest::Send(TEXT("v1/game/#GAMEID#"), TEXT("DELETE"));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("LootLockerTestGame: DeleteGame failed (%d): %s"),
			Response.StatusCode, *Response.Body);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("LootLockerTestGame: Deleted game %d"), GameId);
	}

	return Response.bSuccess;
}

// ─── Feature enablement ───────────────────────────────────────────────────────

bool FLootLockerTestGame::EnableGuestLogin()
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetBoolField(TEXT("enabled"), true);

	const FLootLockerAdminResponse Response =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/platforms/guest"), TEXT("PUT"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: EnableGuestLogin failed (%d): %s"),
			Response.StatusCode, *Response.Body);
	}
	return Response.bSuccess;
}

// ─── Entity provisioning ──────────────────────────────────────────────────────

bool FLootLockerTestGame::CreateLeaderboard(
	const FString& Key, const FString& MemberType, const FString& Direction)
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("name"),                     Key);
	Body->SetStringField(TEXT("key"),                      Key);
	Body->SetStringField(TEXT("type"),                     MemberType);
	Body->SetStringField(TEXT("direction_method"),         Direction);
	Body->SetBoolField  (TEXT("enable_game_api_writes"),   true);
	Body->SetBoolField  (TEXT("overwrite_score_on_submit"), false);

	const FLootLockerAdminResponse Response =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/leaderboards"), TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateLeaderboard '%s' failed (%d): %s"),
			*Key, Response.StatusCode, *Response.Body);
	}
	return Response.bSuccess;
}

bool FLootLockerTestGame::CreateTrigger(const FString& Key, const FString& Name)
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("key"),   Key);
	Body->SetStringField(TEXT("name"),  Name);
	Body->SetNumberField(TEXT("limit"), 0); // 0 = unlimited invocations

	const FLootLockerAdminResponse Response =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/triggers/cozy-crusader/v1"), TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateTrigger '%s' failed (%d): %s"),
			*Key, Response.StatusCode, *Response.Body);
	}
	return Response.bSuccess;
}

bool FLootLockerTestGame::CreateCurrency(
	const FString& Name, const FString& Code, FString& OutCurrencyId)
{
	// Create the currency
	TSharedRef<FJsonObject> CurrencyBody = MakeShared<FJsonObject>();
	CurrencyBody->SetStringField(TEXT("name"), Name);
	CurrencyBody->SetStringField(TEXT("code"), Code);
	CurrencyBody->SetStringField(TEXT("type"), TEXT("soft"));

	const FLootLockerAdminResponse CreateResponse =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/currencies/currency"), TEXT("POST"), SerializeJson(CurrencyBody));

	if (!CreateResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateCurrency '%s' failed (%d): %s"),
			*Code, CreateResponse.StatusCode, *CreateResponse.Body);
		return false;
	}

	TSharedPtr<FJsonObject> Json = ParseJson(CreateResponse.Body);
	if (Json.IsValid())
	{
		const TSharedPtr<FJsonObject>* CurrencyObj;
		if (Json->TryGetObjectField(TEXT("currency"), CurrencyObj))
		{
			(*CurrencyObj)->TryGetStringField(TEXT("id"), OutCurrencyId);
		}
	}

	if (OutCurrencyId.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateCurrency response missing currency.id"));
		return false;
	}

	// Enable game-side SDK writes (credit / debit via SDK)
	const FLootLockerAdminResponse EnableResponse =
		FLootLockerAdminRequest::Send(
			FString::Printf(
				TEXT("game/#GAMEID#/currencies/currency/%s/enable-game-writes"), *OutCurrencyId),
			TEXT("PATCH"));

	if (!EnableResponse.bSuccess)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("LootLockerTestGame: EnableGameWrites for currency '%s' failed (%d): %s — "
			     "SDK credit/debit calls may fail"),
			*Code, EnableResponse.StatusCode, *EnableResponse.Body);
	}

	return true;
}

bool FLootLockerTestGame::CreateProgression(const FString& Key, const FString& Name)
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("key"),  Key);
	Body->SetStringField(TEXT("name"), Name);

	const FLootLockerAdminResponse Response =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/progressions"), TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateProgression '%s' failed (%d): %s"),
			*Key, Response.StatusCode, *Response.Body);
	}
	return Response.bSuccess;
}

bool FLootLockerTestGame::CreateAsset(int32& OutAssetId, const FString& Name)
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("name"),    Name);
	Body->SetNumberField(TEXT("context"), 1); // Default asset context

	const FLootLockerAdminResponse CreateResponse =
		FLootLockerAdminRequest::Send(
			TEXT("v1/game/#GAMEID#/asset"), TEXT("POST"), SerializeJson(Body));

	if (!CreateResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateAsset '%s' failed (%d): %s"),
			*Name, CreateResponse.StatusCode, *CreateResponse.Body);
		return false;
	}

	TSharedPtr<FJsonObject> Json = ParseJson(CreateResponse.Body);
	if (Json.IsValid())
	{
		const TSharedPtr<FJsonObject>* AssetObj;
		if (Json->TryGetObjectField(TEXT("asset"), AssetObj))
		{
			(*AssetObj)->TryGetNumberField(TEXT("id"), OutAssetId);
		}
	}

	if (OutAssetId == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateAsset response missing asset.id"));
		return false;
	}

	// Activate the asset so it appears in player-facing API responses
	FLootLockerAdminRequest::Send(
		FString::Printf(TEXT("v1/game/#GAMEID#/asset/%d/activate"), OutAssetId), TEXT("POST"));

	return true;
}

bool FLootLockerTestGame::GrantAssetToPlayer(
	const FString& PlayerUlid, int32 AssetId, int32& OutInstanceId)
{
	TSharedRef<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetNumberField(TEXT("asset_id"), AssetId);

	const FLootLockerAdminResponse Response =
		FLootLockerAdminRequest::Send(
			FString::Printf(
				TEXT("game/#GAMEID#/player/%s/inventory/grant"), *PlayerUlid),
			TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error,
			TEXT("LootLockerTestGame: GrantAssetToPlayer failed "
			     "(player=%s, asset=%d, status=%d): %s"),
			*PlayerUlid, AssetId, Response.StatusCode, *Response.Body);
		return false;
	}

	TSharedPtr<FJsonObject> Json = ParseJson(Response.Body);
	if (Json.IsValid())
	{
		Json->TryGetNumberField(TEXT("instance_id"), OutInstanceId);
	}

	return true;
}

// ─── SDK initialization ───────────────────────────────────────────────────────

void FLootLockerTestGame::InitializeLootLockerSDK() const
{
	ULootLockerConfig* Config = GetMutableDefault<ULootLockerConfig>();
	Config->LootLockerGameKey = GetActiveApiKey();
	Config->GameVersion       = TEXT("0.0.0.1");
	Config->DomainKey         = GameDomainKey;

	// If the domain key is empty (e.g. env-var shortcut), check for a companion env var
	if (Config->DomainKey.IsEmpty())
	{
		Config->DomainKey =
			FPlatformMisc::GetEnvironmentVariable(TEXT("LOOTLOCKER_GAME_DOMAIN_KEY"));
	}
}

#endif // ENGINE_MAJOR_VERSION > 4
