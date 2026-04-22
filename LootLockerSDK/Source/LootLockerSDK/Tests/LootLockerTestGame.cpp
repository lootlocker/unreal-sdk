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
	ProdKeyBody->SetStringField(TEXT("name"),     TEXT("ci-prod"));
	ProdKeyBody->SetStringField(TEXT("api_type"), TEXT("game"));

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
	DevKeyBody->SetStringField(TEXT("name"),     TEXT("ci-dev"));
	DevKeyBody->SetStringField(TEXT("api_type"), TEXT("game"));

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
	// Step 1: Get asset context ID
	const FLootLockerAdminResponse CtxResponse =
		FLootLockerAdminRequest::Send(TEXT("v1/game/#GAMEID#/assets/contexts"), TEXT("GET"));
	if (!CtxResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: GetAssetContexts failed (%d): %s"),
			CtxResponse.StatusCode, *CtxResponse.Body);
		return false;
	}

	int32 ContextId = 1;
	TSharedPtr<FJsonObject> CtxJson = ParseJson(CtxResponse.Body);
	if (CtxJson.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* Contexts;
		if (CtxJson->TryGetArrayField(TEXT("contexts"), Contexts) && Contexts->Num() > 0)
		{
			const TSharedPtr<FJsonObject>* First;
			if ((*Contexts)[0]->TryGetObject(First))
			{
				(*First)->TryGetNumberField(TEXT("id"), ContextId);
			}
		}
	}

	// Step 2: Create an asset in the game
	TSharedRef<FJsonObject> AssetBody = MakeShared<FJsonObject>();
	AssetBody->SetNumberField(TEXT("context_id"), ContextId);
	AssetBody->SetStringField(TEXT("name"),       TEXT("CI Trigger Asset"));

	const FLootLockerAdminResponse AssetResponse =
		FLootLockerAdminRequest::Send(
			TEXT("v1/game/#GAMEID#/asset"), TEXT("POST"), SerializeJson(AssetBody));
	if (!AssetResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateAsset for trigger failed (%d): %s"),
			AssetResponse.StatusCode, *AssetResponse.Body);
		return false;
	}

	FString AssetUlid;
	TSharedPtr<FJsonObject> AssetJson = ParseJson(AssetResponse.Body);
	if (AssetJson.IsValid())
	{
		const TSharedPtr<FJsonObject>* AssetObj;
		if (AssetJson->TryGetObjectField(TEXT("asset"), AssetObj))
		{
			(*AssetObj)->TryGetStringField(TEXT("ulid"), AssetUlid);
		}
	}
	if (AssetUlid.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateAsset response missing asset.ulid"));
		return false;
	}

	// Step 3: Create a reward backed by the asset
	TSharedRef<FJsonObject> RewardBody = MakeShared<FJsonObject>();
	RewardBody->SetStringField(TEXT("entity_id"),   AssetUlid);
	RewardBody->SetStringField(TEXT("entity_kind"), TEXT("asset"));

	const FLootLockerAdminResponse RewardResponse =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/reward"), TEXT("POST"), SerializeJson(RewardBody));
	if (!RewardResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateReward for trigger failed (%d): %s"),
			RewardResponse.StatusCode, *RewardResponse.Body);
		return false;
	}

	FString RewardId;
	TSharedPtr<FJsonObject> RewardJson = ParseJson(RewardResponse.Body);
	if (RewardJson.IsValid())
	{
		RewardJson->TryGetStringField(TEXT("id"), RewardId);
	}
	if (RewardId.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateReward response missing id"));
		return false;
	}

	// Step 4: Create the trigger with the nested body and reward_id
	TSharedRef<FJsonObject> TriggerInner = MakeShared<FJsonObject>();
	TriggerInner->SetStringField(TEXT("key"),       Key);
	TriggerInner->SetStringField(TEXT("name"),      Name);
	TriggerInner->SetNumberField(TEXT("limit"),     0);
	TriggerInner->SetStringField(TEXT("reward_id"), RewardId);

	TSharedRef<FJsonObject> TriggerBody = MakeShared<FJsonObject>();
	TriggerBody->SetObjectField(TEXT("trigger"), TriggerInner);
	TArray<TSharedPtr<FJsonValue>> EmptySegments;
	TriggerBody->SetArrayField(TEXT("segments"), EmptySegments);

	const FLootLockerAdminResponse Response =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/triggers/cozy-crusader/v1"), TEXT("POST"), SerializeJson(TriggerBody));
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
	CurrencyBody->SetStringField(TEXT("initial_denomination_name"), TEXT("base"));

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
		Json->TryGetStringField(TEXT("id"), OutCurrencyId);
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
	Body->SetBoolField(TEXT("allow_game_writes"), true);
	Body->SetBoolField(TEXT("active"), true);

	const FLootLockerAdminResponse Response =
		FLootLockerAdminRequest::Send(
			TEXT("game/#GAMEID#/progressions"), TEXT("POST"), SerializeJson(Body));

	if (!Response.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateProgression '%s' failed (%d): %s"),
			*Key, Response.StatusCode, *Response.Body);
		return false;
	}

	// Parse the progression ULID id so we can create a usable tier.
	// The auto-created step=1 tier has threshold=0, which causes all points to be
	// clamped to 0. Adding step=2 with threshold=1000 allows points to accumulate.
	TSharedPtr<FJsonObject> ProgressionJson = ParseJson(Response.Body);
	FString ProgressionId;
	if (!ProgressionJson.IsValid() || !ProgressionJson->TryGetStringField(TEXT("id"), ProgressionId) || ProgressionId.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateProgression '%s' - could not parse progression id from response"), *Key);
		return false;
	}

	TSharedRef<FJsonObject> TierBody = MakeShared<FJsonObject>();
	TierBody->SetNumberField(TEXT("step"), 2);
	TierBody->SetNumberField(TEXT("points_threshold"), 1000);

	const FLootLockerAdminResponse TierResponse =
		FLootLockerAdminRequest::Send(
			*(TEXT("game/#GAMEID#/progressions/") + ProgressionId + TEXT("/tiers")),
			TEXT("POST"), SerializeJson(TierBody));

	if (!TierResponse.bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("LootLockerTestGame: CreateProgressionTier for '%s' failed (%d): %s"),
			*Key, TierResponse.StatusCode, *TierResponse.Body);
		return false;
	}

	return true;
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
