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
1066 in review; 1457 mapped, 1438 source-present; 1333 exact / 225099 bytes;
518 match units. These are ledger totals, not a cold aggregate replay.
`claims.csv` remains header-only. Source presence, mapping and diagnostic
interval equality confer no exact credit. The Reimu CPU root remains
source-present in a probe unit with no exact result.

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

## Current ReimuObject entry initializer

Active root `ReimuObject_initialize_action_entry @4A1CE0` has complete
source in `src/characters/ReimuObjectActionEntry.cpp`, probe unit
`gpt-web-reimu-object-action-entry`, and no exact credit. RTTI/vtable6C40A4
slot3C proves ownership; raw CFG closes all1325 instructions/4892 bytes,
42 primary destinations, seven auxiliary switches,39 RETs and a596370 tail.
All65 direct CALLs to ten helpers retain their target multiplicities.

Five x-then-y chained scale assignments restore the822/903/904 return-copy
structure. Explicit906 sequence2/5 and3 edges into908's corresponding angle
tails then restore all548 adjacent metadata bytes and908's pointer/phase
schedule. Diagnostics are41/43, with no earlier equal owner lost; the
callable still ends4A2FFC without included alignment. Source SHA3803a002,
canonical5440-byte payload65298d36; strict first difference+1140/4A2E20.
Only14 callable bytes in906/999 remain different, in pointer/call registers
and preparation. No partial credit or whole-root native proof is claimed.

A genuine `/GL`+`/LTCG` diagnostic DLL now closes through real ordinary
providers, a full private404E60 texture-size provider and CRT startup. Its
quantized lookup declarations/definitions consistently return double;
the refined oriented provider becomes nonexact and is not promoted.
Independent replay verifies all247 relocation fields,181 PE HIGHLOWs,
named direct providers, literal bits and local table/code-pointer roles.
The linked payload equals the ordinary65298d36 payload: the same14 body
bytes remain, with zero metadata differences and the target10h local frame.
This context is a negative control, not original-TU or exactness evidence.
No shared helper/header/profile/binding is changed.

Raw45C390->vslot1C45C180->45C110->436760->4073C0 forwarding does not construct
an integer status. A private natural void/short selector compares202/202,
but does not uniquely prove the original return type or add accepted credit.
Changing the large root's discarded selector result is byte-neutral. The
prior-source RTM/SP1 and typed-velocity controls are also byte-neutral;
reading908's angle before its phase into a float adds32 callable bytes.
On the joined source, pointer captures, physical inheritance and9064-first
ordering all preserve65298d36 and remain unselected.
The next joined-source audit also finds direct RNG expansion, named short
arguments, discarded void result, implicit bool guard, typed color alpha,
GS and correctly ordered `/O2 /Ob1` byte-neutral. An int selector argument
regresses to113 body differences; unsigned short changes frame and conversion
shape. Extra905/907 angle joins and902/905..907 state-one joins regress; do
not generalize906's successful goto form. Complete receipts are below
`build/reimu-object-entry-registers/`. Reimu remains at14 body differences;
next bounded matching work returns to Aya's existing two-byte residual.

See [ReimuObject entry evidence](REIMU_OBJECT_ENTRY_2026_10_19.md).
Current receipts are below `build/reimu-object-entry-abi/`; preceding
receipts remain below `build/reimu-object-entry-lifetimes/` and
`build/reimu-object-entry/`. Previously checked raw/Ghidra RTTI establishes
eight entries including the complete object, with base offsets0/4/130h/330h.
Nine read-only Ghidra DB pins agree and the temporary alias is removed.
All23 accepted members across seven focused helper units replay exact at
the preceding source-recovery checkpoint; their inputs are unchanged here.
The effect unit's existing nonaccepted5F9350 probe remains nonexact. No cold
aggregate replay is claimed.

## Current YoumuObject entry initializer

