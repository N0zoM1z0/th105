# TenshiObject action initializer (`0x00657150`): canonical exact

`0x00657150`, TenshiObject primary slot `+0x3C`, is **100% canonical exact** in
`src/characters/TenshiObjectActionEntry.cpp/.hpp` (`exact-first-tenshi-object-entry`)
across all **8,590 callable bytes** and all **8,902 switch-payload bytes** (1 table,
28 destination words, 198 action remap bytes, tail jump to `0x00596370`).

## Resolution of the trig-pointer and scheduling residual

Replacing raw `reinterpret_cast<unsigned char *>` offset macros with checked
`offsetof`-verified typed views (`TenshiObjectEntryView`,
`TenshiEntryMotionView`, `TenshiAuxiliaryView`) and removing the artificial
`float *const input = H;` locals in `case 854` and `case 940` lets VC8's typed
alias analysis and CSE naturally emit both native `mov reg, edi` copies
(`0x658261` and `0x658C23`) and match all 8,902 payload bytes
(`26030bc35e4311d36d2e5da5826042099bbe894820afc92716589f0e50af6cc2`).

Verification:
```sh
scripts/repo-python scripts/build.py --unit exact-first-tenshi-object-entry --compare --json
```

---
## Historical note (prior nonexact checkpoint)

`0x00657150`, TenshiObject primary slot+3C, now has complete selected source in
`src/characters/TenshiObjectActionEntry.cpp/.hpp`. Formal and independent cold
objects emit 8902 bytes against 8902. Both retain 3672 unmasked differing bytes;
the first is+0x6A7 (`0x006577F7`, target 82/source80), a branch displacement to a
later shared exit. Matching lengths are not exactness. No matches.csv record,
authored exact bytes or aggregate exact credit is added.

Selected canonical full-payload SHA256:
`120ed90b1136e82416472f22f5e5829aae42c7a5b0e90bf2038098fa9202a935`.
The complete comparison includes alignment, all destination DWORDs and all
remap bytes. There are no masks or skipped relocations.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-tenshi-object-entry --compare --json
taskset -c 0 nice -n 10 bash scripts/compile-unit.sh \
  src/characters/TenshiObjectActionEntry.cpp \
  build/exact-first-tenshi-object-entry-20261024/cold.obj
python3 scripts/compare-unit-object.py exact-first-tenshi-object-entry \
  build/exact-first-tenshi-object-entry-20261024/cold.obj --json
