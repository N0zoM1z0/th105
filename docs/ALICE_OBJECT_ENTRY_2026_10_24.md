# AliceObject action initializer: complete canonical exact source

`0x0050C1C0`, AliceObject primary slot+3C, now has complete selected source in
`src/characters/AliceObjectActionEntry.cpp/.hpp`. Formal and independent cold
objects reproduce **10715 callable bytes and all11072 emitted bytes** with
zero unmasked differences. Complete canonical SHA256:
`c6c0684ebdd4a826a41a4e057574d3d96696e924282ad63fd5aa7ee5fef2bdce`.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-alice-object-entry --compare --json
python3 scripts/audit-alice-object-entry.py
taskset -c 0 nice -n 10 bash scripts/compile-unit.sh \
  src/characters/AliceObjectActionEntry.cpp \
  build/exact-first-alice-object-entry-20261024/cold.obj
python3 scripts/compare-unit-object.py exact-first-alice-object-entry \
  build/exact-first-alice-object-entry-20261024/cold.obj --json
python3 scripts/audit-alice-object-entry.py \
  --object build/exact-first-alice-object-entry-20261024/cold.obj
```

All return0. The public payload audit replays every relocation through the
complete section tail, including alignment and both switch tables. There are
no masks or partial exact percentages. Existing-object comparison reports
`build_provenance_verified=false`; the separate cold compilation supplies its
build evidence. Formal receipts include source/compiler/input hashes. Reports
are below `build/exact-first-alice-object-entry-20261024/`.

## Observed target identity, ownership and boundary

Only original Japanese1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/allocator-owned origin anchors classify this root authored.
Primary vtable `0x006C4B54`, slot cell `0x006C4B90`, contains50C1C0. No durable
semantic name or source selection existed before this work. The frozen origin
selector and authored byte denominator remain unchanged. The skip-matching
origin rule now selects29 pending roots/659829 bytes instead of30/670544;
Alice moves to the canonical-exact-authored baseline. Frozen pointer witnesses
remain unchanged; the origin census is regenerated from the same rules.

| Region | Reviewed extent |
| --- | --- |
| Callable | 50C1C0..50EB9A inclusive /10715 bytes |
| Internal unreachable alignment | 50D5C9..50D5CF /7 bytes |
| Internal unreachable alignment | 50D814..50D81F /12 bytes |
| Final compiler alignment | 50EB9B /one NOP |
| Destination table | 50EB9C..50EC37 /39 DWORDs |
| Action800..999 remap | 50EC38..50ECFF /200 BYTEs |
| Next independent callable | 50ED00, immediately outside the payload |

Callable SHA256:
`470700bd2cac163653d42861153065b3103c8a6be2cfd7c058c40e2b6b4beba7`.
Raw traversal accounts for2687 reachable instructions plus four internal
unreachable alignment instructions,2691 decoded total. The latter contain
`lea esp,[esp]`, another such LEA, a jump to the following reachable block,
and `lea ecx,[ecx]`; source does not synthesize these compiler artifacts.
All39 table entries and200 remap bytes are reviewed. Entries36 and38 both
reach50EB89:36 is specifically the explicit998 no-op state,38 the default.
The only external jump is the real980 tail50EB42 ->596370. There are33 RET0
exits,20 local bytes and saved EBP/ESI, with additional EBX/EDI saves for
in-range actions. No EH region is observed.

| Direct callee | Physical calls | Observed contract |
| --- | ---: | --- |
| 68A1A0 | 35 | Compiler FTOL, implicit x87 input |
| 4FCA60 | 28 | Parented request, seven four-byte arguments, RET28 |
| 406540 | 11 | cdecl float atan2_degrees(float y,float x), accepted shared ABI |
| 68A380 | 11 | Compiler __CIsqrt, implicit x87 input/result |
| 4067D0 | 21 | cdecl bounded RNG, unsigned conversion at float use sites |
| 435160 | 4 | ECX=this+4, two float arguments, RET8 |
| 64CCB0 | 16 | Unparented request, seven four-byte arguments, RET28 |
| 45C030 | 3 | ECX parent, unsigned wave handle, RET4 |

All129 direct calls,34 virtual slot0C selectors and the980 tail are retained.
Each selector receives its signed-WORD carrier in a four-byte slot; the extra
FTOL site converts856's H[3]. The selected root has326 relocations:130 REL32
(129 calls and the tail) and196 DIR32 (literals and switch metadata). Every
relocation is replayed. Declaration-only callees receive no source/exact credit.

## Inferred source and independently reviewed family differences

The source retains numeric states, offsets and partial pointer-only receiver
views. Never instantiate/embed these views as a complete recovered owner.
Recent Object initializers provide patterns, but Alice's own instructions,
access widths, callee contracts and edges govern each case. Nominal class
layout, original names/source spelling and TU partition remain unknown.

- 801/805 call the selector only for ordered H[2]>=2. Values below2 and NaN
 retain the existing sequence.801 sequence10 first emits {0,0,12}, then four
 packets **{0,n*90,11} for float n=0,1,2,3 inclusive**. The angle is the second
 item. Whole comparison exposed both the initial wrong item and `<3` endpoint.
- The prefix clears WORD384 before float37C and WORD386 before float380.
 800/806 retain separate physical bodies despite identical heading/selection
 behavior.998 owns an explicit empty case independently of the default mapping.
- All eleven AIM regions read angle coordinates from the owner's opponent+170,
 adding double100 to Y, while distance uses the separate target+34C. Only the
 latter pointer gates the region. Float square/sum and sqrt round trips remain
 distinct; natural sqrt selects the observed compiler helper. Facing does not
 alter the angle here. Do not substitute the existing Alice flight-update body.
- 810/825 read signed parent skill bytes604/607 at thresholds2/4, while816
 replaces BYTE184 with signed parentBYTE609>=4. A negative skill clears it.
 825's request uses action810.820 and851 retain actual four-float packets.
- 849's six-packet loops use {n*60+30,0,6} or the variant14. Layer-1 applies to
 angle<=90 or angle>=270; the other arm uses+1. The negated comparisons retain
 the target's unordered behavior, unlike a positive open-interval conjunction.
 The integer loop has six iterations; it is independent of801's float loop.
- 850/853 round the opponent X difference and fabs result to float, then divide
 by double42/22 and clamp below2. Their radial packet loops step45/30 and use
 second items30/40. The own-opponent pointer is not the distance target pointer.
- 856 converts H[3] to a signed integer before `%2`, multiplies by4 and subtracts
 double2. A negative odd input gives-6; even gives-2 and positive odd gives2.
 It then emits the actual four-float {0,0,9,0} packet. An unsigned/bitwise parity
 rewrite would change the target behavior.
- 852 sequence6 clears184 after wave23;855 wave27 leaves184 set.858 sequence34
 uses wave23 then clears184.903 keeps signed sequence<=6, adds double7 to the
 third packet item, and writes scale120=0.5 before scale11C=3.

## Finite experiments and validation

The first complete private source compiled before any tuning. It retained all
129 direct/34 virtual sites and the real tail, but emitted11068 bytes against
11072. Full comparison localized the801 packet/loop,849 predicate and missing
explicit998 metadata. It also showed that all eleven geometry regions already
matched, so no broad geometry execution matrix was introduced.

A local fenv_access trial changed sqrt into an external call and was rejected;
no false-ABI mapping was supplied to force it through. Reordering801's real
packet assignments and adding998 recovered instruction scheduling and metadata.
Reversing the loop comparison then changed the memory-operand shape; float versus
double constant spelling was byte-neutral and not pursued further. Re-reading
the target x87 status test established the actual **inclusive** endpoint. The
selected `n<=3` form, corrected packet and849 negated guards recover the entire
payload. No assembly, copied bytes, padding or inert liveness is used.

Two new generic literal keys pin observed float24 at6C4A90 and float34 at6C4A78:
`__real@41c00000`/`0000c041` and `__real@42080000`/`00000842`. Every existing
binding is preserved. Formal and independent cold full-payload hashes agree.

IDA preflight still fails because the GUI database has SHA10350095..., so it
supplies no semantics or writes. Raw inspection uses the hash-attested PE. One
serial direct read-only/noanalysis Ghidra run uses CPU0/nice10 and384MiB heap.
Disk/import identity, image base/entry, raw-backed mapped bytes and root hash
are independently checked. Temporary bounded root/helper signatures and real980
CALL_RETURN metadata are read back, rolled back and checked; all nine primary
database pins are unchanged. Its decompiler output remains a hypothesis.

Origin-census regeneration also invokes serial VC8 compilation. An initially
overlapping aggregate replay was stopped and its incomplete log retained as
`cold-all-interrupted-overlap.log`; it supplies no aggregate claim. The final
aggregate replay starts afresh after census generation has terminated.
The replay reuses a prewarmed Wine service with null standard streams to avoid
per-unit service shutdown holding captured pipes. Objects/provenance are still
deleted and rebuilt sequentially; no compiler/source/profile setting changes.
The final `taskset -c 0 nice -n 10 python3 scripts/verify-exact-units.py --all`
returns0: **514 cold units/all1402 accepted functions pass**. Receipt:
`build/exact-first-alice-object-entry-20261024/cold-all.log`. The final full
Alice payload audit also returns0,11072/11072, after that aggregate rebuild
(`cold-all-full-audit.json`). Current accepted authored code totals349017 bytes;
the reviewed denominator remains2136806 bytes.
Continue independently reviewed medium/large Object slot3C peers; preserve the
parked nonexact residuals until new evidence justifies reopening them.
