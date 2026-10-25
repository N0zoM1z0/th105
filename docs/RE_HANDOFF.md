# TH10.5 reconstruction handoff

Active reconstruction resumed on2026-10-25 under the user's large-function,
whole-comparison-first direction. TenshiObject update
**0x0064CD50** is checkpointed complete source-present/nonexact. Active bounded
work is **Alice Fighter update0x004E9F50**: raw42721-byte main/full44080-byte
payload is closed, and the complete manual hypothesis has its first comparison.
Current43996-byte candidate is nonexact and deliberately unselected.
Youmu53CEA0 already has a complete public unselected hypothesis; its absence
from implemented.csv does not mean it is unwritten. One writable session, no
subagents or concurrent VC8/Ghidra jobs; `config/claims.csv` stays header-only.

## Target and environment

Only original Japanese 1.06a is valid: SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
base400000, entry68B9D2. The GUI IDA is still attached to a different executable
(SHA10350095...); its failed preflight blocks that IDA session, not raw PE work.
Any Ghidra use needs independent import/entry/all-mapped-byte attestation.

Use `scripts/repo-python`: CPython3.11.14, Capstone4.0.2, pefile2024.8.26,
Unicorn1.0.2 and setuptools75.8.0. Heavy commands run serially with
`taskset -c 0 nice -n 10`. Monitor memory/swap. Start every bounded unit with:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/check-ida-mcp.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

Local CI is mandatory before each commit/push; remote green cannot replace it.
Commit prefix: `gpt-6.1-sol: ...`. Keep executables, databases, compiler installs,
credentials and generated reports out of Git.

## Durable state

Current checkpoint retains complete Tenshi source and the complete unselected
Alice Fighter hypothesis with a reproducible whole-payload comparison. Exact
acceptance and source-present counts are unchanged.

| Ledger state | Count |
| --- | ---: |
| Provisional / authored / excluded / review candidates |4024 /1596 /1418 /1010 |
| Mapped / source-present |1583 /1564 |
| Exact functions / authored bytes |1412 /381108 |
| Configured units / functions |604 /1572 |

These are live ledger counts, not a new aggregate cold claim. The last aggregate
receipt remains `build/exact-first-remilia-action-entry-20261025/cold-all.log`:
524 accepted units/all1412 functions. Source-present is not exact acceptance.
The local suite now has620 tests. Python environment and public CI were repaired
previously; do not reopen them without a new failure.

## Current bounded work: Alice Fighter4E9F50

[Complete target closure and next source scope](ALICE_FIGHTER_UPDATE_2026_10_25.md).
Public audit: `scripts/audit-alice-fighter-update-target.py`.

- Main42721 SHA58819477; full44080 SHA2bd6bb53 through4F4B80.
- 11169/11170 conservatively reached instructions, sole unreachable3-byte
  alignment4F28ED, no escaping/noninstruction edges;128 RET0s.
- 674 direct calls/27 entries,163 register-indirect calls; aligned frame410.
- All16 tables165 DWORDs, three remaps685 bytes,14 pinned metadata alignment
  bytes account for the complete1359-byte tail.
- Complete source is now src/characters/AliceFighterActionState.cpp/.hpp,
  unit exact-first-alice-fighter-update. It is an identified/unselected compiling
  hypothesis, not an implemented.csv/matches.csv entry. The old partial scaffold
  remains separate and is not called by this root.
- First complete43428 SHA0d7bfb04 was compared before controls. Native400
  re-reads facing after sequence/effect callbacks;400/401 request continuations,
  sequence4 timer gates and401 state-before-counter order are now restored.
- Current formal/cold candidate43996 SHA2655274b,41484 unmasked differences,
  first4E9F58; frame418/410, RETs122/128, direct672/674, indirect158/163.
  All16 table lengths and all685 remap bytes agree, without masking or rebasing.
- Native214 inactive states now go directly to landing check; its flight-end
  gate stays within active1..4. Timer/sequence/velocity/heading/peer reads follow
  actual callback epochs. Six real root prefixes pass; old8dd4473a fails3.
  Public scripts/audit-alice-fighter-action214-paths.py executes real4351C0 and
  stops before the first landing/scratch body, without injected returns/edges.
