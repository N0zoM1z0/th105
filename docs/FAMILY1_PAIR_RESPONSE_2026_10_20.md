# Family1 pair46CA80: complete source review, still nonexact

## Target observations

Only original Japanese TH10.5 v1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The pair resolver is `[46CA80,46CC9E)`,542 bytes/137 instructions, body SHA256
`ea54fb25e5ab2ac5e4b7c2dc17792e6073ef654b22b20a06fce6a9887c1257d6`.
Raw traversal reaches every instruction and accounts for every byte. There
are eight RET8 sites, no switch/alignment island or external jump, one call
to46BCA0 and eight calls to the exact23-byte reset helper46B6C0.

The independently exact dispatcher46DD40 calls it at46DE75 and46DFB7 with
ECX context and two object pointer slots. EBX/ESI/EDI are saved; no local frame
or EH machinery is present. The caller ignores the return register. The
selected void member view explains that contract without uniquely proving the
original C++ return declaration or complete class/TU identity.

The predicate consumes prepared shapes. On a hit, signed16-bit words at
`object->frame_1a8 +10/+12` select32-bit result180 and byte slot184 writes.
Each ordinary slot is its object's unsigned byte1A0 minus one, wrapping to
one byte. These are observed offsets and comparisons; their priority/gameplay
interpretation is inferred. No broader semantic name is assigned to the words.

| Physical RET | Hit condition after the first predicate | Result writes |
| --- | --- | --- |
|46CB05|Left12 nonzero and less than right12|Left4, right8, own slots|
|46CB48|Left12 greater than right12, right12 nonzero|Left8, right4, own slots|
|46CB74|Left12 positive, right12 zero, left12 less than right10|Left4, **left slot from right1A0**, right unchanged|
|46CBB2|Left12 positive, right12 zero, left12 at least right10|Left8, right5, own slots|
|46CC04|Left12 zero, right12 nonzero, right10 nonnegative|Left5, right8, own slots|
|46CC37|Left12 zero and either right12 nonzero/right10 negative, or both12 zero/left10 greater|Right4 and its slot only|
|46CC5F|Both12 zero and left10 less than right10|Left4 and its slot only|
|46CC9B|Equal nonzero12, or both12 zero/equal10|Both4 or both8, own slots|

Every hit path resets extents. Predicate failure also reaches46CC9B, bypassing
all result writes **and the reset**. Eight physical returns do not mean eight
distinct logical outcomes or an unconditional reset on every return.

## Source selection and compiler evidence

`CollisionContext::resolve_group_b_object_clash` in `ObjectResponses.cpp`
was retained, unselected source. Full target review supports its behavior,
including the unusual cross-source slot. It is now mapped/source-present as
`CollisionContext_resolve_group_b_object_clash`; one source comment records
that asymmetry. No shared header, layout, flag or existing binding changes.

The existing probe `cross-v106a-object-responses` now also compares this member
with its real decorated predicate/reset symbols. A fresh formal build still
reports **557 versus542, nonexact**, first strict difference+18/46CA98 in the
entry branch displacement. The source has139 instructions versus target137.
After branch-destination normalization, the large initial path structure is
retained; the later store/register schedule and physical tail sharing differ.
The target shares the right-only response and has a separate left5/right8
return. The source duplicates the right-only response and merges part of the
right8 tail into the common outcome. No prefix/window earns exact credit.

| Fresh control | Complete candidate result |
| --- | --- |
| Retained natural source, pinned SP1 |557; canonical0237b566; nonexact|
| RTM on the same source |Same complete0237b566 payload|
| Right slot before status at the two equal-outcome sites |Same0237b566 payload|
| Both slot-before-status pairs / individual inline outcome helper |571; nonexact|
| Both slot computations before statuses |608; nonexact|
| Chained equal status assignment |581; nonexact|
| Explicit shared outcome value, goto or structured ownership |557; canonical3d02d9e8; nonexact|
| Shared right-only exit, with original equal-outcome ownership |514; nonexact|
| Shared right-only plus other outcome/ordering forms |511/519/591; nonexact|
| Structured shared right-only ownership |487; nonexact|
| Genuine same-context dispatcher/pair definition closure |Pair557/0237b566; dispatcher remains686/686 exact|

One natural two-object outcome helper is outlined by ordinary VC8, creating
an extra call boundary absent from the target; the diagnostic comparator
rejects that unresolved local call. It is not mapped to an invented target.
All controls stay private and unselected. They do not prove a compiler/LTCG
impossibility, original source spelling or an original TU boundary.

