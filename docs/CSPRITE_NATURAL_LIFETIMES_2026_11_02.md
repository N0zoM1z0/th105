# CSprite: replace raw-vptr code with natural lifetimes

The former UiSpriteCtorProbe manually stored a vtable address. It has been
replaced by actual global CSprite constructor/destructor definitions using the
existing CSprite/CSpriteBase/IColor hierarchy in EffectSprite.hpp. Both bodies
are empty ordinary C++ definitions; base construction initializes texture handle
+4 and the compiler performs virtual-table construction/restoration. No shared
header, register convention, compiler flag or fabricated vptr field is changed.

The complete constructor40ADA0 remains16/16 and cleanup40AD50 remains7/7.
The derived constructor has no own game-body operations; its initialization is
inherited from CSpriteBase. The cleanup is only IColor vptr restoration. Those
23 bytes are withdrawn from authored totals and retained as compiler lifetimes,
consistent with the already qualified CSpriteEx default/callback entries.
The physical mappings and canonical comparisons are retained, not lost matches.

## Type and caller proof

The actual source emits24 complete RTTI records covering273 unique bytes for
CSprite, CSpriteBase and struct-tagged IColor. Repeated descriptors are not
counted twice. The first CSprite deleting slot at6C0668 points to40AE80; the
source weak ??_ECSprite auxiliary tag/search-characteristic resolves to its
defined ??_GCSprite, whose complete31-byte body also compares exactly. This
establishes the scoped lifetime/type relationship, not all rendering vtable
slots or an exclusive original symbol/linker ICF choice.

Constructor16 is inventory-unique. Cleanup7 matches both40AD50 and421D30.
The real NetworkBase array site44DC03 selects40AD50 paired with40ADA0:
source fields1/6 are the destructor/constructor and field36 calls68A30C.
All40 bytes match, including count2, stride148 and member offset27C. The
separately proved CSpriteEx callback421D30 remains its own physical entry.
No duplicate byte identity is silently given another role.

The unique manifest selector for40AD50 moves from the EffectSprite comparison
unit to the actual CSprite lifetime unit. The remaining effect owner79 and both
31-byte scalar controls freshly remain exact. Full NetworkBase411/EH197/metadata116
replay passes with the natural CSprite callback declarations.

Twelve tests and378 unique type/lifetime/caller byte mutations reject old raw-vptr
selectors, changed source/type contracts, wrong weak aliases and wrong callback,
count, stride or member operands. Six actual source/header hashes are pinned.
The shared legacy UiPrimitives file is not globally rewritten in this bounded
change; this constructor owner and the selected sprite lifetime unit no longer
use its handwritten vptr initialization.

Combined accounting with the newly qualified implicit packet cleanup8:
authored1429/443911 bytes, source-present1634, authored1653, excluded2072,
review302, mapped1821 and units808. No parent, EH, RTTI, scalar or queue-group
support credit is added. See NETWORK_BASE_NESTED_EH_OWNER_2026_11_02.md.