Root543670 remains nonexact over5159 bytes, but independently proved
YoumuObject vtable6C50BC/slot+0C45C390 supports the local short sequence
declaration. It restores16 additional owner instruction/edge diagnostics,
6/30->22/30. Action902 now computes decay before phase; its complete
671-byte/157-instruction owner diagnostic agrees, for23/30 overall.
No partial or exact credit is added. Source SHA09dd36f0, canonical5488-byte
payload4b9bf0a4, prefix5156 and strict+80 remain. Conversion sites20/21 and
RETs22/23 still expose the different820/850 tail.823 registers and851 value
load timing remain unresolved. The ordinary851 pointer control still merges
distinct851/854 destinations and is rejected. See
[Youmu sequence-word evidence](YOUMU_ENTRY_SEQUENCE_WORD_2026_10_19.md).
The850 angle/comma and all-call direct-short-cast controls are byte-neutral;
state-before-value and explicit dispatch capture still merge851/854 into28
owners. A local restrict alias preserves29 but leaves851's early load and
changes other tails; it is not adopted. Raw factory53B1C0 proves separate
parameter allocation only on its positive-count path, not a global alias
contract. Sources and exact credit remain unchanged; receipts are below
`build/youmu-entry-evaluation/` and nine read-only Ghidra DB pins agree.
Whole-switch returns->breaks and the823 used payload's scope are also
byte-neutral. An outer-switch851 pointer capture, unsigned sequence word
and local fenv_access all regress the current target shape. See the same
evidence page and `build/youmu-entry-exit-context/`; none is selected. Seek
new ownership/type/TU evidence before repeating unchanged source controls.

## Current AyaObject entry initializer

Aya root61F0B0 remains two bytes from its4531-byte target body. The local
vslot+0C sequence parameter is short: it recovers all19 virtual preparations,
including eight CALL EAX sites omitted by the earlier11-site cohort. Raw
callee45C390 consumes the low word of a four-byte stack slot. A natural short
provider in `scripts/probes/animation-sequence-word-abi.cpp` is202/202 using
the existing animation-sequence unit comparator, with no duplicate credit.
The shared int facade and all accepted units elsewhere are unchanged.

Source SHA5ca0fb42/canonical4859-byte payload6f70b6f3 differs only at
61FCA7/+BF7 and61FCAF/+BFF: action856 uses EAX for the same heading-pointer
load/FLD where target uses ECX. Every other byte and all metadata agree.
Owner diagnostics31/33 and an almost-identical payload are not exact credit.
Direct800/810 angle-field writes remove the double float-copy carrier without
changing any ordinary payload byte. The new genuine `/GL /LTCG` diagnostic now
has the target10h local frame and4532 metadata start. Independent replay of
all188 relocation fields and128 HIGHLOWs proves its complete4859-byte payload
equals the ordinary candidate: the same two ModRM bytes remain. There are
no placeholder functions, fabricated callers, ABS code bindings or float/double
symbol aliases. The image is unexecuted and does not prove the original TU.
See [sequence-word ABI evidence](AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md).
A fresh384MiB/CPU0 read-only Ghidra pass attests imported/file identity,
entry, mapped text and the root before decompilation; nine DB pins agree and
its alias is removed. Current receipts are under `build/aya-entry-registers/`.
Fresh856 branch joins,
expanded target reads and852 scale chains are byte-neutral; a real two-float
direction value changes the frame, and int64 conversion introduces an unbound
`_ftol2` rather than testing the target call. Earlier action856 controls also
remain unselected: double Y offset, direct argument, EHa, raw word storage,
verified-offset inheritance and the inlined repeated operation. Sequence
snapshots/extra angle rounding regress the shape. Earlier
receipts are below `build/aya-entry-action856/`; nine read-only Ghidra DB
pins remain unchanged and its alias is removed. Two-byte register context
remains unknown; no exact credit.

The final5ca0fb42 getter audit is also byte-neutral for float value, const
reference and pointer member returns at856. Preserve the selected source;
receipts are under `build/aya-entry-getter/`. Aya remains nonexact; preserve
this checkpoint while the bounded BMP investigation below is active.

## Current CBitmapData BMP loader

