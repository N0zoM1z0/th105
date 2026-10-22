# Auxiliary sprite rendering, 2026-10-22

`AuxiliarySprite_render_auxiliary @ 0x00434F30` is newly recovered and
canonical **441/441** against Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This supplies one of the two previously unselected authored dependencies in
the [complete ReimuObject owner link](REIMU_OBJECT_COMPLETE_OWNER_2026_10_22.md).
No giant-root acceptance follows from the new helper.

## Observed target and ownership

Hash-attested raw PE traversal closes 116 instructions over all 441 bytes of
`434F30..4350E8`, with no holes, overlaps, indirect transfers, embedded data
or external branch exits. The sole conditional edge is `434F3D -> 434F54`;
the sole return is C3 at `4350E8`. Eleven preceding INT3 bytes and seven
following INT3 bytes isolate the callable. The IDA session remains rejected
for its wrong executable hash and supplies no semantic evidence.

Two independently accepted render methods call this address in their directly
decoded entry prefixes: `AnimationObject_render_main @ 435280`, call `43528E`,
and `AnimationObject_render_group_callback @ 493820`, call `493839`. They
pass the auxiliary renderer pointer from owner +154 in ECX, with no stack
arguments. The existing accepted `45CD70` construction allocates 108h and
places a real CSpriteEx at zero; this function's accesses agree with that
wrapper's established offsets.

Observed behavior:

- If the unsigned render-pass byte at `6FBCB8` exceeds 250, reset it to zero
  before calling render mode `(4,0)`. Then call mode `(1,1)` and mode
  `(2, byte(pass+2))` on the real manager at `6FA21C`.
- Reset the sprite transform and scale X by the signed byte facing at +104.
- Preserve Y scale +FC and pivot +F4 across the X scale call. Scale X by +F8
  about `float(facing)*frame_x`, then Y about the saved pivot, then Z by 1
  about zero.
- Rotate about the current frame pivot: Z angle is `float(facing)*angle_100`,
  X/Y angles and Z pivot are zero. X pivot is `frame_x*float(facing)`.
- Translate by `x_e8 - float(facing)*frame_x_f0`,
  `-y_ec - frame_y_f4`, zero; apply the real battle-layout transform at
  `4271B0`, then the real sprite draw publisher at `407AD0`.
- Finally call mode `(3, byte(pass+1))`, rereading the pass byte after drawing.

There are 13 direct calls: four to `404A90`, plus `4073A0`, `4074A0`,
`4074E0`, `407580`, `407620`, `407680`, `4073E0`, `4271B0` and `407AD0`.
The source preserves the target's signed facing conversions, float round
trips and expression ordering. Render pass is not incremented by this
function; its converted mode arguments are wrapped bytes.

## Source and comparison

`src/battle/AnimationAuxiliaryRender.cpp` uses the existing
`AuxiliarySpriteRuntimeView`, real CSpriteEx methods, battle-layout adapter
and RenderModeManager. The only shared-header change is a nonvirtual method
declaration in `AnimationAuxiliarySprite.hpp`; the 108h size and all member
offsets remain checked. No source fields, storage layout, compiler flags,
forced-register constructs or return behavior were changed to shape bytes.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit cross-v106a-animation-auxiliary-render --compare --json
```

The first ordinary `vc8-sp1-probe-o2`, `/GS-` build reproduces the complete
441-byte symbol, including all 13 REL32 and nine global DIR32 operands.
No floating constant address or relocation exception is added. Both canonical
hashes are
`355b80f8b31afd4b00b5c89b186d6b70f62c2e816c8c98fb3552f8d1e4e1f0c7`.
The selected source SHA256 is
`224ccef9134c086ebd501ffd51c46f9b58d830cd9ad873a49b808fbf9cdcd8f9`.
Original nominal class spelling, unused return declaration and original TU
membership remain unproved; the source uses a void/no-argument
contract without inventing a result.

Receipts are `build/animation-auxiliary-render-20261022/formal.json` and
`target-facts.json`. The private raw traversal recipe remains at
`.analysis/animation-auxiliary-render-20261022/target_facts.py`.

## Affected replay and continuation

Fresh serial builds pass four accepted functions:

| Unit | Target | Result |
| --- | --- | --- |
| `cross-v106a-animation-auxiliary-sprite` | `45CD70` | 344/344 |
| `cross-v106a-animation-render-main` | `435280` | 213/213 |
| `cross-v106a-animation-render-callback` | `493820` | 93/93 |
| `cross-v106a-animation-auxiliary-render` | `434F30` | 441/441 |

The other direct shared-header consumer,
`gpt-web-youmu-object-action-entry @ 543670`, also builds and remains nonexact;
it receives no acceptance. Its full comparison is retained rather than
interpreting a nonvirtual declaration as new semantic or byte progress.
`affected-replay.json` and all five complete reports are in the receipt
directory. No aggregate all-unit cold replay is claimed.

Next recover the still unselected `6656E0` luma/alpha renderer, then include
both real bodies and the existing implementation/library providers in the
complete owner link. The prior 36-object failed-link report describes its
own inputs and is not a comparison of the newly extended graph.
