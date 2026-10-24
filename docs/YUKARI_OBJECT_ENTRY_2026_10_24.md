# YukariObject action initializer: complete source, nonexact

`0x005964C0`, YukariObject primary slot+3C, now has complete selected source in
`src/characters/YukariObjectActionEntry.cpp/.hpp`. The pointer-only receiver
views must never be constructed or embedded. Numeric states, offset accesses
and declaration-only helpers deliberately precede readability work.

## Complete comparison and stop condition

Formal and independent cold VC8 builds emit **7888 bytes against7920 target**,
canonical SHA256
`5c4f9128b0d689dbf915d4cae7653f3edbc4257d99f3e777ef792766a5c0d596`.
First mismatch is **+0x80 /0x00596540**, target18/sourceF8, a downstream branch
displacement. Strict complete comparison reports4178 unmasked differing bytes,
including the shifted layout. Neither this count nor the32-byte size difference
is an unreconstructed-byte count. No exact record or byte credit is added.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-yukari-object-entry --compare --json
python3 scripts/audit-yukari-object-entry.py
taskset -c 0 nice -n 10 python3 scripts/audit-yukari-object-entry-paths.py
```

The first two commands return1 for the recorded mismatch; the last returns0
for eleven scoped inputs. Both audits accept `--object`. A separate cold object
is reproducible with `scripts/compile-unit.sh` using the selected source and a
new path below `build/`. The full audit replays every relocation in the emitted
section and requires equality of complete length and bytes, including tables;
there are no masks. Generated receipts live under
`build/exact-first-yukari-object-entry-20261024/`.

The first complete source retains all92 direct calls,28 virtual calls and the
real596370 tail. It also retains all33 destination entries and the entire
200-byte action remap; that remap independently compares equal. Destination
addresses differ with the code layout. Target has29 RET0 instructions; source
has28 because VC8 folds the851/854 suffix. Other instruction-form differences
are an EBP pop placement in825 and the loop's alignment-register spelling.
Instruction-token alignment is diagnostic only and earns no exact credit.

| Trial | Evidence-backed question | Whole-payload result |
| --- | --- | --- |
|00|Complete independently reviewed numeric/offset body, case-scoped payloads|7888, SHA above|
|01|Do explicit returns within the851/854 state0 arms retain both target exits?|Identical to00|
|02|Does a nested state switch retain those independent target exits?|Identical to00|

Two byte-neutral controls close this source-spelling question. Keep00 and
park the suffix/epilogue residual. Do not repeat these trials without new
independent evidence. Original TU/LTCG context remains unknown; this does not
prove LTCG is necessary. Select another complete representative next.

## Observed target, boundary and ABI

Only original Japanese1.06a executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The existing RTTI/vtable origin anchor identifies this root as authored;
primary vtable cell `0x006C5880` contains5964C0. It previously had no durable
name or selected source. No frozen origin selector or authored denominator is
changed by this source selection.

| Region | Reviewed extent |
| --- | --- |
|Callable|5964C0..598263 inclusive /7588 bytes|
|Destination table|598264..5982E7 /33 DWORDs|
|Action remap800..999|5982E8..5983AF /200 BYTEs|
|Next entry|5983B0; independent callable, outside this payload|

Callable SHA256:
`ef5c5200ffc4e88cc62cf70b49723216847d4ac2e6c6ce01c31decebe8d65c4b`.
Complete7920-byte payload SHA256:
`fb73594060287afb176b96a75a0a95832f6986ed9deb7afd8e5112f8896c7352`.
Raw CFG traversal reaches all1826 decoded instructions, including the loop's
fall-through six-byte LEA at597D6A. All table edges land on decoded boundaries;
the only external tail is59816D ->596370. There is no EH region or fabricated
padding. The root reserves16 local bytes and saves ESI/EDI and, for in-range
actions, EBX/EBP; the out-of-range exit does not pop unsaved registers.

| Direct callee | Physical calls | Observed call contract |
| --- | ---: | --- |
|68A1A0|28|Compiler FTOL helper with implicit x87 input|
|45CD70|19|ECX owner, signed WORD resource in one stack slot, RET4|
|435D60|2|ECX receiver, no stack arguments, x87 height return|
|4351A0|2|ECX=this+4, two integer stack arguments, RET8|
|4063D0 /406360|1 each|cdecl float phase, x87 cosine/sine result|
|64CCB0|7|Unparented object request, seven four-byte stack arguments|
|4067D0|22|cdecl random limit; unsigned conversion at these use sites|
|4FCA60|4|Parented object request, seven four-byte stack arguments|
|435160|6|ECX=this+4, two float stack arguments, RET8|

Sequence calls use primary virtual slot0C. The local signed-WORD carrier in a
four-byte slot reproduces the observed pushes; no existing helper declaration
or implementation is changed. Signed facing arithmetic reads BYTE+104 with
MOVSX, while object-request facing uses MOVZX. Auxiliary writes repeatedly
reload owner+154, preserving both width and load epoch. In899 state0 the final
facing byte comes from parent+104;825 state1/2 uses this+104 instead. The
parent-owned and local auxiliary paths must remain distinct.

## Inferences and scoped native controls

SakuyaObject was used as a family reference, not copied as target evidence.
Yukari's early states select unconditionally, and850..855 select when H[2]
is **nonzero**, including negative and unordered inputs. A positive-only guard
would incorrectly skip negative values and NaN. Chained scale stores preserve
actual float rounding; random arithmetic retains target double constants and
unsigned-to-float correction widths. Real three-float payload arrays are
case-scoped, allowing the observed shared980 tail. No inert liveness controls,
assembly, copied instruction bytes or fake returns are used.

The native audit executes eleven specific inputs, eight real RETs and three
prefixes ending at the real virtual selector entry. Native FTOL executes; the
selector body and later gameplay are outside those prefixes. Target memory is
mapped from the attested PE, candidate code is canonicalized from COFF, and
neither helpers nor their results are stubbed. The audit checks receiver state,
meaningful argument slots, return cleanup and x87 control/top/tags. Scratch
stack/register allocation is outside its semantic scope.

| Question | Inputs | Target observation |
| --- | --- | --- |
|850 nonzero guard|+0,-0,+1,-1,qNaN|Both zeroes return; other three reach actual slot0C callee|
|851/854 suffix folding|state0 and state1 for each|State0 has scale0/3 and370=1; only854 sets184=1|
|998 facing signedness|BYTE1 andFF|124=-30/+30 respectively,128=65|

All11 agree. Vector SHA256:
`2ea61476ac83886ff5c80663ac77e0ca942b5882d93ba4bf8305506f4abfd21d`.
A private positive-only guard negative control fails2/11 (negative andNaN),
canonical SHA `63c09e6bde237608e882e43fb29f2a651f84e89104bbd980ff983ab9a67ac306`.
An unsigned998-facing negative control fails1/11 (FF), SHA
`e885fe87fe9d0cc26892ecda49f5a3be992d971da8a731af39ef5c4b37d12519`.
These controls resolve those exact ambiguities, not whole-function equivalence.

## Analysis safety and durable state

IDA preflight fails on GUI SHA10350095..., so that session supplies no semantic
or write evidence. One serial direct Ghidra process uses384MiB heap and CPU0/
nice10. Its file/import identity, image base/entry, raw-backed sections and
root SHA are independently attested. Temporary bounded root/helper views and
CALL_RETURN metadata for the real980 jump are rolled back. All nine pinned
primary database files compare unchanged before/after. The decompiler output
is only a hypothesis: its custom height-return view incorrectly exposes EAX,
so the actual x87 return is recovered from raw instructions and the existing
height implementation, rather than that decompiler type.

Durable changes are source/header, source-selection/name/function ledgers,
one focused unit, four new independently pinned literal keys (18,-230,-250,
and double-10), two public audits and this evidence/handoff. Existing literal
bindings, accepted source headers/compiler flags and exact ledger stay unchanged.
Unknowns remain original source spelling, complete owner layout, original
partition/link context and the cause of the retained suffix/epilogue schedule.
