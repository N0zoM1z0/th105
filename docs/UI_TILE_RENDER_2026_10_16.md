# UI tile renderer: complete source, pending exactness

## Observed target facts

Only the original Japanese TH10.5 v1.06a executable was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`UiTileA4_render @ 0x004099F0` owns `[4099F0,409CE4)`, **756 bytes**,
body SHA-256 `c521a6318217f285e593bff562969f8b7b7ef4687b7e26884df446cb476416eb`.
A fresh recursive raw decode reaches all **246 instructions / 756 bytes**,
including **184 x87 instructions**, with one `RET 0x10` at `409CE1` and no
external direct jumps. The following bytes are INT3 alignment. The existing
authored-origin rule independently pins this body and its exact UI caller at
`454939` inside `ScenarioResultResource::render @ 454890`.

One direct Ghidra headless process reopened the existing private project,
attested the executable hash, image base, PE entry, external-entry marker,
x86 Windows analysis identity, entire mapped `.text`, and this callable's
bytes. It applied the four explicit arguments and saved the working signature.
A second sequential, read-only process independently checked the saved name,
756-byte extent, `__thiscall`, void return hypothesis, five parameters including
the implicit receiver, and 16-byte purge. Full mapped `.text` SHA-256 remains
`f5cb09ff0a54362356d8c4cce853cbcb14552499cce12cf7390d0868db9ebe97`.
Decompiler output is only a hypothesis; raw instructions establish the facts
below. Both runs used a 768 MiB Java heap limit and two active processors.
No factory adapter or IDA analysis was used. The mandatory IDA preflight still
finds the wrong executable, SHA-256 beginning `10350095`.

The explicit stack arguments are **float x, float y, signed int column,
signed int row**. The first two are loaded by `FLD`; the latter by signed
`FILD`, with integer increments for the opposite UV edges. Receiver fields:

| Offset | Physical role established by access/dataflow |
| --- | --- |
| `04` | packed texture handle |
| `08..77` | four 0x1C vertices: x/y/z/rhw/color/u/v |
| `78/7C` | rectangle width/height |
| `80/84` | pivot x/y |
| `88/8C` | scale x/y |
| `90` | angle passed to the quantized orientation helpers |
| `94/98` | UV origin |
| `9C/A0` | UV step per column/row |

The renderer subtracts half a pixel after scaled-pivot displacement. It
materializes float left/top/right/bottom and UV edges, then shares those
rounded values across the four vertices. A nonzero or unordered angle takes
the rotation path: cosine call `409B32 -> 4063D0`, sine call
`409B44 -> 406360`, with each returned value stored as float. All four points
rotate about the original x/y arguments. Source keeps the target's observed
sum associations, including its final vertex's cosine-first y product.

Texture handle zero unconditionally invokes SetTexture(0, null); a matching
nonzero cached handle bypasses binding. A changed nonzero handle calls
`409C8F -> 417800`, dereferences the returned resource cell and binds it.
The manager is `702798`, its stage-zero cache is `7027FC = manager+64`, and
the texture-binding device pointer is at `7036C0`. The draw device is the
existing RenderModeManager member at `6FA220 = 6FA21C+4`. Calls at `409CC3`
and `409CDA` select FVF `0x144` and submit triangle strip type 5, two
primitives, four vertices at receiver+8, stride `0x1C`. COM slot offsets
`104/164/14C` agree with the existing SetTexture/SetFVF/DrawPrimitiveUP ABI.

## Source and strict comparison

`src/ui/UiTileRender.cpp` contains the complete ordinary C++ implementation,
an isolated physical view, and layout assertions. Existing caller and
constructor facades are separate contracts. In particular the unselected
`UiTileA4::render(int,int,float,float)` declaration in UiPrimitives.hpp is
not evidence for this target's argument order. Existing exact callers already
use the supported `(float,float,int,int)` views; no shared header was changed.

Reproduce the current pending body without adding it to the accepted manifest:

```bash
TH105_FP_MODE=strict bash scripts/compile-unit.sh \
  src/ui/UiTileRender.cpp build/tile-render-final.obj
python3 scripts/compare-function.py 0x004099F0 build/tile-render-final.obj \
  --symbol-base '?render@UiTileRenderView@th105@@QAEXMMHH@Z' \
  --rel32-target '?lookup_token@CHandleManager4@th105@@QAEPAPAXI@Z=0x00417800' \
  --rel32-target '?lookup_orientation_cosine_quantized_abs@th105@@YANM@Z=0x004063D0' \
  --rel32-target '?lookup_orientation_sine_quantized_abs@th105@@YANM@Z=0x00406360' \
  --dir32-target '?g_ui_tile_texture_manager@th105@@3UCHandleManager4@1@A=?g_title_resource_manager@th105@@3UTitleResourceManager@1@A' \
  --dir32-target '?g_ui_tile_texture_device@th105@@3PAUD3DDevice9@1@A=?g_title_texture_cache_host@th105@@3PAXA' \
  --dir32-target '?g_render_mode_manager@th105@@3URenderModeManager@1@A=g_render_mode_manager_device_base' \
  --json
```

Result: **756-byte candidate / 756-byte target, nonexact at +2**. The target
reserves 12 bytes; source reserves eight. Before texture binding at `+270`,
all 201 instructions occupy the same offsets and have the same operations,
registers, literals and edges. There are 53 differing instructions in that
region, consisting solely of frame allocation and corresponding ESP-relative
homes. This is diagnostic normalization, **not canonical exact credit**.
The remaining tail additionally differs in SetTexture and SetFVF method-load,
push and register scheduling. The final four-argument return contract agrees.

Recorded controls, all bounded and sequential:

- Direct member rereads under ordinary FP: 686 bytes. Strict FP with local
  exception scheduling disabled: 714 bytes. Restoring real shared float
  edge locals, and using member accesses instead of a pervasive quad alias,
  gives the current 756-byte instruction topology and receiver allocation.
- Plain strict exception scheduling: 748 bytes. Local fenv_access(on) and
  moving the real cosine/sine/old-position declarations outside the branch
  are each byte-neutral relative to the 756-byte control.
- Restoring ordinary bind_texture and submit_textured_primitive source calls
  in one probe leaves bind_texture out of line: 692 bytes, first difference
  still +2. Adding ordinary `inline` to the binder does not change that.
  This does not establish the original inline/TU boundary or justify forced
  inlining, fake stack storage, register forcing, or a global compiler change.

Private scripts, Ghidra hypotheses and reports are under
`.analysis/tile-render-20261016/` and `build/tile-*`; the commands above are
the durable reconstruction reproduction. The root advances to **source-present**
only. No match-unit or matches.csv entry is added. Original TU/compiler-phase
provenance, the extra four-byte frame reservation, and the tail call scheduling
remain unknown. The quantized helpers' original return spelling remains
underconstrained; this caller observes their explicit float materialization.

## TH075 cross-check

TH075's locally recorded math-table evidence (`docs/KNOWLEDGE_BASE.md`, R182)
describes the same 3600-entry / tenth-degree / 900-phase family at
`41CAE0/41CB40/41CB70`. Its lookups convert to integer before integer abs;
TH105's float-phase helpers use floating abs before conversion. This supports
a shared engine-policy lead, not source identity, compiler-profile transfer,
or TH105 exactness. No TH075 files were modified.
