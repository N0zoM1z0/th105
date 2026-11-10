# The scene-base member is a fade pointer

`CSceneBase` now stores a `CFade *` at +4, and Opening writes its color through
that actual class. The old integer `scene_id` and pointer round-trip are gone.
The C-linkage binding name `g_active_scene_id` remains as a historical symbol,
but its declaration now has the correct pointer type. Its address and every
existing relocation binding are unchanged.

## Native value flow

The pinned Japanese 1.06a executable establishes the complete chain:

- WinMain allocates twelve bytes at `6659E1`, installs the RTTI-owned `CFade`
  table `6C74C4` at `6659EF`, and puts the pointer in the startup options.
- Application bootstrap loads that secondary callback at `407DD5` and stores
  it at application +78 at `407DDD`. With singleton `702820`, this is `702898`.
- Opening, Title, Select and SelectScenario constructors read `702898` and
  copy it into their `CSceneBase` member at +4. The relevant reads are
  `41F99F`, `425E23`, `4231E8` and `425383`.
- Opening update loads this member at `41F873` and writes `00FFFFFF` through
  pointer +4 at `41F876`. This is `CFade::color_04`, not a scene number.

The native CFade table has its five established entries at `41E240`,
`41F890`, `41E250`, `41E270` and `41E290`. The corrected scene header only
forward-declares CFade; the Opening implementation includes its existing real
class declaration. No new facade, cast, virtual method or layout padding is
introduced.

## Affected comparison

The source review finds 22 implementation files using the actual scene-base
family, reached by 27 configured units. Another 150 units merely include the
header without using that family. Two of those, texture loading and application
shutdown, were rebuilt as controls instead of rebuilding that entire include
closure.

All 29 before/after units have identical code, owned data, EH/RTTI sections and
relocations: 3,482 non-debug COFF sections compare equal. Complete canonical
root comparisons retain 36 exact results and the same nine nonexact results.
Opening update remains 52/52, its constructor 130/130, Title's complete extent
616/616, SelectScenario's constructor 862/862 and the factory 1064/1064. The
existing Title/member/factory audit also rechecks all 1,105 owned EH bytes and
their complete tables. Select's pre-existing nonexact work remains unchanged.

Input-migration changes, source pins and exact ledgers are untouched.

## Application callback route review

The prior Application initialization candidate still has no supported strict
selection path. The generic `linked_lifecycle` global witness requires a
separate same-class destructor, cleanup EH and a five-byte callback tail.
The observed callback directly performs all 73 bytes of no-EH member cleanup.
`linked_global_caller` requires that same fully witnessed parent; the private
cleanup route requires a caller EH funclet. Neither supplies the missing global
callback form. The texture-service lifecycle route is explicitly bound to its
own 84-byte aggregate and distinct ten-byte callback, so it cannot be reused
for Application. No acceptance retry or validator change was made.

Follow-up, 2026-11-10: the observed inline cleanup now has a complete strict
global-lifecycle proof, and the Application constructor is selected and locally
canonical exact. See `docs/APPLICATION_INLINE_CLEANUP_2026_11_10.md`.
