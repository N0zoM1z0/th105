# IkuObject action initializer: complete canonical exact source

`0x0063B310`, IkuObject primary slot+3C, now has complete selected source in
`src/characters/IkuObjectActionEntry.cpp/.hpp`. The **first complete source**
reproduces all **6229 callable bytes and6551 emitted bytes**, including alignment,
the complete destination table and action remap. Formal and independent cold
objects give zero unmasked differences, canonical payload SHA256:
`328ac0f108052d93697a8a43cdbca339e6e6b4e452fb0fcdba5d113a1be865b2`.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-iku-object-entry --compare --json
python3 scripts/audit-iku-object-entry.py
```

Both commands return0. The public audit replays every relocation in the whole
emitted section and requires complete length/byte equality, without masks.
It also accepts `--object` for an independent object. Cold validation commands:

```sh
taskset -c 0 nice -n 10 bash scripts/compile-unit.sh \
  src/characters/IkuObjectActionEntry.cpp \
  build/exact-first-iku-object-entry-20261024/cold.obj
python3 scripts/compare-unit-object.py exact-first-iku-object-entry \
  build/exact-first-iku-object-entry-20261024/cold.obj --json
python3 scripts/audit-iku-object-entry.py \
  --object build/exact-first-iku-object-entry-20261024/cold.obj
