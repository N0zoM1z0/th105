# Reimu602 frame guard and600/601/602 direction carrier

## Selected source and target identity

`ReimuActionStateHighEntryCases.hpp` now checks602's frame counter, timer and
index before its sequence/count predicates. The600/601/602 effect115 path also
captures the unsigned facing bits in an int, then consumes their signed-byte
interpretation for X and their unsigned value for the direction argument.
All1214 formerly equal complete action-membership/multiplicity checks survive.
The three effect argument-preparation windows now reproduce the target's actual
registers, widths, stack slots and canonical literal addresses. This is bounded
source/dataflow evidence, not partial exact credit or an original-source claim.

The authored parent remains `Reimu_dispatch_action_state_vslot28 @478FA0`,
`[478FA0,48CE2E)`,81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Only original Japanese1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. No implemented/matches row or compiler boundary is added; the root
remains unclassified/declaration-only.

## Observed instructions and inferred C++

**Observed:**602 starts488910. After landing473DD0 and texture publication45F560,
MOVZX488922 reads WORD13E; CMP488929 tests sequence1. Short JNE48892D skips only
the counter45 early-exit check; JG488936 targets the common next-sequence tail
47D7BE. At48893C,488949 and488957 the target tests DWORD144, WORD142 and WORD140
against zero, then CMP488965 tests AX against1 and CMP48896F checks WORD730<14.
Wave8 at488981 and the actual MT call4066B0 at488986 follow only that full guard.

The previous source tested sequence/count before those three zero fields. Its
compiler output instead threaded the first JNE past the complete spawn guard
and generated a redundant CMP AX,AX. Six other inspected high guard prefixes
already had the target's instruction shapes;602 was the exception. Reordering
602's source predicate restores its short skip and actual field-check order.
600/601 retain their sequence/count/modulo-five order.

The MT remainder conversion itself was already correct. The target retains
TEST EDX,EDX488994, FILD m3248899A, JGE48899E and the unsigned2^32 correction
FADD4889A0, then subtracts double35. Source emits the same sequence. A signed
FILD alone would not prove a signed source value; the unsigned `%70U` expression
is retained.

**Observed:**600/601/602/650/651's effect115 preparation, after event23, has16
instructions/64 bytes.602's Y load/FADD begin488A8F/488A95; MOVZX488A9B reads
BYTE104 into EAX, and MOVSX488AA4 interprets AL as signed for X. The same EAX
value supplies the unsigned direction push488AAF. Source previously loaded AL,
then separately zero-extended and sign-extended it, using17 instructions/66 bytes.

**Inferred source carrier:** a used int value in0..255 exposes that wide reuse;
`static_cast<signed char>` preserves the negative-facing X calculation. The
field declaration, helper signature and class layout remain unchanged. An
unsigned-char local is byte-neutral; int and unsigned-int carriers reproduce
the same602 candidate. This does not uniquely identify the original local type.

The selected family carrier restores all three600/601/602 preparation windows,
not just their lengths. Extending it to650/651 also fixes those local windows
but incorrectly merges the target-distinct197/658 and198/608 landing pairs,
losing ten previously equal checks across height/clear/slotC/RET/indirect domains.
That broader control remains unselected. Source selection uses complete-root
ownership and dataflow, rather than a local window or a smaller payload alone.

## Shared-tail investigation and controls

The target has two next-sequence/RET blocks:47D7BE->CALL47D7C5->RET47D7CE and
4852F6->CALL4852FD->RET485306. Full raw decoding finds19 and18 direct incoming
branches. The helper is the accepted unsigned-char thiscall45C220/138-byte
sequence advance; the root discards its return value.

Private source controls are pinned to generated source8751b928 / canonical
01a4ea74 from the previous checkpoint:

|Control|Complete qualified outcome|
|---|---|
|Five early joins, two late joins, combined seven joins, or all-high joins via619/610 labels|Retain both wrong complete memberships;619 or other high callers can move into the wrong copy|
|Early/late/seven outer-switch breaks|All82840 old canonical bytes unchanged|
|Well-typed void return cast or discarded result cast|All82840 old bytes unchanged|
|Inline threshold/count constants|All82840 old bytes unchanged|
|Positive else or inverted else forms, early/late/seven|All82840 old bytes unchanged|
|602 frame-first predicate only|82840-byte canonical `de9e3410cc6cd69ab64242cfe71f0cfd1c846b2dad8b89f53aad6f71f167c1ed`|
|Frame-first plus602 int/unsigned-int direction only|82824-byte canonical `8aeb06ec653ba60b3760993572265b49caf495ff0a76bd03cffc731d51b2f13b`|
|Frame-first plus600/601/602 int carriers, selected|82824-byte canonical6527316d below; no prior equal check lost|
|Carriers extended to650/651|82792-byte bd81246a; ten prior checks lost, rejected|

Returning the helper's unsigned-char value directly from the void root is not
a valid control: VC8 rejects it with C2562. No prototype is altered to admit it.
These source experiments establish neither original TU ownership nor a concrete
standalone-object/LTCG impossibility. The first shared-tail hypothesis did not
solve the full partition; the concrete602 ordering and carrier facts did improve
the selected source. The seven-prefix diagnostic explicitly abstracts the choice
of next-sequence return copy, reports actual destinations separately and cannot
be used as canonical equality.

## Current compilation and comparisons