- Native542 has separate sequence4/8 terminal guards;547/548 threshold and
  landing outcomes share one next-block exit. Two isolated whole-source controls
  support these retained structures. All mapped-case direct/indirect call counts
  now agree, including21414/14,5425/5,547/5483/3. The five special direct arms
  300/520/795/797/798 also agree in call counts after separate instruction and
  constant review; their indirect counts are1/3/2/2/2. Global physical counts
  still differ. Counts prove no behavioral equivalence.
- Read-only384MiB Ghidra evidence is already saved; all9 primary DB file hashes
  unchanged. Its decompiler output has warnings and remains a hypothesis.
- The isolated narrow-facing closed provider also matches46519066/66, but the
  full caller control43464 SHAb046bb87 keeps frame418 and prior membership gaps.
  It is unselected; keep the public int-facing view and close that control.
- Native570/571 write three packet words, but count4 reaches a real16-byte
  memcpy in manager4FAAD0. One private three-word-array control naturally gets
  frame410 but remains43996 SHA08ce1a46,41499 unequal positions, first+17.
  Original array extent is not proved; retain public four-word arrays and close
  the size control. No width/padding grid.
- Fifteen new literal aliases are selected only by this new unit; predecessor
  relocation rows and accepted source/header/flags are unchanged. No new cold
  aggregate claim. Full target floating relocation audit passes.

Public comparisons: scripts/build.py --unit exact-first-alice-fighter-update
--compare --json and scripts/audit-alice-fighter-update.py (both expected1).
Receipts/private recipes remain under build/exact-first-alice-fighter-update-20261025/
and the corresponding .analysis/ scope. Formal/cold full audits agree.

Next: continue this complete root from actual differences: real stack/packet
lifetimes and global physical sharing. The five direct arms have a bounded
instruction/count review, not full execution acceptance. Close the542/547/548
source-structure and570/571 extent controls; do not sweep equivalent spellings.
730's partially defined upper facing bits and570/571's fourth-word provenance
and original array extent remain unknown;
preserve uncertainty rather than inventing data initialization or register
contracts. The source is complete but must stay unselected pending its full
instruction/ABI/default review. Do not rerun Ghidra merely to reread saved
output, broaden to another root yet, or use spelling/padding grids.

## Checkpoint: TenshiObject64CD50

[Target/ABI evidence, first comparison and limits](TENSHI_OBJECT_UPDATE_2026_10_25.md).
Source: `src/characters/TenshiObjectUpdate.cpp/.hpp`.
Unit: `exact-first-tenshi-object-update`.
Audit: `scripts/audit-tenshi-object-update.py`.

- Main41001 bytes/full41984 through657150; complete raw CFG closes9797 reached
  instructions,67 RET0s and eight exact internal alignment bytes, no escaping edges.
- Full payload owns28 tables/195 destination DWORDs and199 primary remap bytes
  (800..998). It directly abuts the independent657150 initializer.
- thiscall/RET0, native aligned frame2A8. Surface fill is stdcall/RET12;
  parent+658 factory slot04 takes nine arguments/RET36. Actual packet tracing
  closes97 requests/53 bases/652 bytes; p244/p384/p520 have4/5/4 words.
- All28 nondefault actions/default have manual source. First full42068 comparison
  was retained before controls. Native801/820 branch-specific trig sites,
 801 direct doubling and800 float transfers were then restored.
- Formal and independent fresh builds emit42508 bytes, SHA8b9f620a...,
 40093 unmasked differences, first64CD58. Aligned frame2B0 and83 RETs versus
 2A8/67. Per-action direct/indirect call censuses agree for all28 actions;
  physical frame-call owner groups remain five versus six. This is nonexact.
- 825 nonzero substates now consume4351C0 AL through the common conditional exit;
  its zero-substate early return and default ignored return remain separate.
  Eight real native-helper inputs pass; the old object fails one (lifetime10
  versus native9). Only four branch-displacement bytes changed, so length and
  aggregate difference count alone would miss this correction.
- The two local spawn declarations now use the exact provider's admitted int-facing
  view; factory slot04 remains separate. This removes byte-home/full-DWORD
  argument artifacts, not proof of original formal width. Native801 cosine
  doubling now has no artificial local-float transfer. Sixteen854 root prefixes /
  801 loop fragments agree in full arguments/state; old byte view fails four
  under A5 stack fill. Public `scripts/audit-tenshi-object-request-paths.py`.
