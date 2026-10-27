# Tenshi action-state 0x0063D3E0

Complete unselected, nonexact C++ candidate:110 action labels, including direct
300/540/795/797/798. Neither implemented.csv nor matches.csv gains credit.

## Native evidence

JP1.06a hash and Factory IDA metadata/entry/inventory were attested before
decompilation. Raw callable63D3E0..648E88 is47784 bytes, SHA-256
83af98e2673c40b5ca2f3caac87ab7a8e4114a758ac65dfeebdae1ad0a14e5b3.
Six switches resolve completely. Of12490 decoded instructions,12489 are
reachable; only seven-byte alignment LEA647C49..647C50 is unreached.
There are125 RETs and789 direct calls to43 targets.

Sparse action regions0..226,301..527,541..788 have35/36/37 destinations.
Three nested difficulty tables end at649328. Complete payload48968 bytes:
a7e25e318b6ffcc43edbca3e9e3e34f311e5343c82c1a0b91d6a6d45a52d6d47.
The following eight alignment bytes are outside this payload.

## Candidate evidence and limits

The pointer-only receiver inherits actual AnimationSequenceObjectView slots.
Event receiver is embedded at130, including435CE0. RNG4066B0 has no arguments;
all46 crossed-ground5F9310 calls inspect AL, while the accepted callee returns int.
Trig calls consume ST0 results, not decompiler input aliases.

Direction arithmetic uses signed bytes, while effect/spawn carriers retain
unsigned byte values. Offsets48/65 multiply integers before floating conversion.
Weather6FA88C is signed16-bit;6FA88F is byte-wide. Landing tails retain their
distinct action/surface/zero-motion orderings. Native FABS rounds to float and
its560/561 comparisons reject unordered operands. Action567's next-Y is double.
Action599 sign-extends its random short before subtracting from-20.

Action604 mode1 initializes only payload[2] before646152; the candidate does
not invent values for slots0/1. Later mode5 initializes slot1 then slot0.
Action214's duplicate retain condition is present at63F529..63F55F; no volatile
workaround is justified. Actions795/797/798 and direction-conditioned214/731
calls retain independent ownership.

Private reachable direct/virtual call counts agree for every nondefault main
table action. This is an omission check, not semantic equivalence. FP widths,
callback-sensitive field lifetimes and predicates require further review.
Difficulty switches720/740/741 do not define every local outside0..3; this
domain is not proved, and no fallback is invented. TU/LTCG ownership is unknown.

## Reproduction and current result

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-tenshi-action-state --compare --json
    scripts/repo-python scripts/audit-tenshi-action-state.py
    scripts/repo-python scripts/map-giant-action-switches.py tenshi-vslot28 --json
    scripts/repo-python scripts/compare-giant-action-switches.py tenshi-vslot28 build/match-units/ExactFirst_TenshiActionState.obj --json

Source full49404 versus native48968; first mismatch+241/63D4D1, native memory
CMP versus source MOVZX/CMP. Candidate callable48243 plus one alignment byte.
Full source SHA-256:
2b22e9403399a55f67bbc327f9346727b419063f2b032952c84b7ed629d84dab.
Full positional difference count46655 includes missing/extra bytes, not a
semantic-completion percentage.

Compiler merges209/221 and210/222, producing33 low owners rather than35.
The manifest permits33 only for diagnostics, never acceptance. Mid/high36/37;
no native group splits. Earlier35/36/37 source still failed bytes.

Ten literals, two width-specific global aliases and one BGM string are added;
existing bindings/accepted consumers are unchanged. Only this unit is built.
Artifacts: build/frontier-63d3e0-20261027/. No assembly, copied target arrays,
fake returns, padding locals or register coercion.

## Coordinate and live packet refinement

The subsequent native arithmetic pass removes artificial Y+0 in burst requests
whose raw callers forward Y directly. It preserves integer150*direction before
conversion in520/521, and native subtraction for negative spell-flash offsets
rather than adding a negated offset. These are operand/operation corrections,
not padding or instruction spelling controls.

Actions412/416 place the live angle immediately after three request floats.
Native642072 writes slot3;6420C7/64211D/642154 reload it and independently negate
it across exposed payload calls. A four-float local packet expresses this live
storage, still passing count3. Four-slot aggregate ownership is an inference
from contiguous live storage and call-clobber reloads, not a recovered source
type. It restores four FCHS sites per action versus one cached negative angle.
All nondefault action arithmetic-operation counts now agree except214/567,
where native alternative paths duplicate additions. Counts are not proof of
operand values, widths or runtime equivalence.

Refined full source49168 versus48968; first+8 is frame allocation330 versus320.
Source SHA-256:
918b3d898d902474ce32c5b71bc9c41abbcdd33ef4a0b6728037161b7d03bb8f.
Full positional difference46592; first table offset48008. The33/36/37 physical
group counts and two low-owner merges remain. The preceding49404 result is
historical. No source-selection or exact credit is added.

A separate explicit shared-idle-label trial for0/2 produced49372 but placed
the common body with action2 rather than native0. It was not adopted; more
source label spelling is not supported as a route to physical ownership.
Current receipts: ring-packet-build.json, ring-packet-full.json and
ring-packet-map.json under the same build directory.


## Shared request tail and caller width

Raw500/501 converge after their first810 request, carrying the address of
their distinct live three-float payload. Function-scope request500/request501
and one typed pointer preserve both lifetimes through the shared second request,
two effects and counters. This restores native physical call sharing without
using a pointer after a block-local array lifetime ends. Physical500/501 spans
are190/351 against187/343; the earlier duplicated500 span was297.

An exhaustive scan of all46 native5F9310 call sites shows immediate TEST AL,AL.
The early interpretation of decompiler int temporaries as EAX-width caller tests
was wrong. The accepted int-returning callee declaration is retained; jump-cycle
and306/309 now explicitly narrow to unsigned char like the other callers.

Current full source49088 versus48968, first+8 (frame330 versus320), SHA-256
3dca3af1096e28913dd1d3a1615ace1ca5b524f6850856f9b6ee3497bdad1eb2.
Full positional difference46201. No exact or implementation credit.
Receipts: caller-width-build.json, caller-width-full.json and
caller-width-map.json. The earlier49168 packet result remains historical.