Authored/source-present root@419FF0 has2230 callable bytes ending exclusively
at41A8A6; RET4 starts41A8A3. Its adjacent45-byte switch metadata is separate.
Fresh raw CFG reaches666/672 decoded instructions; six alignment instructions
remain in strict comparison. Three read-only Ghidra runs leave all nine
primary DB hashes unchanged; aliases are removed. See
[BMP boundary and source-form audit](CBITMAP_BMP_2026_10_19.md).

The old2197-byte section contained only2149 callable bytes, not2197. The
old claim that only stack coloring remained was unproved. Selected source
recovers combined word-mask RGB1555 dataflow and lets VC8 unroll scalar
palette loops. It emits2133 callable +3 alignment +45 metadata =2181 bytes,
still frame438h versus target430h and strict mismatch+10h. The larger97-byte
callable deficit is not an exact-size improvement. No new exact credit.

Both old and selected source pass149 modeled target/candidate execution
cases, with equal bitmap state, allocations, pixel data and cleanup actions.
The147 stable-format cases cover633 target instructions; two allocator
format-mutation stress cases extend coverage to661. These callbacks are model
assumptions, not observed real allocator behavior. All five accepted siblings remain exact.
Private ordinary controls and a real-FileReader diagnostic LTCG link remain
nonexact; the latter lacks the package-file helper provider and cannot support
acceptance. Receipts: `build/cbitmap-bmp-20261019/`. Continue reader/palette
lifetime and EH/TU evidence recovery; do not assume a compiler-phase cause.

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
not correctness scores. That candidate prefix/payload is15860/16401; strict
comparison first differs at+97/48D427 where a flag-preserving constant1 LEA is
hoisted ahead of JLE. The earlier+12E/302-byte-prefix result is historical.
See [counter-read evidence](REIMU_CPU_COUNTER_READS_2026_10_19.md) for those
controls. Direct read-only Ghidra analysis leaves
all nine primary DB pins unchanged; no IDA semantics were used.

The preceding source checkpoint cached policy0's full int selector result and
used explicit signed-word consumption. It reproduced target MOV ECX,EAX;
ordinal/encoding comparison of the whole candidate finds only this functional
instruction changed (plus genuine post-RET alignment). All47 metadata code
pointers preserve destinations. That source SHA256 is
`556098b785ef77ed7b8a49b55fa4c72cd4cf6e60f29dfc7dd88fca12baa3754a`,
canonical16401-byte payload
`70905d5a0663e6c41cbdc5dfd94a9ee56b8ed3a197011432c5270e87b2990ae4`.
Prefix/first mismatch remain15860/+97. See
[policy0/x87 evidence](REIMU_CPU_POLICY0_X87_2026_10_19.md).

That cache source has117 selector sites versus target121 and50 RETs versus52.
Policy0 CFG closure localizes all four missing selector copies: target37
sites/1488 instructions, candidate33/1359. Target76A has only stores and ECX
carries the result; this did not establish an original C++ local declaration.
The direct-field evidence below supersedes the earlier cache-only inference.
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

Preceding terminal observations on the70905d5a payload pass0/16160
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
were unchanged. See [terminal sharing](REIMU_CPU_TERMINAL_SHARING_2026_10_19.md).

The preceding field checkpoint reads signed76A directly. Ordinary VC8 eliminates all
reloads and retains MOV ECX,EAX while removing all44 non-target unsigned range
branches from reachable policy0. Twenty-one manual range gates are natural
field predicates; typed766/768 accesses and macro cleanup are independently
payload-identical. That source SHA256 is
`77234302d395e30a71dbded324b0696e142c0f53ff56cb0c2a34d590a03d7864`,
canonical16457-byte payload
`d3b9a02340e6c4611a46007991b816c5675310b7e1d2cd28221f9a08f2d6ed54`.
Prefix15916, first strict mismatch+12E/48D4BE is the JLE48D4BC displacement.
Root selectors/RETs are118/48 versus target121/52. Policy0 has1385 instructions,
34 selectors and46 RETs; target1488/37/50. All18 previously correct sampled
one-to-one CALL components remain correct; RET/publication memberships have
both gains and losses, not uniform improvement. Selected-shape selection
passes0/16160 with all1488 target instructions, real rolls0..100 and unchanged
empty selector x87 entries/returns. Fresh selected-object general/action-edge/
height suites pass0/51082, for0/67242 on selected canonical code overall.
Nine read-only Ghidra DB pins remain
unchanged. No exact credit is added. See
[signed selection field](REIMU_CPU_ROLL_FIELD_2026_10_19.md).

