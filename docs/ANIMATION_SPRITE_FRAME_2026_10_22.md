# Shared animation sprite frame application, 2026-10-22

`AnimationObject_apply_current_frame @ 0x00436760` is canonical **335/335**
against the original Japanese TH10.5 v1.06a executable, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This is a newly recovered real dependency of the Animation/AttackObject
sequence callbacks, needed by the pending complete ReimuObject owner context.
It does not establish exactness of the giant `496540` root.

## Observed target facts

The raw PE, rather than the rejected IDA session, supplies the evidence.
The complete reachable CFG contains 104 instructions covering every byte of
`436760..4368AE`: 335 bytes, no gaps, overlaps, indirect transfers or embedded
data. Both exits are tail jumps to the independently accepted
`CSpriteEx::commit_transform @ 4073C0`; neither is a separate return block.
The preceding seven bytes are INT3 padding and `4368AF` is another INT3.
The accepted 111-byte `AttackObject_apply_sequence_frame @ 45C110` ends with
its actual `45C17A -> 436760` tail edge.

The receiver is ECX, the embedded sprite begins at +4, the texture-handle
vector pointer is +130, and the current frame pointer is +150. The frame
prefix has signed 16-bit pivot coordinates at +4/+6, texture index at +A,
source rectangle at +C/+E/+10/+12, signed 8-bit render mode at +14, and a
transform pointer at +18. The pointed-to transform supplies three float
scales at +8/+C/+10 and three float angles at +14/+18/+1C.

| Transfer site | Actual destination |
| --- | --- |
| `436792` | `40C100`, checked native `vector<unsigned>::at` |
| `4367AF` | `407160`, seven-argument texture setup |
| `4367B6` | `4073A0`, reset transform |
| `43681F` | `434C10`, scale XYZ about pivots |
| `43686C` | `407680`, rotate XYZ about pivots |
| `43688B` | `4074A0`, scale X about origin |
| `43689C` | `407540`, scale Y about origin |
| `43687A`, `4368AA` | `4073C0`, commit transform |

All four signed rectangle components are read before the checked texture
lookup. After texture setup and reset, mode 0 doubles X and Y using the
attested float `2.0f` at `6C13F0`; mode 2 applies scale and rotation about the
signed frame pivots with Z pivot zero. Other signed modes only commit.
The mode-2 path retains the frame used for transform parameters across the
scale call, while reloading the current frame's pivots for rotation. The
source preserves both lifetimes, including rereading the retained frame's
transform pointer after scaling.

`40C100` was already positively excluded as compiler-generated VC8
`std::vector<unsigned>::at` by its exact caller's decorated template identity.
This work uses the actual pinned header, adds no library facade, and assigns
no authored credit to that 95-byte helper.

## Source and complete comparison

`src/battle/AnimationSpriteFrame.hpp` introduces a nonconstructing ABI view
with checked offsets and the observed common frame prefix. It does not change
existing partial polymorphic views. `AnimationSpriteFrame.cpp` implements
the actual texture lookup, rectangle snapshots, mode dispatch, transformations
and final commit using the existing real sprite declarations.

The initial single call expression emitted 310 bytes and deferred rectangle
loads until after `at()`, contrary to the target observations. Explicit signed
snapshots recovered the full 335-byte shape. Preserving their evaluation and
sprite-reference lifetime recovered the exact encodings. No assembly,
forced-register code, padding, fake return or copied bytes are used.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit cross-v106a-animation-sprite-frame --compare --json
```

The configured ordinary `vc8-sp1-probe-o2`, `/GS-` COFF build compares the full
335-byte symbol, with all nine REL32 and two float-literal DIR32 operands
replayed. Source and target canonical SHA256 are both
`403bd17fa27e733780e1a4b9845ac31cb741838e5c1d5c3e7e35e2aa1af368ec`.
The selected source SHA256 is
`af0c99e0cb9604de935c53701ef19c4969286bd24613d4ad35dead4203185d0c`.
The formal result is retained at
`build/reimu-object-owner-cil-20261022/frame-formal.json`; independent raw
facts are at `build/animation-sprite-frame-20261022/target-facts.json`.

The source returns void and tail-calls the actual void transform publisher.
The shipped nominal return type is unproved. Existing int-return sequence
views remain unchanged; their historical return declarations are not evidence
that this target function computes an integer result. No return value is
invented to combine the separate views.

## Replay and remaining work

Fresh serial builds pass all **19** configured comparisons across:

- `cross-v106a-animation-sequence-virtuals`: 10 functions;
- `cross-v106a-effect-animation-sequence-virtuals`: 8 functions;
- `cross-v106a-animation-sprite-frame`: the new 335-byte body.

The receipts are under `build/animation-sprite-frame-20261022/`, including
`affected-replay.json`. This is scoped verification, not a new all-unit cold
replay. No existing shared header, type layout or selected compiler profile
was changed.

The private complete-owner draft now compiles the real 17-slot ReimuObject
hierarchy, lifetime, pool and root. Its natural void action/finalize bodies
independently reproduce the existing 26/33-byte callbacks, but these private
controls add no acceptance. The full real-provider owner link still needs
completion and comparison. Original nominal declarations, translation-unit
membership and the giant root's compiler context remain unknown.
