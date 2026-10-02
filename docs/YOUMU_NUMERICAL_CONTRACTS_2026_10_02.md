# Youmu actions 606 and 710 numerical contracts, 2026-10-02

This is the checkpoint before [the virtual ABI correction](YOUMU_VIRTUAL_ABI_2026_10_02.md).
Its source observations remain valid; its candidate metrics are historical.

## Current result

`Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains **nonexact** over
all 37,692 callable bytes. The retained ordinary-C++ changes recover unsigned
random-result conversion, signed remainder lowering, ordered angle tests and
the target's arithmetic association. Fresh configured VC8 compilation and
canonical relocation replay still report first mismatch `+0xCA`, target `64`,
candidate `79`. Owner diagnostics remain **24/98**, with no owners gained or
lost. Candidate metadata remains `+0x9354`, versus target `+0x933C`.
No exact functions or bytes are added to the ledgers.

**Evidence:** independently hash-verified raw original Japanese 1.06a PE,
SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
entry point `0x0068B9D2`. IDA preflight still exposes a different image and is
not used. Disassembly starts at the complete root, not arbitrary interior
byte offsets. The auxiliary switch recorded in the preceding action-720
checkpoint still closes all 37,692 bytes / 9,912 reachable instructions.
This work uses no new analysis database, assembly, compiler-profile change,
shared header, relocation target or object partition.

## Action 606: remainder and random-result conversion

**Observed:** `0x537F99..0x537FAC` sign-extends word `self+0x730`, masks
`0x80000001`, then executes the negative correction `DEC / OR -2 / INC`
before testing for a zero result. This is the VC8 signed `% 2` sequence.
The source now expresses `*(__int16 *)(raw + 1840) % 2 == 0`, removing the
decompiler's flag reconstruction and its one-use Boolean. Both expressions
select even values throughout the signed-word domain; this is source-shape
recovery, not a claim that the preceding parity expression changed behavior.
The fresh candidate generates the same signed-remainder operation sequence,
but uses EDX rather than target EAX. Original declarations remain unknown.

Three subsequent `selector_random_roll @ 0x4067D0` calls pass 45, 40 and 100.
At `0x537FB9`, `0x537FFE` and `0x538056`, respectively, the target tests EAX,
stores it for signed `FILD dword`, and conditionally adds **float 2^32** from
`0x6D6EF8` when bit 31 is set. Thus these consumers convert an unsigned
32-bit result, not the retained source's signed `(double)` result. Subsequent
operations are `10 - roll`, `(self.y + 20) - roll`, and
`(roll + self.x) - 50`, with their actual target stores preserved.

The source now uses `(float)(unsigned int)` at these three consumers. The
configured compiler reproduces the target's dword correction operand and
extended-register arithmetic; it does not insert a new float store before
those arithmetic operations. The alternative `(double)(unsigned int)`
probe instead loads qword 2^32 from `0x6D6ED0`, which has the same numerical
value but the wrong target access width and literal address. It is rejected.
These observations constrain the conversion at these consumers; they do not
prove a unique upstream cast spelling, the callee's declared return type, or
the reachability of bit-31 results during gameplay.

Target literal checks also confirm double `10`, `20`, `50` at
`0x6D6EC0`, `0x6C0EF0`, `0x6C3C08`. The later payload expression really
does multiply the signed word by double zero (`0x6CD148`) before adding
double 45 (`0x6C3D48`); that existing expression is preserved.

## Action 710: arithmetic association and ordered range

**Observed:** both eight-iteration loops convert the random result, then
load the loop index and execute this ordered expression:

```text
first loop:  53876C FLD index; 538770 FMUL double 45;
             538776 FADD double 22.5; 53877C FADDP; 53877E FSTP payload
second loop: 5388BD FLD index; 5388C1 FMUL double 45;
             5388C7 FADD double 22.5; 5388CD FADDP; 5388CF FSTP payload
```

The source now groups `roll + (index * 45.0 + 22.5)`, replacing left
association `(roll + index * 45.0) + 22.5`. Both loops preserve their payload
float store. Fresh candidate instructions reproduce the multiply, inner
addition, final `FADDP` and store order. Constants `0x6C3D48` and
`0x6C4638` are verified doubles 45 and 22.5. This recovers the operation
contract; it does not demonstrate an output difference for ordinary bounded
integer rolls and loop indices, where these values are exactly representable.

At `0x5387A2/0x5388F9`, `TEST AH,1 / JNE` rejects negative or unordered
angles. At `0x5387AF/0x538906`, after comparison to float 180
(`0x6D6EDC`), `TEST AH,41h / JP` rejects angles above 180 or unordered.
The falling-through valid arm passes direction +1; the invalid arm passes
-1. Both source predicates now express the inclusive ordered range
`angle >= 0.0 && angle <= 180.0`, with the valid arm first. This preserves
finite-value behavior and restores target NaN rejection. The old
`angle < 0.0 || angle > 180.0` admitted NaN. NaN reachability in these loops
is not established by this local audit.

## Focused comparison and limits

Separate association-only, ordered-range-only, parity-only and conversion-only
private probes isolate these changes. Private objects carry no accepted build
provenance and award no exact credit. Final source is rebuilt through the
configured full-root unit:

```bash
taskset -c 0 python3 scripts/build.py \
  --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
python3 scripts/compare-giant-action-switches.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj --json
```

The formal comparison returns exit 1 for an ordinary mismatch, with no
relocation failure. Target callable hash remains
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`;
final canonical candidate-window hash is
`a134bcc7a8a9e5fd0f1a3f9c3ec1f996f59ad6670e6c18023e12c9e323b20162`.
Action 710 now has equal 882-byte mapped spans, but still differs in
instructions and internal edges; equal size is not acceptance. Action 606
has target/candidate spans 875/883. Remaining differences include its frame
range lowering, register allocation, scratch slots, retained y lifetime and
spawn argument preparation across the third random call. A direct x-argument
probe loses the previously identical action-304 owner and is not retained.
The earlier action-720 signed comparison and switch-arm recovery remain.

These operations are reproducible with natural VC8 C++. The TH08 x87
assembly islands discussed in the preceding common-root note do not establish
an assembly requirement here. Whole-root numerical closure, original types,
TU boundaries and shared-tail ownership remain open. Only this unit is
rebuilt; reported exact totals are unchanged ledger totals, not a cold replay.