The preceding source also fixed two ordered wall predicates: negating
`x<240`/`x>1040` explicitly preserves unordered X behavior, while substituting
>=/<= did not. Actual-helper counterexamples select policy11/bound30 instead
of target policy0/bound60, or policy9/bound30 instead of policy0/bound10.
The new `--x-position-cases` matrix passes0/20200 with two independently
target-confirmed policy/timer/RNG controls. Prior finite-X/height suites did
not prove this case. Only eight TEST/Jcc instructions change among all4008
functional instruction ordinals; all other encodings/edges and47 metadata
pointer destinations remain identical after address replay. Source SHA256 is
`7102660c044b225578aeb52fb5379ef20925ed813f34e7ab6815e760384f01eb`,
canonical16461-byte payload
`4a4cb565b9c023fb82e6f4fbb01e63df711d3b3f59ce15fef1c1f9c52b581792`.
Prefix15920; strict+12E/48D4BE and selectors/RETs118/48 remain nonexact.
Fresh selection/general/height runs pass0/21528, for0/41728 including the new
exceptional-X matrix. All49 finite selector and63 coupled terminal records,
including publication/x87 observations, agree with the preceding source after
instruction-ordinal address replay. The primary instruction stream is unchanged
apart from eight local table addresses moving by4. Generated input arrays
totaling about12MB are removed; the public generator and trace recipes remain.
See [unordered wall evidence](REIMU_CPU_NAN_WALLS_2026_10_19.md).

Latest source completes the remaining two negative wall guards, separately
target-traced at48FE5A/48FE76 and490842/49085E (all TEST AH,5). Four guards
now preserve C0/C2 behavior. Only eight further TEST/Jcc instructions change;
all4008 functional positions/edges and47 metadata pointer destinations agree
after address replay, and the entire pre-policy0 code prefix is byte-identical.
Two longer TESTs consume prior compiler post-RET alignment. Source SHA256 is
`1d121503b98277c808727f58af725f13642dfe5ab78ee91bb03aa32b283876d5`,
canonical16461-byte payload
`07cb7a406e5c136ccd25e97287419f58e7b8b7eaccd502af81e0cb811fbac091`.
Prefix15920, strict+12E/48D4BE and selectors/RETs118/48 remain nonexact.
Fresh0/41728 selected cases preserve all49 finite selector and63 coupled
terminal records, including x87/publication observations. No exact credit.

On pre-checkpoint source7102660c, pinned RTM/SP1 and native-container COFF
controls are fully byte-identical. A genuine closed /GL link with exact SDK
deque94/94, three exact engine units and actual static CRT retains the wrong
aligned EBP frame. Narrowing only five exact-float copy aliases removes that
frame; full four-switch CFG and334-field replay prove its genuine/ordinary
16429-byte equality at ec562ac4, still nonexact to target. Controls are not
selected and linked images are not executed. This does not exclude other
original source/TU/LTCG contexts. See
[compiler phase and remaining wall evidence](REIMU_CPU_PHASE_2026_10_19.md).

The next checkpoint keeps that source/payload unchanged and adds a native
exceptional-height matrix with four target-confirmed qNaN/sNaN policy/timer
witnesses. Fresh0/20200 vectors preserve complete actor/RNG/helper results.
An ordinary inline input helper leaves the entire payload unchanged. Four
independent height cases and narrower independent peer cases overrun491450;
fenv_access(on) changes the12-byte frame to16 and also overruns. None is
executed or selected. Target EBP=2/EDI=400 lifetimes and its two peer-height
comparisons are recorded separately from source hypotheses in
[height and lifetime controls](REIMU_CPU_HEIGHT_CONTROLS_2026_10_19.md).
Replacing43 raw output-word accesses with existing32-bit typed members also
leaves the complete payload unchanged. Mixed output access spelling is not
the demonstrated cause of the remaining allocation/sharing differences.
`build/reimu-cpu-fields/` retains that fresh baseline/control and independent
read-only Ghidra attestation; nine DB hashes agree and its alias is removed.

