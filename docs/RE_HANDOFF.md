# TH10.5 reconstruction handoff

Current bounded checkpoint: score display-name selection **42E990, 990/990**.
Its complete source and canonical comparison are recorded in
[SCORE_DISPLAY_NAME_2026_10_27.md](SCORE_DISPLAY_NAME_2026_10_27.md).
The original accepted 42D3F0/42ED70 family remains unchanged. The already-started
full replay passed all529 units/1417 functions; its first CI found only stale
inventory expectations, corrected before final CI. Future iterations use focused
new/affected-unit builds, not routine full cold rebuilds. Final CI remains
pending at writing; terminal receipts are under `build/frontier-42e990-20261027/`.

The complete preceding handoff is preserved in
[October26 history](RE_HANDOFF_HISTORY_2026_10_26.md). Earlier chronology and
private artifact recovery remain linked from that archive and [ARTIFACTS.md](ARTIFACTS.md).
Live ledgers and fresh command output take precedence over historical counts.

## Start here

1. Read `AGENTS.md`, this file, `docs/ARCHITECTURE.md` and `docs/RE_WORKFLOW.md`.
2. Inspect Git status and the source/evidence document for the intended scope.
3. Use only `scripts/repo-python`, then run the four bounded preflights below.
4. Keep one writable bounded scope, no subagents or concurrent VC8/Ghidra jobs.
   `config/claims.csv` remains header-only. Builds use CPU0/nice10 serially.
5. Compare the first complete medium/large source early. Test one supported
   question per trial; retain byte-neutral results and switch without a grid.
   Review family peers independently. Defer naming/abstraction until exactness.

```bash
git status --short
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/check-ida-mcp.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
```

## Immutable target and environment

Only original Japanese TH10.5v1.06a is valid: SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
image base400000, entry68B9D2. Do not substitute another patch/localization.
The direct IDA launcher currently lacks mcp1.26.0/uv. Factory native IDA was
freshly attested on October27 to this exact target, entry and mapped entry bytes;
its inventory, disassembly, decompilation and xref operations succeeded.
Any Ghidra use requires separate import/entry/mapped-byte attestation. Never
patch the target or infer ownership from disassembler auto-analysis.

The isolated environment pins Python3.11.14, Capstone4.0.2, pefile2024.8.26,
Unicorn1.0.2 and setuptools75.8.0. The repo launcher enforces it. Preserve the
active `.venv`, its external UV interpreter and installed VC8 SP1 toolchain.
Use the VC8 x86 ABI and exact target facts;42 LTCG Rich records do not establish
that a particular standalone mismatch requires LTCG.

## Current durable state

| Ledger state | Count |
| --- | ---: |
| Provisional / authored / excluded / review candidates |4024 /1608 /1419 /997 |
| Mapped / source-present |1597 /1569 |
| Exact functions / authored bytes |1417 /390476 |
| Configured units / functions |618 /1586 |
| Accepted units |529 |

The preceding checkpoint passed all528 accepted units/1416 functions and389486
bytes. Current ledger adds one unit/function and990 bytes. The completed
`cold-all.log` passes all529 units/1417 functions; `local-ci-final.log` is the
post-expectation-correction final gate. Preserve the first failed CI receipt.
Both live under `build/frontier-42e990-20261027/`.

`implemented.csv` means selected source-present; `matches.csv` requires canonical
100% equality against this target. Complete unselected source already exists
for many nonexact roots. Do not infer that a function is unwritten merely from
its absence in implemented.csv. No helper inherits a caller's ownership/match.

## Latest score-family checkpoint

| Target | State | Source / evidence |
| --- | --- | --- |
|42D3F0 |1155/1155 exact |`src/config/ScorePersist.cpp`; [persistence](SCORE_PERSIST_2026_10_26.md) |
|42ED70 |2428/2428 exact |`src/config/ScoreDefaults.cpp`; [defaults](SCORE_DEFAULTS_2026_10_26.md) |
|42F6F0 |Complete1666-byte source vs1672;564 unequal positions, missing6; unselected |`src/config/ScoreLoad.cpp`; [loader](SCORE_LOAD_2026_10_26.md) |

Shared definitions: `src/config/ScoreDataDefaults.hpp`. Constructor43E1A0
independently proves20 map/vector slots. Defaults and persistence use only15
roster keys; source layout is a bounded view, not the complete original owner.

