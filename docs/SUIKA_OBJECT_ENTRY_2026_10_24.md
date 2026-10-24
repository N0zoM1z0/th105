# SuikaObject action initializer: complete source, nonexact checkpoint

`0x005BD380`, SuikaObject primary slot+3C, now has complete selected source in
`src/characters/SuikaObjectActionEntry.cpp/.hpp`. Formal and independent cold
objects give the same9268-byte payload against9284. Both full audits retain6664
unmasked differing bytes, including layout-shifted regions and the16-byte length
difference. First mismatch+80 (`0x005BD400`, target70/source5F) is the entry branch
displacement to the later default exit. This is **not exact**; no matches.csv or
authored exact-byte credit is added.

Selected complete canonical SHA256:
`5da268460e86a4d0aa80b26b7cceac0fd93d25c30c91c7a358755c28ad1b2010`.
All153 physical direct calls,29 virtual selector calls,26 RET0 exits and the
real980 tail remain. All200 remap bytes compare equal. Call counts, equal
semantic controls and instruction alignment are diagnostics, not acceptance.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-suika-object-entry --compare --json
python3 scripts/audit-suika-object-entry.py
taskset -c 0 nice -n 10 bash scripts/compile-unit.sh \
  src/characters/SuikaObjectActionEntry.cpp \
  build/exact-first-suika-object-entry-20261024/cold.obj
python3 scripts/compare-unit-object.py exact-first-suika-object-entry \
  build/exact-first-suika-object-entry-20261024/cold.obj --json
python3 scripts/audit-suika-object-entry.py \
  --object build/exact-first-suika-object-entry-20261024/cold.obj
```

Compilation returns0; all four comparisons return1 for the retained mismatch.
The public full audit replays every relocation through the emitted section
tail, including switch metadata; no byte masks are used. The independent-object
comparator reports `build_provenance_verified=false`; its separate cold compile
supplies build evidence. Formal receipts carry source/compiler/input hashes.
Generated reports are below `build/exact-first-suika-object-entry-20261024/`.

## Observed target identity, ownership and complete boundary

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/allocator-owned vtable anchors classify this root authored.
Primary vtable `0x006C5B04`, slot cell `0x006C5B40`, contains5BD380. No durable
name or source selection previously existed. Origin classification, pending-root
selector and the authored denominator remain unchanged.

| Region | Reviewed extent |
| --- | --- |
|Callable|5BD380..5BF67B inclusive /8956 bytes|
|Internal unreachable loop alignment|5BEEBD..5BEEBF /`8d4900`|
|Destination table|5BF67C..5BF6FB /32 DWORDs|
|Action800..999 remap|5BF6FC..5BF7C3 /200 BYTEs|
|Following separation|5BF7C4..5BF7CF /twelve INT3 bytes|
|Next independent callable|5BF7D0, outside this payload|

Callable SHA256:
`c68b34de61716fde71beec5b827285501cbdf4086dce5abc88a794b7559c529f`.
Complete9284-byte payload SHA256:
`9c143cb673cd84d287096bb3cc4e653bfb0796ff1bdc7402219d19d5bc079de1`.
Raw traversal closes2266 reachable instructions and the one isolated internal
alignment instruction,2267 decoded instructions total. Every destination/edge
is accounted for; the only external jump is5BF4F8 ->596370. The root reserves20
local bytes, saves ESI/EDI and additionally saves EBX/EBP in range. The native
loop entry jumps over the alignment; it is not treated as executable behavior.
No final alignment separates the target callable and destination table.

| Direct callee | Physical calls | Observed contract |
| --- | ---: | --- |
|68A1A0|29|Compiler FTOL, implicit x87 input|
|435160|20|ECX=this+4, two float arguments, RET8|
|4067D0|94|cdecl random bound; unsigned conversion at float use sites|
|64CCB0|6|Unparented object request, seven four-byte arguments, RET28|
|4063D0 /406360|2 /2|Quantized cosine/sine, one float argument|

The selected COFF section contains402 relocations:154 REL32 (153 calls plus
the real980 jump) and248 DIR32 (literals and switch metadata). All are replayed
in both complete audits. The destination entries relocate with code layout;
the200 action-index bytes are independently equal despite the length difference.

## Inferred source and independently checked family differences

Recent exact Iku and parked Tenshi initializer sources provide hypotheses only.
This function's own bytes establish each case, width, read epoch and helper call.
Offsets/numeric states/declaration-only helpers are intentionally retained.
The receiver is a partial pointer-only call view; never construct or embed it
as the complete owner. The local slot0C signed-WORD carrier occupies a four-byte
argument slot without changing the shared selector implementation/header.

Distinct target facts retained in the source include:

- Prefix zeros put float37C before WORD384 and float380 before WORD386. This
 order differs from Tenshi's prefix.998 uses that live zero to set heading0
 and float128=60 without calling the selector.
- 810/815/921/940 execute motion before selecting H[2]. Several other cases
 select before movement. Parent/optional object+34C is reloaded independently
 of the captured input pointer during815/940 sequence10 trigonometric placement.
- 811/816 compare actual horizontal floatF4 after motion; only ordered F4>0
 selects -0.15, otherwise+0.15.812 instead compares its directly assigned
 **vertical** floatF8: ordered-positive gives-0.1, including zero/negative/NaN
 in the+0.1 arm. Do not infer the compared axis from the store destination370.
- 810 sequences1/5,855 sequence6 and921 sequence1 use real float loops0..<4,
 step double1. Payloads are {RNG360,RNG8+double4,3/8/3}; the three loop calls
 request810/855/921 at layer+1.821/857/910 have separate {0,0,1} layer-1 sites;
 only857 accepts both sequence0 and9 for that request.
- 815/940 sequences4 and5 each keep a distinct physical RNG100/360/10 group.
 Their first product is rounded to float before subtracting5, while the last
 product remains extended until adding H[3]. Four real consumed double delta
 captures express the latter lifetime and reproduce the observed memory FADD.
- 817/821/850/853/856 and related branches retain their distinct rounded-product
 forms. Other expressions, including855/1 and930/1, have no intermediate float
 product spill. Constants0.8/0.85/0.9 use double(float literal) values where
 the actual target literal requires them, rather than exact decimal doubles.
- 855 sequence1 negates float370 using double-1 when unsigned RNG100<=50,
 then stores WORD364=RNG35+45 before motion. Sequence3 marks BYTE184, sequence5
 moves without marking it; these are separate native calls.
- 821/910 sequences5/8 set370/374=0.2/0.4;857 also includes sequence10.
 Their sequence8 also passes the earlier random-scale arm. These independent
 checks must not become mutually exclusive branches.
- 940 uses signed WORD13E<=2, including negative values, for BYTE184.
 Sequence10 resets both velocities, computes RNG15*double(float0.1)+0.5 and
 optionally places around+34C. Sequence14 uses370=0.55/scales0.1 and marks184;
 sequence16 uses370=0.4/scales0.1 and clears113;17 only sets scale11C=2 and184;
18 sets both scales0.1.900/901 and999 retain separate native RNG sites.

## Finite experiments and residual

| Trial | Complete payload / result |
| --- | --- |
|00: first complete source|9320 vs9284, first+80, SHAa4b8bbd8...|
|01:reverse four H[3]/product addition expressions|Byte-identical to00|
|02:four real consumed double product captures|9268, selected SHA5da26846...; all four arithmetic forms recovered|
|03:first cosine uses H[0] instead of captured input[0]|Byte-identical to02|
|04:local float-return trig hypothesis|Byte-identical to02; keep supported double view|

The first complete body already retains all physical call sites. Trial02 fixes
an expression-lifetime/code-generation question, not a previously omitted path.
Both subsequent controls are byte-neutral, so park the residual. The native
copies5BDC37 `mov ecx,edi` and5BF419 `mov edx,edi` are absent from the standalone
object. Further differences include pointer-register rotations, the921 loop's
entry jump/alignment,999 selector scheduling and final layout/alignment. An
instruction-token alignment can locate those regions but is not an exact score;
the6664 unmasked bytes include shifted code. No LTCG necessity is proven.
Full owner layout, original source spelling/TU and the scheduling cause remain
unknown. No assembly, inert locals, false ABI, fabricated returns or padding
are introduced. Reopen only with new independent evidence.

## Twelve focused native RET controls

```sh
taskset -c 0 nice -n 10 python3 scripts/audit-suika-object-entry-paths.py
taskset -c 0 nice -n 10 python3 scripts/audit-suika-object-entry-paths.py \
  --object build/exact-first-suika-object-entry-20261024/cold.obj