Final source SHA256 is
`394303cb54595c26e3b4188fe908ac73764b7bb35ee98551205df2b16d1e282f`.
The complete selected canonical557-byte payload SHA256 is
`0237b566331f3cee99ab8d84485aafd831daf37cc6cb5e05bceecbf66f8731dc`.
The formal producer records compiler/source/object/manifest/input hashes;
the object is40ab7cf6. Its existing accepted147-byte46C9E0 member replays
exact, while the existing164-byte46C930 member retains its+52 narrowing
residual. Adding this comparison does not turn either pending member exact.

## Native execution and counterexample

`scripts/audit-family1-pair-response.py` seeds valid geometry by running the
original46DFF0 parent in the established bounded environment. Pair entries
then execute the real target predicate46BCA0, AABB extent46B3B0 and reset46B6C0;
no predicate/hit/extent/game return is supplied by a callback. Pair code and
resource pages remain read-only; writes are guarded to the arena, stack and
one SEH cell. The pair itself must perform no allocation. The parent seed's
limited node-allocation/free environment is disclosed in the parent audit.
The subsequent parent v2 review initializes the target-pinned source168 bindings
and rejects non-SEH zero-page reads. The same2638 pair cases replay with zero
mismatches under that environment; the refreshed receipt is
`build/collision-tail-20261020/pair-final.json`. Pair codegen remains557/542.

The final2638 cases contain:

- 2401 overlapping combinations of four signed words from
  `[-32768,-2,-1,0,1,2,32767]`;
- 49 separated-box misses;
- 160 focused branch cases with independent source bytes0/1/2/255;
- 28 valid identical-pointer cases with common priorities/source bytes.

Each entry resets the original-parent snapshot and compares all128KiB of arena
state, ordered direct calls, MXCSR, actual RET/ESP, nonvolatile registers and
restored x87/SEH state. Deliberately nonzero result/slot and extent seeds expose
preserved-state paths. The complete result is **0/2638 mismatches**, all137
target and139 source instructions visited, all eight physical returns on each
side visited. This includes46CB74, missing from the preceding dispatcher audit.
The real predicate runs2638 times per side; actual extent/reset routines run
2589 times, while49 predicate misses bypass reset.

A source negative control changes only the cross-source slot to the tempting
left-source expression. It fails **12/219 smoke cases**, with equal call traces
but different left slot184. Thus the new domain detects that semantic error;
instruction coverage alone would not establish this sensitivity.

The matrix uses prepared single, axis-aligned boxes. It does not validate every
oriented/compound predicate path, startup, invalid geometry or arbitrary game
state. Full pair instruction coverage and finite native equality establish
neither universal behavior nor canonical exactness. The audit reports existing
object producer verification as false; fresh formal producer evidence is kept
separately. Smoke219 and full2638 reuse inputs and are not additive coverage.

## Analysis safety and reproduction

IDA preflight still reports the wrong imported executable and supplies no
semantics. Direct Ghidra uses one128MiB/nice10/CPU0 read-only process, re-attests
file/imported SHA, entry, all mapped text, the542-byte root and both exact
inbound calls, then reads back the ECX/two-pointer and full-EAX predicate views.
The first disposable signature attempt fails a return-storage resize; it is
corrected before any decompiler result is used. The successful receipt has no
error, and all nine primary database hashes stay unchanged across both runs.
Accepted raw facts remain durable here/in the ledgers; decompiler output is
only a private hypothesis. No factory adapter or target byte patch is used.

```bash
python3 scripts/build.py --unit cross-v106a-object-responses --compare --json
python3 scripts/audit-family1-pair-response.py \
  build/match-units/CrossV106a_ObjectResponses.obj
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```

The formal mixed probe returns1 for its two disclosed nonexact members; the
accepted147-byte member remains exact. The selected native audit returns0;
the deliberately wrong source audit returns1. Generated reports and receipts
are under `build/family1-pair-20261020/`, with raw facts/starts, final formal
comparison, native-final/negative-final and Ghidra-pair receipts. Private
source trials/recipes remain under `.analysis/family1-pair-20261020/`.
This checkpoint adds source coverage only, **zero exact bytes**. The parent
46DFF0 remains1449/1452 with its separate+559 residual. No cold aggregate
replay or new aggregate percentage is claimed.
