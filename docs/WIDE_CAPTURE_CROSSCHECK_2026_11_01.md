# Bounded cross-check after the Tenshi capture correction

The two real Tenshi corrections are recorded in
TENSHI_ACTION_STATE_2026_10_27.md. This follow-up checks the same concrete issue
in twelve other complete current Fighter candidates: missing eight-byte stack
captures across ordinary calls. It is not a claim of whole-root semantic or
canonical equivalence. No neighboring source, header, ABI, profile or ledger
is changed, and no exact bytes are added.

Each configured native unit was freshly compiled serially on CPU0/nice10.
Complete target/source bytes and their actual switch graphs feed the existing
caller-stack dataflow analysis. The private diagnostics expose its SP states
and inspect actual eight-byte stack operands. Explicit direct cleanup contracts,
ordinary callee saves, actual receiver vslots and separately proven peer170
receiver chains are retained. Unknown receivers or stack merges fail closed.
The public comparator and origin validators are unchanged.

| Root | Native/source QWORD operands | Native/source frame bytes | Finding |
| --- | ---: | ---: | --- |
| Yukari57B030 |34/34|1248/1256|All17 store owners present; high captures use a different shared home.|
| Aya602250 |80/79|1000/1000|606 has two branch-local physical spills versus one shared spill, not a missing wide value.|
| Iku620920 |22/22|1024/1024|All11 store owners present.|
| Sakuya4CADB0 |26/26|1240/1192|All13 store owners present; full75042-byte owned callable used.|
| Youmu530200 |24/24|560/560|All12 store owners present; nine peer170/slot8 calls independently qualified.|
| Patchouli50F200 |30/30|1120/1128|Per-action store counts agree.|
| Remilia545090 |22/22|1264/1264|Per-action store counts agree.|
| Yuyuko55D850 |54/54|1256/1264|Per-action store counts agree.|
| Marisa4A3710 |42/42|1216/1224|Per-action store counts agree.|
| Komachi5E20E0 |24/24|1168/1168|Per-action store counts agree.|
| Suika598990 |70/50|1400/1400|605/730 retain the previously documented merged surface-check bodies.|
| Udonge5BFD50 |56/56|1152/1160|Per-action store counts agree.|

Aya606 computes F0+300 before the branch in both versions. Native60E118 loads
F0 and60E11E adds300 before60E124 branches; each arm then spills that same live
ST0 value to QWORD. Current source spills once before its pure parity branch.
Both source arms still consume the pre-RNG double base. The physical one-store
difference does not establish an omitted capture or justify duplicated storage.
Suika605's8/3 and730's7/2 wide-store counts correspond to the already retained
surface-check sharing residual. Source still uses its real double capture;
no action loses all of its wide captures. Those counts are not proof that all
callback lifetimes or numerical behavior agree, nor permission to force copies.

The neighboring captures therefore supply no additional demonstrated instance
of Tenshi542's binary32 truncation. Existing register/home/physical-tail and
semantic uncertainties remain open. No scalar is narrowed to force a frame
size, and no new runtime matrix is required for this negative width check.
Alice and Reimu's separate research-provider graph were not included in the
initial twelve-root claim. The initial description of Alice as only a partial
scaffold was incorrect: the old giant-switch scaffold metadata coexists with
the complete AliceFighterActionState.cpp candidate and its configured unit.
The follow-up below uses that current source, not a redundant reconstruction.

## Boundary and provenance details

The Iku mapper must explicitly select its configured void-root symbol; choosing
the largest COFF section initially selected a different helper. That failed
mapping is not evidence about the root and was corrected without a gate waiver.
Komachi's source has real code after its final RET opcode, ending in a jump;
tracing retains it through the actual first table, rather than cropping at RET.
Marisa's exact observed prologue contains one FLD between alignment and frame
allocation. Both inspected prologue forms are explicitly recognized only in the
private tracing input, not by relaxing any public comparison.

