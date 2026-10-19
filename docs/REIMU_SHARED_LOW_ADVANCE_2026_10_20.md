# Reimu shared low-action advance exit

## Scope and target observations

This checkpoint changes the source hypothesis for the complete action root
`Reimu_dispatch_action_state_vslot28 @0x478FA0`. Use only original Japanese
TH10.5 v1.06a, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The callable `[478FA0,48CE2E)` is 81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The accepted boundary evidence remains in
[the root analysis](REIMU_ACTION_ENTRY_2026_10_17.md).

**Observed:** target advance CALL `47973E ->4351C0` belongs to actions
0/2/9/71/72/74/145. Two other CALLs, `479236` and `4792CD`, belong to0/2.
The shared landing path calls virtual slot8 at47971C, height435D60 at479720
and motion reset45AF40 at47972D; its complete action set is6/7/8/9/306.
A separate landing has actions208/209/210/211/221/222/309. Eight incoming
edges to47973C and the landing/advance instruction windows were independently
read in the re-attested direct Ghidra project. Its executable identity,
entry, mapped text, root hash and vtable cell6C4154->478FA0 qualified.
The read-only process left all nine primary database files unchanged.
IDA's preflight still identifies another executable, so its semantic data
was not used. No target bytes or analysis metadata were changed.

## Source change and controlled alternatives

**Inferred source hypothesis:** actions0/2, recovery71/72/74 and145 can join
action9's discarded-result `advance_frame_and_dispatch(); return` expression.
Actions1/3 still consume the returned byte; other recovery bodies retain
their own advance. The monolithic dispatch alone defines
`TH105_REIMU_SHARED_LOW_ADVANCE`. Its conditional label/jumps live in
`ReimuActionStateLowCases.hpp`, `ReimuActionStateRecoveryBody.hpp` and
`ReimuActionStateMovementAttackCases.hpp`. Standalone staging builds leave
the macro off. No helper definition, shared layout, compiler flag or durable
relocation binding changes.

An earlier low9 experiment combined explicit landing and advance labels.
Its failure did not exclude sharing advance alone. The new controls start
from a freshly rebuilt602 checkpoint and vary those properties separately.

| Source property | Canonical payload prefix | Bytes / callable prefix | Source instructions | Differing direct partitions | Prior equal checks lost / new checks |
| --- | --- | --- | --- | --- | --- |
| Fresh previous source | `6527316d` | 82824 / 81452 | 20254 | 5 | 0 / 0 |
| Explicit landing only | `bb879776` | 82840 / 81468 | 20263 | 3 | 2 / 10 |
| Shared advance only, selected | `78043bc1` | 82824 / 81452 | 20252 | 3 | 0 / 10 |
| Both explicit exits | `38012410` | 82872 / 81500 | 20258 | 3 | 2 / 10 |
| Public conditional-macro form | `78043bc1` | 82824 / 81452 | 20252 | 3 | 0 / 10 |
| Directional return declared bool | `6527316d` | 82824 / 81452 | 20254 | 5 | 0 / 0 |
| Landing return declared bool | `6527316d` | 82824 / 81452 | 20254 | 5 | 0 / 0 |
| Height return declared double | `211807cc` | 82840 / 81468 | 20256 | 5 | 0 / 0 |

All controls retain the570h frame. Each object passes the complete root
relocation/CFG qualification before the structural comparison. A separate
`/FAcs` compilation reproduces the entire selected canonical payload.
Its source attribution maps generated line279's one advance expression to
source CALLs47923A,4793B9 and47A61D: two0/2 copies and the seven-action
shared copy. Each CALL is independently paired with its REL32 relocation.
The listing is compiler output, not assembly used as reconstruction source.
This explains a possible source-to-physical-copy relationship; it does not
recover the original source spelling or compiler translation unit.

The narrow return declarations are underdetermined by these helper bytes:
independent private bool landing/directional providers remain fully
442/442 and184/184 equal, and the double height provider remains89/89 equal
after complete relocation replay. The bool callers are byte-neutral; the
double caller changes without improving ownership. Public helper types
therefore stay unchanged. In particular, the forwarded virtual byte from
4351C0 was not assumed to be bool.

## Complete structural and linked results

**Observed compiler result:** all1214 previously equal complete physical
action-membership/multiplicity checks survive, and ten improve, for1224.
For each of the two landing groups listed above, height, motion reset,
slot8, RET and all-indirect ownership now agree. The complete56-site height
and51-site motion-reset partitions agree. These checks do not establish
argument values, feasible paths or canonical byte equality.

