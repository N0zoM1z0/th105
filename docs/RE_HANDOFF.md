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
The newest CPU-root checkpoint intentionally adds accepted metadata in a
verified private Ghidra copy, reopens it for readback, then replaces the primary
project. Target/mapped bytes remain unchanged; nine new primary file hashes
are recorded in `build/reimu-cpu-root/primary-db-after.json`.

Last checked ledger census: 4023 candidates; 1542 authored, 1415 excluded,
1066 in review; 1456 mapped, 1437 source-present; 1333 exact / 225099 bytes;
517 match units. These are ledger totals, not a cold aggregate replay.
`claims.csv` remains header-only. Source presence, mapping and diagnostic
interval equality confer no exact credit. This checkpoint adds one source
selection/probe unit and no exact result.

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

## Current Reimu CPU root

A second large Reimu root is now identified: `Reimu_update_cpu_action_policy`
@48D390, vslot+58. Callable `[48D390,49120F)` is15999 bytes, SHA256
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.
All4126 instructions are reachable;157 calls target five helpers, four switch
tables close and52 RETs have balanced stacks. The callable ends before its NOP
and metadata. `giant-action-switches.toml` now pins19 action and21 policy
primary destinations plus two checked-front-record tables. Its full C++
candidate is now source-present in `src/characters/ReimuCpuActionPolicy.cpp`,
with probe unit `gpt-web-reimu-cpu-action-policy` and no exact credit. See
[CPU root evidence](REIMU_CPU_ROOT_2026_10_19.md).

Real target-to-target policy0 execution passes0/16000 finite cases, visiting
all1488 Reimu and1486 default policy0 instructions and confirming actual rolls
0..99. This supports shared selection logic, not whole-root equivalence.
An ABI-adapted default-source reference is canonical-byte-identical to the
fresh default object at the same replay address, but differs from Reimu on
1065/5000 complete-return cases. Its command728 and conditional-RNG differences
preclude selecting a blind source copy. The default comparator retains its
known+12E/5F20AE nonexact result.

The manual Reimu tree preserves actual helper execution and the corrected90
lower bound/180 equality. Its initial snapshot-source checkpoint is recorded
in [complete source evidence](REIMU_CPU_SOURCE_2026_10_19.md).
The action-counter checkpoint removes its scalar snapshot and reads the
signed764 field directly. This recovers separate signed bounds: decoded
entry-to-common word JA/JBE branches change52->0 (target0), while JL/JG
change38/2->92/55 (target97/56). These physical-interval counts are diagnostics,
not correctness scores. Candidate prefix/payload are now15860/16401; strict
comparison first differs at+97/48D427 where a flag-preserving constant1 LEA is
hoisted ahead of JLE. The earlier+12E/302-byte-prefix result is historical.
See [counter-read evidence](REIMU_CPU_COUNTER_READS_2026_10_19.md) for those
controls. Direct read-only Ghidra analysis leaves
all nine primary DB pins unchanged; no IDA semantics were used.

Current source additionally caches policy0's full int selector result and
uses explicit signed-word consumption. It reproduces target MOV ECX,EAX;
ordinal/encoding comparison of the whole candidate finds only this functional
instruction changed (plus genuine post-RET alignment). All47 metadata code
pointers preserve destinations. Current source SHA256 is
`556098b785ef77ed7b8a49b55fa4c72cd4cf6e60f29dfc7dd88fca12baa3754a`,
canonical16401-byte payload
`70905d5a0663e6c41cbdc5dfd94a9ee56b8ed3a197011432c5270e87b2990ae4`.
Prefix/first mismatch remain15860/+97. See
[policy0/x87 evidence](REIMU_CPU_POLICY0_X87_2026_10_19.md).

The root still has117 selector sites versus target121 and50 RETs versus52.
Policy0 CFG closure localizes all four missing selector copies: target37
sites/1488 instructions, candidate33/1359. Do not replace its cached selection
roll mechanically: target76A has only stores and ECX carries the result.
Counter reset/RNG preparation already matched; changing neutral store order
also causes undesired partial neutral/facing sharing and remains unselected.
The CPU probe now sets FPSW0/FPTAGFFFF explicitly and checks both TOP and tags
at the stop. Old reports did not attest empty tags and remain historical.
Fresh empty-entry replays pass0/21528 for Reimu, and0/21528 each for default/Aya
after this shared fixture correction. Reimu selection confirms real rolls0..100
and all1488 target instructions. All46420 observed selector entries/returns
per side are empty/TOP0; policy/timer writes show residual scheduling
differences outside those calls. A source-visible actual selector under/Ob1
remains27/27 and leaves the caller completely unchanged. No new exact credit
or aggregate cold replay is claimed.

Newest terminal observations on the unchanged70905d5a payload pass0/16160
selection cases with both terminal and x87 collection. They visit all1488
target policy0 instructions and pair66 CALL/publication/RET records, with
50 target/49 source observed RETs. Caller correspondences have five
non-bijective components: both wrong merges and extra copies contribute to
the net four-selector deficit. Source4904B7/4904C3/4904CF alone serves six
target CALL/timer/RET paths, including bounds15/20/30 and policies9/10/11/12.
The opt-in `--selection-terminals` mode preserves genuine execution and rejects
unreviewed root RETs. An inline two-write operation is byte-identical;
expanded terminals and three cumulative range-gate controls remain unselected,
even where the entry's first302 bytes agree. Selected source and exact ledgers
are unchanged. See [terminal sharing](REIMU_CPU_TERMINAL_SHARING_2026_10_19.md).

## Next reconstruction work

The active scope is the Reimu CPU root: use the complete candidate, coupled
terminal witnesses and original-helper execution to recover CALL/publication/RET sharing and genuine
constant/TU/register lifetimes. Keep the full result/low-word policy model;
do not repeat a missing live value at selector entry explanation without new
evidence. Preserve direct signed764 reads and
the corrected180 equality/RNG order. Do not count finite execution or
diagnostic branch counts as exact progress.
The81KB action root remains an open priority with the constraints below.

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

`build/reimu-cpu-root/` retains the newest complete boundary packet, target
mapper output,16000-case bridge,5000-case rejected reference and metadata
readback receipts. The private Ghidra hypothesis is under
`.analysis/reimu-cpu-root-20261019/`; its copied working project is removed.
`build/reimu-cpu-source/` retains the full-source strict/native reports,
regression controls and unchanged primary DB pins. Its newer typed hypothesis
is under `.analysis/reimu-cpu-source-20261019/`; no copied project is retained.
`build/reimu-cpu-shape/` retains current field-read builds/native reports,
counter/selector CFG profiles and rejected controls. Its read-only typed
hypothesis is under `.analysis/reimu-cpu-shape-20261019/`; alias removed.
`build/reimu-cpu-policy0/` retains current full-width cache, normalized CFG,
selector/publication x87 observations, fresh three-root empty-tag replays and
the rejected helper-visibility control. Its384MiB read-only Ghidra recipe is
under `.analysis/reimu-cpu-policy0-20261019/`; no alias/project copy retained.
`build/reimu-cpu-setters/` retains the current coupled terminal/x87 witnesses,
closed policy0 CFG profiles and five rejected ordinary-C++ controls. Its
read-only Ghidra recipe is under `.analysis/reimu-cpu-setters-20261019/`;
nine DB pins remain unchanged and the project alias is removed.
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
