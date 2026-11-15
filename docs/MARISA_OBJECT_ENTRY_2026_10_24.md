# MarisaObject action initializer: complete source, nonexact checkpoint

`0x004C8050`, MarisaObject primary slot+3C, now has complete selected source in
`src/characters/MarisaObjectActionEntry.cpp/.hpp`. Formal and independent cold
objects give the same 10536-byte payload against 10532. The full audit retains 5019
unmasked differing bytes, including shifted code/metadata and the four-byte
length difference. First mismatch+80 (`0x004C80D0`, target 02/source05) is the
entry branch displacement to the later default exit. No exact credit is added.

Selected complete canonical SHA256:
`81d39347dd1c478a035b58ae8337ca6d10f70aa0fdab935637f856932aabe5ea`.
All 146 physical direct calls,43 virtual calls,45 RET 0 exits and the real 980 tail
remain. All 200 remap bytes compare equal. Case 822's306-byte emitted region also
compares equal after its payload correction. These are diagnostics; acceptance
still requires equality of the whole callable and complete emitted payload.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-marisa-object-entry --compare --json
taskset -c 0 nice -n 10 bash scripts/compile-unit.sh \
  src/characters/MarisaObjectActionEntry.cpp \
  build/exact-first-marisa-object-entry-20261024/cold.obj
python3 scripts/compare-unit-object.py exact-first-marisa-object-entry \
  build/exact-first-marisa-object-entry-20261024/cold.obj --json
