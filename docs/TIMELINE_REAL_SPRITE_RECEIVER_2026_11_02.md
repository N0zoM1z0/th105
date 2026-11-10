# Timeline loader uses the real sprite receiver

Removed the remaining `TimelineSpriteOptionsView` facade from
`SceneTimelineLoader.cpp`. Its four pivot-setting branches now call the actual
`CSpriteEx::set_texture_options(unsigned, int, int, int, int, int, int)` member
already defined in `EffectSprite.hpp`. The manifest names that real symbol at
the unchanged native provider 0x00407160. No shared-header, layout, argument
arithmetic, compiler flag or provider implementation changed.

Before and after builds both reproduce the complete 1676-byte loader payload
at 0x004540F0, including all dispatch tables, SHA256
b6bb1b77c0258c4c24bf3ff0eeec71ea11409e7f1af88d4d91e0dc13fe1af973.
The callable extent stays 1584 bytes. The compiler combines all four options
branches into one member call: REL32 field 755 names the actual seven-argument
CSpriteEx member; field 607 names its five-argument set_texture member.
The payload verifier now checks those exact relocation roles. Five tests reject
the old facade, unsigned-coordinate signature, wrong relocation kind and
missing/extra calls, while accepting the genuine member calls.

The source hash for the independently proved unsigned-deque pop_back was
renewed only after complete payload equality. Its unchanged provenance gate
freshly validates the 23-byte body and actual range-insertion caller. Both
existing compiler-origin groups (8 and 2 anchors) pass unchanged coverage,
extent and complete-inventory checks. These remain compiler provenance, not
new authored exact credit. No global cold rebuild or aggregate freshness claim.

Source raw SHA256: 5c22d10d25327ca6ff6e47f67d980219ad479e86cfed7ab8ce296e00544d517a.
Counts unchanged: exact authored 1429 / 443911 bytes, source 1634, authored 1653,
excluded 2072, review 302, mapped 1821, units 808.
