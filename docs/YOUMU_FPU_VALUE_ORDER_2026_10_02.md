# Youmu floating value order and integer operands, 2026-10-02

## Retained result

**Observed:** `Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains
nonexact over all 37,692 callable bytes. Ordinary C++ now expresses three
additional target properties: action 603's addition grouping, action 696's
float rounding before comparison, and action 526's integer subtraction operands.

Fresh configured comparison first differs at `+0xCA / 0x005302CA`, target
`64`, candidate `DC`. Candidate metadata starts at `+0x92B4`, target
`+0x933C`; its section tail is 38,680 bytes. Diagnostic instruction/edge
identity remains **26/98**, with no gains or losses. There are still 97
physical destinations / 33 low entries without merging target-distinct
owners. No exact function or byte credit is added.

Target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source SHA-256:
`c72808f340547e1834214ec9177e9ba1a4a63c14545c416eb830d7551ef0d24b`.
Canonical compared candidate-window SHA-256:
`a69ef39daed6a812a2087aee84c5018f4cfb0883dee0c99d25a443dcc3718c40`.
The compared window includes candidate metadata; it is not a callable body hash.

## Three instruction-supported source properties

**Observed, action 603:** after the sine call and multiplication, target
`5376ED FLD peerY; 5376F3 FADD double100; 5376F9 FADDP ST(1)` computes
`sine*200 + (peerY+100)`, then stores a qword at `5376FB`. The second
expression similarly has `5377EA FLD peerY; 5377F0 FADD double100;
5377F6 FADDP ST(1)` after multiplication by 250, then a dword store at
`5377F8`. The old source grouped both as `(sineScale+peerY)+100`.

**Inferred source:** parentheses now preserve the observed dependencies.
The final candidate emits the two FADDPs at `53764F` and `537753`, followed
by qword/dword stores at `537651` / `537755`. This correction is local to
these two expressions; action 214's distinct observed addition order remains.
Original source spelling is not uniquely recovered, and no gameplay-value
change is claimed for ordinary inputs.

**Observed, action 696:** `53860C JMP 533966` enters action 311's shared
threshold/decrement path, preserving flags. Its arithmetic is
`53396C FLD velocityX; 533972 FSUB double2; 533978 FSTP dword[ESP+10];
53397C FLD dword[ESP+10]; 533980 JMP 532C70`, which reaches the common
field store/sign clamp. The old candidate retained the subtraction's
unrounded x87 value for the comparison.

**Inferred source:** assigning the decrement through the existing real
float carrier `v305`, then through `v58`, preserves this dword rounding.
The final candidate has `538579 FLD; 53857F FSUB; 538585 FSTP dword;
538589 FLD dword; 53858D JMP 532BD3`. Its arithmetic remains physically
duplicated rather than shared with action 311. This is a value-flow recovery,
not proof of original local identity or shared source labels. A float cast
probe emits the same compared window as the float-carrier probe.

**Observed, action 526:** the target uses signed facing-byte products as
integer subtraction operands: `535937 FISUB` for factor 5, `53599D FISUB`
and `535A0F FISUB` for factor 25. MOVSX and 32-bit integer arithmetic
produce these operands before the subtraction.

**Inferred source:** removing only the three explicit double conversions
allows ordinary float-minus-integer expressions to emit all three FISUBs.
The products range from -640 to 635, or -3200 to 3175, and are exactly
representable as float. The nearby addition expression and all helper ABIs
remain unchanged. Original cast spelling is not uniquely established.

## Comparison coverage and remaining leads

The raw target contains exactly **138 floating comparisons**: 69 FCOM,
55 FCOMP and 14 FCOMPP, with 138 FNSTSW instructions. The existing masked
guard scanner's comparison-address set covers all 138. The candidate has
63 FCOM, 59 FCOMP and 16 FCOMPP, also 138 FNSTSW. Owner comparison counts
agree, and there are zero unordered-only leads under the scanner's ordinal
pairing and finite-equivalence hypotheses. This establishes instruction
coverage, not operand identity, rounding or exception closure. The two CL
masks remain independently proved as 5 by modeled predecessor definitions.

The normalized arithmetic census counts 349 target operations / 348
candidate operations. Its baseline five owner leads reduce to three after
these changes: actions 601 and 710 have target branch-duplicated additions
versus candidate hoisting, and action 696 has a candidate duplicated
subtraction versus the target shared path. This is only a multiset diagnostic:
it normalizes stack identity and does not establish dependency order, value
identity or path equivalence. The action-603 grouping needed separate raw
instruction reconciliation even though both forms contain two additions.

All 49 physical spawn payloads resolve without conflicting modeled ESP
merges. The six differing normalized address-sequence owners remain
mid500/505 and high601/604/605/710. Target traversal still reaches all
37,692 bytes / 9,912 instructions with no unresolved indirect jumps.
Virtual physical-site counts remain target/candidate 107/105 at slot8,
31/31 at slotC, 12/13 at slot14, and 2/2 at slot1C. These are not runtime
call counts or proof of missing behavior.

## Bounded probes and TH08 reference

| Probe | Diagnostic result | Disposition |
| --- | --- | --- |
| Correct three integer subtractions only | 25/98, loses low11, metadata `+0x92B4`. | Property combined with independently observed floating properties. |
| Round action696 only, float carrier or cast | 25/98, loses low11, metadata `+0x92C0`; identical compared windows. | Real float carrier retained in combined result. |
| Group action603 additions only | 25/98, loses low11, metadata `+0x92B8`. | Grouping retained in combined result. |
| Group603 and round696 | 26/98, no gains/losses, metadata `+0x92C4`. | Intermediate diagnostic. |
| All three properties | 26/98, no gains/losses, metadata `+0x92B4`. | Retained through configured rebuild. |
| Explicit action311/696 source join | 24/98, loses low11/mid311, metadata `+0x9298`. | Not retained; original shared source placement remains unknown. |
| Signed-byte spawn parameter, control / with grouping and rounding | 4/98 / 3/98, metadata `+0x9360` / `+0x9370`; first difference `+0x12`. | No signed-byte ABI or relocation changes retained. |

The signed-byte probe used a private signed-char `C` decorated-symbol alias,
not plain-char `D`. Target manager reads DL at `53B266` and stores the low
byte at `53B298`; those observations establish width, not unique source
signedness. A bounded accepted-body census finds a MOVZX forwarding read
of field `+0x33C` at `53CD33` in `CharacterObjectEffectEmitter_update_ping_pong_motion_and_periodic_spawn`.
It does not uniquely recover caller parameter signedness. Existing unsigned
byte fields, helper declarations and durable relocation mappings stay intact.

TH08 checkout `d2a00f4acb4a13916e07a00bd13f714961714628` has actual FSINCOS
assembly in `src/ZunMath.hpp` and FRNDINT assembly in `src/AnmManager.cpp`.
Neither special instruction occurs in this Youmu callable; neither do FSIN,
FCOS, FPTAN or FPATAN. TH08's VC7 examples do not establish an assembly
requirement for these ordinary VC8 arithmetic properties, or settle behavior
of other roots/callees. See [the earlier TH08 source audit](YOUMU_FLOAT_CARRIERS_2026_10_02.md).
No new IDA or Ghidra output is used here. IDA's wrong-target preflight blocks
that session; all new observations use the hash-attested target PE.

## Reproduction and limits

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
```

Fresh configured reports are `build/youmu-fpu-values-final-20261002.json`
and `build/youmu-fpu-values-final-owners-20261002.json`. Explicit-object
guard, stack and arithmetic reports are
`build/youmu-fpu-values-final-guards-20261002.json`,
`build/youmu-fpu-values-final-stack-20261002.json` and
`build/youmu-fpu-values-final-arithmetic-20261002.json`.

Private analysis scripts, each invoked with OBJECT, OWNER_AUDIT and OUTPUT:
`.analysis/youmu-payload-order-20261002/scan-all-guards.py`,
`.analysis/youmu-payload-lifetimes-20261002/stack-packets.py`, and
`.analysis/youmu-fpu-coverage-20261002/arithmetic-census.py`.
Other probes are below `.analysis/youmu-fpu-coverage-20261002/` and
`build/youmu-fpu-coverage-20261002/`; they carry no exact acceptance claim.

Shared-tail placement, argument scheduling, remaining float lifetimes,
original local/TU/compiler context and full numerical closure remain unknown.
No shared header, accepted helper, compiler flag or object partition changed.
Whole-root canonical zero-difference replay remains required. This focused
checkpoint does not claim an aggregate cold replay.
