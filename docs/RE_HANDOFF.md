# TH10.5 reconstruction handoff

Current as of 2026-10-19. This page contains operational state; detailed
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

The newest source change recovers the target's shared 197/658 and 198/608
surface-landing tails with their real int sequence parameter. Complete height,
motion-clear, sequence-callback and RET memberships agree for both pairs; the
entire candidate vslot+C partition now agrees. No previously correct complete
partition regresses. Only two eight-byte windows differ from the prior canonical
source payload; all remaining 82792 bytes are unchanged. These are root
reconstruction diagnostics, not exact functions or partial-byte credit.
See [shared sequence landings](REIMU_SHARED_SEQUENCE_LANDINGS_2026_10_19.md).

Newest analysis proves that one shared C++ advancement expression can yield
four compiler copies, including the unwanted separate9 site. Listed/plain
82808-byte payloads agree completely. Conditional full-CFG x87 dataflow and
5752 actual-helper cases find empty advancement entries; all5292 observed
entries per side have no occupied x87 tags and TOP0. RTM retains the same
complete sharing as SP1 on this source. None of these controls is selected;
current source/pins below are unchanged. See
[low9 call cloning](REIMU_LOW9_CALL_CLONING_2026_10_19.md).

The five explicit float conversions from the preceding checkpoint retain all
seven target FIMUL operations in actions 89, 545/546 and 550/551; their complete
preparation blocks remain unchanged. The 202/203/225/226 common action10 landing
also remains selected. The earlier x87 assumptions and limits remain in
[the x87/type checkpoint](REIMU_X87_OPERAND_TYPES_2026_10_18.md).
Current pins:

| Artifact | Value |
| --- | --- |
| Ordinary object SHA256 | `f1096e59b4c8f07b8f3fd38e8d6f16dfdbc052e7bac3a1d68854b91ca01587be` |
| Generated source SHA256 | `8020a8c37cd98566d534663bcd4c47258e34b3c6a28e656c7f270096da048e30` |
| Ordinary/genuine canonical payload SHA256 | `9a97f6f55a43cf79142eabf22cf738406f8ad68c7a55732b200219e80a2dcbd4` |
| Payload / prefix / frame | 82808 / 81436 / 570h |
| First strict mismatch | +541 / 4791BD, conditional-branch operand at 4791BB |

Genuine and ordinary payloads agree completely, including all 2471 replayed
fields; 1281 HIGHLOWs and eight separate linker alignment bytes qualify.
All 11 switches and 15 request-buffer contracts pass. The complete ownership
census covers all 32 direct callees, indirect calls and RETs, including
multiplicity. Previously equal groups are preserved; the two incoming landing
pairs are corrected. Genuine linking remains nonexact to target.

Fresh selected-source execution passes **0/2548** affected cases: 197/198=384
each, 608=1370, 658=410. Stops are 2440 RETs, eight effects and 100 owned-object
requests; all four actions execute real landing helpers. Integration/default/
common/unresolved740/nonflat-surface checks pass 0/1829. Rebuilt independent
movement and low staging methods pass 0/99 and 0/59. Returning world callbacks
and arbitrary world/resource graphs remain outside this proof. No new exact
credit or all-unit replay is claimed.

The preceding checkpoint's conditional whole-CFG x87 dataflow covers target
20243 and source 20251 instructions, with maximum depths 3/4 and empty stacks at all 153 RETs.
The model's callee-effect and ordinary-path assumptions are explicit in the
focused note. Target FSTP at 47973A and source 4792D2 consume a live FLDZ
zero; setup/advance entries 47973C/47973E and 4792D4/4792D6 are empty.
This does not establish the cause of the remaining sharing differences.

## Next reconstruction work

1. Resolve action9's coupled landing/advance membership with new compiler/TU
   or source evidence. Explicit shared exits still split the correct
   0/2/9/71/72/74/145 advance group. The newest listed/plain, conditional x87
   and actual-entry proof excludes a missing cleanup on the exercised paths;
   repeating goto, branch inversion or constant-parameter controls is not useful.
2. Preserve the now-recovered 197/658 and 198/608 memberships. Their incoming
   ECX scheduling still differs. Resolve distinct 300/320 prefixes and the
   effect/landing/action-gate partitions.
3. Preserve recovered 465190 owned-object and 45C030 wave partitions and the
   202/203/225/226 common landing. Indirect counts remain target 220/source 219;
   only 410/416 have per-action deficits. Slot identities remain provisional.

The six differing direct partitions remain 4351C0, 435240, 435D60, 45AF40,
473DD0 and 478EE0; height/clear membership differences now concern low9 alone.
Total call counts alone can conceal incorrect memberships.
Read [coupled exit constraints](REIMU_LANDING_EXIT_CONSTRAINTS_2026_10_18.md)
and [shared action10 landing](REIMU_SHARED_ACTION10_LANDING_2026_10_18.md)
before repeating goto, switch, helper-visibility or reset controls. Earlier
/Os, /fp:fast and RTM probes emitted no FIMULs on the pre-conversion source.
The newest converted-source RTM control retains all seven FIMULs, but leaves
the same bad advance sharing as SP1. None is selected. Do not repeat unchanged
negative probes without new evidence.
Original source/TU visibility, remaining FP scheduling and whole-root equality
remain unknown. Other roots and prior accepted units are indexed in
[the archived handoff](RE_HANDOFF_HISTORY_2026_10_18.md).

## Artifacts, reproduction and final gate

`build/reimu-ltcg/` retains the current 164-file genuine provider/cache set.
`build/reimu-low9-x87/` retains the newest cloning, listed/plain, RTM, full-CFG
and native-entry recipes/reports. Controls are unselected and disposable.
`build/reimu-sequence-landings/` retains the previous baseline/control recipes,
complete partition census, affected native adapter and qualification receipts.
`build/reimu-x87-state/` retains earlier focused receipts, native/static evidence,
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
