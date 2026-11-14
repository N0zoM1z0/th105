# Title-screen rendering

The RTTI-owned `CTitle` virtual table points to `0x00425740`, the complete
417-byte title-screen renderer. The raw boundary audit reaches all 117 native
instructions. The source uses the established `CTitle` members and retains
all three cosine calls, including the first whose result is discarded, the
color conversions, selected sprite scaling and 12 menu tile renders.

A fresh pinned VC8 build emits 417 bytes, but strict comparison differs first
at +232 because the selected-index load is scheduled before the sprite scale
stores. Equal length is not exactness; no exact bytes are added. This source
has not been exercised in a live game or graphics session.

## 2026-11-14: exact

`CTitle::render` at 0x425740 is canonical exact, 417/417. Two source shapes
mattered:

- The target stores the 1.5/1.0 scale through the materialized `&color_a4`
  pointer (EDI), after reserving the render arguments. An inline
  `CSprite::set_scale(float, float)` reproduces that; direct `color_a4.scale_x_88`
  stores address the fields from `this`.
- The 12-row loop walks `menu_items_224` and addresses the wave offsets relative
  to it. Writing `menu_item_wave_offsets[i] + menu_items_224[i]->x` without a `row`
  local reproduces it; with the local, VC8 bases the loop on the offsets array.