The three remaining differing direct-callee partitions are4351C0,473DD0
and478EE0. All concern300/320, whose two target copies are still merged in
the candidate. Indirect counts remain220 target/219 source; slot14 groups
605/608/651/658 and other previously reported indirect/RET differences
remain unresolved. See [three-action and slot evidence](REIMU_300321_SLOT_CONTEXT_2026_10_19.md).

| Artifact | SHA256 / result |
| --- | --- |
| Generated complete void source | `4931d5b528a29b8f5702ca35bcb488cdc6835094e979bb5ced3b9a31cb11c296` |
| Generated void header | `5212c424d02e266659335e78b728b336b30fe6c1d6557ac8268bf31bdb2610fd` |
| Selected ordinary object | `36816d3a5119c5809a4a910bd0cc071a9f4b9c5719bbf699dae116a92601199b` |
| Genuine producer's ordinary object | `acee0998510ee6eb85bf04baa006e9b912b5a78af6fcff55807580ebb33ad61d` |
| Ordinary / linked complete canonical payload | `78043bc1d973f4abe4f965c18321e5b07d8c83a7bca491e35a4d9421bac0c180` |
| Genuine producer receipt | `9ea53d6b64b70561946d82a7c06c5477bb0a55737b6f0db39569a763d667518f` |
| Linked diagnostic image | `7033537e2eaf797a31e1ece83214a927372afea7600823948430a911fd76c50e` |
| Payload / callable prefix / frame | 82824 / 81452 / 570h |
| Strict first target difference | +541 /4791BD, JNE operand at4791BB |

The real source/CRT `/GL`+`/LTCG` producer was rebuilt serially. Independent
ordinary/linked replay agrees for every payload byte and2473 fields:
1104 numeric literals,1185 REL32 calls,14 local metadata addresses,
7 global addresses and163 local code pointers. All1281 PE HIGHLOW fields,
32 direct-callee identities,11 switches and15 request-buffer contracts
qualify. Eight trailing linker INT3 alignment bytes remain separate from
the82824-byte payload. The five documented nonexact provider diagnostics
remain nonexact. The image was not executed. This is evidence about this
closed compilation experiment, not original-TU recovery or an LTCG
impossibility claim.

## Execution evidence and negative control

Each selected full-root execution uses the new ordinary object. Target
instructions and actual helpers execute until native RET or the first
stated world/resource request entry; arguments and traces are compared.

| Scope | Cases | Differences | Additional qualification |
| --- | --- | --- | --- |
| Changed actions0/2/9/71/72/74/145 | 5752 | 0 | 5536 RETs,206 effect entries,10 owned-object entries |
| Full void integration / shots / nonflat surface | 2675 | 0 | 1010 /1380 /285 cohort cases |
| 602 firing and misses | 210 | 0 | 120 actual MT/object854 entries,90 RETs |
| 300/320/321 focused continuation | 989 | 0 | All native RETs; requires321's real PUSH28/JMP47DA68 predecessor |
| Private bool staging through606 | 2136 | 0 | Cadence1980, texture96, branches60 |
| Wrong extra counter increment before shared advance | 5752 | 5192 | Same inputs/helpers; intended negative detected |

The5752 matrix includes832 cases each for0/2,1600 for9,735 for71,
730 for72,735 for74 and288 for145. It starts with empty x87 tags/TOP0;
all5292 observed4351C0 entries per side retain empty tags/TOP0. This does
not prove arbitrary initial x87 stacks, unmasked exceptions or all floating
environments. The negative increments `frame_counter_144` in private source
at the new shared exit; no helper return is fabricated and the negative
is absent from public source.

The bool606 source is explicitly bounded staging: its guard rejects>606,
later fragments are excluded and the separate sequence-landing macro is
disabled because608/658 labels lie outside that source. The new low-advance
macro remains enabled. An initial full-bool audit was rejected by that
audit's narrower literal contract; no passing full-bool claim is made.
The public complete void source compiles and passes its own full-root
contracts. Repeated and overlapping input sets are not additive unique
coverage.

600/601/602's selected effect115 argument preparations still each equal
all16 target instructions/64 canonical bytes.650/651 do not, consistently
with the preceding checkpoint's unselected wider carrier control.
Returning-world callbacks, resource graphs and indeterminate740 reads
remain outside these execution proofs.

## Reproduction and acceptance

Selected generation, focused compilation, whole-root diagnostics and genuine
link reproduction use repository tools:

