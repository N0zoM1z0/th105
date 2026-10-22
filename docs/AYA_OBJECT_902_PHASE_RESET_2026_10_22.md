# AyaObject902 phase reset correction, 2026-10-22

## Observed target behavior

In update61A290, action902 sequence1 first handles phase6 at61E552..61E568:
increment WORD384 and BYTE184, then clear DWORD180. If phase180 remains
nonzero,61E576 increments WORD364 and61E584 compares it as signed against6.
At>=6,61E58A sets BYTE184=1, clears DWORD180 and clears WORD364. There is no
velocity store or additional next-sequence call in this interval.

The retained source instead reset after>3, assigned velocity30 or0, and called
next_sequence_block when signed BYTE184<=0. Those unsupported operations are
removed; the threshold and actual index/state/count publications are restored.
Mode/time/owner-health transition gates remain, and their next-block calls
continue into movement. Unlike901, raw902 control flow does not return there.

The complete [prior901 checkpoint](AYA_OBJECT_901_TRANSITION_RETURNS_2026_10_22.md)
was rechecked against Japanese1.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
IDA rejects its open image and is not used. This correction is based on raw
branches, operand widths and writes, not inherited comments or another action.

## Selected compilation

The target77-byte interval [61E550,61E59D) matches byte-identically
at candidate root+4325 under translation. Other action families contain the
same byte pattern, so the audit pins the qualified902 location instead of
accepting the first occurrence in the object. This includes the signed threshold,
phase6 handling and index/state/count stores. It is not a standalone function
or a canonical acceptance claim.

The full candidate is20060 bytes, canonical SHA256
`c1a40ab7a6760fcd4afb81b330c2d81b927bdba1dd0c8cedf8801797f9ad1195`.
Metadata starts19592 versus target19524. The configured19522-byte window is
still nonexact at+0x22, target0F/source52, compared SHA256
`919ae83e29664b04da0854f1e7d8f0fc9dc3161039c71ecf2c12e43000162774`.
Owner diagnostics are3/34; counts of diagnostic owners are not exact totals.
Target traversal still closes4630 instructions/all19522 bytes/seven switches.
There are no shared header/ABI/compiler/helper changes or exact-ledger edits.

## Actual animation execution

`scripts/audit-aya-object-902-phase.py` reuses the concrete, actual-animation
fixture from the901 audit. That module is now importable without running its
CLI/matrix; an explicit preparation hook supplies902's actual fields. The
original Aya vtable, frame/next-block and texture-null helper instructions run
unchanged. No return values are fabricated; full root RET, stack cleanup and
callee-saved registers are checked.

All3328 selected executions agree in actor/parameter memory, ordered writes,
helper traces, alpha-read epochs and x87 status/tag. The target performs1440
actual next-block calls across this matrix. The predecessor differs in2208
cases. These are valid concrete animation fixtures, not claims about arbitrary
resources or all gameplay histories.

The matrix includes phase0/1/4/6/8, signed counter364 values-1/0/2/3/4/5/6/32767,
BYTE184 values0/1/127/128/255, two velocities/facings and masked PC53/PC64
nearest-even control words. Default mode4 isolates phase handling; mode0..3
cases exercise both sides of180/320/500/600 expiry limits and owner health
negative/zero/positive. Counters divisible by3 are excluded to avoid entering
actual spawning. Signed WORD rollover is included. Other sequences, spawn
paths, arbitrary aliases/resources and unmasked exceptions remain unproven.

With only902 excluded,4418 paired normal-return instruction graph nodes agree
against the prior full object. The901 execution audit is rerun after making
its fixture importable. This graph check assumes opaque calls return normally;
it cannot replace the canonical comparator or prove callback/exception behavior.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-902-phase.py
python3 scripts/audit-aya-object-901-transition.py
python3 scripts/audit-aya-object-normal-flow.py OLD.obj \
  build/match-units/GptWeb_AyaObjectActionState.obj --exclude-action 902
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

The canonical comparator intentionally reports mismatch. `--previous-object`
adds the finite old-source contrast. Private prior source is under
`.analysis/aya-902-phase-20261022/`; objects/reports are under
`build/aya-902-phase-20261022/`, including `execution.json`, `other-graphs.json`,
`regression901.json`, `selected-formal.json`, and `owner-audit.json`.
Local CI and whitespace checks gate commit/push. Aggregate strict totals remain
unchanged; no all-unit cold replay is claimed. Remaining902 differences include
speed-branch placement, floating scratch homes and spawn argument formation.
