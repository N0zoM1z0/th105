# CSprite: replace raw-vptr code with natural lifetimes

The former UiSpriteCtorProbe manually stored a vtable address. It has been
replaced by actual global CSprite constructor/destructor definitions using the
existing CSprite/CSpriteBase/IColor hierarchy in EffectSprite.hpp. Both bodies
are empty ordinary C++ definitions; base construction initializes texture handle
+4 and the compiler performs virtual-table construction/restoration. No shared
header, register convention, compiler flag or fabricated vptr field is changed.

The complete constructor 40ADA0 remains 16/16 and cleanup 40AD50 remains 7/7.
The derived constructor has no own game-body operations; its initialization is
inherited from CSpriteBase. The cleanup is only IColor vptr restoration. Those
23 bytes are withdrawn from authored totals and retained as compiler lifetimes,
consistent with the already qualified CSpriteEx default/callback entries.
The physical mappings and canonical comparisons are retained, not lost matches.

## Type and caller proof

The actual source emits 24 complete RTTI records covering 273 unique bytes for
CSprite, CSpriteBase and struct-tagged IColor. Repeated descriptors are not
counted twice. The first CSprite deleting slot at 6C0668 points to 40AE80; the
source weak ??_ECSprite auxiliary tag/search-characteristic resolves to its
defined ??_GCSprite, whose complete 31-byte body also compares exactly. This
establishes the scoped lifetime/type relationship, not all rendering vtable
slots or an exclusive original symbol/linker ICF choice.

Constructor 16 is inventory-unique. Cleanup 7 matches both 40AD50 and 421D30.
The real NetworkBase array site 44DC03 selects 40AD50 paired with 40ADA0:
source fields 1/6 are the destructor/constructor and field 36 calls 68A30C.
All 40 bytes match, including count 2, stride 148 and member offset 27C. The
separately proved CSpriteEx callback 421D30 remains its own physical entry.
No duplicate byte identity is silently given another role.

The unique manifest selector for 40AD50 moves from the EffectSprite comparison
unit to the actual CSprite lifetime unit. The remaining effect owner 79 and both
31-byte scalar controls freshly remain exact. Full NetworkBase411/EH197/metadata116
replay passes with the natural CSprite callback declarations.

Twelve tests and 378 unique type/lifetime/caller byte mutations reject old raw-vptr
selectors, changed source/type contracts, wrong weak aliases and wrong callback,
count, stride or member operands. Six actual source/header hashes are pinned.
The shared legacy UiPrimitives file is not globally rewritten in this bounded
change; this constructor owner and the selected sprite lifetime unit no longer
use its handwritten vptr initialization.

Combined accounting with the newly qualified implicit packet cleanup 8:
authored 1429/443911 bytes, source-present1634, authored 1653, excluded 2072,
review 302, mapped 1821 and units 808. No parent, EH, RTTI, scalar or queue-group
support credit is added.
