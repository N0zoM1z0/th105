# Sprite luma/alpha rendering, 2026-10-22

`SpriteRenderEffect_render_luma_alpha @ 0x006656E0` is newly accepted
canonical **248/248** against original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Together with the new [441-byte auxiliary renderer](ANIMATION_AUXILIARY_RENDER_2026_10_22.md),
it supplies both previously unselected authored bodies in the first
[complete-owner link](REIMU_OBJECT_COMPLETE_OWNER_2026_10_22.md). The remaining
provider inclusion and source-contract work is still required before linking.

## Observed target facts

Raw PE traversal closes all 80 instructions over `6656E0..6657D7`, exactly
248 bytes, with no holes, overlapping decodes or embedded data. The single
conditional branch is `6656F1 -> 6657B0`. Both exits use RET28, at `6657AD`
and `6657D5`, consistent with ECX=this and seven four-byte float arguments.
There are four preceding and eight following INT3 bytes. The wrong-image
IDA session was preflighted and rejected again; it supplies no semantics.

The independently accepted 479-byte `AnimationObject_render_color_mode`
at `435540` calls this function at `435718`. Its mode-5 source passes the
three luma weights followed by alpha, red, green and blue. The target's
argument reads and alpha comparison agree with that order.

For zero alpha, the target forwards the three luma arguments to the real
140-byte `render_luma @ 665650`. For nonzero or unordered alpha, it caches
the effect service from `6FD398`, builds two separate live four-float arrays,
and executes the actual pipeline:

| Site | Transfer | Inputs / role |
| --- | --- | --- |
| `66572D` | vslot `88` | `v4Arg0`: luma R/G/B/0 |
| `665762` | vslot `88` | `v4Arg1`: R/G/B/alpha |
| `66576D` | vslot `104` | begin |
| `66577C` | vslot `FC` | configure pair 0,0 |
| `665789` | vslot `100` | select mode 3 |
| `66578D` | direct `407AD0` | real sprite draw publisher |
| `66579B` | vslot `108` | finish first |
| `6657A6` | vslot `10C` | finish second |
| `6657CC` | direct `665650` | zero-alpha luma fallback |

The service pointer, both NUL-terminated parameter names and their initialized
bytes already have attested relocation entries. `v4Arg0` is at `6C3290`,
`v4Arg1` at `6C3288`. No new global address or literal exception is added.

## Source and complete comparison

`src/battle/SpriteRenderLumaAlpha.cpp` implements the observed branches,
arrays, callback sequence and real fallback/draw calls. It is separate from
the existing luma definition, preserving the observed out-of-line fallback
without forced noinline or a forwarding wrapper.

The existing unchanged service declarations move from `SpriteRenderEffects.cpp`
to `SpriteRenderEffects.hpp`, shared by both TUs. Offset assertions check
the observed vtable positions. The three older effect bodies retain all their
canonical bytes after this move. No callback return contract is broadened
beyond that existing ABI view, and no external service implementation or
original nominal interface identity is claimed.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit cross-v106a-sprite-render-luma-alpha --compare --json
```

Ordinary `vc8-sp1-probe-o2`, `/GS-` reproduces the complete 248-byte COFF
symbol, both direct REL32 edges, all three DIR32 references and all seven
indirect-call instructions. Source and target canonical SHA256 are both
`bb79c5de4d19130eef3799c39b8924f75c0df98ece91a16962da35d918d2d3e6`.
The selected source SHA256 is
`9e7480879d9e3e720a1df48708bac831a64613d1b39b0562927e783984f46660`.
Original nominal class/service names and TU membership remain unproved.

The initial full comparison is `build/sprite-luma-alpha-20261022/formal-first.json`.
After adding the shared-header offset checks, the fresh complete replay is
also copied to `formal.json`. `target-facts.json` records the independent
raw CFG, strings, callsites and source pins; its private recipe is retained
under `.analysis/sprite-luma-alpha-20261022/target_facts.py`.

## Scoped replay and next step

All five full comparisons pass in fresh serial builds:

- Existing RGB, alpha/RGB and luma: **199/199**, **173/173**, **140/140** in
  `cross-v106a-sprite-render-effects`.
- New luma/alpha: **248/248** in `cross-v106a-sprite-render-luma-alpha`.
- The real color-mode caller: **479/479** in
  `cross-v106a-animation-render-color`.

All reports and `affected-replay.json` are under the same receipt directory.
No all-unit cold replay is claimed. The 441/248-byte recoveries close the two
source-body gaps, but the prior 36-object link still describes its earlier
inputs. Next include the new bodies and actual existing providers, resolve
the native checked-map dependency and reconcile the quantized lookup return
declarations before evaluating the complete owner/root's code generation.
