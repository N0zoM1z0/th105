# Sprite render finalizer: complete source and handle-load residual

## Observed

`CSpriteEx_finalize_render @ 0x00407AD0` in the hash-attested Japanese TH10.5
v1.06a executable is **219 bytes**, `[407AD0,407BAB)`, SHA-256
`5b4ed5412715bbb05c9c311f9c72fcc9548ab93fb1c5aad0dcb039a43002b698`.
The executable SHA-256 remains
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
All **67 instructions / 219 bytes** decode in one linear callable, with
**43 x87 instructions**, no branches and one RET at `407BAA`. INT3 follows.
Existing authored-origin evidence separately pins exact caller edges from
`AnimationObject_render_color_mode @ 435540` and the SpriteRenderEffect family
at `6654D0`; decoding alone is not an authored-origin argument.

A sequential direct Ghidra session attested target hash, PE entry, image base,
external-entry marker, x86 Windows analysis identity, all mapped `.text` and
the 219-byte body before applying the no-argument thiscall/void hypothesis.
A second read-only process checked the saved name, body size, calling
convention, receiver-only parameter list and zero purge. Both used a 768 MiB
heap limit and two active processors. Ghidra pseudocode remains a hypothesis;
all implementation operations below were checked against raw instructions.
The mandatory IDA preflight failed its target hash and that database was not
used. Private working material is in `.analysis/sprite-render-finalizer-20261016/`.

The body reads the existing `CSpriteEx::working_quad_0b0[4]`, subtracts float
0.5 from x/y and adds it to z, then writes the corresponding fields in
`vertices_08[4]` with stride `0x1C`. It writes all four rhw fields to 1.0 in
vertex order 3/2/1/0. Color and UV fields are untouched. Target `407B6F`
loads receiver+4, `407B72` pushes that texture handle, and `407B78` calls
the known texture-stage binder `404DF0` on manager `702798`, with stage zero.
The RenderModeManager device member at `6FA220` receives SetFVF(0x144) and
DrawPrimitiveUP(5,2,receiver+8,0x1C). There are no control-flow omissions.

## Complete source and comparison

`src/battle/SpriteRenderFinalizer.cpp` defines the previously declaration-only
`CSpriteEx::finalize_render()` using the existing physical class layout and
ordinary C++/COM calls. It changes no shared header or accepted match unit.

```bash
TH105_FP_MODE=strict bash scripts/compile-unit.sh \
  src/battle/SpriteRenderFinalizer.cpp build/sprite-render-finalizer.obj
python3 scripts/compare-function.py 0x00407AD0 build/sprite-render-finalizer.obj \
  --symbol-base '?finalize_render@CSpriteEx@@QAEXXZ' \
  --rel32-target '?bind_texture@TitleResourceManager@th105@@QAEXIH@Z=0x00404DF0' \
  --dir32-target '?g_render_mode_manager@th105@@3URenderModeManager@1@A=g_render_mode_manager_device_base' \
  --json
```

Current result: **219-byte candidate / 219-byte target, nonexact at +0x12**.
The candidate loads the handle into EAX at +12 and pushes it at +1B, while
the target loads ECX at +9F and pushes at +A2. Stage-zero push is also
scheduled differently among the opening x87 instructions. The full ordered
43-instruction x87 sequence agrees after canonical relocation replay; the
56-byte tail `[+A3,+DB)` is byte-identical. Neither observation grants partial
exact credit: canonical acceptance remains the entire 219-byte callable.

Bounded negative controls:

- Making the existing ordinary submit_textured_primitive definition visible
  and calling it naturally inlines the submission but leaves exactly the
  same 219-byte candidate and handle-hoisting residual.
- An isolated four-byte handle view with a normal unsigned conversion is
  also byte-identical to the clean candidate. It is not retained as a class
  layout or production-source claim.
- Strict FP without local exception scheduling control produces 222 bytes
  and changes the rhw publication machinery. A real local half-pixel float
  under the ordinary FP profile produces 217 bytes and a double constant.
- Disabling global optimization locally produces 377 bytes and a non-target
  EBP frame. This is negative profile evidence, not an argument for a global
  flag change or an LTCG diagnosis.
- The pinned VC8 RTM compiler (14.0.50727.42) generates the same complete
  canonical comparison bytes as SP1 for this source. Factoring submission
  into an ordinary physical base-class member and allowing normal inlining
  is also byte-neutral. Neither compiler revision nor this base ownership
  hypothesis explains the current residual. No production source was changed
  by these two controls.

The root is now mapped and source-present. Original source spelling, the
handle load's original inline/compiler phase and any original TU boundary
remain unknown. No matches.csv or accepted match-unit row is added. No fake
barrier, dummy local, volatile/register directive or assembly was introduced.
The small companion [UI tile reconstruction](UI_TILE_RENDER_2026_10_16.md)
has a different COM scheduling residual; its target does not justify changing
this root's independently byte-identical final submission tail.
