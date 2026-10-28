# TH10.5 reconstruction handoff

Current bounded checkpoint: Patchouli request-branch ownership, argument
lifetimes and flight214 physical placement now follow native evidence.
The complete unselected candidate is55026/full55610, first+8, frame468.
All109 actions have matching per-action call/FP-site counts and91 resolved
payload homes; these diagnostics do not establish exactness. See
[PATCHOULI_ACTION_STATE_2026_10_27.md](PATCHOULI_ACTION_STATE_2026_10_27.md)
and build/frontier-50f200-20261027/formal-ownerorder*.json. No exact credit.

Preceding checkpoint: Yuyuko captured-X width and eight aim-argument
lifetimes now follow raw native storage/evaluation evidence. The complete
candidate remains unselected/nonexact,59456/full59672, first+8, frame4F0.
All100 payload homes resolve. See
[YUYUKO_ACTION_STATE_2026_10_28.md](YUYUKO_ACTION_STATE_2026_10_28.md)
and build/frontier-55d850-20261027/formal-lifetimes*.json. No exact credit.

Preceding checkpoint: Yukari aim argument lifetimes now follow the native
DX-outgoing-before-DY sequence at seven atan sites. Their local 32-byte windows
match; the complete candidate remains 57792/full58248, first+8, frame4E8.
See [YUKARI_ACTION_STATE_2026_10_28.md](YUKARI_ACTION_STATE_2026_10_28.md)
and build/frontier-57b030-20261028/formal-aimargs*.json. No exact credit.

Preceding checkpoint: Remilia circular request preparation now recovers
the native 4F0 frame. Its complete unselected 107-action candidate emits
62912/full63316, first +18; all sixteen tables and 101 payload homes resolve.
[KOMACHI_ACTION_STATE_2026_10_28.md](KOMACHI_ACTION_STATE_2026_10_28.md)
and [REMILIA_ACTION_STATE_2026_10_28.md](REMILIA_ACTION_STATE_2026_10_28.md)
record the separate scalar-angle and call-preparation causes. No exact credit.
Latest Remilia receipts: build/frontier-545090-20261028/formal-frame*.json.

Preceding Komachi f1df72c2 remains complete but unselected/nonexact:
64884/full65176, first +42, native 490 frame; 108 actions, seven tables and
94 payload homes. Byte-direction view is supported by its actual manager.
Receipts: build/frontier-5e20e0-20261028/formal-frame*.json.

Preceding Yukari b491d153 remains complete but unselected/nonexact:
57792/full58248, first +8; 124 actions and 101 payload homes resolved. See
[YUKARI_ACTION_STATE_2026_10_28.md](YUKARI_ACTION_STATE_2026_10_28.md).

Preceding Yuyuko97a2575e remains complete but unselected/nonexact:
59428/full59672, first+8;116 actions and100 payload homes resolved. See
[YUYUKO_ACTION_STATE_2026_10_28.md](YUYUKO_ACTION_STATE_2026_10_28.md).

Preceding Patchouli203faa8b remains complete but unselected/nonexact:
54466/full55610, first+8;109 actions and91 payload homes resolved. See
[PATCHOULI_ACTION_STATE_2026_10_27.md](PATCHOULI_ACTION_STATE_2026_10_27.md).

Preceding Tenshi80a9f71d remains complete but unselected/nonexact:49096/full48968,
first+8, two low-owner pairs merged. Its47,784-byte native root and110 actions
are covered; RNG widths, coordinate types, live packets and shared500/501 tail
were refined. See
[TENSHI_ACTION_STATE_2026_10_27.md](TENSHI_ACTION_STATE_2026_10_27.md).

Preceding b14285d6 Fighter reset460200 remains1247/1247 with25 differences,
unselected/nonexact. Directly affected fighter-input-phase remains exact; see
[FIGHTER_BATTLE_RESET_2026_10_27.md](FIGHTER_BATTLE_RESET_2026_10_27.md).

The preceding94f0f3b7 checkpoint corrects general hit resolver46BF80 semantics;
its complete1581/1579 source remains nonexact. See
[GENERAL_HIT_RESOLVER_2026_10_27.md](GENERAL_HIT_RESOLVER_2026_10_27.md).

The prior CBattleManager phase5 transition4724E0 remains991/991 exact, including
its separately audited generated GS/EH code and metadata; cd976369 passed the
final local CI. Weather emission660B30 remains12198/full12348 exact and
WeatherEffectObject entry664E10 remains1383/full1630 exact. The complete
InfoEffectObject and WeatherEffectObject update peers remain nonexact.

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
| Provisional / authored / excluded / review candidates |4024 /1621 /1419 /984 |
| Mapped / source-present |1610 /1582 |
| Exact functions / authored bytes |1427 /413799 |
| Configured units / functions |633 /1603 |
| Accepted units |537 |

The423a2cd checkpoint passed529 cold units/1417 functions and390476 bytes.
Subsequent focused comparisons add story refresh860, replay naming1322 and
pattern expansion1323, deck update1339, stage selection890, selection flow341
EffectObject entry2676; WeatherEffectObject entry1383 and weather emission12198 and battle phase5 transition991,
with unchanged prior receipts retained. Current totals are incremental, not a
new whole-corpus replay. Final CI is the current frontier's `local-ci.log`.

`implemented.csv` means selected source-present; `matches.csv` requires canonical
100% equality against this target. Complete unselected source already exists
for many nonexact roots. Do not infer that a function is unwritten merely from
its absence in implemented.csv. No helper inherits a caller's ownership/match.

## Latest score-family checkpoint

| Target | State | Source / evidence |
| --- | --- | --- |
|42D3F0 |1155/1155 exact |`src/config/ScorePersist.cpp`; [persistence](SCORE_PERSIST_2026_10_26.md) |
|42ED70 |2428/2428 exact |`src/config/ScoreDefaults.cpp`; [defaults](SCORE_DEFAULTS_2026_10_26.md) |
|42F6F0 |Complete1672-byte source;7 SIB-order differences; unselected |`src/config/ScoreLoad.cpp`; [loader](SCORE_LOAD_2026_10_26.md) |

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

The October27 native vector.clear recovery improves the loader to1672 bytes
with7 SIB-order differences (SHA6641fe76). A fresh genuine three-source TU
preserves both exact peers and leaves this new loader residual unchanged.
The four existing native/candidate observer cases agree; no new exact credit.
See the superseding loader note and `build/frontier-42f6f0-clear-20261027/`. Original nominal types/TU and loader stack/iterator scheduling remain
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
