# AyaObject remaining selector conversions and current sequence, 2026-10-02

## Bounded result

This continues [the861 owner/payload checkpoint](AYA_OBJECT_OWNER_RELOADS_AND_FLOAT_PAYLOADS_2026_10_02.md)
on `AyaObject_update_action_state_vslot28 @ 0x0061A290`.
The canonical callable remains `[61A290,61EED2)`,19,522 bytes, SHA-256
`18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`,
in original Japanese1.06a PE
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

**Retained target-supported source:**826 reloads its owner after both stage-
height calls, converts both selector100 payloads as unsigned before floating
subtraction50, and checks the current sequence after those calls/spawn.
903's two selector payloads also use unsigned conversion. Its negative70
literal is float: this recovers the target's DWORD2^32 correction, whereas
the double-literal control emits a QWORD correction. Shared helper declarations,
headers, compiler flags and relocation contracts remain unchanged.

The configured whole-root comparison remains **nonexact at+0x22**,
target0F/candidateE0. Candidate metadata19,476 versus target19,524 narrows
the gap144->48. Section tail19,944 supplies the19,522-byte comparison window,
which includes46 bytes after candidate metadata. Neither size proximity nor
its hash is a body/exact claim. Window SHA-256:
`74cfeeb68664fdf44e4cd295ef255f1082db69285f0c6334d1c19262e9231225`.
Retained LF source SHA-256:
`ae3559bb0751cc155e119e5a16355b566a0824b0776a0a108cee12fbcf8342ed`.
No exact-ledger credit is added.

## Read and conversion observations

**Observed:**826's owner loads are61C0CB,61C163 and61C19A around stage calls
435D60 at61C13E/61C175. The second height comparison uses the owner after
call one; positioning uses the owner after call two. Previous source used
one cached owner. A decoded read-epoch check binds these four coordinate
reads and three loads to the object/target hashes. Actual helper mutation of
the pointer is not established.

After optional spawn64CCB0 at61C24C and the phase counters, target61C2A7
reads object sequence WORD+13E. Previous source used the initial sequence
snapshot, making its sequence-one block unreachable after a sequence-zero
entry even if a called operation changed the sequence. The retained source
restores the current WORD read at candidate61C2C0. A fail-closed decoded
integer-path model starts at the real postspawn PC and checks140 combinations
of mocked sequence, phase and counter values. Target/current agree; previous
candidate differs in26 cases. These are simulated call-boundary mutations,
not evidence that the real helper performs those writes. The check closes
through the sequence guard, frame exit or early-death exit; it does not execute
the whole function or the floating sequence-one tail.

Target `[61C19A,61C21D)` and candidate `[61C1B3,61C236)` agree across131 bytes/
32 instruction forms, translated25 bytes later. Noncall encodings/operands
and translated internal edges agree; both RNG calls retain4067D0 with different
REL32 displacements. This is diagnostic instruction/edge identity, not
canonical byte equality.

**Observed:** all18 target native selector call sites now have their matching
candidate unsigned-FILD correction form: TEST result, FILD32, conditional JGE
around FADD DWORD2^32 at6D6EF8. Earlier candidate lacked it at826/903.
826 calls100 at61C1C0/61C1E3;903 calls40/60 at61EBE9/61EC0B.903 then computes
negative70 minus roll, or roll times the exact widened0.1f at6CD1E0 plus4.
For every actual selector result, including rare inclusive upper100/40/60,
old and restored payload expressions store the same bits under nearest-even
FSTP32. The recovered difference is conversion/type/order evidence rather
than a demonstrated ordinary-value bug. Global x87 control/exception behavior
and whole-root numerical closure remain unknown.

## Negative controls and physical sharing

852's real double converted-facing carrier restores one MOVSX but hoists
FILD before the branch; target duplicates FILD inside the branches. Metadata
19,364 and4/34 owner diagnostics do not justify retention. The extra owner
is802's alignment-sensitive diagnostic, not acceptance. A strict-FP version
still converts before the branch and adds QWORD stores. Its full canonical
comparison stops on unmapped `__real@3d4ccccd`; only its hash-bound unrelocated
COFF conversion order was inspected. No strict profile/literal mapping is
adopted and no strict canonical result is claimed.

A826/861 source-order control moves alpha after Y and reverses scale-add
operands. It does not recover target scheduling; compiler still loads scale
before state. It is not retained. Another control expresses the observed
shared phase/sequence-one edges with ordinary labels, without synthetic
values. It moves the shared tail into861, reduces826 to464 bytes, grows861
to547 and loses800's prior diagnostic. It is also not retained. The target's
physical826 tail ownership remains an original compiler/TU-context question.

| Sequential control |Metadata|826 span|903 span|Diagnostics|
| --- | ---: | ---: | ---: | ---: |
| Fresh previous source |19380|627|1631|3/34|
|826 unsigned payloads |19404|653|1631|3/34|
| Plus826 current owner reads |19464|671|1631|3/34|
| Plus903 unsigned payloads |19488|671|1655|3/34|
| Plus826 current sequence |19476|660|1655|3/34|
|903 float negative70, retained |19476|660|1655|3/34|
| Tail source order, rejected |19468|660|1655|4/34|
| Explicit shared tails, rejected |19228|464|1635|1/34|

Target/current physical spans and instruction counts are826660/155 versus
660/153,8521201/310 versus1206/312,861358/89 versus467/109, and9031697/364
versus1655/363. Raw diagnostics remain entry/800/980,3/34;33 destinations/
zero splits persist. No owner diagnostic is newly accepted.

## Verification and remaining work

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

Final configured reports share prefix `build/aya-payload-and-sequence-final-`.
Private controls/checkers are under `.analysis/aya-facing-lifetime-20261002/`;
objects and source/object/window-hashed `controls-summary.json` are under
`build/aya-facing-lifetime-20261002/`. Existing-object controls lack configured
build provenance; retained source is independently rebuilt through the unit.

Final checks again close4,630 instructions/all19,522 target bytes through
seven switches,124/124 floating guards, two641-value unsignedY paths,
853 select7/current-owner/twelve-role checks,861 read/conversion/range checks,
and450 mocked emission-prefix cases. Prior446-byte/126-instruction pattern
now lies27 bytes later; the194-byte/43-instruction rate/sequence pattern now
lies32 bytes later. Both remain translated diagnostics with fixed external
calls, without same-address canonical equality. RTTI-bound byte-call use remains
verified. IDA still fails target identity and is not used. No new Ghidra
process or aggregate cold replay is required or claimed.

Run mandatory local CI/whitespace gates before commit. Remaining questions
include852 facing conversion/FILD order/scratch homes,826/861 physical tail
sharing and alpha/scale scheduling,903 auxiliary owner sharing/field read
boundaries, other values/lifetimes and original TU/LTCG context. Do not repeat
converted-facing/strict/tail-order/label controls without new independent
evidence. Natural C++ already emits the recovered unsigned conversion forms;
these controls do not establish an assembly requirement.
