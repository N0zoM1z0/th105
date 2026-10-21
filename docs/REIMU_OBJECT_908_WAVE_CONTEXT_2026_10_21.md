# ReimuObject 908: genuine wave-dispatch visibility controls

Root `0x00496540` remains nonexact at `0x0049655F / +31`. Its selected CPP
`3b9e4896` and header `6f469e68` are unchanged. This checkpoint tests actual
callee visibility after the preceding accumulator controls proved byte-neutral.
It adds no authored exact, source selection or ABI change.

Only the hash-attested original Japanese 1.06a executable is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target/status/tracking preflights pass. IDA rejects its wrong open executable;
all new observations come from raw PE instructions and serial CPU0/nice10 VC8
builds. No analysis database or target bytes are modified.

## Observed instructions

The 908 sequence0 even-counter burst calls unparented spawn 64CCB0, then wave
45C030 with index1. Target 4A076A loads float `this+374` **before** sign-extending
word `this+366`, homing the integer at ESP+20, FILD m32 and FADDP. The source at
809E97 instead sign-extends/homes/FILDs the integer and FADDs memory `this+374`.
Both then store `374` and decrement word `366`. The distinction is read/x87
lifetime order, not a missing signed widening or a 16-bit FILD.

The complete 35-byte wave helper 45C030 checks unsigned index <=63, loads the
handle array pointer at receiver+164, indexes the handle and tail-forwards to
401D50 with service receiver 702288. It does not itself implement audio device
calls. Raw 401D50 has a zero-handle RET4 path; the preceding spawn still needs
its real manager/allocation/initializer path before the root can reach that
wave. This checkpoint does not fabricate either opaque return or claim actual
post-wave root execution.

## Target-backed source controls

The private owner view adds only the observed handle-array pointer at +164,
with its offset asserted. The visible-body variant additionally supplies the
real bounds/index/forwarding C++ definition. The genuine service/global use
existing named relocation bindings, and every whole-root relocation is replayed.
There is no noinline attribute, fake callback, forced register or compiler-flag
change.

| Complete caller | Code / metadata bytes | Canonical section SHA prefix | Wave / direct service calls |
| --- | --- | --- | --- |
| Selected baseline | 44832 / 868 | d0ff3d32 | 20 / 0 |
| Observed owner layout, external body | 44832 / 868 | d0ff3d32 | 20 / 0 |
| Genuine visible wave body | 45120 / 868 | e27c889f | 0 / 20 |

The layout-only root is byte-identical to the baseline. With the real body
visible, VC8 naturally inlines all 20 wave calls into handle lookup/service
calls. The separate emitted helper itself remains complete canonical **35/35**,
SHA256 `8ba88176d3ad846dfcdb603e1a3eaea0039d7949e5fbacd7d113b6c9bf458181`.
This independently checks the control's helper implementation/ABI; its existing
acceptance is neither duplicated nor moved.

Despite the inlining, 908 still converts the counter first and uses memory
FADD. The larger root remains nonexact +31. This exact source context therefore
does not recover the target's load order or physical wave calls. It does not
exclude every possible original source partition or link-time context.

Same-TU counter 4963A0 stays **66/66** in all three comparisons, canonical
`ad12b782ed5fc99007456fc66a9615951cee34178850a308316409c5245bb156`.
All experimental inputs are private; selected headers, profiles, ledgers and
accepted units are unchanged. No unrelated or aggregate replay is needed.

## Reproduction and retention

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-object-action-state --compare --json
# Expected nonzero: root nonexact; 4963A0 exact.
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Formal baseline, per-variant full comparisons and instruction facts remain in
`build/reimu-object-908-wave-context-20261021/`. Matching `.analysis/` recipes
preserve frozen baseline source/header/object inputs. Completed unselected
source/object/native sets are compressed with per-file SHA256 readback before
deleting their loose copies. Source recovery must still explain the 908
post-wave lifetime and the other Reimu call/RET sharing differences.