```

Both return0:12 actual RET0 paths, stack delta4, zero mismatches. Vector SHA256:
`f37c89d5b983e8522d86635a4cbb79d6126d30240cc0d7a8f33133646e27ff55`.
Four inputs exercise812/0 with H[1]=+1/-1/0/quiet NaN. Eight exercise815/940
sequences4/5 under x87 control words027F and037F. The actual native RNG returns
100->9,360->1,10->3 from bounded deterministic MT **data** fixtures; the RNG RET
hook independently observes each bound/result. H[3]=float(-0.3) makes the final
scale exactly-2**-27 (bitsB2000000):3*double(float0.1)+float(-0.3). A rounded float
product would instead cancel to zero. Both scale fields are asserted against
the target, not just compared between implementations.

The harness uses the original vtable, checked action-map node,14 linked valid
untextured sequences/frames, native selector/map/frame application/commit,
motion, MT and RNG instructions. No helper/vtable patch, injected result or
synthetic return is used. Full actor bytes, call traces, RNG returns/index and
x87 environment agree through real RETs. Original control word/top0 are checked.
Other actions, object-request bodies and later gameplay are outside this scope.

Changing only the four double captures to float fails exactly8 arithmetic
inputs. Changing only812's predicate to `!(F8<=0)` fails exactly the NaN input.
Receipts: `native-paths.json`, `cold-native-paths.json`,
`negative-float-delta-paths.json`, `negative-unordered-sign-paths.json`.
These resolve concrete precision/ordered-comparison questions without a broad
behavior matrix. They add no canonical exact credit.

## Analysis safety and tracking

IDA preflight rejects GUI database SHA10350095...; it supplies no semantics or
writes. Raw packets use the attested PE. One serial direct Ghidra run uses
CPU0/nice10,384MiB heap, read-only/noanalysis. Disk/import SHA, entry/base,
raw-backed mapped sections and root hash are independently checked. Temporary
bounded root/helper views and CALL_RETURN metadata on the980 jump are read back
and rolled back; all nine primary DB pins remain unchanged. Decompiler output
is a hypothesis and is not mechanically pasted as source. The shared-callee
ranking is refreshed before this root; it confers no implementation credit.

Two new generic literal keys pin observed negatives: `__real@be19999a` to
6C5CA0/9a9919be (-0.15f), and `__real@bdcccccd` to6C4278/cdccccbd (-0.1f).
Existing bindings, accepted headers and compiler flags are untouched. Exact
totals remain unchanged; the earlier Iku aggregate cold receipt is historical,
not a fresh all-unit replay after this source-only addition. Continue another
independently reviewed complete representative; keep finite residuals parked.
