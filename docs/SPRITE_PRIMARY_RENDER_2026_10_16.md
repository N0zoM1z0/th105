# CSprite primary render slots: complete source and bounded COM residuals

## Observed target and ownership

Only the original Japanese TH10.5 v1.06a executable was inspected, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Two complete CSprite primary-vtable entries were still origin-review candidates:

| Address / callable | Primary slot | Bytes | Body SHA-256 |
| --- | --- | ---: | --- |
| `406BE0..406E42` | `6C0668+1C` | 610 | `fa3b6f746fe5529b57abb6f24113ce3f6c33c54f781f975db13b7b89ccc829bf` |
| `406E50..4070B2` | `6C0668+20` | 610 | `6c528e876bc6405bec90252d098e7964d2d3817159e098838b794500ffa8a5be` |

Each has **210 reachable instructions**, **154 x87 instructions**, one
`RET 8`, no external direct jump and 14 subsequent INT3 bytes. After
normalizing internal branch addresses, the two targets differ in exactly one
instruction: `PUSH 0x144` versus `PUSH 0x4142`, at function offset `235`.
The second name records this FVF literal without assuming a rendering mode.

Independent authored identity comes from the exact-backed CSprite constructor
`40ADA0`, whose immediate at `40ADAB` publishes vtable `6C0668`, and the
canonical exact `Menu::render_cursor @ 43F9D0`, which calls `406BE0` at
`43F9FF`. Both constructor and caller were rebuilt: **16/16** and **55/55**
canonical exact. The two vtable dwords, full root hashes, caller edge and six
direct game-helper edges are pinned by the new origin rule. This assigns two
authored roots / 1,220 bytes independently of source matching.

```bash
python3 scripts/audit-sprite-render-family.py
python3 scripts/build.py --unit gpt-web-ui-sprite-lifetime --compare --json
python3 scripts/build.py --unit cross-v106a-menu-render-cursor --compare --json
```

The audit replays target identity, complete CFGs, return purge, padding,
constructor/vtable/caller evidence and the whole target-to-target comparison.
Its JSON under `build/` is diagnostic evidence, never partial exact credit.

## ABI, geometry and Ghidra

Both roots take `this` in ECX and two float stack arguments x/y, with no
other explicit arguments. The existing 0x94 sprite physical layout is
corroborated by four 0x1C vertices at +8, dimensions +78/+7C, pivots +80/+84,
scales +88/+8C and angle +90. The source view names these fields locally and
does not change shared constructor or runtime headers.

Both targets compute rounded float left/top/right/bottom edges after scaled
pivot displacement and a half-pixel subtraction. A nonzero/unordered angle
calls the quantized cosine and sine helpers, materializes each result as
float, and rotates all four vertices around the original x/y arguments.
Color, depth, rhw and UV fields remain untouched. The texture path clears stage
zero for a zero handle, skips a cached nonzero handle, or resolves and binds a
changed handle through `417800`. The final draw uses two triangle-strip
primitives, receiver+8, stride 0x1C and the root-specific FVF literal.

Sequential direct Ghidra sessions attested executable SHA, image base, PE
entry and external-entry marker, x86 Windows analysis identity and full mapped
`.text` before saving each 610-byte function and its two-float thiscall
signature. A fresh read-only session verified both names, extents, void return
hypotheses, receiver plus two float parameters, purge eight and the two body
hashes. All processes used a 768 MiB heap and two active processors. Ghidra
pseudocode remains a hypothesis; the instruction review and complete source
comparison provide independent evidence. No factory adapter was used; the
mandatory IDA preflight failed its target hash and that database was not used.

## Source and comparison

`src/ui/SpriteRender.cpp` provides both complete ordinary C++ methods. Build:

```bash
TH105_FP_MODE=strict bash scripts/compile-unit.sh \
  src/ui/SpriteRender.cpp build/sprite-render-family.obj
python3 scripts/compare-function.py 0x00406BE0 build/sprite-render-family.obj \
  --symbol-base '?render@SpriteRenderView@th105@@QAEXMM@Z' \
  --rel32-target '?lookup_token@CHandleManager4@th105@@QAEPAPAXI@Z=0x00417800' \
  --rel32-target '?lookup_orientation_cosine_quantized_abs@th105@@YANM@Z=0x004063D0' \
  --rel32-target '?lookup_orientation_sine_quantized_abs@th105@@YANM@Z=0x00406360' \
  --dir32-target '?g_sprite_texture_manager@th105@@3UCHandleManager4@1@A=?g_title_resource_manager@th105@@3UTitleResourceManager@1@A' \
  --dir32-target '?g_sprite_texture_device@th105@@3PAUD3DDevice9@1@A=?g_title_texture_cache_host@th105@@3PAXA' \
  --dir32-target '?g_render_mode_manager@th105@@3URenderModeManager@1@A=g_render_mode_manager_device_base' \
  --json
```

For the other root change the address to `0x00406E50` and symbol to
`?render_fvf4142@SpriteRenderView@th105@@QAEXMM@Z`; the other mappings agree.
Both report **610-byte source / 610-byte target, nonexact at +0x21D**.
The complete first **541 bytes** are canonical equal, including all geometry,
rotation, stack homes, branch displacements, return-consumer rounding and the
zero/cache gates. The remaining differences are SetTexture and SetFVF
vtable/method-register allocation and load/push scheduling. Full canonical
function equality is still required; none of the prefix earns exact credit.

Local size optimization produced 626 bytes and a non-target EBP frame. A
private COM view using the native BaseTexture pointer and DWORD parameter
types generated the same complete comparison bytes as the clean source.
The current pinned SDK's BaseTyps/ObjBase declarations also confirm ordinary
virtual stdcall COM methods; newer MinGW's default nothrow macro must not be
silently transferred to this VC8 contract. No shared interface or global
compiler profile was changed.

This family establishes a useful distinction from the
[tile renderer](UI_TILE_RENDER_2026_10_16.md): here the 16-byte frame, all
geometry and all floating lifetimes match. The tile's extra four-byte frame
reservation remains a separate original-TU/compiler-phase unknown. Similarly,
the [SpriteEx finalizer](SPRITE_RENDER_FINALIZER_2026_10_16.md) already matches
its own final COM tail but differs in handle-load scheduling; these are local
residuals, not proof that one common flag or interface change fixes the engine.

Both roots advance to mapped/source-present, with authored origin recovered.
No accepted match unit or matches.csv row is added. Original TU boundaries,
COM call scheduling and unique original source spelling remain unknown.
