# Actual CTile owner and inherited interface

## Scope and native identity

`src/ui/Tile.hpp` declares the actual global CTile, directly derived from the
existing CSpriteBase and IColor, with nine float fields at80..A0 and sizeA4.
Native vtable6C0718 has exactly four inherited slots: scalar40AE80,
set_color40AC50, vertex_colors40AC70 and multiply_color40AC90. The word at
6C0728 belongs to the following COL, not a fifth tile virtual method.
Texture setters and render are nonvirtual. The seven-argument setter uses
signed x/y/width/height/pivots, already independently established by the
canonical266-byte implementation; its ABI is unchanged here.

The complete source-emitted RTTI graph matches247 unique native bytes,
including CTile, CSpriteBase and IColor. The emitted deleting weak external
resolves to the actual31-byte scalar body, also canonical. These supporting
regions do not earn authored bytes.

## Source consolidation

- FileListFinalize now constructs a real CTile and uses its normal implicit
  copy through the existing deque operation. It no longer declares a local
  FileListRenderTile surrogate.
- UiTileTexture now implements actual CTile::set_texture directly, forwarding
  two zero pivots. Whole37 bytes at4098B0 remain exact.
- UiTileRender now implements actual CTile::render over the inherited vertex
  array; physical/raw vptr render view removed. No frame/register forcing.
- The old CTileCopyLifetime.cpp artificial copy-only probe is removed. Existing
  `gpt-web-ctile-copy-lifetime` now compiles the real FileListFinalize owner,
  ordinary /O2 and GS enabled, selecting its implicit164-byte copy4396A0.
- Legacy CNumberTileA4, UiTileA4 and FileListTile views elsewhere remain. This
  scope does not claim those owners are unified or their TU partition recovered.
- Existing shared EffectSprite/IColor headers are unchanged; no wide include
  closure invalidation. Only the three owner sources and new Tile header change.

The private actual-owner comparison preserved exact wrapper37, copy164 and
Growmap341. The ordinary complete page root stays1155/native1106. Native copy
call43A914 and one real source call select the same canonical implicit body.
Full page remote EH equality is not claimed.

The strict-FP render source is756 bytes both before and after, byte-identical
SHA256 `d07d00e4dd3183071fce35c2fd4567568b1edf70a5629763248c5caeac38a3cf`.
Target SHA256 remains
`c521a6318217f285e593bff562969f8b7b7ef4687b7e26884df446cb476416eb`.
Native12/source8 frame and COM scheduling remain unresolved. The renderer is
now reproducible in `exact-first-ctile-render`, not newly source-present or
exact. A preliminary private build accidentally selected default FP and
emitted728 for both forms; it was not used as the strict-FP proof. Corrected
before/after provenance explicitly records the strict profile.

## Verification and accounting

- Fresh formal wrapper37/copy164/Growmap341 comparisons pass.
- Full page1155/1106 and render756/756 comparisons remain explicit mismatches.
- `audit-ctile-real-owner.py`: full RTTI247, table16, weak fallback/scalar31,
  copy164, wrapper37 and actual native/source copy ownership pass.
- Existing unchanged generic implicit-lifetime gate freshly validates17 roots,
  1434 bytes; source pins now point to the actual owner/Tile/base/color headers.
- Existing unchanged Growmap gate freshly validates341, with actual CTile
  decorated symbols. Thresholds, matching rules and origin policy unchanged.
- Five table tests reject extra slots, wrong roles, hidden addends and each
  of16 one-byte native-slot mutations.
- No matches.csv or function-origins.csv changes. Exact1429/443911,
  source1636/authored1655/mapped1823/review300/excluded2072 stay. Units812.

Evidence: `.analysis/frontier-ctile-real-owner-20261102/` and
`build/frontier-ctile-real-owner-20261102/`. Native work serial CPU0/nice10,
original pinned target, no IDA semantics or push.