```bash
python3 scripts/probe-reimu-action-source-shape.py --emit-only --void-root --output-dir build/reimu-ownership-20261020/selected
scripts/compile-unit.sh build/reimu-ownership-20261020/selected/ReimuActionStateDispatch.cpp build/reimu-ownership-20261020/selected/candidate.obj
python3 scripts/audit-reimu-call-sharing.py build/reimu-ownership-20261020/selected/candidate.obj
python3 scripts/audit-reimu-root-relocations.py build/reimu-ownership-20261020/selected/candidate.obj
python3 scripts/audit-reimu-void-root.py build/reimu-ownership-20261020/selected/candidate.obj --cohort integration --cohort shot_boundaries --cohort surface_inputs
taskset -c 0 nice -n 10 python3 scripts/probe-reimu-action-ltcg.py
```

Builds and heavy native/Ghidra probes ran at nice10/CPU0, serially. Local
reports are under `build/reimu-ownership-20261020/`: `summary.json`,
`selected/{receipt,sharing,relocations,preservation}.json`, `listing-proof.json`,
`effect-prefixes.json`, `native-{advance,broad,three}.json`, `native602.json`,
`bool-stage606-native.json` and `negative-counter/native.json`.
The genuine producer/replay are `build/reimu-ltcg/{receipt,coff-replay}.json`.
Private control generation and execution drivers remain under
`.analysis/reimu-ownership-20261020/`; the602 and three-action drivers are
`.analysis/reimu-next-sequence-20261019/native602.py` and
`.analysis/reimu-300320-slots-20261019/native-three.py`.

**Unknown:** whole-root semantics and original compiler context remain
unproved. The candidate still differs from the target, whose reachable
instruction count is20243 versus candidate20252. Root status remains
unclassified/declaration-only; no `implemented.csv` or `matches.csv` row,
exact byte credit, or aggregate percentage claim is added. The next source
ownership problems are300/320's distinct physical copies and the remaining
slot14 groups. Historical combined-exit failures must not be generalized
to every separate source property.

## Follow-up:300/320 source boundaries

After selecting78043bc1, eleven more private controls test whether natural
source function boundaries explain the remaining copies. Each starts from
the selected4931d5b5 source and uses the same ordinary compiler/header and
unchanged public bindings. None is selected.

| Source property | Complete result |
| --- | --- |
| Full300 inline; full320 inline; separate full300/320 inlines; one shared full-action inline; shared three-action completion/event inline | All five reproduce the complete78043bc1 payload, including unchanged physical partitions |
| Full320 inline with precise mode off; completion inline with fenv access on | Both also reproduce the complete78043bc1 payload |
| Named320 friction float | 82888 bytes, prefix81516,20266 instructions; canonical75c00362;1224 prior checks survive and four landing/gate checks improve, but advance/slot8 still merge |
| Explicit three-action event parameter | 82856 bytes, prefix81484,20262 instructions;88b09743; loses the two previously equal300/320/321 event CALL/RET memberships |
| Named320 float plus explicit event parameter | 82904 bytes, prefix81532,20277 instructions;c3626766; loses those two checks and gains the four landing/gate checks |
| Full320 inline with fenv access on | Compiles, but both complete auditors reject the enlarged code/metadata envelope; no qualified correspondence claim |

The ten qualified controls keep570h frames. Source-defined inline bodies
contain the real action or completion operations, rather than external stubs.
The two fenv controls set that property on the private helper definition and
restore it before defining the root; the fast control similarly pushes/pops
the helper's precise-mode setting. The enlarged case is not accepted by
relaxing the diagnostic boundary.

The named-float candidate separately passes0/989 existing native300/320/321
cases. Its independent320 entry still has the wrong instruction shape and
ESP+14 scratch instead of target+24;300's26-instruction prefix agrees.
The byte-identical inline320 control has matching first26 instruction shapes
for both actions, but both entry labels still refer to the same physical
copy. Neither observation recovers two target copies.

Reports and input hashes are in
`build/reimu-300320-inline-20261020/{summary,prefixes}.json` and the per-control
receipts; the source recipe is
`.analysis/reimu-300320-inline-20261020/probe.py`. The raw prefix verifier is
`prefixes.py` beside it. The named-float execution uses the same private
`native-three.py` driver and input hash documented above. These controls
scope the negative result to the tested source/FP contexts. They do not
establish the original TU, unique source identities for a target address,
or an LTCG impossibility. The selected source and all exact ledgers stay fixed.
