# Path-specific instructions — LootLockerManager.h

Applies to: `LootLockerSDK/Source/LootLockerSDK/Public/LootLockerManager.h`

- Treat this file as the **Blueprint-facing facade**. Avoid breaking changes unless explicitly requested.
- Keep diffs minimal and localized; this header is large and used as a user-facing API surface.
- Docs are required for any API you add or change. Match the existing `/** ... */` documentation style in this file.
- When adding Blueprint API:
  - Use `UFUNCTION(BlueprintCallable, Category = "LootLocker Methods | <Area>")` matching existing category naming.
  - If returning a request id, return `FString` and use `UPARAM(DisplayName = "RequestId")`.
  - Use metadata patterns already present when appropriate: `AdvancedDisplay`, `AutoCreateRefTerm`.
  - For deprecations, use `meta = (DeprecatedFunction, DeprecationMessage="...")`, point to the replacement method, and keep the existing “Deprecation date …” comment style.
- Delegate conventions in this file:
  - Blueprint delegates are dynamic (`DECLARE_DYNAMIC_DELEGATE_*`) and commonly use a `...BP` suffix.
  - Prefer existing response struct types (`FLootLockerResponse`-derived) for callbacks.
- Do not introduce logging that could expose sensitive data (tokens, passwords, API keys). If you must log JSON for diagnostics, use the existing obfuscation helpers in `LootLockerUtilities`.
