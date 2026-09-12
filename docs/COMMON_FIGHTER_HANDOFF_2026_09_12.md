# Common Fighter: paused investigation and experiment index

## Stop state

The user requested a documentation checkpoint and commit/push, **not another
reconstruction iteration**. Work is paused at the unchanged production source
from `379a551`. This final batch closes **no additional owner**. Resume only
when requested; do not start a character-completion sweep or switch bosses.

| Item | Verified checkpoint |
| --- | --- |
| Target | Original Japanese TH10.5 1.06a |
| Executable SHA-256 | `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e` |
| Root / callable extent | `0x004740C0..0x004768AB`, 10219 bytes, final RET at `0x004768AA` |
| Source | `src/battle/FighterCommonActionState.cpp` |
| Source SHA-256 | `de817fb14a104e6a7350aa5721c3c67182bf0030d84e92c35b6e868ba347c9b6` |
| Unit | `gpt-web-fighter-common-action-state` |
| Diagnostic owners | **53/66**, 13 pending; not partial exact credit |
| Candidate metadata / section tail | `+0x2838` / 10801 bytes |
| Canonical comparison | **Nonexact**, first difference `+0x14` at `0x004740D4` |
| Target callable SHA-256 | `7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6` |
| Candidate canonical-window SHA-256 | `99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835` |

The first canonical difference is a branch displacement (`48` versus `95`),
not the later SUB/ADD opcode difference. Relocation-aware owner diagnostics
help distinguish these, but do not replace the complete canonical comparison.
No source, compiler profile, shared header, boundary, relocation permission or
exact ledger is changed in this documentation checkpoint.

Fresh artifacts from this batch are `build/common13-switch-typed.json`,
`build/common13-switch-baseline-formal.json` and
`build/common13-switch-baseline-owners.json`. Target/IDA preflight and tracking
validation passed. The baseline formal build returns 1 for the expected
nonexact result; it is not a successful exact verification.

## Read in this order

1. This checkpoint and [RE_HANDOFF.md](RE_HANDOFF.md), then the current source.
2. [Landing and terminal evidence](COMMON_FIGHTER_LANDING_EVIDENCE_2026_09_12.md):
   the retained action-74 and action-790 improvements, plus earlier negatives.
3. [Exit/phase evidence](COMMON_FIGHTER_EXIT_PHASE_EVIDENCE_2026_09_12.md):
   vtable/argument-width readback, single-switch controls and LTCG visibility.
4. [Official VC8 reference index](VC8_REFERENCE.md) when a specific compiler
   question needs corroboration; use its local text/topic extracts, not the
   full PDF. [RTM provenance](VC8_RTM_PROBE.md) pins the alternate compiler.

Read historical documents as phase-scoped hypotheses. Do not rerun their
entire probe history, assume older 51/52-owner counts are current, or invoke
old private scripts that overwrite the production source.

## Remaining 13 owners

| Owners | Exact target observation | Current obstacle |
| --- | --- | --- |
| `entry`, `low:180` | Low SUB EAX,50 at `0x004740DE`; high SUB EAX,691 at `0x00475E20`, without reloading the action | Current nested switches emit ADD-negative. Native single-switch output can emit SUB, but changes case/tail ownership. |
| `low:53,54,55,56,159,160,161,162` | Shared rounded-velocity clamp at `0x00474122`, x87-drop path at `0x00474139`, advance/action-0 terminal at `0x00474161`; all physically in action 50 | Production routes these consumers to a late action-162 owner. Making the early cohort natural fixes 53..56 locally but duplicates the four late bodies. |
| `low:73,75,88` | Selection at `0x00474992` belongs to action 73; 75/88 enter with zero live on x87. Default/drop epilogues remain near action 75. | Production owns selection in 88. Moving selection alone displaces the default epilogues or duplicates action 75. |

Two recent retained improvements must survive any resumed candidate:

- `11dedbf`: action 74's positive landing `if/else` and ordinary switch exit
  recover its full diagnostic owner, 51 -> 52.
- `2dde1fd`: action 140 retains `return`; 143/144/150..153 use `break`.
  Action 790 then reaches the target action-140 terminal, 52 -> 53, no losses.
- `379a551`: the local virtual action parameter is `short`, following all
  15 roster +8 slots into `0x0045BFE0` and the low-word read at `0x00435200`.
  The correction is byte-neutral; sequence remains `int`. Ignored return
  values are not evidence for changing a callee's return type.

## Final batch: measured negative controls

All rows below are private probes, **not production changes**. File stems are
`build/common13-switch-<suffix>` with `.cpp`, `.obj` and `-owners.json`.
RTM uses the `native-short.cpp` input rather than a separate source file.
All compiler invocations were serial, on this root only.