Persistence's first whole source was1155 bytes with80 differences, first42D661.
One real count shared by serialized roster size and loop bound closes all1155
bytes, SHA7c1f3777. All360 instructions/359 reached, RET0,3C-frame EH/cookie,
19 checked-container guards and full relocations are accounted for. Four native
and candidate cases pin332-byte serialization, duplicate records, values above
200, ignored open/encode/write failure results, source preservation and cleanup.
Actual I/O, compression providers and EH unwinding are not executed by fixtures.

A genuine three-source TU preserves both exact roots and leaves the entire
loader residual/SHA9979a9c5 unchanged. This finite definition-visibility lane is
closed. Original nominal types/TU and loader stack/iterator scheduling remain
unknown; no LTCG-impossibility claim follows. The prior bootstrap return-type
repair retains its complete3722-byte/11-difference nonexact body.

Current scope receipts and raw decode:
`build/frontier-42d3f0-20261026/` (`formal-first.json`, `formal-second.json`,
`formal-audit-first.json`, `formal-audit-second.json`, `family-tu-summary.json`,
`origins-write.log`, `origins-check.log`, `cold-all.log`, `local-ci.log`).
Private first/count-control/family-TU sources and replay recipe:
`.analysis/frontier-42d3f0-20261026/`.
The new selected root adds1155 exact authored bytes; no provider receives credit.

## Parked work

Do not reopen these lanes without the independent evidence their dated notes
request. The full history records commands, source pins and unknowns.

- Spell resource CSV4343A0 is exact1646; filtered433B30 remains1987 bytes/two
  operand differences. The genuine family-TU lane is closed.
- Collision debug45E950 is exact3087. Rectangle4012A0 remains394 versus395,
  85 unequal positions; native Z0.5 and finite lifetime controls are retained.
- Scene bootstrap43E2E0 remains3722/11 stack-home differences; effect loader
  437EC0 remains2528/79 differences; Fighter PAT461B70 remains3898 versus3885.
- Profile deck render448F60 is2521/1622 differences. Native execution rejected
  a push-relative missing-count misread; correct zero counts agree in32 events.
- Complete giant sources/hypotheses for Tenshi64CD50, Alice4E9F50, Youmu53CEA0
  and Yuyuko56F700 remain saved in their documented selected/unselected states.
  Aya61F0B0's complete4859-byte payload still has two operand differences.

42E990 is now independently reviewed and exact. Small providers and constructors
remain independent unknowns unless positively classified and compared.

## Private recovery and cleanup

The current-scope portable bundle is
`build/handoff-cleanup-20261026/score-family-resume.tar.gz`; its member hashes and
verified archive SHA are in `score-family-members.json` and `bundle.json` in the
same directory. List the archive before restoring repository-relative members;
avoid overwriting newer work. This ignored local archive is not included by a
Git clone. It excludes target PE, compiler installs, databases and credentials;
those remain separate local inputs. Final CI/remote receipts remain loose in
the current build scope. See [artifact details](ARTIFACTS.md).

Source-backed bytecode cleanup and protected-file/worktree checks are recorded
in `build/handoff-cleanup-20261026/cache-cleanup.json`, `protected-before.json`
and `protected-after.json`. Unknown cache files are retained. Primary Ghidra
state remains under `.analysis/iku-vslot28-20261002/project/`, with the retained
snapshot at `.analysis/archive-loader-shape-20261019/primary-before/`.
Six older detached worktrees contain uncommitted work; preserve them and their
frozen inputs. Their presence does not authorize parallel reconstruction.

## Final gate and future commits

Run the focused affected comparisons first. Shared headers/types/flags/TU or
relocation changes require directly affected-unit replay. Preserve unchanged
acceptance receipts for incremental totals; do not rebuild the whole corpus
routinely. Full cold replay requires an explicit request or demonstrated
repository-wide invalidation that cannot be narrowed.
Every commit/push/PR requires the finished local gate; remote green is additional.

```bash
PYTHONDONTWRITEBYTECODE=1 taskset -c 0 nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
git diff --cached --check
```

Any later source, ledger, script, test or generated-progress edit requires the
local gate again. Commit prefix: `gpt-6.1-sol: ...`. Keep executables, game data,
analysis databases, compiler installs, generated reports, credentials/private
keys and `.tools/mcp_for_gptweb/.env` out of Git.
