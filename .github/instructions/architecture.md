# LootLocker Unreal SDK — architecture & repo structure

This doc is intended to help contributors (and coding agents) quickly answer:
- Where does code live?
- What are the module boundaries?
- Where do HTTP/JSON/auth/session concerns live?
- Where should a change be implemented?

Docs-only guide; it is not a feature spec.

## Repo type

This repo is an **Unreal Engine plugin repo**.
- Plugin root: `LootLockerSDK/`
- Plugin descriptor: `LootLockerSDK/LootLockerSDK.uplugin`
- There is **no** `.uproject` in this repo; consumers copy the `LootLockerSDK/` folder into a project’s `Plugins/` folder.

## Repo map

- Plugin descriptor: `LootLockerSDK/LootLockerSDK.uplugin`
- Plugin config/resources:
  - `LootLockerSDK/Config/FilterPlugin.ini`
  - `LootLockerSDK/Resources/`
- Main runtime module:
  - `LootLockerSDK/Source/LootLockerSDK/`
    - Public headers: `LootLockerSDK/Source/LootLockerSDK/Public/`
    - Private implementation: `LootLockerSDK/Source/LootLockerSDK/Private/`
    - Game API request handlers:
      - Headers: `LootLockerSDK/Source/LootLockerSDK/Public/GameAPI/`
      - Implementations: `LootLockerSDK/Source/LootLockerSDK/Private/GameAPI/`
    - Test sources: `LootLockerSDK/Source/LootLockerSDK/Tests/`
- Editor module:
  - `LootLockerSDK/Source/LootLockerSDKEditor/`

## Modules & boundaries

Modules are defined by the Build.cs files:
- Runtime: `LootLockerSDK/Source/LootLockerSDK/LootLockerSDK.Build.cs`
- Editor: `LootLockerSDK/Source/LootLockerSDKEditor/LootLockerSDKEditor.Build.cs`

### `LootLockerSDK` (Runtime)

**Responsibility**: The shipping SDK used by games.

- Public API surface (safe for external includes):
  - `LootLockerSDK/Source/LootLockerSDK/Public/`
- Internal implementation (do not include from other modules):
  - `LootLockerSDK/Source/LootLockerSDK/Private/`

**Boundary rule**: avoid including `Private/` headers from outside the `LootLockerSDK` module. If something must be used externally, it should be in `Public/` (but expanding the public API should be done carefully).

Notable runtime public entrypoints:
- `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerSDKManager.h` (`ULootLockerSDKManager`)
- `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerManager.h` (`ULootLockerManager`, Blueprint-facing surface)

### `LootLockerSDKEditor` (Editor)

**Responsibility**: Editor tooling/UI. Not packaged into shipped builds.

- Module entrypoint: `LootLockerSDK/Source/LootLockerSDKEditor/LootLockerSDKEditor.cpp` (`IMPLEMENT_MODULE`)
- Example UI: `LootLockerSDK/Source/LootLockerSDKEditor/LootLockerLogViewerWidget.h` / `.cpp`

## Request/transport/serialization/auth: where things live

### HTTP transport layer

- Client class: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerHttpClient.h`
- Implementation: `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerHttpClient.cpp`

Key details:
- Uses `FHttpModule` to create requests.
- Applies authentication header `x-session-token` when `FLootLockerPlayerData::Token` is present.
- Handles request logging (via `FLootLockerLogger`) and builds `FLootLockerResponse`.
- Contains token refresh / retry plumbing (`ShouldRefreshSession`, `RefreshSessionForPlatform`, `RetryOriginalRequest`).

### Endpoints / URL construction

- Endpoint catalog (public declarations): `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerGameEndpoints.h`
- Endpoint initialization/base URL: `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerGameEndpoints.cpp`

Key details:
- Base URL uses `{domainKey}` substitution.
- `LOOTLOCKER_USE_STAGE_URL` toggles stage vs production base URL.

### JSON serialization & response parsing

Common conversion points:
- Generic request/response plumbing: `LootLockerSDK/Source/LootLockerSDK/Private/Utils/LootLockerUtilities.h`
  - `LLAPI<ResponseType>`: wraps request serialization + response parsing.
  - `LootLockerUtilities::UStructToJsonString` and `FJsonObjectConverter` conversions.
- JSON parsing helpers: `LootLockerSDK/Source/LootLockerSDK/Private/Utils/LootLockerUtilities.cpp`
  - `FJsonSerializer` usage and helpers like `JsonObjectFromFString`.

### Auth/session/token handling

- Authentication flows + session start:
  - API types/structs: `LootLockerSDK/Source/LootLockerSDK/Public/GameAPI/LootLockerAuthenticationRequestHandler.h`
  - Implementations: `LootLockerSDK/Source/LootLockerSDK/Private/GameAPI/LootLockerAuthenticationRequestHandler.cpp`
- Persisted player/session state:
  - Public API/types: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerStateData.h`
  - Implementation: `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerStateData.cpp`
