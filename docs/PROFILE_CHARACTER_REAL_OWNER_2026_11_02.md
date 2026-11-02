# Shared CProfileCharacterSelect source owner

The existing CProfileCharacterSelect declaration in ProfileSubmenus.hpp now
supplies the constructor, update, render and destructor implementations. The
separate constructor/update/lifetime views are removed. Its two sprites use
actual global CSprite and design13C uses shared CDesignBase; GuideOverlay is
already the actual shared owner. CProfileKeyConfig's separate lifetime view is
not changed into a claimed complete owner by this work.

The exact288-byte layout remains. Former view offset checks are retained inside
the constructor, where the private members are accessible: sprites8/A8,
design13C, cursors1B4/1C8 and guide1DC. These are compile-time typedef checks,
not runtime locals or liveness constraints. The method refresh_character_preview
remains a declaration to the existing178-byte native body; its pending scheduler
problem is not reopened or promoted. The deck-launch argument and corresponding
constructor-facing pointer now consistently use CSprite* instead of UiSprite94*.

## Whole method and table evidence

All four existing authored roots retain their full canonical bytes:

- Constructor4487E0/571:893034b950a6791c0fed36650191a92403e85abbfcc42249fbd4174af609dc81.
- Update4485B0/372:f25f404821da46d2ca7656f519c6dfd28ee90d8bb853c4f5d0cdd30ccba64882.
- Render448420/205:61c6e991fbd91a94417e52080fc3ccaff07aa9471d67634af1d5098f5650b92d.
- Destructor448730/164:5b0286e37f90065c294b4ea41c73163c4f51800d01a7c3e0216f1645657c05af.

The actual source table has four roles: deleting wrapper448A20, inherited
Menu no-op41F890, update4485B0 and render448420. Native table6C2150 is identified
by CProfileCharacterSelect RTTI, and its relocation anchor now checks all16
bytes rather than its first4. Actual CSprite RTTI/table and all ten CDesignBase
virtual roles are independently checked from the constructor object. The
source's namespace-qualified outer RTTI is not asserted byte-identical to the
native global type, and this is not a full-program linkage claim.

## Complete exception support

The three selected bodies also retain their complete generated EH code and
metadata, including every named relocation, state, cleanup and flag:

- Constructor: code88 at6B9DA0, metadata76 at6DFA20, handler6B9DDD.
- Destructor: code88 at6B9D40, metadata76 at6DF9D4, handler6B9D7D.
- Update: code38 at6B9A90, metadata44 at6DF7F0, handler6B9A9B.

The update unwind entry precedes FuncInfo by8 bytes, unlike the two lifetime
metadata sections; the audit checks their actual respective layouts. All410
support bytes match without masking and earn no authored credit. Handler
anchors are strengthened to complete27-byte bodies; obsolete constructor/update
view symbols are replaced by the actual method identities.

## Affected scope

Actual include closure is8 units. All12 accepted roots in7 units freshly replay
exact. Both30-byte scalar wrappers in the lifetime unit pass the existing
scoped origin gate; only the CharacterSelect symbol changes, not its physical
owner, extent or hash. Existing KeyConfig188 and menu-state/runtime consumers
remain exact. No generic gate or source-only helper is substituted.

The deck constructor remains2132/native2136 with the same16486e43 candidate;
its7/15 number adapters remain exact. Battle menu update remains892 with the
same8b4c4d52 candidate, verified with fresh before/after header controls. Neither
pending body is promoted. Counts remain1427 exact/443604 bytes,1636 source and
812 units.

Evidence: build/frontier-profile-character-real-members-20261102/, including
replays-accepted/, owner-proof.json, full-eh.json, scalar-wrapper receipt and
before/after controls. The private symbolic EH audit is retained under the
corresponding .analysis scope. Default CI and both diff checks gate the local
checkpoint; no cold corpus replay is needed.