## Next reconstruction work

The active bounded scope is YoumuObject's5159-byte initializer at543670.
Preserve the verified short interface, target902 order and29 distinct action
destinations/two switches. Recover real820/850 pointer/vptr lifetime and
conversion/return membership;851 must load its value after the state write
without merging into854. Read YOUMU_ENTRY_SEQUENCE_WORD_2026_10_19.md and
its earlier evidence before repeating controls. Do not transfer a prototype
to another root solely from an equal slot number.

Aya61F0B0 remains open at two bytes. Preserve its19 recovered preparations
and complete metadata. Read AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md before
new controls; do not repeat its unchanged source/profile/helper probes.
Its old11-site scheduling diagnosis is superseded by the observed low-word
consumption and coupled caller/provider compiler evidence.

The Reimu CPU root remains open: use the complete candidate, coupled
terminal witnesses and original-helper execution to recover CALL/publication/RET sharing and genuine
constant/TU/register lifetimes. Keep direct signed764/76A reads and the observed
ECX forwarding. Absence of a machine reload does not prove an original local
cache. Do not repeat a missing live value at selector entry explanation without
new evidence. Preserve the corrected180 equality/RNG order. Do not count finite execution or
diagnostic branch counts as exact progress.
Preserve all four ordered wall negations and exceptional-X positive controls;
do not replace floating-point complements with opposite ordered relations.
Do not repeat the unchanged RTM/native-container/five-float-alias controls;
the latter restores an entry frame but not complete target sharing.
Do not repeat the unchanged input-helper/independent-height/fenv controls;
their negative results do not establish a unique original source spelling.
The43-write typed-output control is likewise completely byte-neutral.
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
`build/reimu-cpu-roll-field/` retains the selected field/natural-range source,
closed CFG profiles, fresh focused Reimu execution and rejected controls. Its
read-only recipe is under `.analysis/reimu-cpu-roll-field-20261019/`; all nine
DB pins remain unchanged and no alias/project copy is retained.
`build/reimu-cpu-geometry/` retains current ordered-wall source/normalization,
real exceptional-X counterexamples and target traces, related replays and
unselected peer/distance controls. Its read-only Ghidra recipe is under
`.analysis/reimu-cpu-geometry-20261019/`; all nine DB pins are unchanged and
the project alias is removed.
`build/reimu-cpu-phase/` retains latest selected replay/normalization, four
target wall traces, pinned RTM/native-container controls and qualified genuine
float-alias link recipes. Its read-only Ghidra recipe is under
`.analysis/reimu-cpu-phase-20261019/`; nine DB hashes remain unchanged and
the project alias is removed. The private linked images are not selected.
`build/reimu-cpu-controls/` retains the unchanged baseline, four rejected
input/height/environment controls, closed policy0 profiles and exceptional-Y
native witnesses. Its read-only Ghidra recipe is under
`.analysis/reimu-cpu-controls-20261019/`; nine DB pins remain unchanged and
the project alias is removed. Generated bulk input arrays are removed.
`build/aya-entry-context/` retains fresh caller/probe comparisons, the complete
4859-byte/two-difference packet, RTTI, unselected controls and genuine source/
CRT links. Its bounded read-only Ghidra recipe is under
`.analysis/aya-entry-context-20261019/`; all nine DB pins agree and the alias
is removed. Linked images are diagnostic and unexecuted.
`build/youmu-entry-word/` retains fresh target/vtable/selected source packets,
the23/30 owner diagnostic, real short-callee witness and rejected851 merge.
Its bounded read-only Ghidra recipe is under
`.analysis/youmu-entry-word-20261019/`; nine DB hashes agree and its alias is
removed. No new native or linked-image execution is claimed.
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
