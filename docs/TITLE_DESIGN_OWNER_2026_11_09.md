# Title's real design member and color provider

Title construction now uses the shared `CDesignBase` at member offset 0x1DC.
The local five-slot `TitleDesignResource` declaration, opaque storage and empty
texture-manager declaration are removed from this translation unit. Its design
member has the actual IColor base, ten virtual roles, vector, list, map and
iterator. Texture loading uses the existing shared manager declaration.

The color slot also had a concrete linkage gap: `CDesignBase::set_color` was
declared but only a separate profile-view class implemented its native body.
`ProfileRenderListColorRuntime.cpp` now defines the real virtual member using
the same UiDesignObject/IColor interface as the other design methods. Its
complete native 81-byte comparison remains exact, including all three checked
iterator runtime calls. The durable profile-facing address label is retained.

## Original ownership evidence

The pinned Japanese 1.06a Title constructor calls `0x4217F0` at `0x425E79`
with the design member receiver, and calls its object lookup at `0x425F7A`
through `0x40CC50`. The actual emitted CDesignBase methods occupy those two
source call sites. Virtual loading retains slot +0x10.

Native table `0x6C08AC` has ten entries. Its primary COL identifies CDesignBase
and a single zero-offset IColor base. Slot +4 at `0x6C08B0` names `0x40BFE0`,
now implemented by the same class declared in the shared header. Full slot roles,
COL/hierarchy geometry and the 93-byte shared IColor RTTI graph are verified.
The source namespace differs from the native nominal descriptor, so the complete
derived type-name bytes are not claimed identical.

## Complete affected verification

- Title remains exact across all 616 owned bytes: 577-byte callable, three-byte
  alignment and nine-entry switch table. All table targets remain in the body.
- The newly visible implicit design constructor, destructor and deleting wrapper
  match 153, 154 and 30 bytes. They remain compiler-generated support.
- Complete Title EH matches 88 code plus 76 metadata bytes. Design construction
  and destruction each match 57 code plus 60 metadata bytes. Their emitted
  IColor/vector/list cleanup providers also match completely.
- Existing sprite and tile virtual tables and their complete 249/247-byte RTTI
  graphs remain valid.
- The seven-root real design-render/lookup unit remains exact, including the
  121-byte provider now called by Title. The actual color provider is exact81.

Only two configured source units changed. No shared header, compiler profile,
origin pin or matching rule changed; the color file has no other source include
consumers. The outer CTitle constructor-facing layout remains separate from
Title.hpp, whose other legacy design facades are outside this change. There is
no new authored exact credit.

Private before-state snapshots and the complete audit are in the matching
`.analysis/` directory. Tracking, lightweight CI and the diff check pass.

The subsequent outer-owner pass unifies the remaining CTitle declarations,
including the factory and both lifetimes. The focused class header avoids
changing unrelated resource consumers. See `TITLE_OUTER_OWNER_2026_11_09.md`.
