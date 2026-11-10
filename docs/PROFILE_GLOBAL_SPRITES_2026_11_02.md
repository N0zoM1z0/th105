# Actual shared profile sprites, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

The shared cursor, profile-message sprite and character-list background now use
actual CSprite declarations in ProfileUiInfrastructure.hpp. ProfileSpriteView,
MenuCursorSpriteView and the partial texture virtual-call interface are removed.
Cursor scale writes use named fields, eliminating byte-offset reinterpretation.
The existing 0x406A60 / 39-byte texture wrapper is now the real
CSprite::set_texture method and directly calls its virtual set_texture_options
with zero pivots. This changes neither its destination nor its whole body.

The three canonical globals at 0x6E6958, 0x6E69F0 and 0x6E6B30 all start with
CSprite table 0x6C0668; cursor scale fields at +0x88/+0x8C are zero in the pinned
image. These are external declarations, not new allocations or initializers.
The global and method relocations now use actual CSprite symbols while retaining
the existing independently qualified allowlist keys and native addresses.
No full-program linkage or unique original source-file placement is asserted.

Actual include closure is eight units. All 22 accepted roots in seven units
remain canonical in serial before/after and final adopted replays. They include
the 39-byte texture wrapper, cursor rendering, profile UI initialization,
message/result setup and shared rendering. All compared hashes are unchanged,
including the pending 2521-byte deck renderer. There is no new authored credit,
compiler flag change, manual vptr, fake ABI or inlining barrier.

Final CI passed all 962 tests in 109.603 seconds. Both diff checks gate the local
checkpoint. Counts remain 1426 exact / 443399 bytes, source 1636, authored 1655,
mapped 1826, excluded 2075, review 297 and units 813.
