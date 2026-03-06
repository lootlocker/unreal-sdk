# Copilot instructions (LootLocker Unreal SDK)

- Read [.github/instructions/architecture.md](instructions/architecture.md) first to understand **where code lives** and the repo’s architectural boundaries.
- Follow guardrails in [.github/instructions/guardrails.md](instructions/guardrails.md).
- Follow conventions in [.github/instructions/style-guide.md](instructions/style-guide.md).
- Reference patterns in [.github/instructions/patterns.md](instructions/patterns.md).
- Path-specific instructions (higher precedence than this file):
  - Public C++ facade: [.github/instructions/LootLockerSDK/Source/LootLockerSDK/Public/LootLockerSDKManager.h.instructions.md](instructions/LootLockerSDK/Source/LootLockerSDK/Public/LootLockerSDKManager.h.instructions.md)
  - Public Blueprint facade: [.github/instructions/LootLockerSDK/Source/LootLockerSDK/Public/LootLockerManager.h.instructions.md](instructions/LootLockerSDK/Source/LootLockerSDK/Public/LootLockerManager.h.instructions.md)
  - Request handler headers: [.github/instructions/LootLockerSDK/Source/LootLockerSDK/Public/GameAPI.instructions.md](instructions/LootLockerSDK/Source/LootLockerSDK/Public/GameAPI.instructions.md)
  - Request handler impls: [.github/instructions/LootLockerSDK/Source/LootLockerSDK/Private/GameAPI.instructions.md](instructions/LootLockerSDK/Source/LootLockerSDK/Private/GameAPI.instructions.md)
- Branching rules:
  - Work only on a work branch (no direct commits to `dev`/`main`).
  - PRs must target **base = `dev`** (never `main`).
- Issue tracking & lifecycle: follow [.github/instructions/implementation-lifecycle.md](instructions/implementation-lifecycle.md).
