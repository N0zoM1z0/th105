# ReimuObject update: complete target CFG and first source phase

The initial source-phase counts below are historical. Current source covers
all41 arms under the void ABI; see [the void-root checkpoint](REIMU_OBJECT_VOID_ROOT_2026_10_20.md).
The complete-extent canonical comparison remains nonexact.

## Identity, ownership and instruction facts

Only original Japanese TH10.5 v1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The existing authored root is496540, reached through ReimuObject primary
vtable6C40A4, slot28/cell6C40CC. It remains unclassified, without a root
implementation or match row.

**Observed:** the complete envelope `[496540,4A197A)` has46138 bytes, SHA256
`399e56d3f1373e76381cafb17e4984845fdb1f680dc0737f864229b52f84e31d`.
The existing ownership ledger excludes ten alignment bytes and retains these
46128 instruction bytes:

| Range, end exclusive | Bytes |
| --- | ---: |
|496540..49D169|27689|
|49D170..4A00ED|12157|
|4A00F0..4A197A|6282|

`scripts/audit-reimu-object-update-target.py` independently decodes all owned
ranges. Its conservative graph reaches all10670 instructions/46128 bytes,
including68 RETs. Every direct edge enters an owned instruction; all22 indexed
jumps have checked guards and destination tables. The primary signed-word
action dispatch has42 destinations, using table4A197C and index bytes4A1A24.
Twenty-one nested dispatches cover sequences and four mode selections in
905..908.903 also uses a sparse byte-index table. No path-feasibility, argument,
stack-depth or whole-root semantic proof follows from this graph closure.

The former405 E8/26-target mapper values are **raw-byte diagnostics**. Actual
instruction decoding finds404 direct CALLs to25 targets. ByteE8 at49C35B lies
inside `D9 E8 / FLD1 @49C35A`; interpreting it as a call invents4C611D.
The old mapper's raw contract is preserved, not relabeled as decoded evidence.
The main-span shared-callee ranker deliberately reports343 calls/24 targets;
61 actual calls, including the53CBC0 edge at4A1612, lie in the remote chunk.
Consequently neither the provisional39853-byte main span nor its rank report
is a complete dependency list for this root.

Six focused tests cover the E8-in-FLD1 counterexample, unreviewed indirect
jumps, branch/table entries inside instructions, skipped alignment and the
complete current target/remote call. They do not turn the facts into a match.

## Handwritten source phase

At the initial88ac760 checkpoint, `ReimuObjectActionStateStaging.cpp/.hpp`
introduced an independent runtime
view and a **coverage boolean** method. It is not the original void update
entry and is not compared against an invented subfunction boundary. It handles
five complete selected arms and the actual default path; the other36 concrete
actions return false without being claimed as implemented.

| Arm | Recovered behavior |
| --- | --- |
|859|Sequence0 initial state, sequence1 acceleration, phase6/reset timer, signed-facing movement, ordered X bounds and animation completion retirement|
|860|Actual sine lookup pulse, alpha25 guard/subtraction and post-animation sequence1/2 retirement checks|
|861|Parameter heading/oriented motion, float-valued scale constants, alpha10 guard, signed-facing movement and the same completion checks|
|980|Actual450-byte53CBC0 provider followed by animation/completion handling|
|998|Owner actions150..158, distinct60/94/100 Y offsets, real virtual next-block operation and owner751 write, sequence1 fade and animation completion|
|Default|Actual animation advance with its result discarded|

These are target-derived source hypotheses. The view asserts offsetsEC/113/
13E/180/330/340/348/364 and size388. Unrecovered object bytes remain explicitly
unknown; no padding, unused local, assembly, fake helper or target return is
introduced to shape a comparison. Source sine return spelling and the complete
original class/TU remain hypotheses. No shared header, existing helper,
compiler profile or public relocation binding changes.

