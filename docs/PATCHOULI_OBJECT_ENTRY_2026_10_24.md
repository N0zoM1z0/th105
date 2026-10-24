# PatchouliObject initializer: complete source, nonexact checkpoint

`0x0052D200`, PatchouliObject primary slot+3C, now has complete selected source
in `src/characters/PatchouliObjectActionEntry.cpp/.hpp`. Formal and independent
cold objects reproduce the same11180-byte payload against11180, but retain3127
unmasked differing bytes, including shifted code and table destinations. First
mismatch+7F (`0x0052D27F`, targetC4/sourceC2) is the entry branch displacement
to the later out-of-range exit. This checkpoint adds source presence only.

Complete selected canonical SHA256:
`1325807290b13f5d9a2c7dcf044e76b9349bbc511a37e690d8b35443028c6325`.
All164 direct calls,27 virtual selectors,32 RET0 exits and the real980 tail
remain. All199 action-remap bytes compare equal. The emitted callable is10829
bytes versus10831, followed by three alignment bytes instead of one. Equal
payload length and local diagnostics do not establish canonical equality.

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-patchouli-object-entry --compare --json
scripts/repo-python scripts/audit-patchouli-object-entry.py
taskset -c 0 nice -n 10 bash scripts/compile-unit.sh \
  src/characters/PatchouliObjectActionEntry.cpp \
  build/exact-first-patchouli-object-entry-20261024/cold.obj
scripts/repo-python scripts/compare-unit-object.py exact-first-patchouli-object-entry \
  build/exact-first-patchouli-object-entry-20261024/cold.obj --json
scripts/repo-python scripts/audit-patchouli-object-entry.py \
  --object build/exact-first-patchouli-object-entry-20261024/cold.obj
```

Compilation returns0; comparisons return1 for the retained mismatch. The public
payload audit replays every relocation through the complete section tail,
without masks. Existing-object comparison reports build provenance unverified;
the separate cold compilation supplies build evidence. Formal receipts include
source/compiler/input hashes. Generated reports are below
`build/exact-first-patchouli-object-entry-20261024/`.

## Observed target identity, ownership and boundary

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/allocator-owned vtable witnesses classify the root authored.
Primary vtable `0x006C4E24`, slot cell `0x006C4E60`, contains52D200. There was no
previous durable name or source selection. Origin rule, authored denominator
and exact ledgers remain unchanged because this root remains nonexact.

| Region | Reviewed extent |
| --- | --- |
| Callable | 52D200..52FC4E inclusive /10831 bytes |
| First alignment | 52FC4F /one NOP |
| Primary destination table | 52FC50..52FCD3 /33 DWORDs |
| Action800..998 remap | 52FCD4..52FD9A /199 BYTEs |
| Second alignment | 52FD9B /one NOP |
| Nested match-identifier table | 52FD9C..52FDAB /4 DWORDs |
| Following separation | 52FDAC..52FDAF /four INT3 bytes |
| Next independent callable | 52FDB0, outside this payload |

Callable SHA256:
`2fc0a96ed27ddab4244b58ca34c0e5c50b516e316ab21f6a441b8b20321a0c4b`.
Complete11180-byte target SHA256:
`67ced657b52e6f61667e3621fab7a715b8c8263db759167e8848602ffeb5bccc`.
The complete traversal reaches all2671 decoded instructions, including internal
loop alignment; no unreachable instruction is left unresolved. Both indirect
jumps follow independently reviewed tables. The only external jump is the real
980 tail52FC29 ->596370. The root reserves24 local bytes, saves EBX/ESI and
additionally saves EDI for in-range actions. All27 virtual calls use slot0C;
27 FTOL sites convert H[2]. No root EH region is observed.

| Direct callee | Physical calls | Observed contract |
| --- | ---: | --- |
| 68A1A0 | 27 | Compiler FTOL, implicit x87 input |
| 4067D0 | 87 | Bounded RNG, unsigned conversions at float use sites |
| 435160 | 26 | ECX=this+4, two float arguments, RET8 |
| 64CCB0 | 6 | Unparented request, seven four-byte arguments, RET28 |
| 45CD70 | 6 | Signed-WORD auxiliary key, four-byte argument slot |
| 435D60 | 3 | ECX owner, no stack arguments, float in ST0 |
| 4FCA60 | 6 | Parented request, seven four-byte arguments, RET28 |
| 4063D0 /406360 | 1 each | Float angle argument, x87 table-value return |
| 496420 | 1 | Low signed-WORD key, float half-width, three ints, RET20 |

The selected section contains455 relocations:165 REL32 (164 calls and the tail)
and290 DIR32 (literals, global and switch metadata). All are replayed. The local
secondary-key declaration uses a signed short because49648C reads only that
WORD from its four-byte argument slot and sign-extends it before lookup. Existing
accepted int-view declarations are unchanged; original nominal spelling remains
unknown. Declaration-only helpers receive no source/exact credit.

## Inferred source, independently checked family differences

The source keeps offsets, numeric states and pointer-only partial receiver
views. Never instantiate/embed those views as a complete recovered owner. The
recent Object initializers supply patterns only; every case is checked against
Patchouli's own instructions, widths, calls and edges.

- The prefix clears WORD384 before float37C and WORD386 before float380.
 800/801 retain consumed float product round trips before adding double1.
 Other formulas, including810/815/816, retain their distinct unrounded products.
- 815/827/830 create auxiliary990 and publish its X/Y/facing separately. The
 stage-height call returns in ST0; it must precede the destination-pointer reload.
 822 instead assigns auxiliary Y0.831 uses Y+320/Y+480 and auxiliary scales2/3.
- 830/831 loop packets preserve **integer RNG40-minus20 before unsigned float
 conversion**, then add float-index times double60. They are not signed angles
 in the ordinary -20..19 range. Each float loop visits0..5.830 emits four words
 {angle,15,3,0};831 emits three {angle,15,1}, with its own Y offsets.
- 826 reads signed parentBYTE60C at thresholds2/4, choosing184 values3/4/5,
 then sends the stored heading rather than re-reading H[0].825 stores separate
 X/Y offsets from the parent; its sequence0 packet is {H[0],40,2}.
- 848 sequence7 tests ordered H[1]==1.853 sequence4 independently tests ordered
 H[1]==0 and ==1, with different RNG bounds and378 values2/-4. A nonzero or
 negated-equality rewrite would change NaN/fractional-input side effects.
- 854 sequence4 retains a captured input pointer across both trig calls. X uses
 signed BYTE facing; Y uses double(float0.2), not the facing factor. Its requests
 use zero-extended BYTE33C as layer, including255. Sequence9 independently
 converts H[1] to four color bytes, then copies H[3] to scales and writes124=75.
- 855 uses signed sequence<=4 and signed inclusive5..9/15..19 guards.857 chooses
 key992/993 through a16-bit boolean addition and preserves the full five-argument
 secondary call.900 uses match0/1/2/3 timers60/75/85/90; out-of-range identifiers
 keep the cleared timer.910 has its own complete physical copy of856's body.
- 890 sets WORD344 without selecting;998 writes heading0 and rotation128=60.
 980 retains the real shared tail instead of a fabricated return or helper body.

## Finite experiments and remaining residual

The first complete source was compiled before tuning. It already retained all
164 direct/27 virtual calls, both tables and the real tail. Whole comparison
localized three unsigned-conversion constant widths,857's extra key extension,
and854's pointer/register and byte-conversion scheduling.

Explicit float conversion after the unsigned integer subtraction restores the
three native DWORD2^32 adjustments instead of QWORD adjustments. Independent
callee inspection supports the local signed-WORD key view and removes857's
extra zero-extension. These changes produce the selected complete payload.
A fresh H[0] pointer-read spelling and a float-return view for the two table
lookups then produce identical bytes to the selected source. Both are unselected;
stop the spelling search and preserve this checkpoint.

The target retains `mov ecx,edi; fld [ecx]` before854's cosine argument where
source directly loads `[edi]`. Later register choices, color-conversion schedule
and855's input-pointer register also differ. The source body ends two bytes
earlier and uses longer final alignment. The whole unmasked comparison remains
3127 differing bytes; this is not a two-byte exactness claim or an LTCG proof.
Nominal trig return types, complete owner/input types, original TU partition and
the source property retaining the extra pointer copy remain unknown.

## Scoped native controls and negative controls

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-patchouli-object-entry-paths.py
```

