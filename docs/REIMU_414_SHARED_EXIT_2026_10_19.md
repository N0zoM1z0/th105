# Reimu414 shared action9 exit and distinct effect tails

## Scope and target observations

This checkpoint changes only case414 in
`src/characters/ReimuActionStateMidShotCases.hpp`, within the authored
`Reimu_dispatch_action_state_vslot28 @00478FA0`. The complete callable remains
`[478FA0,48CE2E)`,81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Only original Japanese1.06a target SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Root status remains unclassified/declaration-only; no implemented
or matches row, staging boundary or partial exact credit is added.

**Observed:** after the actual advancement call4351C0,414 has two independent
zero-counter/timer/frame guards. Sequence1 JE47FA79 and sequence3 JE47FA9C
both target47EDAB. That block loads vslot8, pushes9, places self in ECX,
calls47EDB4 and returns at47EDBD. Complete action membership of this physical
CALL is404/406/414/545. The separate47FA53 vslot8 CALL pushes0 after advancement;
it is not the shared action9 site.

Three distinct effect62/next-sequence/RET tails are also observed:

|Action|CALL435240|Virtual slot14 CALL|RET|
|---|---|---|---|
|410|47F595|47F5A1|47F5AA|
|414|47FB24|47FB30|47FB39|
|416|47FF5A|47FF66|47FF6F|

Primary vtable6C412C has slot28 at6C4154->478FA0, slot8 at6C4134->45BFE0
and slot14 at6C4140->45C220. The latter is the accepted138-byte sequence helper.
Instruction facts come from decoding the attested complete root, then direct
read-only Ghidra12.1 corroboration. Ghidra independently verifies imported
executable hash, PE base/entry68B9D2, x86/windows analysis target, full mapped
text SHA256 `f5cb09ff0a54362356d8c4cce853cbcb14552499cce12cf7390d0868db9ebe97`,
root bytes, slots and instruction flows before emitting the success sentinel.
Temporary instruction creation is confined to the read-only session. All nine
primary DB hashes agree before/after; its build-project alias is removed.
Recipe: `.analysis/reimu-root-branches-20261019/ghidra-readonly.py` and
`ghidra-scripts/Th105ReimuShotTailAudit.java`; receipts/logs are under the
corresponding `build/` directory. The initial lookup found undefined code and
correctly failed without a sentinel; its `ghidra-first` records are retained.
The successful run explicitly disassembles only the attested instruction ranges.
No IDA semantics or target byte patches are used.

## Selected C++ and whole-root controls

**Inferred source shape:** sequence1 explicitly joins the existing sequence3
`set_action(9)` exit through a C++ label. Effect62's `next_sequence_block()` then
uses the outer switch completion via `break`, as410/416 already do. This is a
source hypothesis supported by target behavior and whole-root code generation,
not a claim about the original source spelling or TU.

Private serial VC8 SP1 controls use the unchanged compiler/profile/header:

|Control|Differing direct-callee partitions|Indirect physical target/source|Effect partition|
|---|---:|---:|---|
|Prior selected source|6|220/219|57/55, different|
|414 shared action9 exit only|6|220/218|57/55, different|
|414 effect break only|5|220/221|57/57, equal|
|Both changes, selected|5|220/220|57/57, equal|

The join alone loses a formerly equal414 RET group and is rejected alone.
The break alone retains an extra414 slot8 call and is rejected alone. Combined,
all **1198 previously equal complete action-membership/multiplicity checks**
across32 direct callees, four indirect-slot domains, RETs and aggregate indirect
calls are preserved. The entire435240 effect partition now agrees, including
three separate410/414/416 sites. Indirect physical counts agree per slot:
8=132/132, mixed8/C=2/2, C=51/51,14=35/35. All per-action indirect count deltas
are gone. Slot8 and14 complete memberships still differ: equal totals are not
proof of equal sharing. Complete receipts are `baseline-sharing.json`, the
three control directories, `selected-sharing.json` and
`selected-preserved-groups.json` under `build/reimu-root-branches-20261019/`.
Control source/commands and mutation recipe are retained privately in
`.analysis/reimu-root-branches-20261019/probe.py`.

## Current compilation and strict comparison

The genuine producer was rebuilt from the public selected source. All2473
relocation fields replay:1104 numeric,1185 REL32 calls,14 metadata addresses,
seven globals and163 local code pointers. Ordinary and genuine linked payloads
agree over all82840 bytes, including1372 metadata bytes. The linked envelope's
additional eight alignment bytes remain separate; all1281 PE HIGHLOWs qualify.
The11 switches and15 request-buffer contracts still pass. The local frame is
unchanged570h; target/source reachable instructions are20243/20268.

