# Battle overlay rendering: exact 670-byte body

`BattleObjectManager_render_tail` at `4666A0` is now canonical exact
670/670 against the original Japanese 1.06a target. The configured unit
`exact-first-battle-render-tail-typed` and an independent fresh VC8 object
both reproduce the complete target SHA-256
`916c2058290c838da9b3a11d5ba076df2b0b0156f3ba375a3b314058f656a40f`.
No alignment, switch metadata or adjacent function bytes are included. The
full target closes 177 reachable instructions and all 670 bytes, including
its one return, five direct calls and seven indirect effect-interface calls.
The previously exact phase method at `466980` tail-jumps to this body at
`4669DE`; the original body and edge were independently pinned in the prior
`battle-overlay-render-authored-106a` origin checkpoint.

The ordinary C++ source keeps the observed fade gate, texture fallback and
size lookup, four vertex positions and texture coordinates, two texture binds,
color/alpha publication, two effect vectors, D3DX effect calls and primitive
submission. It is now defined on the existing `BattleObjectManager` source type, whose
vertex array and existing texture and fade fields have asserted native sizes
and offsets. The caller and provider emit the same real C++ member symbol;
this does not establish the original class name. Existing target-bound texture and render
providers retain their independent match status; this root does not give them
new credit.

The earlier probe called a manually exposed effect vtable and remained
nonexact despite a 491-byte prefix. The source now invokes the actual D3DX
COM virtual methods. The already-used reset interface was moved unchanged into
`D3DXEffectInterface.hpp` and shared by both clients; its inherited IUnknown
prefix and method order are corroborated by the installed `d3dx9effect.h`.
The rendering calls use `SetVector`, `CommitChanges`, `Begin`, `BeginPass`,
`EndPass` and `End` at their observed slots. No synthetic register, assembly,
manual vtable, dummy storage or compiler-flag change was used. Correct source
interface and target-backed lifetimes naturally produce the exact result.
This does not establish a full effect implementation or original TU layout.

Reproduction and scope:

- `scripts/repo-python scripts/build.py --unit exact-first-battle-render-tail-typed --compare --json`
  gives the complete exact 670-byte body.
- A separate `scripts/compile-unit.sh` build followed by
  `scripts/compare-function.py` independently gives the same full hash;
  receipts are in `build/frontier-render-tail-typed-20261104/`.
- All five `gpt-web-battle-base-effect-lifetime` bodies remain exact after
  sharing the interface. Nine accepted `cross-v106a-battle-object-manager-runtime`
  bodies, including the exact phase caller, also replay exact. That unit's
  separate `466F40` body remains nonexact and makes the whole unit report
  mismatch; it receives no new credit.
- All 1,018 target-independent project CI tests and the tracking/whitespace
  checks passed on the resulting tree. No whole-corpus cold replay, actual D3D execution, or
  gameplay claim is made.

## Shared real owner, 2026-11-04

The initially accepted partial receiver view has been replaced with the
existing `BattleObjectManager` owner. Its former 0x90-byte opaque render area is
now four typed 0x24-byte vertices, preserving the asserted 0x118-byte manager
layout and existing field offsets. The real caller's unresolved member symbol
now has an actual source definition; a full integrated link is not claimed.

A fresh independent cold build still matches the entire 670-byte original
body. Dependency inspection found eight affected units with 18 accepted roots;
all 18 replayed exact. The manager unit's separate `466F40` remains nonexact
with its prior complete candidate hash unchanged. No new matching bytes are
added by this owner cleanup. See `build/frontier-battle-overlay-real-owner-20261104/`.

## Real-provider linked diagnostic, 2026-11-04

A separate private CIL image now links the actual `BattleObjectManager`
overlay source with the real texture query, resource lookup, texture binding
and render primitive sources. The real rectangle and line source files are
also linked to satisfy the full primitive object's references. The diagnostic
image has no fake executable-address provider or fabricated return. It links
successfully, but its LTCG overlay body is 676 bytes and differs at entry due
to an aligned frame; it does not reproduce the target. It also does not include
the manager phase caller, so this is not a full application integration or an
exact linked-image claim. The independent 670/670 ordinary COFF match remains
the accepted evidence; the separately nonexact providers gain no credit.

Receipt and real-source build recipe:
`build/frontier-overlay-real-cil-20261104/run2.log` and
`.analysis/frontier-overlay-real-cil-20261104/`. The initial attempt lacked the
real rectangle provider and failed to link; it was resolved by adding the
existing rectangle and line sources, not by adding stubs.