- The separate eight-comparison-carrier control retains frame2B0 /46 qword
  accesses at -688/-672/-664. It is unselected; do not repeat it without new
  evidence.53 packet bases/652 bytes remain complete.
- Selector-zero/default900 burst controls have no native source initialization;
  ordinary uninitialized locals preserve the source hypothesis. Scratch-dependent
  behavior and original intent remain unknown; no equivalence claim is made.
- All literal/global aliases are isolated; no accepted unit inputs changed.

Receipts: `build/exact-first-tenshi-object-update-20261025/` (`formal.log`,
`formal-full-audit.json`, `cold-build.log`, `cold-full-audit.json`,
`first-complete.json`, `target-audit.json`).825 receipts use the
`frame-return-*` prefix; the latest width/transfer receipts use `int-view-*`.
The public scoped check is
`scripts/audit-tenshi-object-update-paths.py`. Private recipes and first/control
sources: `.analysis/exact-first-tenshi-object-update-20261025/`.

Alice4E9F50 is now the active complete hypothesis described above. Sakuya4CADB0's smaller report
span is misleading for selection: its ownership ledger already pins74941 code
bytes including ten remote chunks.
Tenshi width/transfer work is saved; keep its comparison-carrier control closed
without new evidence. Nominal names/layouts/TU ownership remain hypotheses.

## Parked questions

Youmu53CEA0 already has a complete public unselected source hypothesis and
closed25944-byte main/full26576-byte target. A fresh26784-byte build reproduces
SHA73359b44,24412 differences, first+8 frame40/48. Changing only its two local
quantized-trig return declarations double->float is whole-payload byte-neutral;
keep that width question closed. Prior frame guards, break exits and period
controls remain closed. See [Youmu evidence](YOUMU_OBJECT_UPDATE_2026_10_25.md).
No source selection or exact claim follows from this control.

Read-only candidate triage also rebuilt CDesignBase40B000: its existing local
EH relocation block and gauge private-ABI residual remain. No loader source,
binding or compiler setting changed; receipts use
`build/exact-first-design-base-load-20261025/`. This is not the active root.

Yuyuko56F700 is selected source-present/nonexact: full34928 SHAc97edd07 versus
35060 target,32764 differences, first56F71F.815's x87 association/direct doubling
and inclusive guards restore its two virtual exits. Broad/narrow continuation
controls repeat the wrong four-frame owner partition; broader sharing also
removes real motion sites. They are unselected and the scoped question is closed.
Do not rerun carrier/flag/spelling grids without independent new evidence.
See [Yuyuko receipts](YUYUKO_OBJECT_UPDATE_2026_10_25.md).

Other parked roots and successful input/control-policy peers are retained in the
[complete prior handoff](RE_HANDOFF_HISTORY_2026_10_25.md) and dated evidence docs.
Do not claim LTCG impossibility from standalone failures alone.

## Private material and cleanup

The same workspace retains all source/objects, accepted receipts, target, tool
installs, primary Ghidra project and pre-analysis backup. All six old detached
worktrees contain uncommitted work; do not remove or treat them as parallel
sessions. [Artifact recovery](ARTIFACTS.md) describes the verified cleanup.

The pre-resume31-file Tenshi handoff also has a portable, hash-verified copy:
`build/handoff-cleanup-20261025/tenshi-resume.tar.gz` (262512 bytes), SHA-256
`9e28ae84cac98d8b96a102901b29dbbd0250d0c32fee74119913eab674c3d6ff`.
This bundle is **local, not in Git**; a fresh clone needs it copied separately.
It includes the earlier partial draft/observations, not this resumed complete
source or new receipts; the complete selected source is now in Git. It contains
no target, compiler or primary DBs.
Its repository-relative members can be restored after checking
`tenshi-resume-members.json`; avoid overwriting newer work.

Final gate in the finished worktree:

```bash
PYTHONDONTWRITEBYTECODE=1 taskset -c 0 nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

The no-bytecode setting avoids recreating the removed cache during maintenance.
The user goal remains active. Continue from the current worktree and receipts.