```

The compile returns 0; all four comparisons return 1 for the retained mismatch. The
existing-object comparator reports `build_provenance_verified=false`; the separate
cold compilation supplies build evidence. Formal receipts carry the source, compiler
and build-input hashes.

## Observed target identity, ownership and boundary

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/vtable origin anchors classify the root authored;
primary vtable `0x006C670C`, slot cell `0x006C6748`, contains 657150. No durable
name or source selection previously existed. Origin classification and the
pending-root rule remain unchanged because this root is nonexact.

| Region | Reviewed extent |
| --- | --- |
|Callable|657150..6592DD inclusive /8590 bytes|
|Compiler alignment|6592DE..6592DF /2 bytes, `8bff`|
|Destination table|6592E0..65934F /28 DWORDs|
|Action 800..997 remap|659350..659415 /198 BYTEs|
|Following separation|659416..65941F /ten INT3 bytes|
|Next independent callable|659420, outside this payload|

Callable SHA256:
`dfea8312b7e70d27f7ab6aaf1ab4404867ac4a0a434f826d0373cb50d5ae5d52`.
Complete 8902-byte target payload SHA256:
`26030bc35e4311d36d2e5da5826042099bbe894820afc92716589f0e50af6cc2`.
Raw CFG traversal reaches all 2112 decoded instructions, including the internal
loop alignment, all 28 destinations and every direct edge. There are 24 RET 0
exits,26 virtual slot 0C calls and one external tail 6591F3 ->596370. The function
reserves 20 local bytes, saves EBP/ESI and saves EDI only for in-range actions.
The source retains the real 980 tail and 24 RETs. The emitted two-byte final
alignment and 198-byte remap compare equal; the destination addresses vary with
the code layout. No target padding is copied into source.

| Direct callee | Physical calls | Observed contract |
| --- | ---: | --- |
|68A1A0|28|Compiler FTOL, implicit x87 argument|
|4067D0|57|cdecl random bound, unsigned conversions at float sites|
|435160|20|ECX=this+4, two float arguments, RET 8|
|435D60|8|ECX receiver, x87 stage-height result|
|45CD70|8|Auxiliary replacement, signed-WORD argument in four-byte slot|
|4FCA60|7|Parented object request, seven four-byte arguments, RET 28|
|64CCB0|6|Unparented object request, seven four-byte arguments, RET 28|
|4063D0 /406360|3 /3|Quantized cosine/sine, one float stack argument|
|45C030|1|Parent wave request with unsigned handle 56|

All 141 physical direct calls and 26 virtual calls remain. The root COFF section
contains 336 relocations:142 REL32 (141 calls plus the tail) and 194 DIR32
(literals, global and switch metadata). Every relocation is replayed by the
full audit. Equal call counts alone are not semantic or canonical acceptance.

## Inferred source and independently checked family differences

IkuObject and the recent Object initializer sources supply working hypotheses;
Tenshi's actual constants, offsets, argument widths, reads and branches are
checked against its own instructions. The source intentionally keeps numeric
states, offset accesses and declaration-only helpers. Receiver classes are
pointer-only partial call views: never construct or embed them as full owners.
The local signed-WORD selector carrier uses a four-byte stack slot and does
not change the existing shared selector implementation or header.

Specific retained target facts include:

- Prefix zero order is F4/F8/370/374/378, WORD384, float 37C, WORD386,
 float 380, BYTE184, then WORD364/366/368/36A/36C.
- 801 sequence 0 and 920 sequence 4 execute motion, load H[0], write BYTE184,
 then store the loaded heading. A real consumed double capture preserves this
 read epoch even when the input aliases BYTE184. Motion remains before the
 capture; moving the capture across the real helper is unsupported.
- 801 sequence 4 and 920 sequence 8 store direction from unsigned RNG 100
 **<=50**, inclusive. Other shown direction branches use <=49. Both parent
 deltas are stored before the actual RNG call.
- 820's optional object pointer+34C differs from parent+348. States 1/2/5
 retain separate repeated checks; layer BYTE33C is zero-extended. State 3
 uses the parent and writes float 378=5.
- 854/940 retain the input pointer across the cosine and sine calls, with a
 fresh H[1] read for the latter magnitude. 854's Y formula adds parentY+double100
 before the sine product;940 adds parentY alone. Facing multiplication is signed
 BYTE104, whereas object-request facing is zero-extended BYTE104.
- 940 sequence 7 reloads H[0] after the intervening owner stores for its payload.
 Sequence 13 dispatches parent handle 56, clears DWORD144, and supplies
 {H[0],180,9}; actual native order evaluates sine/Y before cosine/X.
- 960/961 and 962 use signed WORD13E<=7, including negatives. Global effect 14
 sets BYTE111/112=128; auxiliary 989 uses widths 1.05/1. For 962 the auxiliary Y
 is negative parent float 828. Its real float counter 0..<8, step double 1,
 yields {RNG 30+n*double 45,20,4}. Layer+1 covers ordered angle 0..180 inclusive,
 otherwise-1; the 815 request obtains its real Y from stage_height().
- Case-local payload lifetimes retain the real 980 jump. Real product-rounding
 temporaries and target literal widths remain explicit; no inert local,
 fabricated return, fake ABI, assembly or byte array is used for matching.

## Finite complete-function experiments

| Trial | Whole payload / result |
| --- | --- |
|00: first complete source|8890 vs 8902; first+80; SHA 77960b23...|
|01: preserve both heading-read epochs|8890; SHAf5f36541...; alias defect fixed|
|02:962 natural separate layer-branch spawn expressions|8902; selected SHA 120ed90b...; first+6A7|
|03:854/940 first cosine uses -H[0] instead of -input[0]|Byte-identical to 02|
|04:local float-return trig declaration hypothesis|Byte-identical to 02; keep supported double view|

Trial 02 naturally emits the independently prepared branch arguments and
merges the native call, retaining the original call counts. It does not add
synthetic paths. Trials 03/04 were scoped to the two native pointer copies and
x87 return scheduling. Both are byte-neutral; do not repeat them unchanged.
An unproven return-precision declaration is not retained solely because it
generates the same bytes.

Remaining observed differences include the native pointer copies
658261 `mov edx,edi` and 658C23 `mov eax,edi`, regional register rotations,
940 payload/argument scheduling,960/962 registers, loop alignment and epilogues.
The standalone source omits those copies. The early displacement mismatch is
an effect of later layout;3672 byte differences include shifted regions and
must not be described as a handful of isolated opcode corrections. The correct
source/TU cause remains unknown; no LTCG requirement has been established.
Park this checkpoint and select another complete representative.

## Ten focused native controls

Both path audits (since removed) returned 0: ten inputs, ten actual RETs, zero mismatches. Vector SHA256:
`d5c23241eeb65cfd04d212c3588d5b585d7fbc7936d9fbed0ea350fd0c6e54ee`.
Four inputs exercise 801/0 and 920/4 with ordinary versus BYTE184-aliased input;
six exercise 801/4 and 920/8 with actual native random returns 49/50/51. The harness
uses the original vtable, a checked one-node action map,14 linked untextured
sequence/frame fixtures and deterministic MT state data. Original selector,
map lookup, frame application/commit, motion, MT and RNG instructions execute;
no helper/vtable code is patched and no return/result is injected. A hook at
the native RNG RET observes its actual bound 100/result. All ten complete RET 0
with stack delta 4 and unchanged x87 control word/top0. Full actor bytes, native
call traces, RNG state index/returns and x87 environment are compared.

The target separately confirms heading 1.0 after mode BYTE184=1 on the first
four inputs, parent deltas 540/80 and direction 1/1/0 on each threshold triple.
The original 00 source fails exactly the two aliases. A negative control changing
only both <=50 guards to <=49 fails exactly the two actual 50 inputs. Reports:
`native-paths.json`, `cold-native-paths.json`, `negative-heading-paths.json` and
`negative-threshold-paths.json` under the scoped build directory. These controls
resolve two concrete semantic questions; all other actions/gameplay remain
outside their execution scope. They add no exact credit.

## Analysis safety and remaining unknowns

IDA preflight rejects the GUI database SHA 10350095..., so it supplies no
semantics or writes. Raw analysis uses only the hash-attested PE. One serial
direct Ghidra run uses CPU 0/nice10,384MiB heap and read-only/noanalysis mode.
Imported/disk SHA, base/entry, raw-backed section bytes and root hash are checked
independently. Temporary bounded root/helper signatures and CALL_RETURN on
the 980 tail are read back and rolled back; all nine primary DB pins remain
unchanged. Decompiler output is only a hypothesis, never pasted as source.

One new generic literal key `__real@3f866666` pins the observed float 1.05 to
`0x006C4244`, bytes 6666863f. Existing bindings, accepted source headers and
compiler flags are untouched. Full owner identity/layout, original TU/spelling,
trig return precision beyond the used x87 ABI, and residual compiler scheduling
remain unknown. Exact totals are unchanged; the previous Iku 513-unit cold
aggregate receipt is historical evidence, not a new all-unit replay here.
