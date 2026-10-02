# Youmu shared effect tails, 2026-10-02

The shared-tail source below remains. A subsequent one-branch ordered-facing
correction changes the source and canonical window hashes; current Ghidra
attestation and comparison are recorded in
[the numerical follow-up](YOUMU_GHIDRA_NUMERICAL_2026_10_02.md).

## Current result

`Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains **nonexact** over
37,692 target callable bytes. Source now expresses the two observed shared
effect paths using ordinary field stores and control flow. Correct ECX virtual
calls remain. The candidate again has **97 physical destinations**, including
33 low entries, without the preceding merges of `[209,212,221]` and `[210,222]`.
The strict owner auditor can pair all owners and reports **24/98** diagnostic
instruction/edge-identical owners. This is a fresh result, not a restoration of
the old incorrect-ABI checkpoint or an exact-byte promotion.

Candidate metadata starts at **+0x92B4 (37,556)**, versus target
**+0x933C (37,692)**. The formal full comparison returns an ordinary mismatch
at **+0xCA / 0x005302CA**, target `64`, candidate `D9`, after a 202-byte
canonical prefix. No unknown relocation blocks this retained candidate.
Exact ledgers receive zero additional credit.

## Observed target graph

Evidence is the hash-attested original Japanese 1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA still exposes the wrong `10350095...` image and is not used. This work
uses raw target disassembly; no new Ghidra process or database write is needed.

| Target action group | Observed value stores and shared path |
| --- | --- |
| 208 | VX 0, VY 23, AY 0.75; clear byte +0x47E; effect 63 |
| 211 | Load float 3 at 0x5318EC; jump 0x5318F2 to VX store 0x53158A and the 208 path |
| 209 | VX 11, VY 17.5, AY float 0.8; a separate effect 63 path |
| 210 | Load float -11 at 0x5317FE; jump 0x531804 to VX store 0x5316C7 and the 209 path |
| 212/221 | VX 11, VY 17.5, AY float 0.8; jump 0x5319F8 to AY store 0x5315A2 in the 208 path |
| 222 | Load float -11 at 0x532263; jump 0x532269 to VX store 0x5319E0 in the 212/221 path |

The ordinary path reads unsigned facing at 0x5315AE, pushes trailing argument
1 and facing, then loads Y for the effect. The 209 path pushes trailing 1 at
0x5316CD before the VY/AY stores, then reads facing and loads Y before pushing
facing. Both call the same accepted effect helper at 0x435240 with
`(63, X, Y, unsigned_facing, 1)`. Distinct physical tails and scheduling are
observed; distinct final gameplay results are not inferred.

Fresh complete raw traversal reaches **9,912 instructions / 37,692 bytes**,
including the action-720 auxiliary table, with no unresolved indirect jumps or
unledgered direct targets. This remains bounded-root evidence; virtual callees
are not classified by that traversal.

## Retained source hypothesis

The duplicated source blocks had lost the distinction between the ordinary
jump effect tail and the 209/210 tail. Four natural joins now express the
observed state/effect sharing:

- 210 stores VX -11, then shares 209's VY/AY/effect path.
- 211 stores VX 3, then shares 208's VY/AY/effect path.
- 222 stores VX -11, then shares 212/221's VY/AY path.
- 212/221/222 join the ordinary effect path after the acceleration write.

The source joins sit after real field stores; they do not introduce artificial
floating values to carry across labels. Four now-unused numerical temporaries
are removed. All preceding guards, signed sequence comparisons, float-rounded
vertical updates and virtual call contracts remain. The constants and final
state writes are unchanged. The labels model target-supported shared control
flow, not proof that the original author used these labels or any goto.

**Unknown:** VC8 currently places common stores/tails in later physical owners;
target places them in the positive/ordinary owners. Field-store joins avoid
new carry-value spills, but do not reproduce target tail placement, registers
or the two effect argument schedules. No assembly or LTCG requirement is
established by this discrepancy. Shared headers, flags, relocation targets
and object partition are unchanged.

## Closed private probes

A function-local `fenv_access(on)` probe separates the low groups but creates
98 root destinations and metadata +0x9108. It emits QWORD comparison operands
for retained double literals, including unmapped `__real@c034000000000000`
(-20), whereas these target comparisons use float operands. Its effect tail
sharing still differs. Formal comparison is **blocked**, not exact or a
valid owner score. No floating-environment setting is retained.

Explicit joins carrying the old numerical locals restore 97 destinations,
metadata +0x9314, but introduce float stack temporaries at joins. Narrowing the
real 23/0.75/0.8 carry values gives +0x9324 and 24/98 diagnostic owners, still
with extra spills. Widening the 11/-11 carry values gives +0x9304 and emits
unmapped double 11; its formal owner audit is blocked. Neither type variant
is retained. These metadata sizes alone do not rank correctness.

The retained field-store joins produce +0x92B4 and 24/98, with no newly
introduced carry-value spills in this action family. Removing the four unused
locals and adding explanatory comments leaves the probe's complete raw COFF
text and relocations byte-identical. Only the normal configured build below
supplies retained build provenance. Private artifacts remain under `.analysis/`
and `build/` and are not committed.

TH08's fsincos/frndint islands remain external reference for actual hardware
operation contracts; they do not establish an assembly requirement here. See
[the preceding x87 reference](COMMON_FIGHTER_X87_AND_GHIDRA_2026_10_02.md).

## Reproduction

```bash
taskset -c 0 python3 scripts/build.py \
  --unit gpt-web-youmu-vslot28-full-root --compare --json \
  > build/youmu-shared-effect-tails-20261002.json
python3 scripts/compare-giant-action-switches.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj --json \
  > build/youmu-shared-effect-tails-topology-20261002.json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json \
  > build/youmu-shared-effect-tails-owners-20261002.json
```

The focused build/comparison exits 1 for the documented mismatch. Both
mapping/audit commands succeed; the owner result is diagnostic only.
Canonical target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Canonical candidate comparison-window SHA-256:
`8dd9a077351eb196881220ae5bd77f832c66531bf7ad981e672ad917603541ac`.
This 37,692-byte candidate window includes table bytes after +0x92B4 and is
not a candidate callable-body hash. Source file SHA-256:
`89bdbd83b52fb40f8133d47b4647919731fc8d6d5c6308c1dc89049207bea166`.
Only the affected unit is rebuilt. Aggregate exact totals remain ledger totals,
not a new cold all-unit replay.