```

These also return0. The existing-object comparator correctly reports
`build_provenance_verified=false`; the separate cold compile command supplies
its build evidence. Formal build receipts include source/compiler/input hashes.
Generated reports are below `build/exact-first-iku-object-entry-20261024/`.
No compiler profile, accepted source header or existing literal binding changes.

## Observed target identity, ownership and complete boundary

Only original Japanese1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/vtable origin anchors classify this root authored;
primary cell `0x006C64E0` contains63B310. It previously had no durable source
selection or semantic name. This acceptance changes neither the frozen origin
selector nor the authored byte denominator. The existing skip-matching origin
rule now selects30 pending roots/670544 bytes instead of31/676773: Iku moves
to the canonical-exact-authored baseline. The frozen pointer witnesses stay
unchanged; the origin census is regenerated from the same rules.

| Region | Reviewed extent |
| --- | --- |
|Callable|63B310..63CB64 inclusive /6229 bytes|
|Compiler alignment|63CB65..63CB67 /3 bytes, `8d4900`|
|Destination table|63CB68..63CBDF /30 DWORDs|
|Action800..998 remap|63CBE0..63CCA6 /199 BYTEs|
|Following separation|63CCA7..63CCAF /nine INT3 bytes|
|Next independent callable|63CCB0, outside this payload|

Callable SHA256:
`60c81c5592227a87ca5e2e99a8447fcb43739405284ce67ef6ebe86054cce608`.
The complete6551-byte payload hash is given above. Raw CFG traversal accounts
for all1630 decoded instructions, all30 table destinations and every direct
edge. The only external jump is the real tail63CA93 ->596370. There are29 RET0
exits and no EH region. The root reserves16 local bytes and saves ESI/EDI;
in-range actions additionally save EBX. Only815 temporarily saves EBP around
the selector, then releases it before its state branches. The generated source
naturally reproduces this layout; no padding, assembly or dead liveness is used.

| Direct callee | Physical calls | Observed contract |
| --- | ---: | --- |
|68A1A0|25|Compiler FTOL with implicit x87 input|
|4FCA60|19|Parented object request, seven four-byte arguments, RET28|
|496420|2|ECX owner, key/float half-width/three integers, RET20|
|435160|2|ECX=this+4, two float arguments, RET8|
|4067D0|29|cdecl random bound, unsigned conversion at these float use sites|
|64CCB0|5|Unparented object request, seven four-byte arguments, RET28|
|435D60|2|ECX receiver, no stack arguments, x87 stage-height return|

Thus all84 direct calls,25 virtual slot0C calls and the real980 tail are
retained. COFF contains226 root relocations:85 REL32 (84 calls and the tail)
and141 DIR32 (literal/switch metadata). Every one is replayed in the complete
comparison. No callee implementation is imported into the root merely to alter
visibility or code generation.

## Inferred source shape, independently checked family differences

The recent SakuyaObject, YukariObject and KomachiObject sources supply working
patterns only. Iku is reconstructed from its own exact bytes, operand widths,
callee contracts, table mapping and control flow. It matches on the first
complete compile, so no spelling sweep or large behavioral matrix is added.

The source intentionally retains offsets, numeric action/sequence values and
declaration-only helpers. Receiver classes are pointer-only partial call views;
**never instantiate or embed them as a complete recovered owner**. The local
signed-WORD slot0C carrier in a four-byte slot reproduces observed calls without
changing the existing shared selector declaration/implementation. Full nominal
class identity/layout, original source spelling and original TU partition remain
unknown even though the root is exact.

Specific target facts preserved in the source include:

- 899/995 select only when H[2] is ordered-positive. Unlike Yukari's nonzero
 predicate, negative and unordered values skip the selector.995 writes BYTE134
 before its predicate;899 first assigns the input heading.
- 823 reads the parent's **signed BYTE60F** independently at thresholds2 and4,
 selecting BYTE184 values2/3/4 before its two parented requests. Negative skill
 values follow the low branch.
- 802 sequence3 multiplies signed facing by the input float for124; sequence4
 multiplies by the actual double-20 literal. Parent/object-request facing is
 separately zero-extended from BYTE104.
- Real case-local three-float payload arrays retain19 parented and5 unparented
 request sites, including different layer values and zero/actual/stage-height Y
 coordinates. They preserve the shared980 tail instead of keeping a live array
 across every switch arm.
- 859 and920 both emit3/5/6/9 payload variants, but only859 clears DWORD180.
 817 sequence6 uses payload9 at literal Y0, while910 sequence4 uses payload6.
 818 sequence0's parented request uses payload1 and its unparented request uses3.
- Observed float product spill/reload boundaries remain explicit in real consumed
 temporaries. Other formulas, including857's combined random scaling and850
 sequence5, retain their distinct single-rounding forms and actual double
 constants. Applying Komachi's two-stage formula indiscriminately would change
 these bytes.
- 810 and851 write the same scale pair2/0.75, but only810 resets BYTE17C;930
 sequence2 adds double90 to its stored heading and writes scales15/0.

Canonical equality proves these selected instruction/storage/control-flow forms
against this executable; it does not recover higher-level gameplay names or
establish a complete owner layout. Earlier parked nonexact roots remain parked.

## Analysis safety and reproducible evidence

IDA preflight still fails because its GUI database SHA is10350095..., so that
session supplies no semantics or writes. Raw inspection uses only the verified
PE. One serial direct Ghidra run uses CPU0/nice10 and384MiB heap. The disk/import
SHA, image base/entry, raw-backed mapped sections and6229-byte root hash are
independently checked. Temporary bounded root/helper signatures and CALL_RETURN
metadata on the real980 jump are read back and rolled back; all nine primary
database pins compare unchanged. Decompiler output is a hypothesis; it is not
mechanically pasted into source.

A single new generic literal key, `__real@c034000000000000`, pins double-20 to
`0x006C4F88`, bytes `00000000000034c0`. Existing keys remain unchanged. Formal
and independent cold whole-payload reports both reproduce the target hash.
No partial percentages or sampled-equivalence claims substitute for acceptance.

For any published aggregate total, run the required cold sequential replay:

```sh
taskset -c 0 nice -n 10 python3 scripts/verify-exact-units.py --all
```

The complete sequential run passes **513 cold units/all1401 accepted functions**,
with the new Iku root last. Receipt: `build/exact-first-iku-object-entry-20261024/cold-all.log`.
A final full-payload audit of the aggregate-rebuilt Iku object also passes6551/6551
(`cold-all-full-audit.json`). Current accepted authored code totals338302 bytes;
the reviewed denominator remains2136806 bytes.
Continue independently reviewed medium/large Object slot3C peers; Iku's exact
source establishes useful lifetime/rounding patterns, not another owner's
semantics or compiler boundary.
