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

## Issue Tracking & Lifecycle

All SDK work is driven by a tracking issue in [lootlocker/index](https://github.com/lootlocker/index). That issue is the single source of truth for status, decisions, and acceptance criteria. **You must keep it up to date throughout your work.**

### Project Status

This issue will almost always be tracked in project https://github.com/orgs/lootlocker/projects/75. Update the issue's project status as your work progresses:

| Situation | Status to set |
|-----------|--------------|
| You start working on the task | **In Progress** |
| You are blocked and need input from a human | **Blocked** |
| A PR has been opened and is ready for review | **In Review** |

### Architectural Decisions & Questions

Do not make undocumented assumptions. If a question or decision arises during implementation:
- Leave a comment on the tracking issue describing the question or decision clearly.
- Tag @kirre-bylund so it can be addressed.
- Set the project status to **Blocked** and stop work on the affected area until answered.

### Linking PRs

As soon as you open a PR in this repo, post a comment on the tracking issue with the PR link. Also link the PR formally via GitHub's "Development" section on the tracking issue.

### Acceptance Criteria & Definition of Done

Check off items in the tracking issue's Definition of Done as they are completed. If scope changes during implementation, update the acceptance criteria in the tracking issue and leave a comment explaining what changed and why.
