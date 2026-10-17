# Iku actions565–568: staged C++ and original-code checks

> Current source: `src/characters/IkuActionState.cpp`. The original family
> file was consolidated after the measurements recorded below. Those receipts
> describe the earlier source; fresh combined-dispatch and preserved-family
> results are in [the unified upper-action checkpoint](IKU_UPPER_SOURCE_2026_10_17.md).

`src/characters/IkuObject818Actions.cpp` now recovers the four complete action
bodies as a semantic staging helper. These belong to the59038-byte root
`Iku_dispatch_action_state_vslot28 @ 620920`; they are not independently
isolated target functions. The root remains declaration-only/source-incomplete
in the ledgers, with no match unit or exact credit.

## Observed target control and data

The only target is Japanese TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
root SHA-256 `abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The [original family inventory](IKU_565_568_OBJECT_818_FAMILY_2026_10_02.md)
identifies physical entries6296BE/629E96/62A668/62AEF6. Its raw checker now
also traverses all shared tails:2119 instructions/8495 unique executable bytes,
comprising2063 instructions/8390 physical case bytes plus56 remote instructions/
105 shared bytes. All23 outward physical-case branch sites remain inside the
root. This union is an action CFG diagnostic, not additive authored-byte credit.

The checker qualifies all56 static object818 calls and their absolute x87
literal recipes, including both members of each pair. Phase0 has three pairs;
phase1 has four. The three-float payloads are:

| Index | First payload | Second payload |
| --- | --- | --- |
| 0 | -30,10,0 | -15,10,0 |
| 1 | -20,20,0 | -10,20,0 |
| 2 | -10,30,0 | -5,30,0 |
| 3, phase1 only | -5,40,0 | -2.5,40,0 |

Each call independently reads signed facing for `facing*99 + X`, forwards the
raw facing byte, and passes float-rounded `Y + 145.0`. The target's Y constant
is eight bytes. The source preserves the separate state tests and coordinate
reads after calls, rather than caching an entire pair's inputs.

The periodic counter+732 is sign-extended before signed division by6; +734's
phase bound uses signed JGE. Negative indices below the bound emit no pair
but still increment+734. The source retains both16-bit counter increments.
565/567 test+6C0, while566/568 test+6C4 before possibly clearing byte+750.

567/568 subtract acceleration+100 from vertical velocity+F8 before the real
descending-surface predicate, except sequence2 uses the landing helper. A
crossing clears motion, stores real surface height and selects sequence2
through vslot0C. Later sequence/frame gates include action9, effect62 followed
by vslot14, resource200/floor120, scaled counter50, wave18 and float0.6 stores.
565/567 publish DWORD+180 after the scaled-counter call;566/568 publish it
before that call. Shared tails and the timer recheck after wave dispatch are
retained. These are manually reviewed raw-instruction contracts; typed Ghidra
output was used only as a hypothesis.

## Natural source and native scope

The staging view inherits the existing accepted animation prefix and virtual
interfaces without modifying that header. Its new bool method reports whether
it handled one of these four actions; it does not impersonate the void target
root. Factoring repeated phase/pair logic is a source hypothesis, not original
TU, inlining, helper-boundary or class-size evidence. No assembly, executable
byte implementation, fabricated helper return or padding is introduced.

`scripts/probe-iku-object818-actions.py` builds the source with SHA-pinned VC8
`/O2 /GS- /GR /EHsc /MT`, retaining source/header/tool/object receipts. It loads
all real emitted COFF text/literal sections for native execution, resolves
local relocations and explicitly records same-target source-view aliases to
the accepted helper interfaces. This is a COFF execution diagnostic, not a
genuine linked image or canonical comparison.

Both sides execute the original root prelude to the actual selected case.
One then continues original instructions; the other invokes the compiled
staging helper on that post-prelude actor state. Original landing, surface,
frame, motion, counter and x87 conversion implementations execute normally.
Wave dispatch uses an explicit zero-handle array and the genuine audio
entry's zero-handle return, without an audio backend or result hook.

The2516-case matrix has **zero differences** in the complete7B8 actor view,
helper order/arguments, intermediate+180 state and x87 conversion inputs:

| Observation endpoint | Cases |
| --- | ---: |
| Genuine RET, stack+4 and preserved callee-saved registers | 1896 |
| First object818 spawn entry465190 | 588 |
| Effect62 entry435240 | 8 |
| Action0/9 virtual target45BFE0 | 12 |
| Sequence2 virtual target45C390 | 12 |

Every endpoint has an empty x87 stack and unchanged control word. The matrix
covers both facings, phase gates, signed WORD boundaries, indices-32768/-1/0/1/
2/3/4/32767, resource variants, frame/timer gates, scaled-counter phases0/3/4,
flat-stage descending crossings and PC53/64 nearest masked modes. Input SHA-256:
`790fdcee2e105f592176276cc80c3de6766228783c04abdb9ca1422f153f78fc`;
target-output SHA-256:
`8c378e64158513f1dba5813ee0ceb6f33c20602a9a0918a9f417a19776746de0`.
It visits1394 original root instructions, including the prelude/shared tails.
This is sampled coverage, not all2119 family instructions or all15132 root
instructions.

Two reproducible intentionally changed source controls each differ8/452 smoke
cases. Unsigned+732 remainder changes negative-counter actor state. Reversing
the+180 publication order changes recorded state at helper entry even when
the final actor bytes agree; this is an ordering discriminator, not a claim
of visible gameplay differences. The baseline452-case smoke has zero differences.

```bash
python3 scripts/audit-iku-object-818-family.py
python3 scripts/probe-iku-object818-actions.py > build/iku-object818-source-native.json
python3 scripts/probe-iku-object818-actions.py --smoke > build/iku-object818-source-smoke.json
python3 scripts/probe-iku-object818-actions.py --control unsigned-tick --smoke > build/iku-object818-unsigned-control.json
python3 scripts/probe-iku-object818-actions.py --control publication-order --smoke > build/iku-object818-publication-control.json
```

The two control commands intentionally exit1. Generated control sources,
objects and receipts stay below `build/`; private raw inspection stays below
`.analysis/iku-object818-20261017/`.

The second spawn's backend, post-effect/action/sequence backend behavior,
expired animation, nonzero audio handles, exceptional FP/unwinding behavior,
remaining106 nondefault Iku action IDs and original whole-root compiler context
remain unverified. No partial match is accepted. Next, extend target-reviewed
natural C++ across the remaining root families before selecting a complete
root unit and running its canonical comparison.