|Artifact|SHA256/value|
|---|---|
|Generated source|`46f97f0ae19c0ab145e5779067939fabc96af07742e92f77e69edc9820b71cc8`|
|Ordinary object|`8e9f7dfacd38f15d88764b691af2d3369620e7d1a806dea1b6b9555f1384a1bf`|
|Complete ordinary/genuine canonical payload|`3f11d7d68edcc8447dac7d07ca74891dd4d9bc3b68d19bdd21197e08ed369192`|
|Producer receipt|`b0edd86dcbb076b1293b328654a7ae5cb4f1536e6892b0c3f14ddc2f24bdea3d`|
|Payload / code prefix / frame|82840 /81468 /570h|
|First strict target mismatch|+541 /4791BD: targetA9/source4A|

Object hashes include COFF timestamps; reproducible source/canonical hashes and
compiler receipts qualify the comparison. `build/reimu-ltcg/coff-replay.json`
contains the full linked correspondence. An earlier effect audit rejected a
stale producer support digest; the public producer was rerun, without receipt
hash overrides, before accepting the new effect execution.

Reproduce the selected root diagnostics serially:

```bash
taskset -c 0 nice -n 10 python3 -B scripts/probe-reimu-action-ltcg.py
python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
python3 -B scripts/audit-reimu-root-relocations.py build/reimu-ltcg/ordinary.obj
taskset -c 0 nice -n 10 python3 -B scripts/audit-reimu-void-root.py build/reimu-ltcg/ordinary.obj --cohort shot_boundaries --cohort integration --cohort surface_inputs
taskset -c 0 nice -n 10 python3 -B scripts/audit-reimu-shot-effect-returns.py --output-dir build/reimu-root-branches-20261019/effect-returns-selected
```

## Execution evidence and limits

Fresh selected ordinary-root execution gives **0/2675 differences**:
1380 shot boundaries,1010 integration inputs sampling all128 nondefault actions,
and285 nonflat surface inputs. Input SHA256
`0e67cae006499020bea8fcb508aa311d710ce27da157685ecec0e55fb33d8cdc`.
Real target/source helpers, memory/call outcomes and RET/ESP/saved-register/x87
contracts are compared under the existing fixture. The private combined build
passes the same inputs and complete payload identity; it is not additional
unique coverage. Report: `selected-native.json`.

Actual effect construction, virtual-next, root RET and destruction pass
**0/60** cases. Two independent target processes agree with the source over
6980-byte snapshots/case: all three SHA256 values are
`a983c3fd28b5a73067cfe7f68e47a94e5ab3a71040dbde84a1d8a42f74e48e3f`.
Input profiles SHA256
`cf891eadda3a95119914c73a2f7dcb89608e77e3d013e643a35b7722385d367c`.
This executes canonical CRT/manager/callback/destruction paths with Wine kernel32
imports; it does not substitute a game callback return. Supplied untextured
resources, later effect ticks, exceptions and arbitrary worlds remain outside
the proof. Receipt: `effect-returns-selected/receipt.json`.

A wrong-source control changes only the joined414 `set_action(9)` to0, then
passes the same object envelope and relocation gates. The public native audit
returns exit1 with **8/1380** real mismatches, including action13C and animation
state differences on the sequence1/3 return paths. Input SHA256
`394deccae7ceebecf1fac43ea8fa7242b6db412f8abbed3e304272058d4281e6`.
This is semantic sensitivity, not an early gate failure. Recipe label:
`wrong-414-action0`; report: `wrong-414-native.json`.

The independent bool stage is rebuilt from current fragments through418, with
later includes omitted, its ordinary pending cutoff restored to418 and local
landing fragments selected. Its recipe is
`.analysis/reimu-root-branches-20261019/stage.py`; generated source, compiler
receipt and native result are below `bool-stage/`. Focused motion/required-branch
execution passes **0/578** (540+38), input SHA256
`2da5cb344daea76aa44823d39c708c5668b419a47b14f35a91630ebc026f60f3`. The full later bool object
is outside the old mid-shot oracle's literal scope and correctly fails that
gate; no bindings or oracle checks are weakened to accept it.

**Unknown:** the remaining five differing direct partitions are4351C0,435D60,
45AF40,473DD0 and478EE0. Target has1188 direct CALLs versus source1185, with one
missing physical copy each for4351C0/473DD0/478EE0, principally300/320 sharing.
Low9 landing ownership, slot8/14 memberships and root RET sharing remain open.
The strict first difference remains+541; neither a full-root native proof nor
canonical root equality follows from this checkpoint. Returning world requests,
indeterminate740 inputs and arbitrary resource graphs remain scoped out. Shared
ABI/layout/provider/flag/relocation ledgers and accepted exact units are unchanged;
no all-unit replay or new exact-byte total is claimed.
