# TH10.5 reconstruction handoff

Current as of 2026-10-18. This page contains operational state; detailed
checkpoints are in [the October 18 archive](RE_HANDOFF_HISTORY_2026_10_18.md),
[the October 2 archive](RE_HANDOFF_HISTORY_2026_10_02.md) and
[the September archive](RE_HANDOFF_HISTORY_2026_09_26.md). Live ledgers and
fresh canonical comparisons override historical prose.

## Target, workflow and acceptance

Use only original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Read [AGENTS.md](../AGENTS.md), [architecture](ARCHITECTURE.md) and
[workflow](RE_WORKFLOW.md) before changing reconstruction state. Use one
writable session, one bounded unit and serial VC8 builds. Keep heavy work at
nice10/CPU0; clean obsolete products periodically. Do not delegate matching.

```bash
git status --short
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
```

The target passes verification. The attached IDA session still reports a
SHA256 beginning `10350095`, so do not use its semantic data. Hash-attested
raw PE analysis is available. Independently re-attest any direct Ghidra
project before using it; do not use the factory adapter or patch target bytes.
Nine primary database files remain unchanged in this checkpoint.

Last checked ledger census: 4023 candidates; 1542 authored, 1415 excluded,
1066 in review; 1455 mapped, 1436 source-present; 1333 exact / 225099 bytes;
516 match units. These are ledger totals, not a cold aggregate replay.
`claims.csv` remains header-only. Source presence, mapping and diagnostic
interval equality confer no exact credit. No progress ledger changes here.

The user prioritizes the large Reimu root, requests commit **and push**, and
asks to avoid routine full historical/all-unit replays. Run focused affected
checks; a deliberate aggregate percentage claim requires a cold
`verify-exact-units.py --all`. The README already contains the requested
notice about ongoing reconstruction and the substantial work still needed.

## Current Reimu source checkpoint

