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
submission. It uses a pointer-only `BattleObjectRenderTailView` with asserted
vertex, texture and fade offsets; it does not construct that partial view or
claim the original class name. Existing target-bound texture and render
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
