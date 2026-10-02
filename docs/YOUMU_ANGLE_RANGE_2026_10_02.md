# Youmu angle ranges and TH08 x87 reference, 2026-10-02

## Result and scope

**Observed:** `Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains
nonexact over the complete 37,692-byte callable. This checkpoint corrects
three unordered angle gates in actions 601, 602 and 604, and the addition
association in actions 601 and 604. These changes use ordinary C++.
The target callable hash remains
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.

The fresh configured comparison first differs at `+0xCA / 0x005302CA`, target
`64`, candidate `D9`. Candidate metadata remains `+0x92B4`, versus target
`+0x933C`. Strict owner auditing remains **24/98 diagnostic owners**, with
97 physical switch destinations / 33 low entries and no merged target owners.
There is no new exact function or byte credit. No shared header, compiler
profile, relocation target, or object partition changes.

## Observed angle guards

All three gates compare the stored float angle against zero and then 180.
The target's first test sends less-than **or unordered** to the outside path;
the second sends greater-than **or unordered** to that same path. The first
outside edge drops the still-live x87 angle before joining the second edge.

| Action | First compare / test / outside edge | Second compare / test / outside edge |
| --- | --- | --- |
| 601 | `536DDF FCOM ST(1); 536DE5 TEST AH,01; 536DE8 JNE 536E35` | `536DEA FCOMP [6D6EDC]; 536DF2 TEST AH,41; 536DF5 JP 536E37` |
| 602 | `537114 FCOM ST(1); 53711A TEST AH,01; 53711D JNE 53713F` | `53711F FCOMP [6D6EDC]; 537127 TEST AH,41; 53712A JP 537141` |
| 604 | `537BAC FCOM ST(1); 537BB2 TEST AH,01; 537BB5 JNE 537C02` | `537BB7 FCOMP [6D6EDC]; 537BBF TEST AH,41; 537BC2 JP 537C04` |

For less/equal/greater/unordered, the x87 condition bits in AH are
`01/40/00/45`. The first branch truth vector is `true/false/false/true`;
the second is `false/false/true/true`. Inside chooses the `+1` spawn argument,
outside chooses `-1`. Actions 601/604 also choose horizontal offset
`150*facing` inside and `175*facing` outside; action 602 uses self X in both.

The retained source previously used `angle < 0 || angle > 180`, whose two
ordered C++ comparisons are both false for NaN. It now uses
`!(angle >= 0 && angle <= 180)`. Fresh VC8 output reproduces the target's
`TEST AH,01; JNE` and `TEST AH,41; JP` in all three gates. These are matching
local conditions, not whole physical-owner or whole-function exact claims.

**Unknown:** whether these angle inputs can become NaN during normal game
execution. This audit establishes target branch behavior, not reachability
of a particular floating value or full exception-environment equivalence.

## Observed addition association

In action 601, target `536DAF FLD index; 536DB3 FMUL double 45;
536DB9 FADD double 22.5; 536DBF FADDP ST(1)` adds the unsigned random roll
only after computing `index*45 + 22.5`. Action 604 repeats this sequence at
`537B7C/537B80/537B86/537B8C`. Both finish with a dword payload store.
The preceding signed FILD plus conditional `+2^32` implements the already
retained unsigned conversion of the random result.

The old source grouped `(roll + index*45) + 22.5`. Explicit parentheses now
preserve `roll + (index*45 + 22.5)`. Fresh VC8 output moves FADD 22.5 before
FADDP, without adding an intermediate store. This is instruction-order
recovery; the bounded normal random/index values need not produce different
numeric results. The original source spelling is not uniquely recovered.

## Focused validation

Three private probes independently apply only the range correction, only
the association correction, and both. Each retains metadata `+0x92B4` and
24/98 diagnostic owners, without gaining or losing an identical owner.
Private sources are under `.analysis/youmu-angle-range-20261002/`; their
objects and reports are under `build/youmu-angle-range-20261002/`.
Existing-object comparisons are diagnostics with unverified build provenance.
The retained source is separately rebuilt through the configured unit:

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
```

Fresh reports are `build/youmu-angle-final-20261002.json` and
`build/youmu-angle-final-owners-20261002.json`. Raw target traversal still
reaches all 9,912 instructions / 37,692 callable bytes without unresolved
indirect jumps. A private AH-guard scanner pairs 136 target/candidate guards
by physical owner and ordinal, finding six unordered-only leads before the
correction and zero afterward. Operand and edge inspection confirms the
three range corrections. Ordinal pairing is a lead-finding method, not proof
that every floating comparison, value lifetime, or exception path is closed.
Its final report is `build/youmu-angle-final-guards-20261002.json`.

## What the TH08 examples establish

**External source evidence:** independently reread the local TH08 checkout at
`d2a00f4acb4a13916e07a00bd13f714961714628`; no TH08 rebuild or exact acceptance
was performed in this checkpoint. `src/ZunMath.hpp:38/:57/:145` uses inline
`FSINCOS` for vector operations and the sincos macro. `src/AnmManager.cpp:1146`
uses `FRNDINT` on four coordinates before subtracting 0.5 and paired stores.
The modern branch spells those operations with `nearbyintf`; it does not
establish equal VC7 instruction output. `docs/BUILD_MATCHING.md:467` records
that VC7 sin/cos intrinsics do not fuse into FSINCOS. These are concrete
special-instruction examples, not a general claim that x87 needs assembly.

**Observed TH105 distinction:** a full linear decode of this reconciled
Youmu callable contains ordinary x87 arithmetic, comparisons and stores,
with no FSINCOS or FRNDINT instruction. This bounded census does not describe
its callees or the rest of TH105. Its trigonometric call contracts use the
existing quantized lookup helpers. The current range/association discrepancies
are reproducible with natural VC8 source. Earlier TH105 rotation and body
collision exact units also demonstrate natural-source x87 recovery; see
[the earlier TH08 reference](COMMON_FIGHTER_X87_AND_GHIDRA_2026_10_02.md).

**Unknown / next:** actual shared-tail placement, argument scheduling,
stack-slot/value lifetimes and original TU/compiler context remain unresolved.
Neither the TH08 examples nor the current mismatch proves an assembly or
LTCG requirement for this root. No new Ghidra output is used by this batch;
all accepted observations above come from the hash-attested target PE.
