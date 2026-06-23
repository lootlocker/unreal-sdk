// Copyright (c) 2021 LootLocker

#pragma once

/// @addtogroup Init
/// @{

#include "CoreMinimal.h"
#include "LootLockerFileConfig.generated.h"

/**
 * Data struct for the pre-configured file config, loaded at startup from the "<PackageName>PreConfig[-<identifier>].bytes"
 * file in the plugin's Config directory. When present and containing a non-empty api_key, it overrides
 * DefaultGame.ini settings and locks the editor UI to prevent drift.
 *
 * The file supports plain JSON or AES-256-ECB + PKCS7 + Base64 encrypted content. Plain JSON is
 * recommended during development; encrypted files should be used for distribution.
 *
 * Build-time flags (enable_google_subsystem_helper, etc.) live in the optional "build_flags" JSON
 * section and are consumed only by Build.cs at compile time — not at runtime.
 *
 * Supported JSON fields:
 *   api_key                                       (string, required — empty or missing means "inactive")
 *   domain_key                                    (string)
 *   game_version                                  (string, default "1.0.0.0")
 *   allow_token_refresh                           (bool, default true)
 *   log_outside_of_editor                         (bool, default false)
 *   log_level                                     (string: "Error"|"Warning"|"Display"|"Verbose"|"VeryVerbose"|"NoLogging", default "Warning")
 *   enable_file_logging                           (bool, default false)
 *   enable_presence                               (bool, default false)
 *   enable_presence_auto_connect                  (bool, default true)
 *   enable_presence_auto_disconnect_on_focus_change (bool, default true)
 *   enable_presence_in_editor                     (bool, default true)
 *   multi_user_session_mode                       (string: "Hotseat"|"SingleSession"|"ProfileSwitching"|"NotSet", default "NotSet" is internal and will be resolved at first launch")
 *   use_legacy_http_stack                         (bool, default false)
 *
 * Build-time only (parsed by Build.cs, ignored at runtime):
 *   build_flags.enable_google_subsystem_helper    (bool)
 *   build_flags.show_outdated_sdk_message         (bool)
 *   build_flags.enable_beta_error_reporting       (bool)
 *   build_flags.force_legacy_http_stack           (bool)
 */
USTRUCT()
struct LOOTLOCKERSDK_API FLootLockerFileConfig
{
	GENERATED_BODY()

	UPROPERTY()
	FString api_key;

	UPROPERTY()
	FString domain_key;

	UPROPERTY()
	FString game_version = TEXT("1.0.0.0");

	UPROPERTY()
	bool allow_token_refresh = true;

	UPROPERTY()
	bool log_outside_of_editor = false;

	/** Enum name string: "Error"|"Warning"|"Display"|"Verbose"|"VeryVerbose"|"NoLogging" */
	UPROPERTY()
	FString log_level = TEXT("Warning");

	UPROPERTY()
	bool enable_file_logging = false;

	UPROPERTY()
	bool enable_presence = false;

	UPROPERTY()
	bool enable_presence_auto_connect = true;

	UPROPERTY()
	bool enable_presence_auto_disconnect_on_focus_change = true;

	UPROPERTY()
	bool enable_presence_in_editor = true;

	/** Enum name string: "Hotseat"|"SingleSession"|"ProfileSwitching". Default "NotSet" means "do not override". */
	UPROPERTY()
	FString multi_user_session_mode = TEXT("NotSet");

	UPROPERTY()
	bool use_legacy_http_stack = false;
};

/// @}
