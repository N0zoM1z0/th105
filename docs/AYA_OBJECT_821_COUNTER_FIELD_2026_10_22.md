# AyaObject821 growth counter field correction

## Observed discrepancy and selected fix

The selected source for root61A290 used WORD36C for action821 sequence0's
angle-growth counter. Fresh target decoding instead establishes WORD364:

| Target instruction | Observation |
| --- | --- |
|61B8BE ADD WORD[ESI+364],BP|Add6 to the16-bit counter|
|61B8C5 MOVZX EAX,WORD[ESI+364]|Read it for signed AX comparison with90|
|61B8D1 MOV WORD[ESI+364],DI|Store90 on the clamp path|
|61B8DE MOVSX EAX,WORD[ESI+364]|Sign-extend the actual sine argument|
|61B8F2 CALL406480|Original integer-angle sine lookup|

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The wrong-image IDA preflight still rejects its session; target bytes
and complete VC8 COFF provide this evidence. The table/owner audit is a
candidate-partition diagnostic, not standalone function acceptance.

Four source references in action821 now use `state_364`. The layout and the
separate WORD36C storage stay unchanged. The shared owner view already declares
both as shorts; no ABI/header/helper/compiler/manifest change is needed.
The earlier quarter-speed motion/callback repairs concerned other paths and
did not establish correctness of this sequence0 counter.

## Actual execution

`scripts/audit-aya-object-821-counter.py` executes from the actual root entry
through original34-byte integer sine406480 and62-byte frame4351C0 to RET.
The orientation table comes from the original initializer4065B0 via
`iku_native_math.lookup_fixture`, SHA256
`c134fa85e7988574c2db386dc8e14de2113d6e465c18f4503bd265219c5ca898`.
No sine values or helper returns are synthesized. The frame fixture stays below
its virtual-dispatch threshold; unknown code/writes fail closed through the
shared native callback guard.

3300 cases independently vary signed WORD364 and WORD36C, covering negative
values,83/84/85 and89/90 clamp boundaries,32761/32762/32767 wrap boundaries,
eight masked x87 precision/rounding settings and seven growth float patterns
including signed zero, finite values, largest finite, infinity and NaN.
Phase5 retirement and phase6 controls are included. Signed-short wrap is
observed under the actual VC8 instructions, not assumed from portable C++.

| Observation | Predecessor differences | Selected differences |
| --- | ---: | ---: |
|Complete compared case|3190|0|
|Final actor memory|3132|0|
|Ordered actor writes|3190|0|
|Actual sine argument|2436|0|

All110 phase5 cases return without sine/frame execution. The other3190 execute
both original helpers. Some predecessor final states coincide after clamping
or float saturation, but its write address is still wrong in every active
case. This is a real field/behavior repair, not only a timing or placement
improvement. Parameters, helper calls, final x87 status/tag, saved registers and
stack cleanup are also checked. The matrix does not prove arbitrary resources,
callbacks, unmasked exceptions or other821 sequences.

## Complete object change and scope

The complete20036-byte canonical payload differs in **exactly four bytes**:

| Root-relative offset | Previous | Selected |
| --- | --- | --- |
|16C5|6C|64|
|16CC|6C|64|
|16D9|6C|64|
|16E8|6C|64|

They are the low displacement bytes in ADD/MOVZX/MOV/MOVSX respectively.
Every other byte, including metadata, is unchanged. The auditor's optional
`--previous-object` reports complete sizes/hashes and these byte deltas.
The strict outside821 normal graph separately agrees on4331 nodes with no
carrier allowance; it assumes normal opaque-call returns. The byte delta also
bounds the change within821 itself, rather than leaving its other paths hidden
behind the action exclusion.

Full canonical SHA256 changes from
`623294c32b653875c56df1232a75948b08525755d3e660d3afdce43ea481902d` to
`158b7e91cf148a91f949d89b5b10261fbfbc807f2dd48a09cf6bfe8c95c376c4`.
Compared19522-byte window SHA256 is now
`f7af00e91cafddc8c85ef9a9f56507caca6a71c0471cb0d1a9bbf951bb9ebe3c`.
Metadata remains19568; the canonical root still fails at offset34/hex22,
target0F/candidate3B. Action821 remains1082 bytes versus target1123; physical
layout, remaining read/scheduling differences and other paths remain pending.
Raw owner diagnostics stay3/34. Exact totals remain1381 functions/234914 bytes;
no new function-level exact credit or aggregate replay is claimed.

## Reproduction

Receipts live under `build/aya-821-counter-20261022/`:
`before.json` records the expected failing predecessor run;
`selected-native.json` binds the differential matrix and complete canonical delta;
`canonical-delta.json` additionally decodes the four changed instructions;
`outside821.json`, `selected-owner.json` and `selected-formal.json` record their
respective scopes. The predecessor object is from8ecffe2's selected source.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-821-counter.py --previous-object build/aya-821-counter-20261022/previous.obj
python3 scripts/audit-aya-object-normal-flow.py build/aya-821-counter-20261022/previous.obj build/match-units/GptWeb_AyaObjectActionState.obj --exclude-action 821
python3 scripts/ci.py
git diff --check
```

The configured comparison still exits1. No accepted unit's code, partition or
relocations changed. Existing selected903 read timing and other source fixes
are preserved byte-for-byte by the full canonical delta.