Suika table5AC664 and Udonge5D06BC each have four real destinations followed by
native INT3 alignment. Their own immediately preceding CMP EAX,3 / JA guards,
indexed JMPs and absence of incoming branches bypassing those guards establish
the four-word bounds. Extra CC bytes remain recorded as metadata alignment,
not jump destinations or discarded comparison bytes. Full canonical inputs
are never shortened or patched by this diagnostic partition.

Private receipts are build/frontier-{yukari,aya,iku,sakuya,youmu}-stack-lifetimes-20261101/
and build/frontier-roster-wide-captures-20261101/{patchouli,remilia,yuyuko,marisa,
komachi,suika,udonge}/. Each contains fresh build and actual graph/stack/operand
facts; summary.json records completed batch checks and initial-blocked files
retain the superseded parser attempts. Private scripts retain all exact input
contracts. No process ran in parallel and no generated source image executed.

All neighboring whole comparisons remain nonexact. Exact1582/449309 bytes,
source1782, authored1802, mapped1809, excluded1791/review434 and units765 stay.
Default CI235 and whitespace pass for this documentation checkpoint.


## Alice correction and fresh wide-capture check

The existing complete3024-line Alice candidate and
exact-first-alice-fighter-update unit were checked before any source edits.
Its earlier bounded controls remain closed as documented in
ALICE_FIGHTER_UPDATE_2026_10_25.md. Factory-native IDA metadata, entry point,
five raw-PE mapped samples and inventory/disassembly/decompiler/caller/callee
preflight passed independently; the retained5211-line decompilation remains
provisional semantic evidence, not code to copy or exactness proof.

A fresh serial CPU0/nice10 compile reproduces complete44032-byte canonical
SHA2564d312925be3f754e27ef0f963632f8034ca587c6b09be35dc7a7ff8aefd5bd1d.
The strict44080-byte target comparison remains nonexact. The unchanged frame
residual is1048/1040 bytes and first mismatch+8. No source, header, unit, ABI,
profile or ledger is changed.

Both graphs expose18 QWORD operands, nine wide stores, and79 distinct payload
homes with no unknown payload pointers. Store ownership agrees for200,201,
202,203,223,224,225,226 and310. The eight dash captures retain the horizontal
base across both real RNG calls;310 retains updated vertical position across
the real435D60 surface call. Native310 store4ECF56/compare4ECF5F and source
4ECE59/4ECE62 both use QWORD at normalized home32. The eight dash captures use
home24 in both graphs. There is no further missing-wide-capture correction
supported by this check. Counts and stack-pointer closure alone do not prove
all request extents, callback epochs or whole-root execution equivalence.

Receipts are build/frontier-alice-action-state-20261101/alice/: formal.json,
map.json, native/candidate-wide.json, payload and peer-facts reports,
wide-capture-windows.asm and summary.json. The existing complete candidate
remains unselected and nonexact. The stale scaffold-only planning statement
is corrected here and in RE_HANDOFF.md, without promoting historical metadata.

## Reimu research candidate, same bounded check

The existing generator emits the complete void/default candidate from current
Reimu fragments, rather than treating the bool staging adapter as the root.
Fresh serial CPU0/nice10 generation gives82808 bytes, object
94297b98e5b7b9a9514988aad6631403fc1629396ec69fe3d85aad8200dcc8cf,
and canonical replay fbc0293d5e7ab9b39aca3d83c4d044ce7603d2e28d7961d2ff7736ef3f360177.
The existing relocation audit qualifies all2473 relocations:1185 calls,
1104 literals,14 metadata addresses,163 code pointers and7 globals. None is
unresolved. Whole payload remains nonexact against82924 target bytes.

Both graphs expose40 QWORD operands,20 stores,112 resolved payload homes and
1392-byte frames. Per-action store counts agree, including all three616
captures and one each for565,566,612 and730. No additional missing-wide
capture is demonstrated. This does not prove all request extents or whole-root
execution equivalence. No source is modified or selected; no exact credit.
Receipts are build/frontier-reimu-wide-captures-20261101, with fresh generator,
existing relocation audit and separate native/candidate graph/stack reports.