| Suffix | Source property tested | Owners / metadata | Result versus production |
| --- | --- | --- | --- |
| `direct` | Single switch with case 690 sharing 54/60; real shared clamp labels inside case 50; 51/52 break | Audit blocked; low table has 49 destinations, section tail 10873 | Required topology is absent. No owner count is claimed. |
| `sequence-cohort` | Independent native selection bodies: 73 returns; 75 uses a positive full guard then breaks; 88 selection breaks | 51/66 / 10332 | Loses default owner 68 and 799. Action 73 has the target local length but wrong epilogue destination; 75 expands to 195. |
| `conditional-sequence` | 75 explicitly conditionally jumps to the genuine 73 selection label, then returns; 88 has an independent selection/break | 51/66 / 10332 | Same two regressions; 75 expands to 200. A conditional goto alone does not preserve target placement. |
| `native-short` | Earlier natural action-0 assignment cohort, now with the corrected `set_action(short)` declaration | 56/66 / 10560 | Gains 53/54/55/56, loses 799, and leaves 159..162 at 146 bytes each. Rejected. |
| `native-rtm` | Same `native-short.cpp`, RTM 14.00.50727.42 instead of SP1 .762 | 56/66 / 10560 | Same gain/loss set and unresolved owners. This is an owner-level result, not a claim that complete COFF files are identical. |
| `float-clamp` | Production's shared `double v4` changed to `float`; all assignments already originate from rounded float values | 52/66 / 10256 | Loses 799 and moves required intermediate store/reload boundaries. 159 shrinks to 53; 162 remains 146. Smaller is not better here. |
| `field-clamp` | Shared clamp compares the assigned velocity field with zero, instead of `v4 > v3`; removes the now-unused zero local | 52/66 / 10304 | Loses 799; shared tail still belongs to 162 and that owner expands to 154. |
| `shared-break` | Only the genuine `LABEL_11` terminal's ordinary exit changes from return to break | 53/66 / 10296 | No owner improvement. This was the already-running probe when the user requested the stop. |

The final batch's baseline and the previous production comparison have the
same canonical-window hash above. Do not describe a matching owner count or
metadata offset alone as byte-neutrality for other probes.

### Important phase distinction

Fresh raw-COFF inspection of the natural cohort shows the two float rounding
steps in action 159, followed by FST to the velocity field and FCOMP ST(1).
Its common tail is nevertheless emitted locally. The analogous action-163
arithmetic instead jumps back to the action-62 clamp. The outstanding question
is why these source/optimizer contexts share differently, **not whether VC8
can generate the two required float rounding stages**.

Microsoft's [SP1 backend change list](https://devblogs.microsoft.com/cppblog/vc2005-sp1-bug-fixes-back-end/)
was checked again. It establishes that backend fixes existed, not a particular
tail-merging rule or an explanation for TH105. Both baseline and natural-cohort
RTM controls have now failed to improve their respective diagnostic results.

## Earlier approaches already covered

The linked evidence notes contain the detailed outcomes. Avoid repeating these
without a newly demonstrated type, lifetime, source or TU distinction:

- Explicitly normalized selectors and unsigned inner selectors: retained
  baseline window unchanged. Single-switch lowering emits SUB but can merge
  target-distinct 50/51/52 or 62/63/64, or place an extra 690 body near the
  high dispatcher. Keeping all 51 low destinations still was not sufficient.
- Independent float assignment/compound-update/rounded-expression cohorts:
  early sharing can improve while late 159..162 duplicate. Explicit late
  labels, direct-primary labels and negative completion guards did not close
  the simultaneous layout.
- Duplicated selection, full else arms, ternary sequence arguments, reordered
  cases and inline selection helpers: local length successes did not recover
  both selection ownership and the default/x87-drop exits.
- Ordinary `std::min`/inline helpers can remain external calls. Explicitly
  inlined slide helpers changed rounding placement without closing the root.
  No helper symbol was assigned a fabricated target address.
- Simple size/strict-FP controls changed the frame or introduced other
  non-target code. Standalone RTM baseline was also negative.
- `/GL` plus `/LTCG`, exported versus retained-only, and native assignment
  versus live cross-label intermediates still produced an aligned EBP frame.
  The tracked `scripts/probe-ltcg-visibility.sh` reproduces the visibility
  control. Its unresolved DLLs must never be executed or treated as canonical
  objects. These negatives do not prove all truthful original TU contexts
  impossible.

## Resume discipline and open questions

The unresolved issues are original switch/source partition, simultaneous tail
ownership, and compiler/TU phase. Exact original source syntax and the root's
original LTCG status remain **unknown**. Byte-identical tails are not proof
that a particular source-level sharing construct or optimizer pass produced
them. No unconditional standalone-compiler impossibility claim is justified.

On an explicitly requested resume, start with current source and fresh IDA
attestation. Seek an independently motivated discriminator for the coupled
owner graph. Check gained **and lost** owners, then the whole canonical body.
Do not add assembly, padding, inert locals, artificial liveness, extra cases,
ABI lies or comparator exemptions to reach a local count.

The user specifically exempts unrelated accepted-unit replay and global cold
builds in this boss loop. The minimum affected-root sequence is:

```bash
git status --short
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
python3 scripts/build.py --check
python3 scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json
python3 scripts/audit-giant-action-owners.py fighter-common-action \
  build/match-units/GptWeb_FighterCommonActionState.obj \
  --unit gpt-web-fighter-common-action-state --json
```

The formal comparison currently returns 1. Run the audit separately even after
that expected nonexact exit. A probe audit returning 2 with empty JSON is a
failed topology/relocation audit, not a zero-owner result.

Before any future commit/push: stage the intended files, run
`python3 scripts/ci.py`, `git diff --check`, and `git diff --cached --check`
in the finished worktree. Any subsequent material edit invalidates that gate.
Keep the single-agent/no-concurrent-VC8-build rule and the commit prefix
`gpt-6-astra:`. No new aggregate cold-replay claim is made by this checkpoint.
Generated probes, reports, compiler binaries, target executable and databases
stay ignored; the durable reading route and findings are tracked here.
