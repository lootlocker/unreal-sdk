# Doxygen documentation rules (Unreal SDK)

All public types in `Public/GameAPI/` must be Doxygen-documentable.
These rules exist because the docs are built with `EXTRACT_ALL = NO` and
`HIDE_UNDOC_MEMBERS = YES`, so undocumented members are silently dropped.

---

## Delegate types (`DECLARE_DELEGATE_*`)

Every `DECLARE_DELEGATE_*` invocation must be immediately preceded by a
`/** … */` doc comment.  A minimal form is acceptable:

```cpp
/** C++ response callback delegate; receives an @ref FMyResponse result. */
DECLARE_DELEGATE_OneParam(FMyResponseDelegate, FMyResponse);
```

The comment must go **directly** above the `DECLARE_DELEGATE_*` line (no
blank line between them) and must be inside the `@addtogroup` block for its
feature area (see *Grouping delegates* below).

---

## Enum classes (`enum class E…`)

Every `UENUM` / `enum class` pair must follow this exact layout:

```cpp
/// @addtogroup <GroupName>
/// @{
UENUM(BlueprintType, ...)
/** One sentence describing what this enum represents. */
enum class EMyEnum : uint8 { … };
/// @}
```

Three constraints:

1. **Doc comment between `UENUM` and `enum class`** — not before `UENUM`.
   (`UENUM(…)` expands to blank via `PREDEFINED`; a comment placed before it
   loses its association with the enum after expansion.)

2. **Own `@addtogroup` block** — each enum must have its own `@{`/`@}` pair.
   File-scope enums have no HTML page (SOURCE_BROWSER = NO), so they can only
   be linked if they are group members.

3. **Group name must match a `@defgroup`** declared in `.doxygen/groups.dox`.

---

## Grouping delegates

Delegates must also be inside an `@addtogroup` block so they appear on the
group page and are linkable from function signatures.  Place the block around
the contiguous section of `DECLARE_DELEGATE_*` lines:

```cpp
/// @addtogroup <GroupName>
/// @{
/** C++ response callback delegate; receives an @ref FA result. */
DECLARE_DELEGATE_OneParam(FAResponseDelegate, FA);
/** C++ response callback delegate; receives an @ref FB result. */
DECLARE_DELEGATE_OneParam(FBResponseDelegate, FB);
/// @}
```

---

## Struct / response types

Every `USTRUCT` on the public SDK surface must have a `/** … */` comment with
at least a one-sentence description.  This is also required for Doxygen to
produce a linkable page for the struct.

---

## Maintenance scripts (do not rely on them as the primary workflow)

Three idempotent helper scripts live in `.doxygen/scripts/` and can assist
when adding a batch of new types.  They are **not a substitute for writing
correct comments upfront**:

| Script | What it does |
|---|---|
| `Add-TypeDocComments.ps1` | Adds minimal `/** */` comments to undocumented delegates and a known set of enum classes |
| `Move-EnumDocComments.ps1` | Moves enum doc comments from before `UENUM` to between `UENUM` and `enum class` |
| `Add-EnumGroupTags.ps1` | Wraps enums in `@addtogroup/@{…@}` blocks |
| `Add-DelegateGroupTags.ps1` | Wraps delegate sections in `@addtogroup/@{…@}` blocks |

Run `doxygen .doxygen/Doxyfile` from the repo root to verify, then open
`docs/html/index.html` and confirm the new type appears on its feature group
page and is linked from the function that uses it.
