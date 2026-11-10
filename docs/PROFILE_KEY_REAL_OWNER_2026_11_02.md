# Actual CProfileKeyConfig owner

CProfileKeyConfig now uses the same declaration for construction, rendering,
update and destruction. Its design8 is shared CDesignBase; tiles40/E8 are global
CTile. The local design-load, tile-render and capture-call receiver views are
removed in favor of ordinary member calls. capture_key_input remains a private
declaration to the pending790-byte native body; its old785-byte SETNE/shared-tail
comparison and prior CIL controls are not reopened by this scope.

Both profile submenu destructors now use their actual shared classes, so the
obsolete ProfileSubmenuLifetime.hpp is removed. The KeyConfig scalar-wrapper
selector is renamed to the actual emitted member; its native owner/hash stay
unchanged. Tile.hpp now includes minimal engine/Sprite.hpp rather than pulling
Collision/GameMode declarations through EffectSprite.hpp. Tile definitions,
layout and algorithms do not change, and no incompatible MatchSetup views are
merged. The three affected source-pin groups are refreshed after full proofs.

## Canonical methods and ownership

The existing four complete authored bodies remain exact:

- Constructor44BA90/567:46f1573be4b7f93ea164565fdd9b84b35e297d210fdef62d7b7c743dd28c7555.
- Render44B340/501:205363072c252da518fca971d36487e1209e7b55c81a7a3f26de6225fb8efb47.
- Update44B860/355:1c80fe67804060a7195a01ff134ff599da3ed6cd3865b1dd043d2c3e95e9459e.
- Destructor44B9D0/188:f7b22ef50ee434b5349f30cab127cccde0cffbe698cc4f32390cc82ca62bef92.

Native table6C22EC is identified by CProfileKeyConfig RTTI and now attests all16
bytes: deleting44BCD0, inherited Menu41F890, update44B860 and render44B340.
The constructor object supplies those actual source roles, the complete247-byte
CTile RTTI graph/four-slot table and all ten design virtual roles. Source outer
namespace RTTI identity and full-program linkage are not claimed.

## Complete generated exception support

Constructor EH code98 at6BA060 and metadata76 at6DFBE4 match in full, including
handler6BA0A7. Destructor code98 at6B9FF0 and metadata76 at6DFB98 also match,
including handler6BA037. Every relocation, cleanup, callback, state and flag is
replayed without masking. The two-tile cleanup jumps resolve to the shared
40AD50 lifetime body; this does not prove an exclusive original CTile/CSprite
physical identity. The Guide array cleanup keeps its actual callback/stride/count.
The two handler anchors are strengthened to27 complete bytes. All348 support
bytes receive no authored credit.

## Scope and checks

Actual include closure is23 units. All17 accepted roots across12 units freshly
replay exact; the19 other configured roots in13 units preserve fresh before/after
hashes. The scalar-wrapper gate passes2/60, generic implicit lifetime17/1434 and
implicit design2/307 pass, and the CSpriteEx/default gate retains full Select
EH461/metadata188. Select render4, character12 and profile preview6 guarded
finite cases/negative controls pass without claiming runtime/helper execution.

No source/exact count changes:1427 exact/443604 bytes, source1637 and813 units.
Default CI and both diff checks gate the local checkpoint.
