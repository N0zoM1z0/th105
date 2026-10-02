# Youmu float argument carriers and x87 guard coverage, 2026-10-02

## Retained result

**Observed:** `Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains
nonexact over all 37,692 callable bytes. Two real X-argument carriers in
actions 601 and 710 are now float rather than retained decompiler-derived
double locals. Fresh configured VC8 SP1 comparison first differs at
`+0xCA / 0x005302CA`, target `64`, candidate `D8`.

Strict instruction/edge diagnostics improve from **24/98 to 26/98** owners,
gaining `low:11` and `high:798` without losing a previously identical owner.
Candidate metadata starts at `+0x92B0`, versus target `+0x933C`. Candidate
still has 97 physical switch destinations / 33 low entries and no merged
target-distinct owners. Owner diagnostics do not establish authored exact
bytes; no exact function or byte credit is added. The metadata gap grows
from 108 to 140 bytes, so this is not a claim of closer overall body size.

Target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source SHA-256:
`f734a9ce0f2c389811ad641028eb24d5289791b83234bc4838ba23c276b1bd14`.
Canonical compared candidate-window SHA-256:
`7e91bc5723880cc587416f887d4fdda3a07b80a00cdfcbfe4a9f58f5ca94e86c`.
The candidate window contains its earlier metadata and is not a body hash.

## Target argument rounding and source inference

**Observed:** each branch in action 601 rounds its computed X to a dword
before joining the common spawn call. Inside computes `selfX + 150*facing`;
outside computes `selfX + 175*facing`. Both use signed facing and integer
multiplication, followed by FILD and addition of the float member `+0xEC`.
Action 710 has the same branch-local rounding with factor 140 in both arms.

| Action / arm | Target dword store / reload | Common X-argument store |
| --- | --- | --- |
| 601 inside | `536E2B FSTP [ESP+34]; 536E2F FLD [ESP+34]` | `536E74 FSTP [ESP]` |
| 601 outside | `536E6C FSTP [ESP+34]; 536E70 FLD [ESP+34]` | `536E74 FSTP [ESP]` |
| 710 inside | `5387E8 FSTP [ESP+34]; 5387EC FLD [ESP+34]` | `538831 FSTP [ESP]` |
| 710 outside | `538829 FSTP [ESP+34]; 53882D FLD [ESP+34]` | `538831 FSTP [ESP]` |

**Inferred:** a float carrier naturally represents the observed rounded X
value. The source retains the existing arithmetic and branch ownership,
changing only declarations `v111` and `v138`. Action 710 already assigns
float branch values `v423/v424`; its double carrier adds an unnecessary
widening representation. The inferred types are not unique original local
declarations. This does not prove a numerical bug in the preceding source:
an outgoing float argument can itself round, and optimized code can move
stores. The candidate still hoists some argument preparation and arithmetic;
the target's entire evaluation schedule is not recovered by these two edits.

The earlier contiguous object-853 payload, unordered angle/facing guards,
addition association, signed period, and corrected virtual-call ABI remain.
See [the payload extent](YOUMU_PAYLOAD_EXTENT_2026_10_02.md) and its linked
numerical and ABI evidence.

## Guard coverage extension

**Observed:** the earlier immediate-AH-mask scanner covered 136 guards. Two
additional sites use `TEST CL,AH`, with CL inherited from a real divisor:

| Action | Divisor definition | Compare / status / test | Reject edge |
| --- | --- | --- | --- |
| 545 | `53637B MOV ECX,5; 536380 IDIV ECX` | `536388 FCOMP [ESI+F4]; 53638E FNSTSW AX; 536390 TEST CL,AH` | `536392 JP 5363BD` |
| 546 | `53656A MOV ECX,5; 53656F IDIV ECX` | `536577 FCOMP [ESI+F4]; 53657D FNSTSW AX; 53657F TEST CL,AH` | `536581 JP 5365AC` |

A backward CFG definition check resolves all modeled predecessors to the
respective `MOV ECX,5`, with no intervening call or ECX-family overwrite.
The comparison is `0 versus velocityX`; mask 5 and JP reject equal, greater
and unordered comparison outcomes. Emission therefore requires ordered
positive velocityX. Fresh candidate operands and edges agree. No new source
correction is needed for these two guards.

The extended scan covers **138 target / 138 candidate** masked guards, with
equal per-owner counts and zero unordered-only leads under its finite-order
equivalence hypotheses. Ordinal pairing is a diagnostic, not proof of all
comparison semantics, numerical association, exception behavior or value
lifetime. The two register-mask sites are separately reconciled above.

The stack/def-use packet again resolves all 49 physical spawn payload sites
in target and candidate, with no conflicting modeled ESP merges or unknown
payload definitions. Six owners retain different normalized address
sequences: mid 500/505 and high 601/604/605/710. Both frames remain `0x230`;
these discrepancies do not justify additional frame padding.

## Isolated source and compiler probes

| Probe | Whole-window/owner observation | Disposition |
| --- | --- | --- |
| Four actual array-scope variants | Byte-identical to the preceding payload checkpoint, 24/98. | Not retained. |
| Only action-601 X carrier float | 25/98, gaining high 798; metadata `+0x92D0`. | Supported property retained with the second carrier. |
| Only action-710 X carrier float | 26/98, gaining low 11 and high 798; metadata `+0x92B0`. | Supported property retained. |
| Both X carriers float | 26/98, same gains and no losses; metadata `+0x92B0`. | Fresh configured rebuild retained. |
| Assignment to the existing float inside both 601 branches | Same compared window as the 601-only float carrier. | Alternate spelling not retained. |
| Either range-result local narrowed to uchar | 19/98; loses mid 304/401/402/520/521. | Not retained; downstream byte consumption does not prove local width. |
| Existing named animation/sequence prefix, optionally peer prefix | 25/98, metadata `+0x92A4`; no further gain. | Not retained; no shared header changed. |
| Installed VC8 RTM, both float carriers | 25/98, metadata `+0x92BC`; first mismatch `+0xCA`, target64/candidateE3. | Private compiler probe; configured SP1 profile retained. |

RTM `cl.exe`, `c1xx.dll` and `c2.dll` report `14.0.50727.42`.
RTM cl SHA-256 is
`3cbf4306526c06a07d09fd4785ac290c7ac7b52355944e7b377e08f5d8e7ece7`;
configured SP1 cl SHA-256 remains
`71c93ca5bddc9b2816d0e053cac2b952f926f6b9321fab6b1ab6e8603621324c`.
This bounded negative probe does not identify the shipped compiler revision.
Existing-object probes have diagnostic, unverified build provenance.
No accepted helper, shared type, compiler flag, relocation mapping or object
partition changes. The prior branch-local 601 call duplication also remains
negative; it expands the frame and changes unrelated payload addresses.

## TH08 reference and remaining scope

**External source evidence:** reread local TH08 checkout
`d2a00f4acb4a13916e07a00bd13f714961714628`. `src/ZunMath.hpp:38/:57/:145`
contains real FSINCOS islands; `src/AnmManager.cpp:1146` uses FRNDINT for four
coordinates. The modern branches call cosf/sinf or nearbyintf, without
establishing equal legacy instruction output. The constant-index island in
`src/Supervisor.cpp:427` is separately labeled historical in
`docs/VC7_ZUN_PATTERNS.md:190`. No TH08 build or exact acceptance is claimed.

TH08's natural-source examples recover real float homes, staged stores,
comparison operand ownership and unordered masks. Their VC7 `/Od` recipes
are hypotheses to test under this root's VC8 `/O2`, not transferable facts.
See [the earlier TH08 comparison](YOUMU_ANGLE_RANGE_2026_10_02.md).

**Observed:** a complete decode of this TH105 callable contains no FSINCOS,
FRNDINT, FSIN, FCOS, FPTAN or FPATAN. Its quantized trigonometric helpers are
out-of-root calls. TH08's special-instruction examples do not establish an
assembly requirement here or describe those callees. This checkpoint uses
hash-attested raw target bytes; it uses no new Ghidra or IDA analysis.

**Unknown:** physical shared-tail placement, actual argument schedules,
remaining float lifetimes, original local/TU ownership and full numerical
closure. A whole-root zero-difference canonical replay remains required.

## Focused reproduction

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
```

Configured build and owner reports are
`build/youmu-float-carriers-final-20261002.json` and
`build/youmu-float-carriers-final-owners-20261002.json`.
Private guard scanner:
`.analysis/youmu-payload-order-20261002/scan-all-guards.py`.
Private stack/definition analysis:
`.analysis/youmu-payload-lifetimes-20261002/stack-packets.py`.
Both take explicit object, current owner report and output arguments; their
default owner reports belong to older checkpoints. Final outputs are
`build/youmu-float-carriers-final-guards-20261002.json` and
`build/youmu-float-carriers-final-stack-20261002.json`.
Raw traversal still reaches all 9,912 target instructions / 37,692 callable
bytes, including the auxiliary switch, without unresolved indirect jumps.
These are focused results; no aggregate cold replay is claimed.
