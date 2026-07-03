# Release Notes Template

Use this template when drafting a GitHub release for the Unreal Game SDK.

## Title Format

```
LootLocker_UnrealSDK_V{MAJOR}.{MINOR}.{PATCH}
```

Examples: `LootLocker_UnrealSDK_V10.4.0`, `LootLocker_UnrealSDK_V10.3.2`

---

## Body Template — Major/Minor Release

```markdown
### Features

• 🚀 **Feature Title** — Description of the feature. Keep it user-facing and
actionable. Mention what problem it solves or what new capability it unlocks.
• 🔗 **Another Feature** — Another description. Use emojis to visually group
related features (e.g. 💳 for payments, 📱 for platform-specific, 🎮 for auth).
• 📚 **Documentation / Tooling** — If applicable.
• Minor additions without their own emoji header.

### Fixes

• Fixed an issue where X would happen when Y.
• Fixed a crash when Z was null.
• Fixed compilation errors on platform/engine version.
• Fixed `UProperty` name mismatches between C++ and Blueprint surfaces.

### Breaking Changes

• Removed `DeprecatedClass` / `DeprecatedMethod` — use `NewClass` / `NewMethod` instead.
• `EOldEnum` replaced by `ENewEnum` — update your switch statements.

### Deprecations

• `OldMethod` is now deprecated and will be removed in v{NEXT_MAJOR}. Migrate to `NewMethod`.

### Refactoring

• Summary of internal changes that users should be aware of but don't change
the public API surface (e.g. HTTP client rewrite, delegate restructuring).

Full Changelog: [v{PREV_VERSION}...v{NEW_VERSION}](https://github.com/lootlocker/unreal-sdk/compare/v{PREV_VERSION}...v{NEW_VERSION})
```

---

## Body Template — Patch Release

```markdown
### Fix

• Fixed a crash when X is null.
• Fixed missing `UPROPERTY` / `UFUNCTION` specifiers.
• Fixed packaging/building error on engine version Y.

Full Changelog: [v{PREV_VERSION}...v{NEW_VERSION}](https://github.com/lootlocker/unreal-sdk/compare/v{PREV_VERSION}...v{NEW_VERSION})
```

---

## Writing Guidelines

- **Audience:** Game developers using LootLocker in Unreal Engine. Keep
  descriptions user-facing — describe what _they_ can do or what was fixed
  for _them_. Use Unreal terms: Blueprint, UCLASS, UFUNCTION, UPROPERTY,
  UObject, Actor, etc.
- **Links:** Use full URLs for cross-references (blog posts, docs, compare links).
- **Emojis:** Use to visually group features. Common ones:
  - 🚀 Major new capability
  - 💳 Payments / purchases
  - 🎮 Authentication / platforms
  - 📱 Platform-specific (mobile, console)
  - 📚 Documentation / reference docs
  - 🧪 Testing / CI
  - ⚡ Performance / real-time (Presence, WebSockets)
  - 🔍 Filtering / search
  - 🔗 Linking / connected accounts / remote sessions
  - 🛒 Store / catalog
  - 📣 Broadcasts / notifications
- **Sections:** Only include sections that have content. Don't add empty headings.
- **Compare link:** Always include the `Full Changelog` link at the bottom.
