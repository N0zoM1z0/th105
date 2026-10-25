# TH10.5 reconstruction handoff

Session stopped for the user's requested cleanup and handoff on 2026-10-25.
The next agent should resume **TenshiObject update 0x0064CD50**, whose private
source is still incomplete and uncompiled. No reconstruction process is left
running. Read `AGENTS.md`, `docs/ARCHITECTURE.md`, `docs/RE_WORKFLOW.md` and this
handoff before changing state. One writable session, no subagents/concurrent VC8
or Ghidra processes; `config/claims.csv` stays header-only.

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

Last reconstruction checkpoint: `535e1b9`, remote CI40174101247 passed.
The subsequent maintenance checkpoint changes documentation/artifact storage,
with no game source, ABI, profile, relocation or acceptance change.

| Ledger state | Count |
| --- | ---: |
| Provisional / authored / excluded / review candidates | 4024 /1596 /1418 /1010 |
| Mapped / source-present | 1582 /1563 |
| Exact functions / authored bytes | 1412 /381108 |
| Configured units / functions | 602 /1570 |

These are live ledger counts, not a new aggregate cold claim. The last aggregate
receipt remains `build/exact-first-remilia-action-entry-20261025/cold-all.log`:
524 accepted units/all1412 functions. Source-present is not exact acceptance.
The latest local suite has604 tests. Python environment repair and public CI
are complete; do not reopen them without a new failure.

## Current bounded work: TenshiObject64CD50

[Target/ABI evidence and exact resume notes](TENSHI_OBJECT_UPDATE_2026_10_25.md).
The function remains unclassified/source-missing in the public ledgers: no
name, implementation selection, match unit or exact credit has been added.

- Main41001 bytes, full41984 through657150; complete raw CFG closes9797 reached
  instructions,67 RET0s and eight exact internal alignment bytes, no escaping edges.
- Full payload owns28 tables/195 destination DWORDs,199 primary remap bytes
  (800..998, not999) and four metadata alignment bytes. It directly abuts the
  independent657150 initializer; do not require nonexistent trailing INT3 padding.
- thiscall/RET0, frame2A8 and `AND ESP,-8`. Preserve observed dataflow; no dummy
  double, forced stack alignment or register shaping.
- 427 direct calls/22 entries;22 primary virtual calls plus one factory call.
  Surface-range filling is **stdcall/RET12**. Factory slot04 uses parent+658
  as receiver and nine arguments/RET36; it is not a primary Object virtual.
- Actual argument-slot tracing closes97 requests and53 packet bases/652 bytes.
  p244 has4 words, p384 has5, p520 has4 and is also passed with count3.
  Their native calls are654639/65473F/654AF8; never assume every packet has3 words.
- One readonly384MiB Ghidra run completed, all nine primary database hashes
  unchanged. Its output warns about stack spacebase; treat it as a hypothesis.
- `.analysis/exact-first-tenshi-object-update-20261025/probe.cpp/.hpp` contains
  the declaration view and **only actions800/801**. It is incomplete, uncompiled
  and unselected; independently review those branches too. Continue at810,
  then complete all28 nondefault actions/default before the first full comparison.

Raw observations and receipts:
`build/exact-first-tenshi-object-update-20261025/`.
Private recipes:
`.analysis/exact-first-tenshi-object-update-20261025/` (`raw.py`, `ghidra.py`,
`Th105TenshiObjectUpdate.java`, `frame_facts.py`, `packet_predecessors.py`,
`packet_counts.py`, `review.py`). The roster shared-callee census was refreshed
before this analysis; refresh again before any new action-family decompile.

Next: check those files, finish manual source, compile the first complete body
and compare **all41984 bytes** early. Let actual differences drive bounded trials.
Keep numeric states/offsets and declaration-only providers; defer naming/cleanup.
Never promote a partial source or use counts/similarity as exact evidence.

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

The31 active ignored Tenshi files also have a portable, hash-verified copy:
`build/handoff-cleanup-20261025/tenshi-resume.tar.gz` (262512 bytes), SHA-256
`9e28ae84cac98d8b96a102901b29dbbd0250d0c32fee74119913eab674c3d6ff`.
This bundle is **local, not in Git**; a fresh clone needs it copied separately.
It includes recipes/draft/observations, not target, compiler or primary DBs.
Its repository-relative members can be restored after checking
`tenshi-resume-members.json`; avoid overwriting newer work.

Final gate in the finished worktree:

```bash
PYTHONDONTWRITEBYTECODE=1 taskset -c 0 nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

The no-bytecode setting avoids recreating the removed cache during maintenance.
No active goal remains from this session; wait for the new agent's instructions.
