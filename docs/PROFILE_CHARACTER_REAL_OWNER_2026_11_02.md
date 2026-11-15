# Shared CProfileCharacterSelect source owner

The existing CProfileCharacterSelect declaration in ProfileSubmenus.hpp now
supplies the constructor, update, render and destructor implementations. The
separate constructor/update/lifetime views are removed. Its two sprites use
actual global CSprite and design 13C uses shared CDesignBase; GuideOverlay is
already the actual shared owner. CProfileKeyConfig's separate lifetime view is
not changed into a claimed complete owner by this work.

The exact 288-byte layout remains. Former view offset checks are retained inside
the constructor, where the private members are accessible: sprites 8/A8,
design 13C, cursors 1B4/1C8 and guide 1DC. These are compile-time typedef checks,
not runtime locals or liveness constraints. The method refresh_character_preview
remains a declaration to the existing 178-byte native body; its pending scheduler
problem is not reopened or promoted. The deck-launch argument and corresponding
constructor-facing pointer now consistently use CSprite* instead of UiSprite94*.

## Whole method and table evidence

All four existing authored roots retain their full canonical bytes:

- Constructor 4487E0/571:893034b950a6791c0fed36650191a92403e85abbfcc42249fbd4174af609dc81.
- Update 4485B0/372:f25f404821da46d2ca7656f519c6dfd28ee90d8bb853c4f5d0cdd30ccba64882.
- Render 448420/205:61c6e991fbd91a94417e52080fc3ccaff07aa9471d67634af1d5098f5650b92d.
- Destructor 448730/164:5b0286e37f90065c294b4ea41c73163c4f51800d01a7c3e0216f1645657c05af.

The actual source table has four roles: deleting wrapper 448A20, inherited
Menu no-op41F890, update 4485B0 and render 448420. Native table 6C2150 is identified
by CProfileCharacterSelect RTTI, and its relocation anchor now checks all 16
bytes rather than its first 4. Actual CSprite RTTI/table and all ten CDesignBase
virtual roles are independently checked from the constructor object. The
source's namespace-qualified outer RTTI is not asserted byte-identical to the
native global type, and this is not a full-program linkage claim.

## Complete exception support

The three selected bodies also retain their complete generated EH code and
metadata, including every named relocation, state, cleanup and flag:

- Constructor: code 88 at 6B9DA0, metadata 76 at 6DFA20, handler 6B9DDD.
- Destructor: code 88 at 6B9D40, metadata 76 at 6DF9D4, handler 6B9D7D.
- Update: code 38 at 6B9A90, metadata 44 at 6DF7F0, handler 6B9A9B.

The update unwind entry precedes FuncInfo by 8 bytes, unlike the two lifetime
metadata sections; the audit checks their actual respective layouts. All 410
support bytes match without masking and earn no authored credit. Handler
anchors are strengthened to complete 27-byte bodies; obsolete constructor/update
view symbols are replaced by the actual method identities.

## Affected scope

Actual include closure is 8 units. All 12 accepted roots in 7 units freshly replay
exact. Both 30-byte scalar wrappers in the lifetime unit pass the existing
scoped origin gate; only the CharacterSelect symbol changes, not its physical
owner, extent or hash. Existing KeyConfig188 and menu-state/runtime consumers
remain exact. No generic gate or source-only helper is substituted.

The deck constructor remains 2132/native2136 with the same 16486e43 candidate;
its 7/15 number adapters remain exact. Battle menu update remains 892 with the
same 8b4c4d52 candidate, verified with fresh before/after header controls. Neither
pending body is promoted. Counts remain 1427 exact/443604 bytes,1636 source and
812 units.

Default CI and both diff checks gate the local checkpoint; no cold corpus replay is
needed.
