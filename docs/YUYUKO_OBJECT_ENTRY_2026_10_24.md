# YuyukoObject initializer: complete source, nonexact checkpoint

`0x00578000`, YuyukoObject primary slot+3C, now has complete selected source in
`src/characters/YuyukoObjectActionEntry.cpp/.hpp`. Formal and independent cold
objects reproduce the same11139-byte canonical payload against11143. All169
direct calls,26 virtual selectors,29 RET0 exits and the real980 tail remain.
The199 action-remap bytes compare equal. The complete unmasked comparison still
has7299 differing bytes, including shifted code and table destinations; this
checkpoint adds source presence only, with no exact credit.

Selected canonical payload SHA256:
`4cd30e13a075944efd6303622e35207828728e43f4c455e6ef17b9782bedc5e4`.
The emitted callable is10823 bytes versus10828, followed by one NOP and315
metadata bytes. First mismatch+7F (`0x0057807F`, targetC1/sourceBC) is the entry
branch displacement to the later out-of-range exit. Neither the small size
difference nor local instruction agreement establishes whole-function equality.

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-yuyuko-object-entry --compare --json
scripts/repo-python scripts/audit-yuyuko-object-entry.py
taskset -c 0 nice -n 10 bash scripts/compile-unit.sh \
  src/characters/YuyukoObjectActionEntry.cpp \
  build/exact-first-yuyuko-object-entry-20261024/cold.obj
scripts/repo-python scripts/compare-unit-object.py exact-first-yuyuko-object-entry \
  build/exact-first-yuyuko-object-entry-20261024/cold.obj --json
scripts/repo-python scripts/audit-yuyuko-object-entry.py \
  --object build/exact-first-yuyuko-object-entry-20261024/cold.obj
