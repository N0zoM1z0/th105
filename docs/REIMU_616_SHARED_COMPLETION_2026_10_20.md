# Reimu616 shared completion and complete RET ownership

## Scope and target observations

This remains work on `Reimu_dispatch_action_state_vslot28 @478FA0`, not a
new616 function boundary. The original Japanese TH10.5 v1.06a executable
SHA256 is `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable `[478FA0,48CE2E)` is81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Root status remains unclassified/declaration-only. No implemented/matches
row or exact byte credit is added.

**Observed:**616's CALL489EF5 advances animation through4351C0.
TEST AL,AL489EFA and JNE489EFC branch to479486 on completion. That block
loads the vtable into EDX, loads slot8 into EAX, pushes action0, calls EAX
at47948F and returns at479498. Its complete action membership is
3/304/550/551/616/619/669. A different block loads the slot into EDX and
calls at47BFC8, returning47BFD1; its membership is215/412/797.

The preceding source sent616 to the latter block. Both blocks perform the
same abstract setter operation, but their physical ownership and register
preparation differ. Per-action call counts and native state agreement alone
did not resolve that distinction.

Direct read-only Ghidra independently re-attests raw/imported identity,
base/entry, x86/windows target, mapped text, the full root hash and vtable
cell6C4154->478FA0. It verifies489EFC->479486 and decodes both setter/RET
tails plus616's effect preparation. All nine primary database hashes remain
unchanged and the temporary alias is removed. IDA's failed preflight still
identifies another executable; its semantics and IDA-only typed packet are
not used. Raw hash-attested bytes and direct Ghidra provide the facts here.

## Selected source and complete byte preservation

**Inferred source:**616's completed branch can join619's already-existing
`set_action(0); return` expression. `ReimuActionStateHighMiddleCases.hpp`
replaces that duplicate616 pair with a goto, and puts its label inside619's
completed branch. It does not re-run619's advance or preceding predicates.
Both actions remain in the same source fragment. No layout, helper prototype,
ABI, compiler flag, binding or translation-unit partition changes.

A fresh ordinary build repeats the preceding954cd26c source /bb2b2a43
payload before the edit. The selected generated source is
`7650c8d3b96683b69ef596d6eac0793ed8350ae24a7840c608a629e9929d43cf`.
Full canonical replay proves that the new82808-byte payload differs from
that baseline **only inside one four-byte JNE immediate at489E8E**:

| Observation | Value |
| --- | --- |
|Source branch|489E8C|
|Old source destination|47BF86|
|Selected source destination|479485|
|Changed root-relative byte offsets|69358,69359,69360|
|All bytes outside that immediate|Unchanged, including all metadata|

The selected source destination is the homologous EAX setter block; its
one-byte address difference from target479486 belongs to earlier code.
This is whole-payload invariance between two qualified candidates, not
canonical equality to target. No opcode, floating operation, argument
preparation, data pointer or unrelated edge changes.

All1230 prior equal complete physical membership/multiplicity checks survive;
six improve, for1236. The two setter groups now agree across slot8, RET and
all-indirect domains. **All153 physical RET memberships/multiplicities agree**,
including sites outside nondefault-action reachability. The35-site slot14,
51-site slotC and mixed8/C partitions retain their earlier equality.

Only300/320 remain different in physical CALL partitions:4351C0,473DD0,
478EE0 and slot8. Total indirect counts remain220 target/219 source; slot8
is132/131. No dynamic-count, path-feasibility, argument-equivalence or byte
equality claim follows from the ownership census alone.

## Controlled alternatives

Ten private controls start from the same freshbb2b2a43 baseline. All compile
and qualify under both complete object auditors; every frame remains570h.

| Source property | Canonical prefix | Payload / prefix | Source instructions | Old checks lost / new checks |
| --- | --- | --- | --- | --- |
|Byte carrier in616|`bb2b2a43`|82808 /81436|20245|0 /0|
|Int or unsigned-int616 carrier|`aba67d99`|82840 /81468|20261|13 /0|
|Short616 carrier|`cca9ebb0`|82856 /81484|20263|13 /0|
|Unsigned-short616 carrier|`641c0cf2`|82856 /81484|20263|13 /0|
|Root-scope616 int or one reused root int for all11 carriers|`aba67d99`|82840 /81468|20261|13 /0|
|Join619 completion, selected|`fbc0293d`|82808 /81436|20245|0 /6|
|Join669 completion instead|`fbc0293d`|82808 /81436|20245|0 /6|
|Join619 plus616 int carrier|`aba67d99`|82840 /81468|20261|13 /0|

The wide616 controls split650/651's correct landing group and disturb the
two correct next-sequence groups. They remain rejected. Target616 also
uses wide unsigned facing bits followed by signed-byte X arithmetic, but
that local observation does not justify losing complete-root constraints.
Its target effect preparation has22 instructions versus selected23;
the int control has22 but still differs in actual preparation bytes.
It is not a local exact match. The alternative619/669 source joins produce
identical complete payloads, so the original source label owner remains
underdetermined. No standalone-object or LTCG impossibility is established.

## Native completion protocol and negative source

The public `scripts/audit-reimu-616-completion.py` retains the complete void
root's object/metadata, surface, native helper, stack/RET ABI, state and trace
checks. It combines1576 existing616 high-middle inputs with320 supplied
sequence0 terminal states. It requires actual target execution through
489EF5/489EFC/479486/47948F/479498 on every completed input.

| Cohort | Cases | Required completed cases |
| --- | --- | --- |
|Motion|108|2|
|Nodes|252|0|
|Hover|1176|0|
|Hover shape|10|0|
|Texture|16|8|
|Existing required branches|14|0|
|Additional sequence0 completion|320|320|

The additional320 cases span five facings, two X and Y values, two x87
precisions, both players and both own/peer texture-duration settings.
The complete1896-case run passes0 differences:330 native completed setter/RET
chains,1423 other native RETs and143 first owned866 request entries.
Every request must be the real465190/866 entry with the existing actual
stack payload checks. A prototype's assumption that every inherited
"terminal" sequence reaches completion failed on the target. All original
inputs remain in the final matrix; only the explicit sequence0 terminal
domain forces completion. The remaining observed outcomes are checked by
cohort rather than silently discarded.

Input SHA256 is
`17e37523e79a7bd6722f0a006c06d45336923e131ea1a2d8ad59a5af6c54f4c8`.
Private source changing only616's completed operation to `set_action(1)`
passes both object auditors but fails **330/1896**, exactly the completed
domain's case count. The public audit exits1 as intended. No
helper return, world callback or target byte is fabricated.

Fresh selected full-root integration/shot/nonflat replay passes0/2675;
the public ten-action effect-direction audit passes0/400. Those matrices
retain their existing scopes and are not additive unique coverage. The
original full bool staging source also compiles, without an original-boundary
or full bool-native claim. Returning owned-object/effect construction,
arbitrary resource/animation graphs and initial floating environments remain
outside these bounded proofs.

## Real linked correspondence and remaining work

| Artifact | SHA256 / value |
| --- | --- |
|Focused selected object|`ccd995bedbb0f79ddbdab12286994af3a8735e9ba358857dd8f545a9e5d017eb`|
|Genuine producer's ordinary object|`df730f4f18cd10c67a935960fce1d8f97c07b46e38883283ca1ae67341c45df9`|
|Complete ordinary / genuine payload|`fbc0293d5e7ab9b39aca3d83c4d044ce7603d2e28d7961d2ff7736ef3f360177`|
|Genuine producer receipt|`10818536b0334cb8144dbbdbc97ac8923620be38d8595564b94f65bd9ad510c6`|
|Linked diagnostic image|`3aed6c4c53d07ddb54f1df19f2749b5dd624702b988c8bec7f7dd7a1592c41fb`|
|Payload / callable prefix / frame|82808 /81436 /570h|
|Target / source reachable instructions|20243 /20245|
|First strict target difference|+541 /4791BD, JNE operand at4791BB|

The current real source/CRT closure agrees for every ordinary/linked payload
byte, including2473 replayed fields,1281 PE HIGHLOWs,32 direct callee identities,
11 switches and15 request-buffer contracts. Eight linker INT3 bytes remain
outside the payload. The five documented nonexact providers remain nonexact;
the image was not executed. This experiment does not identify the original TU.

**Unknown:**300/320's distinct copies,616's effect preparation,720's temporary
homes, indeterminate740 inputs and full-root/world semantics remain unresolved.
Equal instruction totals or ownership groups cannot substitute for strict
canonical comparison. No aggregate percentage or all-unit cold replay is claimed.

## Reproduction and retained evidence

```bash
python3 scripts/probe-reimu-action-source-shape.py --emit-only --void-root --output-dir build/reimu-return616-20261020/selected
scripts/compile-unit.sh build/reimu-return616-20261020/selected/ReimuActionStateDispatch.cpp build/reimu-return616-20261020/selected/candidate.obj
python3 scripts/audit-reimu-call-sharing.py build/reimu-return616-20261020/selected/candidate.obj
python3 scripts/audit-reimu-root-relocations.py build/reimu-return616-20261020/selected/candidate.obj
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-616-completion.py build/reimu-return616-20261020/selected/candidate.obj
taskset -c 0 nice -n 10 python3 scripts/probe-reimu-action-ltcg.py
```

Local reports are under `build/reimu-return616-20261020/`: `facts.json`,
`summary.json`, `selected/{receipt,sharing,relocations,preservation}.json`,
`effect-prefixes.json`, `native616-public.json`, its `negative-action/`
counterpart, `native-directions.json`, `native-broad.json` and Ghidra/DB pins.
The current genuine receipts remain `build/reimu-ltcg/{receipt,coff-replay}.json`;
predecessor receipts are archived in this checkpoint's `prior-genuine/`.
Private regeneration recipes remain under the matching `.analysis/` directory.
VC8 builds run serially; heavy jobs use CPU0/nice10 and the single Ghidra
process uses a128MiB heap. Generated objects/reports and databases are not committed.
