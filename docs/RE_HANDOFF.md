# TH10.5 reconstruction handoff

Active reconstruction resumed on2026-10-25 under the user's large-function,
whole-comparison-first direction. TenshiObject update
**0x0064CD50** is checkpointed complete source-present/nonexact. The next bounded
candidate is **Alice Fighter update0x004E9F50**, provisionally42721 bytes.
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

Current checkpoint adds the complete Tenshi update, its reproducible unit,
isolated bindings and public full-payload audit. Exact acceptance is unchanged.

| Ledger state | Count |
| --- | ---: |
| Provisional / authored / excluded / review candidates |4024 /1596 /1418 /1010 |
| Mapped / source-present |1583 /1564 |
| Exact functions / authored bytes |1412 /381108 |
| Configured units / functions |603 /1571 |

These are live ledger counts, not a new aggregate cold claim. The last aggregate
receipt remains `build/exact-first-remilia-action-entry-20261025/cold-all.log`:
524 accepted units/all1412 functions. Source-present is not exact acceptance.
The local suite now has620 tests. Python environment and public CI were repaired
previously; do not reopen them without a new failure.

## Current bounded work: TenshiObject64CD50

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

Next: reconstruct the complete Alice Fighter slot28 root4E9F50 (provisional
42721-byte main). No complete AliceActionState source or match unit currently
exists. Sakuya4CADB0's smaller report span is misleading for this choice: its
ownership ledger already pins74941 code bytes including ten remote chunks.
Re-run bounded preflight, reconcile Alice's full CFG/metadata against the exact
PE and review callee contracts before writing the complete body and comparing
it early.
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