- Player/session token data model:
  - `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerPlayerData.h` (`FLootLockerPlayerData` has `Token` + `RefreshToken`)
- Config flags that affect auth behavior:
  - `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerConfig.h` (ex: `AllowTokenRefresh`, `DomainKey`)

### Error/result representation

- Base response + error factory:
  - `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerResponse.h`
- Error payload structure:
  - `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerErrorData.h`

## “Where do I implement X?” (decision table)

| Task | Primary location(s) |
|---|---|
| Add a new endpoint/API call | Add/declare endpoint in `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerGameEndpoints.h` and initialize it in `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerGameEndpoints.cpp`. Implement the call in the relevant request handler under `LootLockerSDK/Source/LootLockerSDK/Private/GameAPI/` with its public declaration/types in `LootLockerSDK/Source/LootLockerSDK/Public/GameAPI/`. |
| Add request/response structs | Usually in the relevant `LootLockerSDK/Source/LootLockerSDK/Public/GameAPI/*RequestHandler.h` (USTRUCT/UPROPERTY for reflection/Blueprint support when needed). |
| Change auth/session start flows | `LootLockerSDK/Source/LootLockerSDK/Public/GameAPI/LootLockerAuthenticationRequestHandler.h` and `LootLockerSDK/Source/LootLockerSDK/Private/GameAPI/LootLockerAuthenticationRequestHandler.cpp`. |
| Change how tokens are stored/cached | `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerStateData.h` and `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerStateData.cpp` (SaveGame slots, default player selection, active/cached state). |
| Change the HTTP layer (headers, retries, timeouts, refresh behavior) | `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerHttpClient.h` and `LootLockerSDK/Source/LootLockerSDK/Private/LootLockerHttpClient.cpp`. |
| Change JSON serialization/parsing conventions | `LootLockerSDK/Source/LootLockerSDK/Private/Utils/LootLockerUtilities.h` and `LootLockerSDK/Source/LootLockerSDK/Private/Utils/LootLockerUtilities.cpp` (and any request handler that does bespoke parsing). |
| Change the SDK’s public facade surface | `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerSDKManager.h` (C++-style static API surface) and/or `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerManager.h` (Blueprint-facing surface). |
| Add/adjust Blueprint-exposed API | Prefer adding to `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerManager.h` (uses dynamic delegates and reflection macros). Be careful not to expand the public API unnecessarily. |
| Add tests | `LootLockerSDK/Source/LootLockerSDK/Tests/` and helpers in `LootLockerSDK/Source/LootLockerSDK/Tests/TestUtils.h`. |
| Editor-only tooling | `LootLockerSDK/Source/LootLockerSDKEditor/` (ex: `LootLockerLogViewerWidget.*`). |

## Common pitfalls

- **Accidental API surface expansion**: anything added under `Public/` becomes part of the module’s public interface; avoid exposing internal helpers.
- **Missing API Surface expansion**: Adding request DTOs and methods in request handlers but not exposing them through `LootLockerSDKManager.h/cpp` and `LootLockerManager.h/cpp` makes it invisible to users.
- **Private header leakage**: don’t include `LootLockerSDK/Source/LootLockerSDK/Private/...` from other modules.
- **Duplication**: many request handlers already exist under `Public/GameAPI/` and `Private/GameAPI/`; search before adding another.
- **Reflection gotchas**: if a type is used in Blueprint/UE reflection, it must be declared with `UCLASS`/`USTRUCT` and members need `UPROPERTY` / functions need `UFUNCTION`.
- **Async/callback lifetime**: most API calls complete via delegates/lambdas; ensure captured data remains valid and avoid capturing UObjects without considering lifetime.
- **Sensitive logging**: request bodies can contain secrets; use existing obfuscation helpers (see `LootLockerSDK/Source/LootLockerSDK/Private/Utils/LootLockerUtilities.*`).

## Links

- Guardrails: [.github/instructions/guardrails.md](guardrails.md)
- Copilot instructions: [.github/copilot-instructions.md](../copilot-instructions.md)
