# CSelect scene entry 0x00421120

Complete783-byte native root is reconstructed using the current shared CSelect
layout and native checked vector/deque containers. The method captures the
match setup, conditionally starts the canonical title BGM, binds both selected
inputs and their cursor pairs, restores random/explicit character positions,
restores stage/music choices, publishes UI visibility and config match id,
then binds both character displays. The three random flags at setup4C..4E are
observed beyond the older bounded MatchSetup prefix; the local view does not
assert a newly constructed object's full extent.

Current candidate is783/native783 but nonexact at+225. At the original checkpoint it was not selected; it has since been selected,
but still has no exact credit. Receipt: build/frontier-421120-20261028/byte-ui-enabled.json.
Target SHA:fe27b3c54058dc2f9a1b5bdb27abb28a87b40fed6698fe48a247a864ada1e76a.

Target-backed lifetime/type refinements:
- The numeric0/1 secondary flag expression materializes an integer before
  publishing its low byte.
- Input pointer is first stored into the scene. Only the non-null branch
  materializes the real pointer value passed by reference to deque push_back.
  The input is reloaded after that call and shared by both cursor bindings.
- Cursor binding uses the ordinary branch form already present in the repo's
  MenuCursorBindings.cpp, retaining null-input behavior.
- The primary UI receiver is captured before flag92 is published. A byte UI
  enabled view preserves the native direct byte copy; a bool source-flag view
  produces identical complete bytes. The original nominal bool/byte spelling
  remains unresolved and no shared layout was changed.

These changes advance the canonical agreeing prefix from47 to225 bytes,
without asserting partial credit. The current residual starts in EBX zero
scheduling across the secondary mode predicate; the candidate puts a shared
zero after the branch while native duplicates it into both outcomes. Its
two-byte length difference is compensated by loop alignment, so equal total
size is not evidence of equality. No invented dependency/volatile/register
forcing is used.

The15-entry character-order table at6E61C8 is freshly pinned. The BGM uses
the existing data/bgm/op.ogg mapping, and the stage music table reuses6288.
Native6183F0 is a block-size4,16-byte-block pointer-deque push_back with
reference input; the caller relocation is supported by that decoded behavior.
No authored or generated helper credit is added for it.

Raw recursive CFG receipt: build/frontier-421120-20261028/boundary.json.
Earlier focused controls are retained beside the current receipt. Only the
new unit was compiled; source headers, global flags and existing callers were
unchanged.

## Source registration, 2026-11-04

The retained complete source is now individually selected and mapped. Its
783-byte original body has 228 reachable instructions and one return; the exact
network-select on-enter method calls it at `426554`. The original whole-body
hash and that edge are pinned by `select-scene-entry-authored-106a`.

A fresh pinned comparison produces the same 783-byte nonexact candidate,
first differing at +225, with canonical SHA-256
`c5a5b8b1dc50bbd2e16c13d84f36263ed6bead06faa0536c0547a9fed2474ef3`.
No equal-size, prefix or game-execution claim is counted as exact. The
specific origin rule was checked directly; no full origin-census replay is
claimed. Receipt: `build/frontier-select-entry-register-20261104/compare.json`.