```

Compilation returns0; comparisons return1 for the retained mismatch. The public
payload audit replays every relocation through the complete section tail,
without masks. Formal receipts pin compiler/source/inputs; existing-object
comparison reports unverified build provenance, supplied separately by the
independent cold compilation. Reports remain below the cited build directory.

## Observed target, ownership and complete boundary

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/allocator/vtable evidence classifies this root authored.
Primary vtable `0x006C55C4`, slot cell `0x006C5600`, contains578000. No durable
name or source selection existed before this checkpoint. Authored origin and
denominator are unchanged; `matches.csv` is unchanged.

| Region | Reviewed extent |
| --- | --- |
| Callable | 578000..57AA4B inclusive /10828 bytes |
| Destination table | 57AA4C..57AABF /29 DWORDs |
| Action800..998 remap | 57AAC0..57AB86 /199 BYTEs |
| Following separation | 57AB87..57AB8F /nine INT3 bytes |
| Next independent callable | 57AB90, outside this payload |

Callable SHA256:
`b05dbd0b58eba3dfe417baf15401a45405f60dc5a173763becd62f9e75d29299`.
Complete11143-byte target SHA256:
`5cf0ed1dfe099e8bffaa78ffd2620fd6cae98d370750c04766adcbd90631702d`.
Raw traversal reaches all2718 decoded instructions; no unreachable instruction
is unresolved. The single indirect jump follows the reviewed table/remap. The
only external jump is real980 tail57AA26 ->596370. The root reserves20 local
bytes, saves EBX/ESI and additionally saves EDI for in-range actions. All26
virtual calls use slot0C.27 FTOL calls comprise26 H[2] selectors plus811's
float-loop-index conversion. No root EH region is observed.

| Direct callee | Physical calls | Observed contract |
| --- | ---: | --- |
| 68A1A0 | 27 | Compiler FTOL, implicit x87 input |
| 4067D0 | 91 | Bounded RNG; unsigned conversions at float use sites |
| 435160 | 23 | ECX=this+4, two float arguments, RET8 |
| 4FCA60 | 14 | Parented request, seven four-byte arguments, RET28 |
| 64CCB0 | 6 | Unparented request, seven four-byte arguments, RET28 |
| 4063D0 /406360 | 3 each | Float angle argument, x87 table-value return |
| 496420 | 2 | Low signed-WORD key, float half-width, three ints, RET20 |

All472 selected section relocations are replayed:170 REL32 (169 calls plus
the tail) and302 DIR32 (literals and switch metadata). The local496420 key
view follows49648C's signed-WORD read from its four-byte argument slot. Existing
accepted declarations are unchanged. Nominal helper types remain hypotheses;
declaration-only callees receive no implementation or exact credit.

## Inferred source and independently reviewed family differences

The source retains offsets, numeric states and pointer-only partial receiver
views. Do not construct or embed these as complete recovered owners. Peer
initializers supply patterns only; this root's own instructions establish its
fields, widths, side effects and complete cases.

- The clear prefix writes WORD384 before float37C and WORD386 before float380.
 800 uses a consumed float RNG100 product before subtracting double5, while
 its RNG10 scales keep the product extended before adding double0.5.
- 810/811/816/826/850/853/854/856/857/902 keep two independent RNG100 calls
 that both write370, even though the second store can overwrite the first.
 854 retains two separate sequence5 guards and two complete physical copies.
 Calls can mutate the sequence; these guards cannot be merged speculatively.
- 801 sequence2 copies selfY to F8, rather than input H[1].815 assigns scales
 11C10 then1200.1 separately.820/900 multiply signed BYTE facing by integer50
 before adding parentX, and separately add double170 to parentY.
- 811 sequence14 branches on signed parentBYTE608 at thresholds1/3. Three
 separate float loops visit0..2,0..3 or0..4. Their packets are
 {n*double15-H[0],20,n}, with signed int(n)%4 in the last branch; final WORD36C
 is3/4/5. The first two loops are not one invented shared spawn call.
- **816 sequence12 leaves the second word of its first three-word request
 untouched.** The target writes packet[0]=0 and packet[2]=13 only. Its later
 request sets packet[1]=0.5 and packet[2]=14. Source therefore does not invent
 an initial zero store. This preserves the observed partial initialization;
 the nominal meaning and arbitrary incoming stack residue remain unknown.
- 826 sequence0 emits eight unparented requests and returns immediately.
 Its sequence1..4 guard belongs only to the other path. The first complete
 source incorrectly continued to that guard after the spawn loop; raw review
 and the whole comparison restore the physical return.
- 850/853 increment H[0] by double30 after the first request, write3702, and
 copy fresh H[0] to heading at the end of the case.851/854 sign-extend the
 low WORD of RNG360 into DWORD144.854 draws secondary half-width before its
 separate random division count; two named consumed values preserve that order.
- 852/855 consume a float RNG20 product before adding double1 to374.852 also
 writes the random timer;855 instead writes378200. Both independently draw
 the unsigned sign selector.854 sequence3 uses the inclusive unsigned<=49 test.
- 857 sequence0..3 deliberately requests **action816**. Sequence12 emits six
 first-loop packets {RNG20+H[0]-double10,RNG20+double10,0}, then requests
 {0,lastSpeed,13} at layer-1 and {0,0.5,15} at layer+1. The first addition has
 no consumed float sum before subtracting10. The direct unsigned-to-float
 expression with double H[0] recovers that native expression without the
 first source's extra materialization of the small RNG value.
- 821/858/920 preserve an input pointer across trig calls. Cosine magnitude
 uses the captured pointer, while sine magnitude reloads H.821 uses target X/Y
 without a null guard;858 adds signed WORD36C*integer4 to both headings and
 scales X by signed BYTE facing;920 negates the input heading and saves X/Y.
- **922 sequences0 and1 both assign F10C100.** The target loads100 once and
 retains it on the x87 stack through the guards; sequence1's final FSTP is
 not a zero store. Sequence0 assigns scales0.05; sequence1 assigns3700.4.
 998 writes heading0/rotation12860;980 keeps the real shared tail.

## Finite comparisons and remaining unknowns

The first complete source was compiled and compared before tuning. It retains
all169 direct/26 virtual calls and complete switch metadata. Comparison exposes
816's extra packet initialization,826's missing immediate return, a materialized
857 float operand, and922's retained100. Those independently reviewed corrections
are selected. An if/else with actual374 stores removes the conditional
expression's extra float round trip in854. Capturing854's division count before
the call restores its native grouped argument cleanup.

Two subsequent controls are byte-neutral: read H[0] afresh for the first cosine
argument; use float rather than double for the table-valued trig return views.
Both reproduce the selected canonical SHA exactly. Stop these spelling trials.

The target keeps three pointer copies before821/858/920 trig operands. Source
eliminates them and chooses different scratch registers/call schedules in the
following regions. One internal loop-alignment NOP partly offsets these six
missing copy bytes; the callable is still five bytes shorter. The entire
unmasked payload remains nonexact, not a five-byte exactness claim or proof of
LTCG. An independent equal-instruction alignment checks all210 direct jump
destinations with no incompatible or unresolved edge (`edge-audit.json`);
this diagnostic does not replace the canonical comparison. Original TU
partition, complete owner layout, nominal trig return types
and the source property retaining those pointer copies are unknown. Preserve
this checkpoint and select another complete representative; revisit only with
new independent evidence.

## Scoped native controls and falsifying negative controls

```sh
taskset -c 0 nice -n 10 scripts/repo-python scripts/audit-yuyuko-object-entry-paths.py
```

All8 inputs pass on formal and independent cold objects:4 complete real RETs
and4 first-spawn fragments. Selector, checked tree, frame commit, FTOL, MT and
bounded RNG execute their actual instructions against read-only data fixtures.
There is no injected helper result/return/jump. Candidate code runs in a separate
canonical memory overlay; the target PE on disk is unchanged.

- 852 sequence3 uses actual native rolls100=38,180=0,360=0,20=9,100=0. MT state
 word2400000 tempers to2108212345 for the fourth draw.374 becomes
 -1.9000000953674316, distinguishing the consumed-product rounding in both
 x87 precision modes.922 sequences0/1 complete real RETs and retain F10C100.
- 857 fragments begin at the first real RNG20 instruction after the sequence12
 motion setup and stop at the first genuine64CCB0 entry. H[0]=16777216 and
 real rolls7/0 produce {16777213,10,0} in both precision modes.816 fragments
 begin at FLDZ after motion setup and stop at the first64CCB0 entry. Two
 different seeded second-word residues survive in {0,residue,13}. The source
 entry is mapped by its independently checked physical motion-call ordinal
 and instruction anchor; no target-relative source-offset assumption is made.
 Motion setup, later iterations and the spawn bodies are outside these fragment
 checks. They do not establish whole-game behavioral equivalence.

Four separately compiled complete negative sources are rejected: elide852's
product rounding (2/2); replace922 sequence1's100 with0 (1/2); consume857's
addition in a float temporary (2/2); initialize816's untouched word (2/2).
An expression-only angle spelling did not consume the addition under VC8 and
was not a falsifying control; the actual consumed float sum supplies that check.
`--kind round|retained|angle|packet` isolates each question. Private recipes and
full canonical/native reports remain below.analysis/ and build/.

IDA preflight still rejects GUI SHA10350095..., so it supplies no semantics or
writes. One serial direct read-only/noanalysis Ghidra run uses CPU0/nice10 and
384MiB heap. Disk/import/entry/mapped raw-backed bytes and the complete root
hash are checked. Temporary root/helper signatures and the real-tail CALL_RETURN
override are rolled back and read back; all nine primary database pins remain
unchanged. Decompiler output is retained only as a hypothesis.

The only new generic literal key is float0.05, `__real@3d4ccccd`, bytescdcc4c3d
at6C4668. All existing bindings, accepted headers and compiler settings are
unchanged. A conservative exact-name scan of all514 accepted whole objects and
their explicit manifest bindings finds no affected accepted unit. This addition
is not a new aggregate cold replay; prior locked aggregate exact totals remain
unchanged. Continue the remaining independently reviewed Object slot3C peer.