```

Compilation returns 0; all four comparisons return 1 for the retained mismatch. The
full audit replays every relocation through the complete section tail, including
both destination tables and the action remap; there are no masks. Existing-object
comparison reports `build_provenance_verified=false`; the separate cold compilation
supplies build evidence. Formal receipts include source/compiler/input hashes.

## Observed target identity, ownership and boundary

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/allocator-owned vtable anchors classify the root authored.
Primary vtable `0x006C44FC`, slot cell `0x006C4538`, contains 4C8050. No durable
name or source selection previously existed. Origin classification, pending-root
selector and authored denominator remain unchanged because this is nonexact.

| Region | Reviewed extent |
| --- | --- |
|Callable|4C8050..4CA7DD inclusive /10126 bytes|
|Internal unreachable loop alignment|4C86E9..4C86EF /`8da42400000000`|
|Final compiler alignment|4CA7DE..4CA7DF /`8bff`|
|Primary destination table|4CA7E0..4CA89B /47 DWORDs|
|Action 800..999 remap|4CA89C..4CA963 /200 BYTEs|
|Nested match-identifier table|4CA964..4CA973 /4 DWORDs|
|Following separation|4CA974..4CA97F /twelve INT3 bytes|
|Next independent callable|4CA980, outside this payload|

Callable SHA256:
`4aaebfa43b4c0efabaf2b6fdddfcf4f7e1c97dfde8c23a6ebf2a8a881360220b`.
Complete 10532-byte payload SHA256:
`374f0f36f53eed919047c7a8453880a50b5df7952036717a643f174743b290b2`.
Raw traversal reaches 2649 instructions plus the one isolated internal alignment
instruction,2650 decoded total. Each indirect dispatch follows its own reviewed
table. The only external jump is 4CA75F ->596370. There are 45 RET 0 exits,20 local
bytes, saved ESI/EDI and additional EBX/EBP saves for in-range actions. Virtual
calls comprise 38 slot 0C selectors and 5 slot 1C frame selectors; each FTOL result
is passed in one four-byte argument slot. No EH region is observed.

| Direct callee | Physical calls | Observed contract |
| --- | ---: | --- |
|68A1A0|43|Compiler FTOL, implicit x87 input|
|4067D0|51|cdecl bounded random draw, unsigned conversion at float sites|
|4066B0|18|Raw MT19937 result, unsigned remainder at caller|
|496420|4|Secondary animation, int/float/three int arguments, RET 20|
|64CCB0|7|Unparented request, seven four-byte arguments, RET 28|
|435160|4|ECX=this+4, two float arguments, RET 8|
|4FCA60|16|Parented request, seven four-byte arguments, RET 28|
|45CD70|1|Signed-WORD auxiliary resource in four-byte slot|
|465190|1|Parent-owned object forwarding call, seven arguments, RET 28|
|406360|1|Quantized sine, float argument/x87 result|

The selected root section has 415 relocations:147 REL32 (146 calls plus the tail)
and 268 DIR32 (literals, global and switch metadata). Every one is replayed.
The raw MT remainder form is preserved; it must not be replaced by the bounded
helper, whose division algorithm is different.

## Inferred source and independently checked family differences

The source retains offsets, numeric states and declaration-only helpers.
Recent Object initializers provide patterns only. Every case is checked against
this root's own operands, callee contracts and edges. Partial receiver classes
are pointer-only call views: never construct/embed them as full owners. The
selector/frame signed-WORD carriers use four-byte slots and do not change
accepted shared declarations. Return values of those virtual calls are unused
here; nominal original class identity/types remain unknown.

- Prefix zero order follows 37C, WORD384,380,WORD386.800 starts both scales 2,
 marks184, stores H[0] heading, then selects. Only signed sequences 2..5 use
 scale 1. Its sequence 7 also writes the generated magnitude back into H[1].
- 801/802 retain separate repeated RNG sites and writable H[0]/H[1]. Real
 consumed float magnitude and unsigned integer producer captures keep the
 calculation before looking up its destination.800/801 use magnitude base 10,
802 base 15;860 adds integer 10 before unsigned-to-float conversion.
- 811's sequence 0 emits 16 four-float requests plus one final request, then
 moves and reloads heading. Its float-angle packet is {80-RNG160,
 RNG 250*double(float 0.1)+10,3,RNG 45}; the final packet is {0,0,4,0}.
- 821 selects from **H[0]**, not H[2]. Signed sequence<=2 writes velocities 6/4.5;
 sequence 5 sends one-float packets 7 and 8 at layers+1/-1.822's signed<=5 branch
 sends {0,0,12}; sequence 6 sends {H[0],0,7} then **{H[0],0,8}**, changing the
 third item. The first whole comparison exposed the initially mistaken second
 item; the corrected 306-byte region is identical, with no partial exact credit.
- 825's signed<=3 resource key zero-extends the sequence first, then adds 991
 as a full integer.900 instead adds 991 in 16 bits then zero-extends. Negative
 sequence behavior therefore differs: do not normalize the two forms.
- 852/853 start scale 11C=4 while 120=0; the prefix's live x87 zero supplies
 the latter.853 keeps signed BYTE facing multiplication and separate sequence 10/
11 resource/scaling operations.865/901 capture H[0] before the mode-byte write
 at sequence 8, retaining the observed heading-read epoch under aliasing.
- 859/860/861/912/913 select H[3] through slot 1C after slot 0C.859 compares
 unsigned RNG 100<=50 before selection. Its four-float parent-owned request is
 {0,0,4,signed sequence}; the packet's leading zero is real despite the
 decompiler's misleading stack-local grouping. Repeated sequence guards after
 real calls are retained.860 uses {0,0,3,0} then {0,0,4,0} with different helpers.
- 863 computes velocity from the parent's opponent+170, double 50 and signed
 facing. Its three-request loop uses raw MT modulo 180/50, then bounded RNG 15.
 The layer is zero-extended BYTE364, including 255 when the WORD is-1; it is
 not a signed-1 layer argument. Integer facing*DWORD144*20 precedes the X sum.
- 865 sequence 19 optionally computes sine(float(-T.H[0]-parent7AC))*double-4;
 absent+34C leaves heading untouched.901's sequence 19 instead clears 184 and
 reloads H[0]. Both end with scale 120=0.1.
- 869/920 retain three independent parented requests with 3/4/4 float packets;
 later requests retain the first heading across the real helper.900 uses its
 own opponent+170 (distinct from 863), signed sequence guards, timer 366 from
 the 0/1/2/3 match table, and independent later scale/mode branches.
- 913 retains the real RNG bound 1 call, then*double 16-double8 and motion;
 no deterministic-call elimination is introduced.989 clears color bytes only
 after its real spawn;990 clears 134;998 writes heading 0/rotation128=60.

## Finite experiments and retained residual

| Trial | Complete payload / result |
| --- | --- |
|00:first complete source|10608 vs 10532, SHA 4936869d...; all call counts already agree|
|01:correct 822's third payload item|10608, SHAd00c8798...; actual semantic correction|
|02:consumed producer captures before input-array destinations|10584, SHAbaa4abdf...; four magnitude forms recovered|
|03:float rather than double carrier for integral input writes|10584, SHAfba6a4fe...; restores DWORD conversion correction|
|04:explicit double cast on 801/2 RNG operand|Byte-identical to 03; unselected|
|05:retain four real unsigned heading producers until destination conversion|10548, SHA 1b4f986d...; removes four redundant float spills|
|06:unsigned producer captures for 801/2 sum and 860 integer-add result|10536, selected SHA 81d39347...|
|07:unsigned sequence carrier at 825 guard/resource call|Byte-identical to 06; unselected|
|08:separate 16-bit900 key/add before resource call|Byte-identical to 06; unselected|

All captures feed real arithmetic/stores. No inert local, copied target array,
assembly, fabricated return, ABI lie or padding is used. Trial 06 recovers the
remaining producer forms;07/08 are consecutive neutral controls, so park.
Residuals include 825's redundant zero-extension/register,826/827 and 901 selector
scheduling,859/861 constant 1 materialization (MOV versus LEA),900 resource/payload
scheduling and nested-case order,913 constant placement,980 tail placement and
final alignment. The raw 5019 differences include shifted code; a four-byte
length delta is not a four-byte mismatch claim. Full source/TU/compiler cause
remains unknown, and no LTCG requirement is established. Reopen only with new
independent evidence; continue another complete representative.

## Ten focused native RET controls and negative witnesses

Both path audits (since removed) returned 0: ten actual RET 0 paths, stack delta 4, zero mismatches. Vector SHA256:
`aa1db8d4272e5a37f588c89cabcc63dc0a30f1fa28eb9645d6a794489a582c36`.
Six inputs exercise 900/12 with match identifier-1/0/1/2/3/4, confirming timer
0/120/120/180/240/0. Three exercise 821 with H[0]=0/2/6 and H[2]=11, confirming
the true selection source and resulting velocities. One exercises 902/1's two
raw MT calls/remainders. Actual native MT returns 2806323152 and 4194449 yield
remainders52 and 89; scale bits 3FC28F5C and heading 89 are independently asserted.
The bounded algorithm would produce 65 for the first draw, rather than 52.

The original vtable, checked one-node action map,14 valid linked untextured
sequence/frame fixtures, selector/map/frame application/commit and MT bodies
execute original instructions. An observation hook reads MT/RNG RET values;
there is no patched helper/vtable, injected result or synthetic return. Full
actor bytes, native calls, random draws/index and x87 environment agree. Control
word 027F and top 0 are retained. Other actions, spawn bodies and later gameplay
are outside the execution scope.

A negative source changing only 821's selection to H[2] fails all 3 corresponding
inputs. Replacing only the inline modulo producer with the bounded helper fails
the 902 input. Reports: `native-paths.json`, `cold-native-paths.json`,
`negative-selector-paths.json`, `negative-modulo-paths.json`.
Separately, restoring the incorrect 822 item changes exactly one canonical byte:
4C8E0B, displacement 1C->18. The public full audit's diagnostic 306-byte equality
becomes false (`negative-payload-full-audit.json`); root comparison remains
nonexact in both versions. None of these witnesses adds authored exact credit.

## Analysis safety, literals and unknowns

IDA preflight rejects GUI database SHA 10350095...; it supplies no semantics or
writes. Raw fact packets use only the hash-attested PE. Two serial direct Ghidra
passes use CPU 0/nice10,384MiB heap, read-only/noanalysis. The second corrects the
temporary secondary-helper extent 200 to its independently ledgered274; no helper
body from the short view is relied on. Imported/disk SHA, entry/base, raw-backed
mapped sections and root hash are independently checked. Temporary bounded root/
helper views and CALL_RETURN on the 980 jump are read back and rolled back; all
nine primary DB pins remain unchanged. Decompiler output is only a hypothesis,
never mechanically pasted as source. Shared-callee ranking is refreshed first.

Five new generic literal keys pin actual target values; existing bindings,
accepted headers and compiler flags are untouched:

| Key suffix | Address / bytes | Value |
| --- | --- | --- |
|3fa47ae140000000|6C4700 /00000040e17aa43f|double(float 0.04)|
|40900000|6C3EA8 /00009040|4.5f|
|3fe66666|6C46F8 /6666e63f|1.8f|
|41b00000|6C3D58 /0000b041|22.0f|
|c010000000000000|6C4648 /00000000000010c0|double-4|

Each suffix belongs to a `__real@` key. Full nominal owner identity/layout,
original source/TU and residual scheduling remain unknown. Exact totals are
unchanged; the prior Iku all-unit cold receipt is historical evidence, not a
fresh aggregate replay after these nonexact source additions.