All8 inputs pass, also on the independent cold object:6 complete real RETs and
2 first-spawn loop fragments. The original selector, checked tree, frame commit,
FTOL, MT and bounded RNG execute against read-only resource data fixtures. No
helper return/result or jump is injected. The source runs as a separate canonical
memory overlay; the target executable on disk is unchanged.

800 sequence1 executes real roll(50)=19 from MT state word32904, verifying the
rounded-product scale1.190000057220459 in both x87 precision modes.853 sequence4
uses H[1] bits for0,1,0.5 and quiet NaN, verifying ordered selection and actual
RNG consumption.830 fragments begin at52DFD1 with real first-iteration register/
stack/packet inputs and stop at the first genuine64CCB0 entry. Real roll(40)=0
from state word1 yields packet {4294967296,15,3,0} in both precision modes.
The auxiliary prefix, later loop iterations and spawn body are outside this
fragment scope; these inputs are not whole-game behavioral equivalence proof.

Three separately compiled complete negative sources are rejected: eliding800's
product rounding fails2/2; substituting H[1]!=1 for the first853 equality fails2/4;
converting before subtracting20 in the loop fails2/2. Each full canonical mismatch
is retained. `--kind round|guard|loop` restricts the public auditor to that
specific ambiguity. Recipes/reports remain private under.analysis/ and build/.

IDA still fails preflight with GUI SHA10350095..., so it supplies no semantics
or writes. Two serial direct read-only/noanalysis Ghidra runs use CPU0/nice10
and384MiB heap. Identity, entry, mapped raw-backed bytes and the bounded root
hash are independently checked. The second corrects a temporary stage-height
return view from EAX to the observed ST0, with storage readback. Temporary root/
helper signatures and CALL_RETURN tail metadata are rolled back and read back;
all nine primary database pins remain unchanged. Decompiler text is a hypothesis.

Two new generic keys pin float0.7 at6C3CD8 and float1.75 at6C4FB8:
`__real@3f333333`/`3333333f` and `__real@3fe00000`/`0000e03f`. Existing bindings,
accepted headers and compiler profiles are unchanged. A conservative exact-name
scan of all514 accepted objects plus their explicit manifest bindings finds no
affected accepted unit (`relocation-impact.json`); the comparator rejects unknown
literal keys rather than implicitly resolving them. Exact totals stay at the
previous locked aggregate checkpoint; this addition is not a new aggregate cold
replay. Continue another complete Object slot3C peer and reopen this residual
only with new independent evidence.