Boss: `Reimu_dispatch_action_state_vslot28 @478FA0`, authored but still
unclassified/declaration-only. Callable `[478FA0,48CE2E)` is 81550 bytes,
SHA256 `dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The target CFG covers 20243 reachable instructions / 81488 code bytes, plus
62 bytes of proved alignment gaps, 1188 direct calls to 32 callees, 153 RETs
and 11 switches. See [boundary evidence](REIMU_ACTION_ENTRY_2026_10_17.md).
Do not promote staging methods to original compiler boundaries or add an
implemented/matches row without complete supporting evidence.

The newest source change is five explicit float conversions across
`ReimuActionStateMovementAttackCases.hpp`, `ReimuActionStateMid540Cases.hpp`
and `ReimuActionStateMid550Cases.hpp`. They recover all seven target FIMUL
operations in actions 89, 545/546 and 550/551 without changing arithmetic
order, ABI, profile or adding rounding stores. Complete operand preparation
blocks of 54/37/37/37/37/45/58 bytes agree. These are internal diagnostics,
not exact functions or partial-byte credit. The previous shared action10
landing recovery for 202/203/225/226 remains selected.

Fresh evidence and limits are in
[the x87/type checkpoint](REIMU_X87_OPERAND_TYPES_2026_10_18.md).
Current pins:

| Artifact | Value |
| --- | --- |
| Ordinary object SHA256 | `1962c4202fdab172c3a6d95ee4dd563957f1653334d66a0d07cff07b001086b5` |
| Generated source SHA256 | `72df0da474154f8203df746ae8c5484fe41d697b65e7ccb34e2c411d92b4b307` |
| Ordinary/genuine canonical payload SHA256 | `967ab8fdda07897afedf43e034bd85e0d5d756afdc915b05394f9a6977ede6c5` |
| Payload / prefix / frame | 82808 / 81436 / 570h |
| First strict mismatch | +541 / 4791BD, conditional-branch operand at 4791BB |

Genuine and ordinary payloads agree completely, including all 2471 replayed
fields; 1281 HIGHLOWs and eight separate linker alignment bytes qualify.
All 11 switches and 15 request-buffer contracts pass. Complete source
physical partitions for all 32 direct callees, indirect calls and RETs are
preserved, including multiplicity. Genuine linking remains nonexact to target.

Selected-source execution passes **0/4628** affected cases: 89=320,
545=1366, 546=1366, 550=788, 551=788. Real stops: 3516 RETs, 24 effects,
1088 owned-object requests. All seven multiplication sites execute; explicit
empty x87 entry tags produce the predicted one live value/TOP7. Partial
movement and integrated-low rebuilds pass 0/99 and 0/59. Returning world
callbacks, subsequent fan/ring iterations and arbitrary FP environments are
still outside this proof. No all-unit replay or new exact credit was claimed.

Conditional whole-CFG x87 dataflow covers target 20243 and source 20251
instructions, with maximum depths 3/4 and empty stacks at all 153 RETs.
The model's callee-effect and ordinary-path assumptions are explicit in the
focused note. Target FSTP at 47973A and source 4792D2 consume a live FLDZ
zero; setup/advance entries 47973C/47973E and 4792D4/4792D6 are empty.
This does not establish the cause of the remaining sharing differences.

## Next reconstruction work

1. Resolve action9's coupled landing/advance membership from target control
   flow and x87 live values. Factoring its landing previously fixed one group
   while splitting the correct 0/2/9/71/72/74/145 advance group.
2. Resolve 197/198/608/658 height/clear/sequence memberships, then distinct
   300/320 prefixes and the effect/landing/action-gate partitions.
3. Preserve recovered 465190 owned-object and 45C030 wave partitions and the
   202/203/225/226 common landing. Indirect counts remain target 220/source 219;
   only 410/416 have per-action deficits. Slot identities remain provisional.

The six differing direct partitions remain 4351C0, 435240, 435D60, 45AF40,
473DD0 and 478EE0. Total call counts alone can conceal incorrect memberships.
Read [coupled exit constraints](REIMU_LANDING_EXIT_CONSTRAINTS_2026_10_18.md)
and [shared action10 landing](REIMU_SHARED_ACTION10_LANDING_2026_10_18.md)
before repeating goto, switch, helper-visibility or reset controls. Current
same-source /Os, /fp:fast and RTM probes do not recover the seven FIMULs;
none is selected. Do not repeat unchanged negative probes without new evidence.
Original source/TU visibility, remaining FP scheduling and whole-root equality
remain unknown. Other roots and prior accepted units are indexed in
[the archived handoff](RE_HANDOFF_HISTORY_2026_10_18.md).

## Artifacts, reproduction and final gate

`build/reimu-ltcg/` retains the current 164-file genuine provider/cache set.
`build/reimu-x87-state/` retains focused receipts, native/static evidence,
private adapters and resource/cleanup records. Older generated report paths
may have been cleaned; regenerate them from the retained recipes and dated
notes. Never treat an old ignored report as a current comparison. Preserve
`resources/`, compiler installs and the primary Ghidra project.

The source checkpoint's genuine producer is:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
```

It qualifies ordinary/linked correspondence and affected provider comparisons;
it does not accept the root. See the focused note for smaller sharing,
request-buffer and native commands. The current producer peaks about 313 MiB;
static/native qualification peaks about 291/151 MiB, serially on CPU0.

Before **every commit, push or pull request**, run in the finished worktree:

```bash
python3 scripts/ci.py
git diff --check
```

A local CI pass is mandatory; GitHub Actions does not substitute. Any later
source, ledger, script, test or generated-progress edit requires the gate again.
Remove disposable CI bytecode afterward. Commit stable work with
`gpt-6.1-sol: ...`, push, then verify the remote branch equals local HEAD and
check the worktree is clean. Do not commit executables, data, analysis
projects, generated reports, toolchains or credentials.