|Artifact|SHA256/value|
|---|---|
|Generated selected source|`c9107448d21588ecd59f4b528b14ec7a82fb7d77a4f8c13d6b7c9f6f5c562481`|
|Ordinary object|`fa172c304ff7bf7cf5291487bcbee9f71b009656ed8918b5ec0abf667a0eeff7`|
|Complete ordinary/genuine canonical payload|`6527316db79ea2e1e3dd600c057f6376b472fcf43f7f6d9f2f861dac716481a8`|
|Genuine producer receipt|`de9c95cd46d9bcbcbecee1034bc46214a5ae79e26e60875799fe7d2ab45e22c6`|
|Payload / prefix / frame|82824 /81452 /570h|
|Reachable target/source instructions|20243 /20254|
|First strict target mismatch|+541 /4791BD: targetA9/source41|

The genuine producer was rebuilt after the selected source edits. All82824
ordinary/linked payload bytes agree, including1372 metadata bytes and2473
replayed fields. All1281 PE HIGHLOWs qualify; eight linker alignment bytes are
accounted for separately, outside that payload. Field roles remain
1104 numeric,1185 REL32 calls,14 metadata addresses, seven globals and163 code
pointers. All11 switches and15 request-buffer contracts qualify. COFF object
hashes include timestamps; source/canonical hashes and compiler receipts qualify
reproduction. The full linked correspondence is `build/reimu-ltcg/coff-replay.json`.

Five direct partitions still differ, and physical direct counts remain1188/1185.
Indirect counts remain220/219; slotC and mixed8/C partitions stay equal. Among
the two large slot14 groups,601/602/604 now associate with the target's group;
605/608/651/658 still differ. Complete slot8/14 and RET ownership remains open.
No new exact bytes or aggregate cold replay is claimed.

## Native evidence and reproducible scope

Fresh selected ordinary execution passes0/2675 integration/shot/nonflat cases,
input SHA256 `0e67cae006499020bea8fcb508aa311d710ce27da157685ecec0e55fb33d8cdc`,
and0/210 602 firing/miss inputs, SHA256
`1059297b0f580c45ddabc9785119149a0b8a2a668aa1e83ca8736a5d9913b55d`.
The latter cover signed counts-32768/-1/0/13/14/15, five facings, both x87
precisions and the three actual-native-seeded states0/5489/FFFFFFFF.120 cases
require the real MT draw and object854 entry/three-float payload;90 require RET.
An initial unsupported seed request correctly failed the fixture gate; the
successful matrix uses the existing real406670 seeding paths, not fabricated MT
returns. Changing the count bound<14 to<=14 qualifies structurally but fails30/210.

The selected canonical payload also equals the private family candidate that
passes0/480 next-sequence threshold cases and0/100 effect115 entry cases. The
threshold matrix spans13 high actions/16 guards and requires200 actual47D7C5
callbacks and120 actual4852FD callbacks through root RET;440 cases RET and40
stop at real object465190 entry. Input SHA256
`e606fb7e7b8a7566c9ae4042451d1d740dc6f6bb2472ad50f494153090167197`.
An ownership-wrong all-high-join control also passes480; native agreement alone
therefore does not establish physical sharing. A wrong608 >20->>=20 source
control passes object/relocation gates and produces10/480 real mismatches.

The effect matrix samples600/601/602/650/651, five facings, two X values and both
x87 precisions, requiring100 actual effect115 entries. Input SHA256
`0dbf2d0f31f087b6277120cf590f26a5cfcffa8d632314e5eea4551cfe18db85`.
A wrong602 unsigned X consumption instead of signed-byte interpretation gives8/100
real mismatches. These execute real preceding game helpers and compare entry
arguments; returning object/effect constructors remain outside the proof.
Independent bool staging through606 passes0/2136 cadence/texture/required-branch
cases, input SHA256 `cb73802c2ee04ddc6ecdf94801bcf2124e75c046bbc3053e10a49373b2ab5465`.
Repeated/code-identical matrices are not counted as additional unique coverage.

Direct read-only Ghidra independently checks imported target hash, base/entry,
x86/windows analysis target, full mapped text and callable bytes before decoding
both tails/all37 edges,602's guards/unsigned conversion and five preparation
windows. All nine primary DB hashes remain unchanged and temporary aliases are
removed. Java heap128MiB and CPU0/nice10 bound the analysis; VC8 builds are serial.
Recipes are `.analysis/reimu-next-sequence-20261019/{probe,native,native602,effect115,guard-prefixes,effect-prefixes,stage}.py`
and the three `ghidra*.py`/Java pairs; reports are below the corresponding build
directory. The prior8751b928 baseline is pinned there for regenerating controls.

```bash
taskset -c 0 nice -n 10 python3 -B scripts/probe-reimu-action-ltcg.py
python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
python3 -B scripts/audit-reimu-root-relocations.py build/reimu-ltcg/ordinary.obj
taskset -c 0 nice -n 10 python3 -B .analysis/reimu-next-sequence-20261019/native602.py build/reimu-ltcg/ordinary.obj
```

**Unknown:** whole-root canonical equality, original TU/profile/visibility,
remaining ownership and returned-world/resource behavior remain unproved.
Indeterminate740 inputs, arbitrary stacks/animation graphs and full-game state
stay outside native admission. Shared ABI/layout/flags/bindings and all accepted
exact units are unchanged. The root remains one bounded authored reconstruction.
