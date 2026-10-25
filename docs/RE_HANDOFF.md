# TH10.5 reconstruction handoff

Active reconstruction resumed on2026-10-25 under the user's large-function,
whole-comparison-first direction. Current bounded root is **TenshiObject update
0x0064CD50**, now complete source-present/nonexact. One writable session, no
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
- Formal and independent fresh builds emit42916 bytes, SHA2391a745...,
 40643 unmasked differences, first64CD58. Aligned frame2C0 and83 RETs versus
 2A8/67. Per-action direct/indirect call censuses agree for all28 actions;
  physical frame-call owner groups remain five versus six. This is nonexact.
- Selector-zero/default900 burst controls have no native source initialization;
  ordinary uninitialized locals preserve the source hypothesis. Scratch-dependent
  behavior and original intent remain unknown; no equivalence claim is made.
- All literal/global aliases are isolated; no accepted unit inputs changed.

Receipts: `build/exact-first-tenshi-object-update-20261025/` (`formal.log`,
`formal-full-audit.json`, `cold-build.log`, `cold-full-audit.json`,
`first-complete.json`, `target-audit.json`). Private recipes and first/control
sources: `.analysis/exact-first-tenshi-object-update-20261025/`.

Next: one evidence-backed lifetime/float-transfer or shared-exit question, then
recompare the whole41984-byte payload. Avoid a frame/flag/spelling grid; preserve
repeated neutral controls and switch when no new evidence remains. Nominal
names/layouts/TU ownership are still hypotheses. No exact credit was added.

## Parked questions

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