Fresh VC8 `/O2 /GS- /GR /EHsc /MT` compilation succeeds. Source SHA256 is
`4e0fbf2b1009282f5ca2d5a54587fb5c622c8b5024e1bf9fdf89927aef9ae955`;
header SHA256 is
`aa7158500eceab61a1d0f4d54d426dfa9b04856a6da8aaef1bc241e60193a13a`.
Observed object SHA256 is
`22849d4ecceb504a1427bec2e653632a9e9b6051d0811923e614d83e5d538baf`.
The1292-byte staging text/metadata is relocation-replayed at800000, SHA256
`e1cd2be6853ec3da604b4038ec2d5038746b60cb5cf020c8400c8e5e6687b803`.
This is an execution image, **not** a target-equal root or accepted exact unit.
The existing-object audit explicitly reports build provenance unverified.

## Native evidence and limits

`scripts/audit-reimu-object-scalar-actions.py` passes **0/1625**. Inputs hash to
`cfd4322e018a2a78be9cdb19cbe9a4b177cc453d3aa6578429f99be2245d7b0c`.
These cases visit249 root instruction addresses, not the complete10670.
There are26 default,432 action859,756 action860/861,216 action980,189 action998
and six terminal inputs.860/861 include x87 control words27F/37F;859 includes
unordered X. Thresholds, phase/index wrapping, owner action boundaries and
actual frame/block transitions remain in the matrix.

The original table initializer4065B0 runs unchanged to generate the3600-entry
lookup fixture, hash
`c134fa85e7988574c2db386dc8e14de2113d6e465c18f4503bd265219c5ca898`.
This is not a host-computed sine/cosine replacement. Original finite fabs,
control-word and conversion routines execute normally. Both sides execute1117
actual animation-advance entries and245 sprite commit chains. Actor388 bytes,
owner800 bytes,16 parameter bytes, helper ordering, floating control word,
TOP and tags are compared.1612 inputs reach a real RET with balanced stack,
preserved callee-saved registers and empty x87 state;13 stop at the real
64CCB0 spawn entry with receiver, seven arguments and pointed payload compared.
No helper result, vtable cell, code byte or callback return is supplied.

Two independent wrong-source controls complete the same matrix and exit1:

| Wrong source | Detected differences /1625 |
| --- | ---: |
|859 reset threshold `>5` changed to `>=5`|24|
|861 alpha guard `<10` changed to `<=10`|54|

This is sampled evidence for the declared source phase. Returning spawn/world
graphs, arbitrary initial stacks, unmasked exceptions, extreme overflowing
integer inputs, the remaining36 arms and full-root source/byte equality remain
unproved. The fixture's13 spawn stops are not return coverage. No partial exact
credit, root source-present row or new match unit is recorded.

## Database safety and reproduction

Direct Ghidra independently attests executable/import identity, base/entry,
x86/windows target, mapped `.text`, full envelope and vtable cell. The primary
initially has no function object at496540. A read-only working function uses
the three proved ranges and an ECX pointer/void view. Its complete C export
remains below `build/` as a hypothesis; warnings about removed blocks and type
propagation are retained, not pasted as source or accepted as semantic proof.
Code analysis and syntax-tree export are disabled for the bounded successful
run at128MiB Java heap/CPU0/nice10. Earlier missing-function, expanded-analysis
and heap-failure attempts remain separate from that successful receipt. All
nine primary DB file hashes remain unchanged and the temporary alias is removed.
The failed IDA preflight is not used for semantics; no factory adapter is used.

```bash
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-update-target.py --json
taskset -c 0 nice -n 10 scripts/compile-unit.sh src/characters/ReimuObjectActionStateStaging.cpp build/reimu-object-update-20261020/scalar-stage.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/reimu-object-update-20261020/scalar-stage.obj --output-dir build/reimu-object-update-20261020/positive
python3 -m unittest discover -s tests -p test_reimu_object_update_target.py
```

Private Ghidra recipes are below `.analysis/reimu-object-update-20261020/`;
target maps, build logs, positive/negative inputs, receipts and the decompiler
hypothesis stay below the corresponding `build/` directory. Builds are serial.
The [projectile follow-up](REIMU_OBJECT_PROJECTILES_2026_10_20.md) adds
800/801/804/807/808 against their shared exits and actual helper contracts.
Another31 concrete arms remain. Existing Fighter478FA0 and
Object-entry4A1CE0 source/acceptance checkpoints remain unchanged.
